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
        std::cout << "MyWorker1::processMessage(" << *message_casted << ")" << std::endl;
    }

    void clean_exit() override
    {
        std::cout << "MyWorker1::clean_exit()" << std::endl;
        std::cout << "MyWorker1::getQueueSize() = " << MyWorker1::getQueueSize() << std::endl;
        MTL::MTLWorkerThread::clean_exit();
    }
};

class MyWorker2 : public MTL::MTLWorkerThread
{
public:
    MyWorker2() = default;
    virtual ~MyWorker2() = default;
    virtual void processMessage(MTL::Message message) override
    {
        int *message_casted = static_cast<int *>(message.get());
        std::cout << "MyWorker2::processMessage(" << *message_casted + 10 << ")" << std::endl;
    }

    void clean_exit() override
    {
        std::cout << "MyWorker2::clean_exit()" << std::endl;
        std::cout << "MyWorker2::getQueueSize() = " << MyWorker2::getQueueSize() << std::endl;
        MTL::MTLWorkerThread::clean_exit();
    }
};

class MyWorker3 : public MTL::MTLWorkerThread
{
public:
    MyWorker3() = default;
    virtual ~MyWorker3() = default;
    virtual void processMessage(MTL::Message message) override
    {
        int *message_casted = static_cast<int *>(message.get());
        std::cout << "MyWorker3::processMessage(" << *message_casted + 100 << ")" << std::endl;
    }

    void clean_exit() override
    {
        std::cout << "MyWorker3::clean_exit()" << std::endl;
        std::cout << "MyWorker3::getQueueSize() = " << MyWorker3::getQueueSize() << std::endl;
        MTL::MTLWorkerThread::clean_exit();
    }
};

int main()
{
    std::cout << "Running Example 3 for MTL Version " << MTL_VERSION_MAJOR << "." << MTL_VERSION_MINOR << "." << MTL_VERSION_PATCH << std::endl;
    MyWorker1 myWorker1;
    MyWorker2 myWorker2;
    MyWorker3 myWorker3;

    MTL::MTLThreadManager threadManager;

    threadManager.addThread(std::make_unique<MTL::MTLThread>(myWorker1));
    threadManager.addThread(std::make_unique<MTL::MTLThread>(myWorker2));

    MTL::MTLThread thread(threadManager);
    thread.run();
    std::cout << "First Burst of message when Worker 1 and Worker 2 are running and the Thread Manager is Running" << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        myWorker1.pushMessage(message);
        myWorker2.pushMessage(message);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    std::cout << "Suspend" << std::endl;
    thread.suspend();
    std::cout << "Second Burst of message when Worker 1 and Worker 2 are running and the Thread Manager is suspended " << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        myWorker1.pushMessage(message);
        myWorker2.pushMessage(message);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "Resume" << std::endl;
    thread.resume();
    std::cout << "Add Worker 3 while the Thread Manager is Running  " << std::endl;
    threadManager.addThread(std::make_unique<MTL::MTLThread>(myWorker3));
    std::cout << "Third Burst of message when Worker 1 and Worker 2 and Worker 3 are running and the Thread Manager is Running " << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        myWorker1.pushMessage(message);
        myWorker3.pushMessage(message);
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
    std::cout << "Thread Manager Terminated" << std::endl;

    return 0;
}