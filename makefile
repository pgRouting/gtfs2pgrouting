CC=gcc
CFLAGS=-W -Wall -pedantic -I/usr/include/postgresql

# Depends on postgresql
LDFLAGS=-lpq
EXEC=gtfs2pgrouting


all : $(EXEC)

gtfs2pgrouting : gtfs2pgrouting.o sql_utils.o verbosity.o data_loader.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

gtfs2pgrouting.o : gtfs2pgrouting.c
	$(CC) -o $@ -c $^ $(CFLAGS)

sql_utils.o : sql_utils.c
	$(CC) -o $@ -c $^ $(CFLAGS)

verbosity.o : verbosity.c
	$(CC) -o $@ -c $^ $(CFLAGS)

data_loader.o : data_loader.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean : 
	rm -rf *.o

.PHONY: gtfs2pgrouting
.PHONY: gtfs2pgrouting.o