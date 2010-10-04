#include "database.h"

using namespace std;

MYSQL *DB_conn = NULL;
MYSQL_RES *DB_result = NULL;
FILE * DB_log = NULL;

string DB_USER = "root";
string DB_PASS = "";
string DB_HOST = "127.0.0.1";
string DB_NAME = "balloontrack";

char DB_buf[16384];

/// TODO: This could use a more robust error checking method 

void DB_connect() {
    DB_log = fopen("database.log","w");

    DB_conn = mysql_init(NULL);
    
    if (DB_conn == NULL) {
        fprintf(DB_log, "Error %u: %s\n", mysql_errno(DB_conn), mysql_error(DB_conn));
        return;
    }

    if (mysql_real_connect(DB_conn, DB_HOST.c_str(), DB_USER.c_str(), 
                                    DB_PASS.c_str(), DB_NAME.c_str(),
                                    0, NULL, 0) == NULL) {
        fprintf(DB_log,"Error %u: %s\n", mysql_errno(DB_conn), mysql_error(DB_conn));
        return;
    }
    
    fprintf(DB_log,"Database connecton established.\n");
}

void DB_query(char* item ...) {
    char query[1024];
    int i = 0;
    
    query[0] = 0x00;
    
    /// Connect to the DB if necessary
    
    if(!DB_conn) DB_connect();
    if(!DB_conn) return;
    
    /// Assemble the query

    va_list v;
    va_start(v, item);
    
    while( item[i] != 0x00 && i < 1000) {
        if(item[i] == '%' && item[i+1] == 'd') {
            sprintf(query,"%s%d",query,va_arg(v,int));
            i++;
        } else if(item[i] == '%' && item[i+1] == 'f') {
            sprintf(query,"%s%f",query,va_arg(v,double));
            i++;
        } else if(item[i] == '%' && item[i+1] == 's') {
            sprintf(query,"%s%s",query,va_arg(v,char*));
            i++;
        } else {
            sprintf(query,"%s%c",query,item[i]);
        }
        i++;        
    }
    
    va_end(v);
    fprintf(DB_log, "Executing Query: %s\n",query);

    /// Execute the query
    
    if(!mysql_query(DB_conn, query)) {
        DB_result = mysql_store_result(DB_conn);
        fprintf(DB_log, "Rows Returned: %d\n",mysql_num_rows(DB_result));
    } else {
        fprintf(DB_log, "Error querying database.\n");
    }
}

char* DB_resultAsText() {
    if(!DB_isQueryReady()) return("");

    int i = 0;
    MYSQL_ROW row;
    int num_fields;

    DB_buf[0] = 0x00;
    
    num_fields = mysql_num_fields(DB_result);
    
    while ((row = mysql_fetch_row(DB_result)))
    {
      for(i = 0; i < num_fields; i++)
      {
          sprintf(DB_buf,"%s%s ",DB_buf, row[i] ? row[i] : "NULL");
      }
      sprintf(DB_buf,"%s\n",DB_buf);
    }
    
    mysql_free_result(DB_result);    

    return DB_buf;
}

vector<string> DB_getAllFlights() {
    DB_query("select distinct concat_ws('-',DeviceID,FlightID) from aip where FlightID != \"\" order by Timesstamp DESC limit 15;");

    int i = 0;
    MYSQL_ROW row;
    int num_fields;
    
    vector<string> result;
    
    if(!DB_isQueryReady()) return result;

    num_fields = mysql_num_fields(DB_result);
    
    while ((row = mysql_fetch_row(DB_result))) {
          DB_buf[0] = 0x00;
          sprintf(DB_buf,"%s%s",DB_buf, row[i] ? row[i] : "NULL");
          string tmp = string(DB_buf);
          result.push_back(tmp);
    }
    
    mysql_free_result(DB_result);    

    return result;
}

map<string, string> DB_getMostRecentGPS(string flight_id) {
    DB_query("select Altitude, Rate, Lat, LatRef, Lon, LonRef, Spd, Hdg, Status from gps where concat_ws('-',DeviceID,FlightID)=\"%s\" and Lat != 0 order by Timestamp desc limit 1;",flight_id.c_str());

    MYSQL_ROW row;
    int num_fields;
    
    char buf[64];
    
    const float M_TO_FT = 3.2808399;
    const float KNOT_TO_MPS = 0.514444444;
    
    map<string, string> result;

    if(!DB_isQueryReady()) return result;

    num_fields = mysql_num_fields(DB_result);
    
    if (row = mysql_fetch_row(DB_result)) {
        result["Altitude"] = string(row[0]);
        result["Altitude_m"] = string(row[0]);
        sprintf(buf,"%d",(int)(atoi(row[0])*M_TO_FT));
        result["Altitude_ft"] = string(buf);
        result["Rate"] = string(row[1]);
        sprintf(buf,"%d",atoi(row[1]) - 10000);
        result["Rate_mps"] = string(buf);
        sprintf(buf,"%d",(int)((atoi(row[1]) - 10000)*M_TO_FT));
        result["Rate_fps"] = string(buf);
        result["Lat"] = string(row[2]);
        result["LatRef"] = string(row[3]);
        result["Latitude"] = string(row[2]) + string(row[3]);
        result["Lon"] = string(row[4]);
        result["LonRef"] = string(row[5]);
        result["Longitude"] = string(row[4]) + string(row[5]);
        result["Spd"] = string(row[6]);
        result["Spd_knots"] = string(row[6]);
        sprintf(buf,"%f",(float)(atof(row[6])*KNOT_TO_MPS));
        result["Spd_mps"] = string(buf);
        result["Hdg"] = string(row[7]);
        result["Status"] = string(row[8]);
    }
    
    mysql_free_result(DB_result);

    return result;
}

vector<string> DB_getMostRecentAnalog(string flight_id) {
    DB_query("select "
             "A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18 "
             "from aip "
             "where concat_ws('-',DeviceID,FlightID)=\"%s\""
             "order by Timesstamp desc limit 1;",flight_id.c_str());

    MYSQL_ROW row;
    int num_fields;
    
    vector<string> result;

    if(!DB_isQueryReady()) return result;

    num_fields = mysql_num_fields(DB_result);
    
    if (row = mysql_fetch_row(DB_result)) {
        for(int i = 0; i<18;i++) {
            result[i+1] = string(row[i]);
        }
    }
    
    mysql_free_result(DB_result);

    return result;
}

Plot DB_getPlotData(char* table, char* data_column, string flight_id) {
    // Small hack to fix a typo in the database    
    string timestamp = "Timestamp";
    if(!strcmp(table,"aip")){
        timestamp = "TimesStamp";
    }
    
    DB_query("select UNIX_TIMESTAMP(%s)-UNIX_TIMESTAMP(), Altitude, %s from %s " 
             "where concat_ws('-',DeviceID,FlightID)=\"%s\" "
             "order by %s asc;",
             timestamp.c_str(),
             data_column, table, flight_id.c_str(),
             timestamp.c_str());
    Plot result;

    if(!DB_isQueryReady()) return result;

    MYSQL_ROW row;

    while (row = mysql_fetch_row(DB_result)) {
        result.time.push_back(strtod(row[0],NULL));
        result.altitude.push_back(strtod(row[1],NULL));
        result.data.push_back(strtod(row[2],NULL));
    }

    mysql_free_result(DB_result);    
    
    return result;
}

bool DB_isQueryReady() {
    if(!DB_conn) return false;
    if(!DB_result) return false;
    return true;
}
