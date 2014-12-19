#ifndef INCLUDED_CHAN_
#define INCLUDED_CHAN_

#include <memory>   // shared_ptr
#include <utility>  // pair
class channel;

template<typename T>
class chan {
    // The insertion operator sends values over the channel
    friend chan<T> &operator<<(chan<T> ch, T const &val);
    // The extraction operator receives them
    friend chan<T> &operator>>(chan<T> ch, T &val);
    //friend chan<T> &operator>>(chan<T> ch, std::pair<bool, T> &conditional_val) noexcept;
    friend chan<T> &operator>>(chan<T> ch, T &&);

    std::shared_ptr<Channel<T>> d_impl;
    
    public:
        chan();
        explicit chan(size_t capacity);
        chan(chan<T> const &other) = default;

        size_t size() const;
        T &&operator~(chan<T> &ch);     // Shortcut/alias for >>
};

#endif
