#include <iostream>
// #include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
// #include <netinet/in.h>
// #include <netdb.h>
#include <string>
#include <unistd.h> // close()

int main(int argc, char const *argv[]) {
    int socketCliente;
    std::string datos;
    sockaddr_in servidor;
    int opt;
    // socklen_t longitudServidor;
    do {
        std::cout << "Estas son tus opciones:" << std::endl << "\t1) DAY" << std::endl << "\t2) TIME" << std::endl << "\t3) DAYTIME" << std::endl << "Selecciona una opción: ";
        std::cin >> opt;
        switch (opt) {
            case 1:
                datos = "DAY";
                break;
            case 2:
                datos = "TIME";
                break;
            case 3:
                datos = "DAYTIME";
                break;
            default:
                std::cout << std::endl << "Un número del 1 al 3 porfa plis..." << std::endl << std::endl;
        }
    } while(opt<1||opt>3);
    socketCliente = socket(AF_INET, SOCK_DGRAM, 0);
    if( socketCliente == -1 ){
        std::cerr << "No se puede abrir el socket cliente" << std::endl;
        exit(-1);
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(2000);
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t longitud_servidor = sizeof(servidor);

    int enviado = sendto(socketCliente, datos.c_str(), sizeof(datos), 0, (sockaddr *) &servidor, sizeof(servidor));

    if(enviado < 0){
        std::cerr << "Error al solicitar el servicio" << std::endl;
    }
    else{
        char datos[256];
        int recibido = recvfrom( socketCliente, datos, sizeof(datos), 0, (sockaddr *) &servidor, &longitud_servidor);
        if(recibido > 0){
            std::cout << datos << std::endl;
        }
    }
    close(socketCliente);

    return 0;
}
