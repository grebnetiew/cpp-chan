#ifndef INCLUDED_CHANNEL_
#define INCLUDED_CHANNEL_

#include <memory>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>   // in try_receive
#include <exception>

template<typename T>
class Channel: private std::unique_ptr<std::deque<T>> {
    bool d_open = true;
    size_t d_cap;
    size_t d_receivers_present = 0;
    std::mutex d_mutex;
    std::condition_variable d_senders;
    std::condition_variable d_receivers;

    public:
        explicit Channel(size_t capacity);

        size_t size() const;
        void send(T const &element);
        void receive();
        void receive(T *result = nullptr);
        bool try_receive(T *result);
        void close();

        class ClosedException: public std::exception {
            char const *what() const noexcept override {
                return "Interacting with a closed channel";
            }
        };

    private:
        void waitForSenders(std::unique_lock<std::mutex> &ul);
        void moveElement(T *result);
};

#include "channel.f"
#include "size.f"
#include "send.f"
#include "receive.f"
#include "tryreceive.f"
#include "close.f"
#include "waitforsenders.f"
#include "moveelement.f"

#endif
