#include "channel.ih"

template<typename T>
Channel::Channel()
:
    unique_ptr<deque<T>>(new deque<T>()),
    d_cap(0)
{}

template<typename T>
Channel::Channel(size_t capacity)
:
    unique_ptr<deque<T>>(new deque<T>()),
    d_cap(capacity)
{}
