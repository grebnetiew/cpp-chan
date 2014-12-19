#ifndef INCLUDED_CHANNEL_
#define INCLUDED_CHANNEL_

#include <deque>
#include <memory>
#include <condition_variable>
#include <mutex>

template<typename T>
class Channel: private std::unique_ptr<std::deque<T>> {
    size_t d_cap;
    size_t d_receivers_present = 0;
    std::mutex d_mutex;
    std::condition_variable d_senders;
    std::condition_variable d_receivers;

    public:
        Channel();
        explicit Channel(size_t capacity);

        using std::unique_ptr<std::deque<T>>::size;
        void send(T const &element);
        T receive();
        bool try_receive(T &val);
};

#endif
