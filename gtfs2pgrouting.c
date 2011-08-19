/*
 * gtfs2pgrouting.c
 *
 *  Created on: 18-Aug-2011
 *      Author: jkk
 */
#include <argp.h>
#include <stdlib.h>
#include <string.h>

#include "data_loader.h"
#include "sql_utils.h"

const char *argp_program_version = "gtfs2pgrouting 0.9";
const char *argp_program_bug_address = "<justjkk@gmail.com>";

/* Program documentation. */
static char doc[] =
    "gtfs2pgrouting - Import GTFS from csv into postgres database";

/* A description of the arguments we accept. */
static char args_doc[] = "INPUT_SOURCE";

/* The options we understand. */
static struct argp_option options[] =
    { { 0, 0, 0, 0, "Database Settings:" },
      { "dbname", 'd', "DBNAME", 0, "Database name(mandatory)" },
      { "dbuser", 'u', "DBUSER", 0, "Database username" },
      { "dbpass", 'p', "DBPASS", 0, "Database password" },
      { "dbhost", 'h', "HOSTNAME", 0, "Database hostname" },
      { "dbport", 'P', "DBPORT", 0, "Database port" },
      { 0, 0, 0, 0, "General Options:" },
      { "verbose", 'v', 0, 0, "Produce verbose output" },
      { "format",
        't',
        "FORMAT",
        0,
        "Type of GTFS input. Options are: 'folder', 'zip'. Default:'folder'" },
      { "schema",
        's',
        "SCHEMA",
        0,
        "Schema for grouping all gtfs tables. Default is 'gtfs'" },
      { "data-only",
        'D',
        0,
        0,
        "Specify if the gtfs tables are already created.\n"
        "Used to append to existing gtfs data." },
      { 0 } };

/* Used by main to communicate with parse_opt. */
struct arguments {
  char *schema;
  char *input_source;
  int verbose;
  char *format;
  int data_only;
  database_settings db;
};

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
   know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key) {
  case 'd':
    arguments->db.name = arg;
    break;
  case 'u':
    arguments->db.user = arg;
    break;
  case 'p':
    arguments->db.pass = arg;
    break;
  case 'h':
    arguments->db.pass = arg;
    break;
  case 'P':
    arguments->db.port = arg;
    break;
  case 'v':
    arguments->verbose = 1;
    break;
  case 't':
    arguments->format = arg;
    break;
  case 's':
    arguments->schema = arg;
    break;
  case 'D':
    arguments->data_only = 1;
    break;
  case ARGP_KEY_ARG:
    if (state->arg_num >= 2)
      /* Too many arguments. */
      argp_usage(state);
    arguments->input_source = arg;
    state->next = state->argc;
    break;

  case ARGP_KEY_END:
    if (state->arg_num < 1)
      /* Not enough arguments. */
      argp_usage(state);
    break;

  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv) {
  struct arguments arguments;
  PGconn *conn;

  /* Default values. */
  memset(&(arguments.db), 0, sizeof(database_settings));
  arguments.db.user = NULL;
  arguments.db.pass = NULL;
  arguments.db.host = NULL;
  arguments.db.port = NULL;
  arguments.verbose = 0;
  arguments.format = "folder";
  arguments.schema = "gtfs";
  arguments.data_only = 0;

  /* Parse our arguments; every option seen by parse_opt will
   be reflected in arguments. */
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  conn = make_connection(&(arguments.db));

  if (!arguments.data_only) {
    if (run_sql(conn, "create schema %s", arguments.schema)
        || run_sql(conn, "set search_path to %s", arguments.schema)
        || run_sql_file(conn, "create_tables.sql")) {
      fprintf(
          stderr,
          "Error setting up gtfs schema\nIf the tables are already present, run with -D flag to skip schema creation\n");
      exit(1);
    }
  }

  if (!strcmp(arguments.format, "folder")) {
    if (import_from_folder(conn, arguments.schema, arguments.input_source)) {
      fprintf(stderr, "Error importing gtfs from folder.\n");
      exit(1);
    }
  } else if (!strcmp(arguments.format, "zip")) {
    fprintf(stderr, "This feature is not supported yet.\n");
  }

  exit(0);
}
