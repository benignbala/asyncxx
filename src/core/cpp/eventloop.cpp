#include "eventloop.hpp"

EventLoop::EventLoop(int size) {
    this->size = size;
    epollfd = epoll_create(size);
}
