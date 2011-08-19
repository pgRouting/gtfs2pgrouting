/*
 * data_loader.h
 *
 *  Created on: 18-Aug-2011
 *      Author: jkk
 */

#ifndef DATA_LOADER_H_
#define DATA_LOADER_H_

#include "sql_utils.h"

typedef enum {
  G_AGENCY,
  G_STOPS,
  G_ROUTES,
  G_CALENDAR,
  G_SHAPES,
  G_TRIPS,
  G_STOP_TIMES,
  G_FREQUENCIES,
  G_COUNT
} GTFS_FILE;

int import_from_folder(PGconn *conn, char *schema, char *folder_path);

#endif /* DATA_LOADER_H_ */
