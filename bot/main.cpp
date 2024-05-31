/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfirmin <edfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:03:15 by edfirmin          #+#    #+#             */
/*   Updated: 2024/05/31 17:37:57 by edfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "../ServerExceptions.hpp"
#include "../Server.hpp"

int check_log(char *buff)
{
    std::string line;
    std::istringstream copy (buff);
    std::getline(copy, line, ' ');
    std::getline(copy, line, ' ');
    if (line != "" && line.compare("001"))
        return (0);
    return (1);
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << "The bot only need <port>, <server ip> and <serv. password> in param. !!!" << std::endl;
        return (2);
    }
    try
    {
        int port = atoi(argv[1]);
        std::string s_ip = argv[2];
        std::string pass = argv[3];
        int serv_sock = 667;
        struct sockaddr_in serv;
        srand(time(NULL));
        std::string bot_nick("[BOT]");
        char buff[1024];

        std::stringstream out;
        out << (rand() % 999);
        bot_nick += out.str();

        std::memset(&serv, 0, sizeof(serv));
        serv.sin_family = AF_INET; //Specify its a tcp ipv4
        //-------------------------//
        in_addr_t   a = inet_addr(s_ip.c_str());// A REVOIR
	    serv.sin_addr.s_addr = a;            // A REVOIR
	    serv.sin_port = htons(port);         // A REVOIR
        //-------------------------//
        int bot_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (bot_sock < 0)
		    throw(SocketCreationError());//modif
        serv_sock = connect(bot_sock, (struct sockaddr *)&serv, sizeof(serv));
        if (serv_sock < 0)
        {
            shutdown(bot_sock, SHUT_RDWR);
            throw (BotCreationFail());//modif
        }
        std::string mes = "PASS " + pass + "\r\nNICK " + bot_nick + "\r\nUSER bot 0 * :Robot-Boy";
        send(bot_sock, mes.c_str(), std::strlen(mes.c_str()), 0);
        size_t i = recv(bot_sock, buff, sizeof(buff) - 1, 0);
        buff[i - 1] = '\0';
        if (!check_log(buff))
        {
            shutdown(bot_sock, SHUT_RDWR);
            throw (BotCreationFail());//modif
        }

        mes = "WHO 0";
        send(bot_sock, mes.c_str(), std::strlen(mes.c_str()), 0);
        size_t j = recv(bot_sock, buff, sizeof(buff) - 1, 0);
        buff[j - 1] = '\0';
        
        std::cout << buff << std::endl;
        shutdown(bot_sock, SHUT_RDWR);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return (0);
}
