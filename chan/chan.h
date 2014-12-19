#ifndef INCLUDED_CHAN_
#define INCLUDED_CHAN_

#include <memory>   // shared_ptr
#include <utility>  // pair
#include "../channel/channel.h"

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

#include "chan.f"
#include "size.f"
#include "operatorll.f"
#include "operatorrr.f"
#include "operator~.f"

#endif
