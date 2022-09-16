#ifndef SQL_QUERY_H
#define SQL_QUERY_H

char tablesCreationQuery[] = "CREATE DOMAIN wgs84_lat AS DOUBLE PRECISION CHECK(VALUE >= -90 AND VALUE <= 90);\n"
"CREATE DOMAIN wgs84_lon AS DOUBLE PRECISION CHECK(VALUE >= -180 AND VALUE <= 180);\n\n"

"CREATE TABLE agency\n"
"(\n"
"  agency_id         text UNIQUE NULL,\n"
"  agency_name       text NOT NULL,\n"
"  agency_url        text NOT NULL,\n"
"  agency_timezone   text NOT NULL,\n"
"  agency_lang       text NULL,\n"
"  agency_phone      text NULL,\n"
"  agency_fare_url   text NULL,\n"
"  agency_email      text NULL\n"
");\n\n"

"CREATE TABLE stops\n"
"(\n"
"  stop_id           text PRIMARY KEY,\n"
"  stop_code         text UNIQUE NULL,\n"
"  stop_name         text NOT NULL,\n"
"  stop_desc         text NULL,\n"
"  stop_lat          wgs84_lat NOT NULL,\n"
"  stop_lon          wgs84_lon NOT NULL,\n"
"  zone_id           text NULL,\n"
"  stop_url          text NULL,\n"
"  location_type     int2 NULL CHECK(location_type >= 0 and location_type <= 4),\n"
"  parent_station    text NULL,\n"
"  stop_timezone     text NULL,\n"
"  wheelchair_boarding int2 NULL CHECK(location_type >= 0 and location_type <= 2    ),\n"
"  level_id          text NULL,\n"
"  platform_code     text NULL\n"
");\n\n"

"CREATE TABLE routes\n"
"(\n"
"  route_id          text PRIMARY KEY,\n"
"  agency_id         text NULL REFERENCES agency(agency_id) ON DELETE CASCADE,\n"
"  route_short_name  text NOT NULL,\n"
"  route_long_name   text NOT NULL,\n"
"  route_desc        text NULL,\n"
"  route_type        int2 NOT NULL CHECK(route_type >= 0 and route_type <= 12),\n"
"  route_url         text NULL,\n"
"  route_color       text NULL,\n"
"  route_text_color  text NULL,\n"
"  route_sort_order  int NULL CHECK(route_sort_order > 0),\n"
"  continuous_pickup int2 NULL CHECK(continuous_pickup >= 0 and continuous_pickup <= 3),\n"
"  continuous_dropoff int2 NULL CHECK(continuous_dropoff >= 0 and continuous_dropoff <= 3)\n"
");\n\n"

"CREATE TABLE calendar\n"
"(\n"
"  service_id        text PRIMARY KEY,\n"
"  monday            boolean NOT NULL,\n"
"  tuesday           boolean NOT NULL,\n"
"  wednesday         boolean NOT NULL,\n"
"  thursday          boolean NOT NULL,\n"
"  friday            boolean NOT NULL,\n"
"  saturday          boolean NOT NULL,\n"
"  sunday            boolean NOT NULL,\n"
"  start_date        date NOT NULL,\n"
"  end_date          date NOT NULL\n"
");\n\n"

"CREATE TABLE shapes\n"
"(\n"
"  shape_id          text,\n"
"  shape_pt_lat      wgs84_lat NOT NULL,\n"
"  shape_pt_lon      wgs84_lon NOT NULL,\n"
"  shape_pt_sequence integer NOT NULL,\n"
"  shape_dist_traveled double precision NULL,\n"
"  PRIMARY KEY (shape_id, shape_pt_sequence)\n"
");\n\n"

"CREATE TABLE trips\n"
"(\n"
"  route_id          text NOT NULL REFERENCES routes ON DELETE CASCADE,\n"
"  service_id        text NOT NULL REFERENCES calendar,\n"
"  trip_id           text NOT NULL PRIMARY KEY,\n"
"  trip_headsign     text NULL,\n"
"  trip_short_name   text NULL,\n"
"  direction_id      boolean NULL,\n"
"  block_id          text NULL,\n"
"  shape_id          text NULL,\n"
"  wheelchair_accessible int NULL,\n"
"  bikes_allowed     int2 NULL CHECK(bikes_allowed >= 0 and bikes_allowed <=2)\n"
");\n\n"

"CREATE TABLE stop_times\n"
"(\n"
"  trip_id           text NOT NULL REFERENCES trips ON DELETE CASCADE,\n"
"  arrival_time      interval NOT NULL,\n"
"  departure_time    interval NOT NULL,\n"
"  stop_id           text NOT NULL REFERENCES stops ON DELETE CASCADE,\n"
"  stop_sequence     integer NOT NULL,\n"
"  stop_headsign     text NULL,\n"
"  pickup_type       int2 NULL CHECK(pickup_type >= 0 and pickup_type <=3),\n"
"  drop_off_type     int2 NULL CHECK(drop_off_type >= 0 and drop_off_type <=3),\n"
"  shape_dist_traveled double precision NULL,\n"
"  timepoint         boolean NULL,\n"
"  PRIMARY KEY (trip_id, stop_sequence)\n"
");\n\n"

"CREATE TABLE frequencies\n"
"(\n"
"  trip_id           text NOT NULL REFERENCES trips ON DELETE CASCADE,\n"
"  start_time        time NOT NULL,\n"
"  end_time          time NOT NULL,\n"
"  headway_secs      integer NOT NULL\n"
");\n";

#endif
