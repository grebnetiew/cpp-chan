#include "chan.ih"

template<typename T>
chan<T> &operator<<(chan<T> ch, T const &val) {
    ch.d_impl->send(val);
    return ch;
}