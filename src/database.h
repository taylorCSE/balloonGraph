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
string DB_asValveStatus(string input);
string DB_asCutDownStatus(string input);
string DB_asAirTemp(string input);
string DB_asSurfaceTemp(string input);
string DB_asReeling(string input);
string DB_asPressure(string input);
string DB_asTestPressure(string input);
string DB_asTemperature(string input);
string DB_asRH(string input);
string DB_asMETGround(string input);
string DB_asWindSpeed(string input);
string DB_asWindDirection(string input);

string DB_asTwoPartPressure(string input_a, string input_b);
string DB_asTwoPartTemp(string input_a, string input_b);
string DB_asTwoPartRH(string input_a, string input_b);
string DB_asCalculatedDewpoint(string input_a, string input_b);
string DB_calculateError(string input_a, string input_b);
string DB_asReferenceDewpoint(string input_a, string input_b, string input_c, string input_d);

#endif
