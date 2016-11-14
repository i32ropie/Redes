#ifndef P2_SERVIDOR_HPP
#define P2_SERVIDOR_HPP

#define MAX_CLIENTES 50

#include <map>
#include <regex>
#include <vector>
#include "jugador.hpp"

int manejar_peticion(std::string peticion){
    std::map<std::string, int> m = {{"^USUARIO [[:alnum:]]+$", 1}, {"^PASSWORD [[:alnum:]]+$", 2}, {"^REGISTRO -u [[:alnum:]]+ -p [[:alnum:]]+$", 3}, {"^PARTIDA-INDIVIDUAL$", 4}, {"^PARTIDA-GRUPO$", 5}, {"^CONSONANTE [b-df-hj-np-tv-z]$", 6}, {"^VOCAL [aeiou]$", 7}, {"^RESOLVER .+$", 8}, {"^SALIR$", 9}, {"^$", 9}};
    for(auto it = m.begin() ; it != m.end() ; ++it){
        if(std::regex_match(peticion, std::regex(it->first)))
            return it->second;
    }
}

bool check1(const int &socket, const std::vector<r::Player> &jugadores){
    for(auto it = jugadores.begin() ; it != jugadores.end() ; ++it){
        if(it->get_socket() == socket)
            return not it->get_username().empty();
    }
}

bool check2(const int &socket, const std::vector<r::Player> &jugadores){
    for(auto it = jugadores.begin() ; it != jugadores.end() ; ++it){
        if(it->get_socket() == socket)
            return not it->get_username().empty() and not it->get_password().empty();
    }
}




#endif

// Example program
//#include <iostream>
//#include <string>
//#include <map>
//#include <regex>
//
//int manejar_peticion(std::string peticion){
//    std::map<std::string, int> m = {{"^USUARIO [[:alnum:]]+$", 1}, {"^PASSWORD [[:alnum:]]+$", 2}, {"^REGISTRO -u [[:alnum:]]+ -p [[:alnum:]]+$", 3}, {"^PARTIDA-INDIVIDUAL$", 4}, {"^PARTIDA-GRUPO$", 5}, {"^CONSONANTE [b-df-hj-np-tv-z]$", 6}, {"^VOCAL [aeiou]$", 7}, {"^RESOLVER .+$", 8}, {"^SALIR$", 9}};
//    for(auto it = m.begin() ; it != m.end() ; ++it){
//        if(std::regex_match(peticion, std::regex(it->first)))
//            return it->second;
//    }
//    return 0;
//}
//
//int main()
//{
//    std::string a;
//    while(1){
//        std::getline(std::cin, a);
//        std::cout << manejar_peticion(a) << std::endl;
//    }
//}
