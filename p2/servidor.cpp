#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <ctime>
#include <map>
#include <unistd.h> // close()
#include "jugador.hpp"
#include "partida.hpp"

int main(){
    int socket, nuevo_socket;
    int salida;
    sockaddr_in servidor, cliente;
    char buffer[250];
    fd_set read_fds, aux_fds;
    int on, ret;

    socket = socket(AF_INET, SOCK_STREAM, 0);
    if(socket == -1){
        std::cerr << "No se puede abrir el socket cliente" << std::endl;
        exit(-1);
    }

    on = 1;
    ret = setsockopt( socket, SOL_SOCKET, SO_REUSEADOR, &on, sizeof(on));

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(2000);
    servidor.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(socket, (sockaddr *) &servidor, sizeof(servidor)) == -1 ){
        std::cerr << "No se pudo hacer bind" << std::endl;
        close(socket);
        exit(-1);
    }

    socklen_t cliente_len = sizeof(cliente);

    if(listen(socket, 1) == -1){
        std::cerr << "No se pudo hacer listen" << std::endl;
        close(socket);
        exit(-1);
    }

    FD_ZERO(&read_fds);
    FD_ZERO(&aux_fds);
    FD_SET(socket, &read_fds);
    FD_SET(0, &read_fds);

    // signal(SIGINT, manejador);
    bool salir = true;
    while(true){
        if(salir){
            for(int i = 0 ; i < 100 /*partidas.size()*/ ; ++i){
                // jugadores = partidas[i].get_jugadores();
                // for(int j = 0 ; j < jugadores.size() ; ++j){
                //     send(jugadores[i].get_socket(), "Desconexión del servidor\n", strlen("Desconexión del servidor\n"). 0);
                //     close(jugadores[i].get_socket());
                //     FD_CLR(jugadores[i].get_socket(), &read_fds);
                // }
                close(socket);
                exit(EXIT_SUCCESS);
            }
        }
        aux_fds = read_fds;
        salida = select(FD_SETSIZE, &aux_fds, NULL, NULL, NULL);
        if(salida > 0){
            for(int i = 0 ; i < FD_SETSIZE ; ++i){
                if(FD_ISSET(i, &aux_fds)){
                    if(i == socket){
                        if((nuevo_socket = accept(socket, (sockaddr *) &cliente, &cliente_len)) == -1 ){
                            std::cerr << "Error aceptando peticiones" << std::endl;
                        }
                        else{
                            if(/*partidas.size() < MAX_CLIENTES*/){
                                // Game tmp
                            }
                        }
                    }
                }
            }
        }
    }
}