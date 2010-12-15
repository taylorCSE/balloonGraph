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

extern string DB_STATUS;

void DB_connect();
void DB_query(char * item ...);
char* DB_resultAsText();
vector<string> DB_getAllFlights();
map<string, string> DB_getMostRecentGPS(string flight_id);
vector<string> DB_getMostRecentAnalog(string flight_id);
Plot DB_getPlotData(string data_column, string flight_id);
bool DB_isQueryReady();
string DB_asVoltage(string input);
string DB_asRate(string input);
string DB_asGPSStatus(string input);

#endif
