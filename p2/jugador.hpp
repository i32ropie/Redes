#ifndef __JUGADOR_HPP__
#define __JUGADOR_HPP__

#include <string>
#include <sqlite3.h>
#include "extra_functions.hpp"

namespace r{
    class Player{
        private:
            std::string _username;
            std::string _password;
            uint _score;
            uint _wins;
            uint _loses;
        public:
            Player(const std::string &st){
                sqlite3 *db;
                sqlite3_open( "players.db", &db);
                sqlite3_stmt *stmt;
                std::string order = "select * from players where username = ?";
                int rc = sqlite3_prepare_v2(db, order.c_str(), -1, &stmt, NULL);
                if( rc != SQLITE_OK )
                    // TODO: Quitar los throws y manejar los errores.
                    throw std::string(sqlite3_errmsg(db));
                sqlite3_bind_text(stmt, 1, st.c_str(), -1, 0);
                rc = sqlite3_step(stmt);
                this->set_username(std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0))));
                this->set_password(std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1))));
                this->set_score(sqlite3_column_int(stmt, 2));
                this->set_wins(sqlite3_column_int(stmt, 3));
                this->set_loses(sqlite3_column_int(stmt, 4));
                sqlite3_finalize(stmt);
                sqlite3_close(db);
            }
            Player(const std::string &username, const std::string &password){
                // TODO: Hacer función para insertar nuevos usuarios con control de parámetros.
                sql_stmt("insert into players (username, password) values ('" + username + "', '" + password + "')");
                // TODO: Hacer esto más bonito.
                *this = (* new Player(username));
            }
            inline void set_username(const std::string &username) { _username = username; }
            inline void set_password(const std::string &password) { _password = password; }
            inline void set_score(const uint &score) { _score = score; }
            inline void set_wins(const uint &wins) { _wins = wins; }
            inline void set_loses(const uint &loses) { _loses = loses; }
            inline std::string get_username() const { return _username; }
            inline std::string get_password() const { return _password; }
            inline uint get_score() const { return _score; }
            inline uint get_wins() const { return _wins; }
            inline uint get_loses() const {return _loses; }
            friend std::ostream &operator <<(std::ostream &output, const Player &p){
                output << "\tUsername: " << p.get_username() << std::endl;
                output << "\tPassword: " << p.get_password() << std::endl;
                output << "\tScore: " << p.get_score() << std::endl;
                output << "\tWins: " << p.get_wins() << std::endl;
                output << "\tLoses: " << p.get_loses() << std::endl;
                return output;
            }
    };
}

#endif
