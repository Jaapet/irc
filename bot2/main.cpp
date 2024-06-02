/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:03:15 by edfirmin          #+#    #+#             */
/*   Updated: 2024/06/02 19:08:20 by ndesprez         ###   ########.fr       */
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
    std::string suf = " :Hi mate, welcome to our IRC server, hope you enjoy it :)\r\n";
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

void parseMessage(const std::string &message, Message &outmessage) 
{
	if(message[0] == '\r' && message[1] == '\n')
		return;
    outmessage.clear();
    
    size_t pos = 0;
    size_t end = message.size();

    // Check for sender (prefix)
    if (message[pos] == ':') {
        size_t prefixEnd = message.find(' ', pos);
        if (prefixEnd != std::string::npos) 
		{
            outmessage.sender = message.substr(pos + 1, prefixEnd - pos - 1);
            pos = prefixEnd + 1;
        } 
		else 
		{
            return; // Invalid message format
        }
    } 
	else 
	{
        outmessage.sender = "";
    }

    // Get command
    size_t commandEnd = message.find(' ', pos);
    if (commandEnd != std::string::npos) 
	{
        outmessage.command = message.substr(pos, commandEnd - pos);
        pos = commandEnd + 1;
    } 
	else 
	{
        outmessage.command = message.substr(pos);
        return;
    }

    // Get params and payload
    while (pos < end) {
        if (message[pos] == ':') 
		{
            // Trailing param (payload)
            outmessage.payload = message.substr(pos + 1);
            break;
        }
        
        size_t paramEnd = message.find(' ', pos);
        if (paramEnd != std::string::npos) 
		{
            outmessage.params.push_back(message.substr(pos, paramEnd - pos));
            pos = paramEnd + 1;
        } 
		else 
		{
            outmessage.params.push_back(message.substr(pos));
            break;
        }
    }
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

        // mes = "QUIT\r\n";
        // send(bot_sock, mes.c_str(), std::strlen(mes.c_str()), 0);
        // size_t k = recv(bot_sock, buff, sizeof(buff) - 1, 0);
        // buff[k - 1] = '\0';



        // char buffer[BUFFER_SIZE];
	    // memset(buffer,'\0',BUFFER_SIZE);
	    // int nbytes = recv(cur_fd, buffer, sizeof(buffer), 0);
        int rec = 1;
        char buf[1024];
        Message msg;
        int guess = rand() % 999 + 1;
        while (rec >= 0)
        {
            rec = recv(bot_sock, buf, sizeof(buf), 0);
            if (rec < 1024)
            {
                buf[rec] = '\0';
                parseMessage(std::string(buf), msg);
                if (atoi(msg.payload.c_str()) <= 1000 && atoi(msg.payload.c_str()) > 0)
                {
                    int ans = atoi(msg.payload.c_str());
                    if (ans < guess)
                        mes = "Higher !\r\n";
                    else if (ans > guess)
                        mes = "Lower !\r\n";
                    else
                    {
                        mes = "Well played !\r\n";
                    }
                }
                else
                    mes = "Send a number between 1 and 1000.\r\n";
                std::cout << mes << std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return (0);
}

