#include "database.h"

MYSQL *DB_conn = NULL;
MYSQL_RES *DB_result = NULL;
FILE * DB_log = NULL;

char DB_buf[16384];

void DB_connect() {
    DB_log = fopen("database.log","w");

    DB_conn = mysql_init(NULL);
    
    if (DB_conn == NULL) {
        fprintf(DB_log, "Error %u: %s\n", mysql_errno(DB_conn), mysql_error(DB_conn));
        return;
    }

    if (mysql_real_connect(DB_conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
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
    fprintf(DB_log, "Executing Query: %s",query);

    /// Execute the query
    
    mysql_query(DB_conn, query);
    DB_result = mysql_store_result(DB_conn);
}

char* DB_resultAsText() {
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

vector<string> DB_getAllDevices() {
    DB_query("select distinct DeviceID from aip order by DeviceID ASC;");

    int i = 0;
    MYSQL_ROW row;
    int num_fields;
    
    vector<string> result;

    num_fields = mysql_num_fields(DB_result);
    
    while ((row = mysql_fetch_row(DB_result))) {
          DB_buf[0] = 0x00;
          sprintf(DB_buf,"%s%s ",DB_buf, row[i] ? row[i] : "NULL");
          string tmp = string(DB_buf);
          result.push_back(tmp);
    }
    
    mysql_free_result(DB_result);    

    return result;
}

map<string, string> DB_getMostRecentGPS(int device_id) {
    //DB_query("select * from gps where Lat != 0 order by Timestamp desc limit 1;");
    DB_query("select Altitude, Rate, Lat, LatRef, Lon, LonRef, Spd, Hdg from gps where DeviceID=%d and Lat != 0 order by Timestamp desc limit 1;",device_id);

    MYSQL_ROW row;
    int num_fields;
    
    map<string, string> result;

    num_fields = mysql_num_fields(DB_result);
    
    if (row = mysql_fetch_row(DB_result)) {
        result["Altitude"] = string(row[0]);
    }
    
    mysql_free_result(DB_result);

    return result;
}
