#include <iostream>
#include "jugador.hpp"
#include "extra_functions.hpp"

int main(int argc, char const *argv[]) {
    std::string h, z;
    std::cout << "Introduce un nombre: ";
    std::cin >> h;
    if(sql_exists(h)){
        r::Player p1(h);
        std::cout << "Cargado usuario:" << std::endl << p1;
    }
    else{
        std::cout << "Escribe una contraseña para él: ";
        std::cin >> z;
        r::Player p1(h, z);
        std::cout << "Creado usuario" << std::endl << p1;
    }
    return 0;
}
