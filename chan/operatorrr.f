template<typename T>
chan<T> &chan<T>::operator>>(T &val) {
    this->d_impl->receive(val);
    return *this;
}

template<typename T>
chan<T> &chan<T>::operator>>(T &&) {
    this->d_impl->receive();
    return *this;
}