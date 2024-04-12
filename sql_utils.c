/*
 * sql_utils.c
 *
 *  Created on: 18-Aug-2011
 *      Author: jkk
 */

#include "sql_utils.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "verbosity.h"

PGconn *make_connection(database_settings *db)
{
	PGconn *conn = NULL;
	print_info("Trying to connect to database.\n");
	conn = PQsetdbLogin(db->host, db->port, NULL, NULL, db->name, db->user,
						db->pass);
	if (PQstatus(conn) != CONNECTION_OK)
	{
		fprintf(stderr, "Error connecting to database.\n");
		exit(-1);
	}
	print_info("Successfully connected to database.\n");
	return conn;
}

int run_prepared_sql(PGconn *conn, char *sql)
{
	print_info("Executing SQL: '%s'\n", sql);
	PGresult *res = PQexec(conn, sql);
	return (PQresultStatus(res) != PGRES_COMMAND_OK);
}

int run_sql_file(PGconn *conn, char *file_path)
{
	char buff[1024];
	char *sql = (char *)malloc(sizeof(char) * 1024);
	FILE *fp;
	int i, ret;
	print_info("Opening SQL file from path: '%s'", file_path);
	fp = fopen(file_path, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error opening file for reading: %s\n", file_path);
		return -1;
	}
	fgets(buff, 1024, fp);
	i = 1;
	while (!feof(fp))
	{
		print_info("Reallocating sql buffer to %d bytes\n", i * 1024);
		sql = (char *)realloc(sql, sizeof(char) * i * 1024);
		strcat(sql, buff);
		fgets(buff, 1024, fp);
		++i;
	}
	ret = run_prepared_sql(conn, sql);
	free(sql);
	return ret;
}

int run_sql(PGconn *conn, char *fmt, ...)
{
	char sql[10240]; // XXX:Maximum size of sql < 10KB
	int ret;
	va_list arg;
	va_start(arg, fmt);
	vsprintf(sql, fmt, arg);
	va_end(arg);
	ret = run_prepared_sql(conn, sql);
	return ret;
}


int add_foreign_key(PGconn *conn, char *table, char *column, char *ref_table, char *ref_column)
{
	PGresult *result;
	int res = 0;
	char query[1024] = {0};

	sprintf(query, "ALTER TABLE %s ADD FOREIGN KEY %s REFERENCES %s(%s);", table, column, ref_table, ref_column);

	result = PQexec(conn, query);

	if (PQresultStatus(result) == PGRES_COMMAND_OK)
	{
		printf("okkkk\n");
		res = 1;
	} else 
	{
		res = 0;
	}
}