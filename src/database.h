#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>

#define DBUG_OFF

#include <my_global.h>
#include <mysql.h>

#define DB_USER "root"
#define DB_PASS "root"
#define DB_HOST "127.0.0.1"
#define DB_NAME "hawkeye"

void DB_connect();
void DB_query(char * item ...);
char* DB_resultAsText();

#endif
