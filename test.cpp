#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

const int PORT = 6667;
const int BACKLOG = 5;
const int BUFFER_SIZE = 1024;

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size;
    char buffer[BUFFER_SIZE];
    fd_set master_set, read_fds;
    int fdmax;

    // Création du socket serveur
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Erreur de création du socket");
        exit(1);
    }

    // Configurer l'adresse du serveur
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Lier le socket à l'adresse et au port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur de liaison");
        exit(1);
    }

    // Mettre le socket en mode écoute
    if (listen(server_socket, BACKLOG) < 0) {
        perror("Erreur d'écoute");
        exit(1);
    }

    // Initialiser le jeu de descripteurs de fichiers
    FD_ZERO(&master_set);
    FD_SET(server_socket, &master_set);
    fdmax = server_socket;


    while (true) {
        read_fds = master_set;  // Copier le jeu principal
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("Erreur de select");
            exit(1);
        }

        // Parcourir les descripteurs pour voir ceux qui sont prêts
        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {  // Si prêt pour la lecture
                if (i == server_socket) {
                    // Nouveau client
                    sin_size = sizeof(client_addr);
                    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &sin_size);
                    if (client_socket < 0) {
                        perror("Erreur d'acceptation");
                    } else {
                        FD_SET(client_socket, &master_set);
                        if (client_socket > fdmax) {
                            fdmax = client_socket;
                        }
                        std::cout << "Nouvelle connexion de " << inet_ntoa(client_addr.sin_addr) << std::endl;
                    }
                } else {
                    // Données d'un client existant
                    int nbytes = recv(i, buffer, sizeof(buffer), 0);
                    if (nbytes <= 0) {
                        // Erreur ou connexion fermée par le client
                        if (nbytes == 0) {
                            std::cout << "Connexion fermée par " << i << std::endl;
                        } else {
                            perror("Erreur de réception");
                        }
                        close(i);
                        FD_CLR(i, &master_set);
                    } else {
                        // Données reçues
                        buffer[nbytes] = '\0';
                        std::cout << "Reçu : " << buffer << " de " << i << std::endl;
                        // Envoyer une réponse (exemple simple)
                        std::string msg = "Réponse du serveur\n";
                        send(i, msg.c_str(), msg.length(), 0);
                    }
                }
            }
        }
    }
    close(server_socket);
    return 0;
}