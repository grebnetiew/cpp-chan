#include "chan.ih"

template<typename T>
chan<T> &chan<T>::operator<<(T const &val) {
    this->d_impl->send(val);
    return *this;
}