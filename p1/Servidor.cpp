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
#include <cstdlib>

int main(int argc, char const *argv[]) {
    int socketServidor;
    sockaddr_in servidor, cliente;
    socketServidor = socket(AF_INET, SOCK_DGRAM, 0);
    std::string datos;
    if( socketServidor == -1 ){
        std::cerr << "No se puede abrir el socket servidor" << std::endl;
        exit(-1);
    }
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(2000);
    servidor.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(socketServidor, (sockaddr *) &servidor, sizeof(servidor)) == -1 ){
        std::cerr << "No se pudo hacer bind" << std::endl;
        close(socketServidor);
        exit(-1);
    }
    socklen_t longitud_cliente = sizeof(cliente);
    while(true){
        char datos[256];
        int recibido = recvfrom(socketServidor, datos, sizeof(datos), 0, (sockaddr *) &cliente, &longitud_cliente);
        std::string aux1 = std::string(datos);
        std::map<std::string, std::string> helper;
        if(recibido > 0){
            time_t rawtime;
            tm * timeinfo;
            char buffer_1[256], buffer_2[256], buffer_3[256];
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(buffer_1,256,"%A, %d %B %Y",timeinfo);
            strftime(buffer_2,256,"%H:%M:%S",timeinfo);
            strftime(buffer_3,256,"%A, %d %B %Y; %H:%M:%S",timeinfo);
            helper["DAY"] = std::string(buffer_1);
            helper["TIME"] = std::string(buffer_2);
            helper["DAYTIME"] = std::string(buffer_3);
            sendto(socketServidor, helper[aux1].c_str(), helper[aux1].size(), 0, (sockaddr *) &cliente, longitud_cliente);

        }
    }

    close(socketServidor);
    return 0;
}
