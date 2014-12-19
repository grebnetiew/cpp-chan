#include "chan.ih"

template<typename T>
chan<T> &chan<T>::operator>>(chan<T> ch, T &val) {
    val = this->d_impl->receive();
    return ch;
}

template<typename T>
chan<T> &chan<T>::operator>>(chan<T> ch, T &&) {
    this->d_impl->receive();
    return ch;
}