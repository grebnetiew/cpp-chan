template<typename T>
void Channel<T>::close() {
    d_open = false;
    d_senders.notify_all();
    d_receivers.notify_all();
}