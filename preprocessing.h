#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <string.h>

char agency_columns[7][] = {
    "agency_id",
    "agency_name",
    "agency_url",
    "agency_timezone",
    "agency_lang",
    "agency-phone",
    "agency_fare_url",
    "agency_email"
}

int is_in(char *string, char **list, int list_length);

#endif