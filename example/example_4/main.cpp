#include <iostream>
#include "MTL.h"

class MyWorker1 : public MTL::MTLWorkerThread
{
public:
    MyWorker1() = default;
    virtual ~MyWorker1() = default;
    virtual void processMessage(MTL::Message message) override
    {
        int *message_casted = static_cast<int *>(message.get());
        std::cout << "MyWorker1::processMessage(" << *message_casted << ")"
                  << " thread ID : " << std::this_thread::get_id() << std::endl;
    }

    void clean_exit() override
    {
        MTL::MTLWorkerThread::clean_exit();
    }
};

int main()
{
    std::cout << "Running Example 4 for MTL Version " << MTL_VERSION_MAJOR << "." << MTL_VERSION_MINOR << "." << MTL_VERSION_PATCH << std::endl;
    MyWorker1 myWorker1;

    MTL::MTLThreadPool threadPool(myWorker1, 4);

    MTL::MTLThread thread(threadPool);
    thread.run();
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        threadPool.onMessage(message);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    std::cout << "Suspend" << std::endl;
    thread.suspend();
    for (int i = 10; i < 20; ++i)
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        threadPool.onMessage(message);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "Resume" << std::endl;
    thread.resume();

    for (int i = 20; i < 30; ++i)
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        threadPool.onMessage(message);
    }
    int counter = 0;

    std::cout << "Exit" << std::endl;
    thread.clean_exit();
    while (thread.isRunning())
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Counter: " << counter << std::endl;
        counter++;
    }
    std::cout << "Thread Pool Terminated" << std::endl;

    return 0;
}