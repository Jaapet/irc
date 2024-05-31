/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfirmin <edfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:03:15 by edfirmin          #+#    #+#             */
/*   Updated: 2024/05/31 15:35:51 by edfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "../irc/Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "The bot only need <port> and <server ip> in param. !!!" << std::endl;
        return (2);
    }
    try
    {
        int port = atoi(argv[1]);
        std::string s_ip = argv[2];
        struct sockaddr_in serv;
        std::memset(&serv, 0, sizeof(serv));
        serv.sin_family = AF_INET; //Specify its a tcp ipv4
        //-------------------------//
        in_addr_t   a = inet_addr(s_ip.c_str());// A REVOIR
        std::cout << a << std::endl;           // A REVOIR
	    serv.sin_addr.s_addr = a;             // A REVOIR
	    serv.sin_port = htons(port);         // A REVOIR
        //-------------------------//
        int bot_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (bot_sock < 0)
		    throw(std::exception());//modif
        if (connect(bot_sock, (struct sockaddr *)&serv, sizeof(serv)) < 0)
            throw (std::exception());//modif
        //char const *mes = "salut je suis le bot du serv. !!!\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return (0);
}
