#include <iostream>
#include "extra_functions.hpp"
#include "jugador.hpp"
#include "partida.hpp"

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    bool salir = false;
//    char c;
    std::string c;
    int opt;
    std::string res;
    r::Game game(SINGLEPLAYER, true);
    game.add_player(*(new r::Player()));
    std::string sol = game.get_solution();
    do{
        std::cout << "Estado actual" << std::endl << "\t" << game.get_actual_state() << std::endl;
        std::cout << "\n1. Letra.\n2. Resolver.\n\nElige: ";
        std::cin >> opt;
        if(opt == 1){
            std::cout << "\n\nLETRA: ";
            std::cin >> c;
        }
        else{
            std::cin.ignore();
            std::cout << "\n\nRESUELVE: ";
            std::getline(std::cin, res);
        }
        if(opt == 1){
            game.check_letter(c[0]);
        }
        else{
            if(game.solve(res)){
                salir = true;
            }
        }
    }while(not salir);

    return 0;
}



//
//int main(){
//    r::Player p;
//    p.set_score(3);
//    std::string username, passwd;
//    std::cout << "Introduce el username: ";
//    std::cin >> username;
//    std::cout << "Introduce la contraseña: ";
//    std::cin >> passwd;
//    p.create_user(username, passwd);
//    std::cout << p << std::endl;
//    return 0;
//}