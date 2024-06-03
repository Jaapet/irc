/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:03:15 by edfirmin          #+#    #+#             */
/*   Updated: 2024/06/03 15:15:44 by ndesprez         ###   ########.fr       */
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
#include "../Message.hpp"
#include "../Message.cpp"

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

std::vector<std::string>  splitBuffer(std::string const &str)
{
    std::string del = "\r\n";
    std::string tmp2;
    std::string tmp = str;
    size_t  f = 4;
    std::vector<std::string> com;

    while (f != std::string::npos)
    {
        f = tmp.find(del);
        tmp2 = tmp.substr(0, f);
		if (!tmp2.empty())
        	com.push_back(tmp2);
        if (f == std::string::npos)
            break;
        tmp = tmp.substr(f + del.size(), tmp.size() - 1);
    }
    return (com);
}

std::vector<std::string> split(const std::string& str, char delimiter) 
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) 
	{
        tokens.push_back(token);
    }

    return tokens;
}

void send_mp(char *buff, int bot_sock)
{
    std::vector<std::string>   tab = splitBuffer(buff);
    std::vector<std::string>   ttab;
    std::string pre = "PRIVMSG ";
    std::string suf = " :Hi mate, welcome to our IRC server, hope you enjoy it. Be the first to guess the number between 1 and 1000 !\r\n";
    std::string com;
    for (size_t i = 0; i < tab.size() - 2; i++)
    {
        ttab = split(tab[i], ' ');
        if (ttab[1].compare("352"))
            break;
        com += pre + ttab[7] + suf;
    }
    send(bot_sock, com.c_str(), std::strlen(com.c_str()), 0);
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
        std::string bot_nick("GUESS-");
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
        std::string mes = "PASS " + pass + "\r\nNICK " + bot_nick + "\r\nUSER bot 0 * :Robot-Boy\r\n";
        send(bot_sock, mes.c_str(), std::strlen(mes.c_str()), 0);
        size_t i = recv(bot_sock, buff, sizeof(buff) - 1, 0);
        buff[i - 1] = '\0';
        if (!check_log(buff))
        {
            shutdown(bot_sock, SHUT_RDWR);
            throw (BotCreationFail());//modif
        }

        mes = "WHO 0\r\n";
        send(bot_sock, mes.c_str(), std::strlen(mes.c_str()), 0);
        size_t j = recv(bot_sock, buff, sizeof(buff) - 1, 0);
        buff[j - 1] = '\0';
        
        send_mp(buff, bot_sock);

        


        int rec = 1;
        char buf[1024];
        int guess = rand() % 999 + 1;
        std::cout << "Random number to guess " << guess << std::endl;
        while (rec >= 0)
        {
            rec = recv(bot_sock, buf, sizeof(buf), 0);
            if (rec < 1024 && rec > 0)
            {
                buf[rec] = '\0';
                std::vector<std::string> message = split(buf, ' ');
                message[message.size() - 1].erase(message[message.size() - 1].begin());
                std::string payload = message[message.size() - 1];
                std::string sender = message[0].erase(message[0].find('!'));
                sender.erase(sender.begin());
                if (atoi(payload.c_str()) <= 1000 && atoi(payload.c_str()) > 0)
                {
                    int ans = atoi(payload.c_str());
                    if (ans < guess)
                        mes = "Higher !\r\n";
                    else if (ans > guess)
                        mes = "Lower !\r\n";
                    else
                    {
                        mes = "Well played ! Goodbye...\r\n";
                    }
                }
                else
                    mes = "Send a number between 1 and 1000.\r\n";
                std::string rep = "PRIVMSG " + sender + " :" + mes;
                
                send(bot_sock, rep.c_str(), std::strlen(rep.c_str()), 0);
                if(mes == "Well played ! Goodbye...\r\n")
                {
                    mes = "QUIT\r\n";
                    send(bot_sock, mes.c_str(), std::strlen(mes.c_str()), 0);
                    recv(bot_sock, buff, sizeof(buff) - 1, 0);
                    exit(0);
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return (0);
}

