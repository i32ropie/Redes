#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <string>
#include <unistd.h>

int main(){
    int socket_cliente;
    sockaddr_in servidor;
    char buffer[250];
    fd_set read_fds, aux_fds;

    socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
    if( socket_cliente == -1 ){
        std::cerr << "No se puede abrir el socket cliente" << std::endl;
        exit(EXIT_FAILURE);
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(2050);
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t longitud_servidor = sizeof(servidor);


    if( connect(socket_cliente, (sockaddr *) &servidor, longitud_servidor) == -1 ){
        std::cerr << "Error de conexión." << std::endl;
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&aux_fds);
    FD_ZERO(&read_fds);

    FD_SET(0,&read_fds);
    FD_SET(socket_cliente ,&read_fds);
//    std::cout << "> ";
    do{
        char buffer[250];
        bzero(buffer,sizeof(buffer));
        std::string tmp_buffer;
        aux_fds = read_fds;
        select(socket_cliente+1, &aux_fds, NULL, NULL, NULL);
        if(FD_ISSET(socket_cliente, &aux_fds)){
            recv(socket_cliente, buffer, sizeof(buffer), 0);
            tmp_buffer = std::string(buffer);
            std::cout << "SERVIDOR: " << tmp_buffer << std::endl;
        }
        else{
            std::cout << "> ";
            fflush(stdout);
            if(FD_ISSET(0, &aux_fds)){
                std::getline(std::cin, tmp_buffer);
                // comprobar si quiere salir
                if(tmp_buffer == "SALIR"){
                    close(socket_cliente);
                    exit(EXIT_SUCCESS);
                }
                send(socket_cliente, tmp_buffer.c_str(), tmp_buffer.size(), 0);
            }
        }
    }while(true);

}