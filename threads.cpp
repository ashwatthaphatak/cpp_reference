#include <iostream>
#include <thread>

using namespace std;

class MyClass {
public:
    void function_1(string& msg) {
        cout << "Hello from function 1" << msg << endl;
        msg = "Message from function 1";
    }
};

int main() {
    // MyClass func;
    thread thread1(function_1, "Hello from thread 1");
    thread thread2([] {
        cout << "Hello from thread2" << endl;
    });

    thread1.detach(); // causes a daemon thread which then is its own process
}


/**

So there are a few things that I need to understand and know here:
1. Let's say I have a function declared or a class or an object class object declared somewhere, and that class object takes a few arguments. Then I can pass those arguments to my thread, and if I want to pass those by reference (which means that I would just want to use the default arguments within the original object), then I can pass them by reference. If not, I can just pass them by value if I want to use my own arguments for that object.
2. If I don't want to share data between two threads because that causes communication overhead, then I can use the.move() functionality to actually move my value from my main or current thread to a child thread.
3. Similarly, I can also use move to transfer ownership of one of my threads to another thread. Let's say I do t1 = thread t1; thread t1 is able to move thread t2. This is given that I have already created a thread t2 before. After this, I only need to join thread T1 back because now have transferred ownership of T2 back to T1. Once T1 joins, T2 is implicitly also terminated.
Another small thing is join and detach. When I do a t1.join(), when I do a.join() for any thread, the current thread (i.e., the program) will wait until that point for the thread on which I have called the join to finish and only then it will proceed forward. Otherwise, I can do a.detach() operation where these two threads (the thread which I have detached) will separate from the main thread. It will keep running under the same PID but it will terminate independently and the OS will reclaim the thread resources once it terminates. It will not then block the main thread. 


WTF are lvalues and rvalues? 

for example -> int i = 10
        here, i is and lvalue because it has a memory address and 10 is an rvalue because it does not have a memory address.

        lvalue = permament value with a location in memory
        rvalue = temporary value without a location in memory

So basically, an rvalue is something that forces the compiler to temporarily give it a location before it actually assigns that value to an actual location on the memory (being some location held by the variable). It does not matter if I am doing so string three = string one + string two, in this case, string one and string two will still be lvalues. The addition of string one and string two will still be an rvalue because that concatenated string result will be stored by the compiler in some temporary place before it's stored in the actual location of string three. 




*/