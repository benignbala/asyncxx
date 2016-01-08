#include "socket.hpp"

Socket::Socket() {
    family = AF_INET;
    type = SOCK_STREAM;
    host = "";
    port = 0;
    sock = 0;
    cliSock = 0;
}

Socket::Socket(int family, int type, std::string & host, int port) {
    this->family = family;
    this->type = type;
    this->host = host;
    this->port = port;
    sock = 0;
    cliSock = 0;
    memset(&mySock, 0, sizeof(sockaddr_in));
}

Socket::Socket(std::string & host, int port) {
    this->host = host;
    this->port = port;
    family = AF_INET;
    type = SOCK_STREAM;
    sock = 0;
    clisock = 0;
    memset(&mySock, 0, sizeof(sockaddr_in));
}

void Socket::init() {
    sock = socket(family, type, 0);
    if (sock < 0) {
	throw SocketException("Cound not create socket: %s", strerror(errno));
    }
    mySock.sin_family = family;
    mySock.sin_port = htons(port);
    mySock.sin_addr.s_addr = inet_addr(host.c_str());
    if ( bind(sock, (struct sockaddr*)&mySock, sizeof(mySock)) < 0) {
	throw SocketException("Could not bind to socket: %s", strerror(errno));
    }
}

void Socket::listen_(int queue) {
    listen(sock, queue);
}

Socket & Socket::accept_() {
    cliSock = accept(sock, (struct sockaddr*)&client, sizeof(client));
    if (cliSock < 0) {
	throw SocketException("Could not accept on socket %d: %s", sock, strerror(errno));
    }
    Socket c;
    c.setSock(cliSock);
    c.setHost("");
    clients.push_back(c);
    return c;
}

std::string & Socket::read_() {
}

std::string & Socket::read_(int bytes) {
    int read = 0;
    std::string data;
    char buf[4096];
    while (read < bytes) {
	read += recv(sock, buf, 4096, 0);
	data += buf;
    }
    return data;
}

void Socket::write_(std::string data) {
    int sent = 0;
    int bytes = data.length();
    while (sent <= bytes) {
	std::string curr = data(sent, 4096);
	sent += send(sock, curr.c_str(), 4096, 0);
    }
}

void Socket::close_() {
    close(sock);
}
