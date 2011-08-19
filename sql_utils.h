/*
 * sql_utils.h
 *
 *  Created on: 18-Aug-2011
 *      Author: jkk
 */

#ifndef SQL_UTILS_H_
#define SQL_UTILS_H_

#include "libpq-fe.h"

typedef struct {
  char *name;
  char *user;
  char *pass;
  char *host;
  char *port;
}database_settings;

PGconn *make_connection(database_settings *db);
int run_sql_file(PGconn *conn, char *file_path);
int run_sql(PGconn *conn, char *sql_text, ...);

#endif /* SQL_UTILS_H_ */
