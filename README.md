cpp-chan
========

This is an attempt to replicate the channels from Go in C++, in a thread-safe (of course) and exception-safe manner.
At the moment it is primarily an exercise.

For those who are not familiar with the concept: a channel is simply a device to send and receive values of a certain type. It is designed with thread comunication in mind, but can be used as a fifo-like storage device too.

The basic channel is like a named pipe: both a sender and a receiver must be present for communication to work. The default operators for sending and receiving block until both are present.

If you specify a capacity (say, n) during construction, a buffer is created, and the first n items can be sent without blocking the thread. If none are removed in the meantime, the n-plus-first attempt to send will block as if the cannel were unbuffered.

It consists of two classes, the API of which is as follows.

# chan

The main interface. They are implemented as a shared pointer and can therefore be copied and moved without `cutting the links between both ends'.

## Constructing
To create a synchonous channel,

    chan<int> chToWorker;
    thread thr(do_work, chToWorker);

The worker thread gets a copy of the channel, which acts like a reference.

To create an asynchonous channel with space for five ints,

    chan<int> chToWorker(5);

## Communicating

To store something,

    chToWorker << 4;
    chToworker << 3 << -1;

To receive something,

    int result;
    chToworker >> result;

If you don't want to block if the channel isn't being sent to, use the conditional receive operator. It returns a pair of bool and the channel's type. If the former is true, you received an object as the second element. If the first is false, there was nothing to receive, and the second element is default-constructed.

    pair<bool, int> result(~ch);
    if (result.first) {
        cout << "Got a result: " << result.second << endl;
    } else {
        cout << "Nope.\n";
    }
    //...
    result = ~ch; // try again
    
## Closing channels

After a channel has been closed, sending to it will generate an exception. This applies also to senders that are still waiting for a receiver. Receivers will receive values normally if they were already stored (in the buffered case), and throw exceptions when the channel is empy.

    ch.close();

# Channel

This is the implementation. You are not expected to interact with it.
This class is* exception-safe: operations that throw exceptions will not otherwise affect the objects involved.

*) This means: if you notice that this is not true, that is a bug. Please inform me.
