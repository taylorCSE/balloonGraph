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

extern FILE * DB_log;

extern string DB_USER;
extern string DB_PASS;
extern string DB_HOST;
extern string DB_NAME;

void DB_connect();
void DB_query(char * item ...);
char* DB_resultAsText();
vector<string> DB_getAllDevices();
map<string, string> DB_getMostRecentGPS(int device_id);
Plot DB_getPlotData(char* table, char* data_column, int device_id);

#endif
