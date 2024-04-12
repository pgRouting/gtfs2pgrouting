/*
 * sql_utils.h
 *
 *  Created on: 18-Aug-2011
 *      Author: jkk
 */

#ifndef SQL_UTILS_H_
#define SQL_UTILS_H_

#include <libpq-fe.h>

/**
 * @brief 
 * 
 */
typedef struct
{
	char *name;
	char *user;
	char *pass;
	char *host;
	char *port;
} database_settings;

/**
 * @brief Establish a connection to a PostgreSQL database
 * 
 * @param db All parameters needed for connection to the DB
 * @return PGconn* 
 */
PGconn *make_connection(database_settings *db);

/**
 * @brief Run a .sql file containing a SQL query
 * 
 * @param conn The PostgreSQL connection
 * @param file_path The path of the file to open
 * @return int 
 */
int run_sql_file(PGconn *conn, char *file_path);

/**
 * @brief Run a SQL query into a PostgreSQL database
 * 
 * @param conn The PostgreSQL connection 
 * @param sql_text The SQL query as a string 
 * @param ... 
 * @return int 
 */
int run_sql(PGconn *conn, char *sql_text, ...);

int add_foreign_key(PGconn *conn, char *table, char *column, char *ref_table, char *ref_column);

#endif /* SQL_UTILS_H_ */
