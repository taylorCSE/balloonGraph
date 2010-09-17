#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>

#define DBUG_OFF

#include <vector>
#include <map>
#include <string>

#include <my_global.h>
#include <mysql.h>

#include "Plot.h"

#define DB_USER "root"
#define DB_PASS "root"
#define DB_HOST "127.0.0.1"
#define DB_NAME "hawkeye"

extern FILE * DB_log;

void DB_connect();
void DB_query(char * item ...);
char* DB_resultAsText();
vector<string> DB_getAllDevices();
map<string, string> DB_getMostRecentGPS(int device_id);
Plot DB_getPlotData(char* table, char* data_column, int device_id);

#endif
