/*
 * data_loader.c
 *
 *  Created on: 18-Aug-2011
 *      Author: jkk
 */

#include "data_loader.h"
#include <unistd.h>
#include <string.h>

#include "verbosity.h"

#define BUF_SIZE 1024
#define SQL_SIZE 2048

const char *GTFS_FILENAME[] = {"agency.txt",
							   "stops.txt",
							   "routes.txt",
							   "calendar.txt",
							   "calendar_dates.txt",
							   "shapes.txt",
							   "trips.txt",
							   "stop_times.txt",
							   "frequencies.txt"};

const char *GTFS_TABLENAME[] = {"agency",
								"stops",
								"routes",
								"calendar",
								"calendar_dates",
								"shapes",
								"trips",
								"stop_times",
								"frequencies"};

int import_from_folder(PGconn *conn, char *schema, char *folder_path)
{
	GTFS_FILE i;
	int ci;
	FILE *fp;
	char sql[SQL_SIZE] = {0};
	char buf[BUF_SIZE] = {0};
	PGresult *result;
	char *err = NULL;

	char is_calendar_present = 1;

	print_info("Entering into folder: %s\n", folder_path);
	if (chdir(folder_path))
	{
		fprintf(stderr, "Unknown folder : %s\n", folder_path);
		return -1;
	}

	for (i = 0; i < G_COUNT; ++i)
	{
		memset(sql, 0, SQL_SIZE);
		memset(buf, 0, BUF_SIZE);
		print_info("Trying to open file: %s\n", GTFS_FILENAME[i]);
		fp = fopen(GTFS_FILENAME[i], "r");
		if (fp == NULL)
		{
			if (i == G_CALENDAR )
			{
				is_calendar_present = 0;
				print_info("Calendar not found. Calendar_dates must be present\n.");
				continue;
			}
			else if ((i == G_CALENDAR_DATES) && (!is_calendar_present)) {
				print_info("Neither Calendar not Calendar_dates found.\n");
				return -1;
			}
			else if (i == G_SHAPES || i == G_FREQUENCIES)
			{
				print_info("Optional file '%s' not found. Ignored.\n", GTFS_FILENAME[i]);
				continue;
			}
			else
			{
				fprintf(stderr, "Required file '%s' not found\n", GTFS_FILENAME[i]);
				return -1;
			}
		}
		else
		{
			ci = 0;
			// while ((buf[ci++] = getc(fp)) != '\n')
			// 	;
			char c = 0;
			while ((c = getc(fp))  != '\n')
			{
				if (c > 0)
				{
					buf[ci] = c;
					ci++;
				}
			}
			buf[ci] = '\0';
			sprintf(sql, "COPY %s(%s) FROM STDIN WITH CSV HEADER;", GTFS_TABLENAME[i], buf);
			result = PQexec(conn, sql);

			printf("%s\n", sql);

			if (PQresultStatus(result) != PGRES_COPY_IN)
			{
				fprintf(stderr, "Error trying to copy into '%s'.\n", GTFS_TABLENAME[i]);
				print_info("%s\n", PQresultErrorMessage(result));
				return -1;
			}

			memset(buf, 0, BUF_SIZE);

			fgets(buf, BUF_SIZE, fp);

			int errorStdIn = 0;
			errorStdIn = PQputCopyData(conn, buf, strlen(buf));


			while (!feof(fp))
			{	
				errorStdIn = PQputCopyData(conn, buf, strlen(buf));

				fgets(buf, BUF_SIZE, fp);
			}
			
			PQputCopyEnd(conn, err);
			print_info("Copied contents of '%s' into table '%s'.'%s'\n\n", GTFS_FILENAME[i], schema, GTFS_TABLENAME[i]);
		}
		fclose(fp);
	}
	return 0;
}
