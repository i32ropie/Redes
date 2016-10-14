#ifndef __EXTRA_FUNCTIONS_HPP__
#define __EXTRA_FUNCTIONS_HPP__

#include <sqlite3.h>
#include <string>
#include <iostream>
#include "jugador.hpp"


bool sql_exists(const std::string &st){
    sqlite3 *db;
    int rc = sqlite3_open("players.db", &db);
    std::string order = "select * from players where username = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, order.c_str(), -1 , &stmt, NULL);
    sqlite3_bind_text(stmt, 1, st.c_str(), -1, 0);
    if (rc != SQLITE_OK)
        throw std::string(sqlite3_errmsg(db));
    // http://stackoverflow.com/a/14438228
    sqlite3_bind_text(stmt, 1, st.c_str(), -1, 0);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return rc==SQLITE_ROW?true:false;
}

void sql_stmt(const std::string &st){
    sqlite3 *db;
    sqlite3_open("players.db", &db);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, st.c_str(), -1 , &stmt, NULL);
    // std::cout << "st.c_str() = " << st.c_str() << std::endl;
    // std::cout << "rc = " << rc << std::endl;
    if (rc != SQLITE_OK)
        throw std::string(sqlite3_errmsg(db));
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

#endif
