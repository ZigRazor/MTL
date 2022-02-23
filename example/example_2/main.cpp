#include <iostream>
#include "MTL.h"

class MyWorker : public MTL::MTLWorkerThread
{
public:
    MyWorker() = default;
    virtual ~MyWorker() = default;
    virtual void processMessage(MTL::Message message) override
    {
        int *message_casted = static_cast<int *>(message.get());
        std::cout << "MyWorker::processMessage(" << *message_casted << ")" << std::endl;
    }
};

int main()
{
    std::cout << "Running Example 2 for MTL Version " << MTL_VERSION_MAJOR << "." << MTL_VERSION_MINOR << "." << MTL_VERSION_PATCH << std::endl;
    MyWorker myWorker;
    MTL::MTLThread thread(myWorker);
    thread.run();
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        myWorker.pushMessage(message);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    thread.suspend();
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        myWorker.pushMessage(message);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "Resume" << std::endl;
    thread.resume();
    std::cout << "Exit" << std::endl;
    thread.clean_exit();
    // thread.force_exit();
    int counter = 0;
    while (thread.isRunning())
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Counter: " << counter << std::endl;
        counter++;
    }
    std::cout << "Thread Terminated" << std::endl;

    return 0;
}