#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
class Socket {
public:
    Socket();
    Socket(int family, int type, std::string & host, int port);
    Socket(std::string & host, int port);
    virtual ~Socker();
    void init();
    std::string & read_();
    std::string & read_(int bytes);
    void write_(std::string data);
    void listen_(int queue);
    Socket & accept_(Socket & s);
    void close_();
    void setSock(int sockfd);
    void setHost(std::string & clientHost);
    
private:
    int sock;
    int cliSock;
    int family;
    int type;
    int port;
    std::string host;
    struct sockaddr_in mySock;
    struct sockaddr_in client;
    vector<Socket> clients;
};

#endif
