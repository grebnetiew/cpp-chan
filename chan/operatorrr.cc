#include "chan.ih"

template<typename T>
chan<T> &operator>>(chan<T> ch, T &val) {
    val = ch.d_impl->receive();
    return ch;
}

template<typename T>
chan<T> &operator>>(chan<T> ch, T &&) {
    ch.d_impl->receive();
    return ch;
}