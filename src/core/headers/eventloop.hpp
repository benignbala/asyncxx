#ifndef _EVENTLOOP_H_
#define _EVENTLOOP_H_

#include <sys/epoll.h>

class EventLoop {
public:
    EventLoop(int size);
    virtual ~EventLoop();
    void register(int  s);
    void unregister(int s);
    void run();

private:
    int epollfd;
    vector<struct epoll_event> events;
    struct epoll_event ev;
    int size;
};


#endif
