gtfs2pgrouting
==============
This is an importer tool that uses postgresql c library to load GTFS data in the form of CSV files into Postgresql database.
[GTFS](http://code.google.com/transit/spec/transit_feed_specification.html) is the de-facto standard for transit data. The database schema is designed to follow the specifications as strictly as possible. The purpose of this tool is to enable pgrouting users with an easy way to import GTFS data into the database and use the newly developed 'Multi-modal public transport Routing' library.

Source Code
------------
The source is an Eclipse Project. It can be imported as an existing project in Eclipse.

Install
-------
1. `cd Release` # Go into the Release folder
2. `make` # Invoke GNU Make utility
3. `` # There is no third step.

Executing
---------
`./gtfs2pgrouting -?` # provides a detailed list of all the options available
A common scenario is to specify the database name and path to the gtfs data like this:
`./gtfs2pgrouting -d mydatabase /home/user/Downloads/transit_data`
