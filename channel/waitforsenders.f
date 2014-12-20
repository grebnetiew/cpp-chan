template<typename T>
void Channel<T>::waitForSenders(std::unique_lock<std::mutex> &ul) {
    d_senders.notify_all();                 // Notify senders I'm here
    while (size() == 0) {                   // Wait until item
        if (!d_open) {
            throw ClosedException();
        }
        d_receivers.wait(ul);
    }
}