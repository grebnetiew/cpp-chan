#ifndef INCLUDED_CHAN_
#define INCLUDED_CHAN_

#include <memory>   // shared_ptr
#include <utility>  // pair
#include "channel.H"

template<typename T>
class chan {
    std::shared_ptr<Channel<T>> d_impl;
    
    public:
        chan();
        explicit chan(size_t capacity);
        chan(chan<T> const &other) = default;

        size_t size() const;
        // The insertion operator sends values over the channel
        chan<T> &operator<<(T const &val);
        // The extraction operator receives them
        chan<T> &operator>>(T &val);
        chan<T> &operator>>(T &&);
        std::pair<bool, T> operator~();
};

template<typename T>
chan<T>::chan(): d_impl(new Channel<T>()) {}

template<typename T>
chan<T>::chan(size_t capacity): d_impl(new Channel<T>(capacity)) {}

template<typename T>
size_t chan<T>::size() const {
    return d_impl->size();
}

template<typename T>
chan<T> &chan<T>::operator<<(T const &val) {
    this->d_impl->send(val);
    return *this;
}

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

template<typename T>
std::pair<bool, T> chan<T>::operator~() {
    T result;
    return std::pair<bool, T>(this->d_impl->try_receive(result), result);
}

#endif
