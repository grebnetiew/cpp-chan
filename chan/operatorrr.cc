#include "chan.ih"

template<typename T>
chan<T> &chan<T>::operator>>(T &val) {
    val = this->d_impl->receive();
    return *this;
}

template<typename T>
chan<T> &chan<T>::operator>>(T &&) {
    this->d_impl->receive();
    return *this;
}