#include <iostream>
#include "MTL.h"

class MySharedObject : public MTL::MTLSharedObject
{
public:
    MySharedObject(unsigned int id) : MTLSharedObject(id)
    {
        std::cout << "MySharedObject::MySharedObject()" << std::endl;
        value = 0;
    }
    ~MySharedObject()
    {
        std::cout << "MySharedObject::~MySharedObject()" << std::endl;
    }

    int getValue()
    {
        return value;
    }
    void setValue(int v)
    {
        value = v;
    }

private:
    int value;
};

class MyRunnable : public MTL::MTLRunnable
{
public:
    MyRunnable(MTL::MTLSharedMemory *sharedMemory) : m_sharedMemory(sharedMemory){};
    virtual ~MyRunnable() = default;
    void run(MTL::MTLThreadInterface *threadIf)
    {
        std::cout << "Hello World!" << std::endl;
        int counter = 0;
        while (true)
        {
            if (threadIf->getThreadState() == MTL::E_MTLThreadState::STOPPED)
            {
                std::cout << "Stopped Thread Id: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else if (threadIf->getThreadState() == MTL::E_MTLThreadState::SUSPENDED)
            {
                std::cout << "Suspended Thread Id: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else if (threadIf->getThreadState() == MTL::E_MTLThreadState::EXITED)
            {
                std::cout << "Exited Thread Id: " << std::this_thread::get_id() << std::endl;
                break;
            }
            else if (threadIf->getThreadState() == MTL::E_MTLThreadState::RUNNING)
            {
                MySharedObject &myObj = dynamic_cast<MySharedObject &>(m_sharedMemory->getSharedObjectById(1));
                std::cout << "Thread Id: " << std::this_thread::get_id() << " starting Value: " << myObj.getValue() << " end Value: " << myObj.getValue() + 1 << std::endl;
                myObj.setValue(myObj.getValue() + 1);
                m_sharedMemory->releaseSharedObject(myObj);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                counter++;
            }
        }
    }

    void stop()
    {
        std::cout << "Stopping" << std::endl;
    }

    void suspend()
    {
        std::cout << "Suspending" << std::endl;
    }

    void resume()
    {
        std::cout << "Resuming" << std::endl;
    }

    void clean_exit()
    {
        std::cout << "Exiting" << std::endl;
    }

    void force_exit()
    {
        std::cout << "Force Exiting" << std::endl;
    }

private:
    MTL::MTLSharedMemory *m_sharedMemory;
};

int main()
{
    std::cout << "Running Example 5 for MTL Version " << MTL_VERSION_MAJOR << "." << MTL_VERSION_MINOR << "." << MTL_VERSION_PATCH << std::endl;
    std::unique_ptr<MySharedObject> myObj(new MySharedObject(1));
    MTL::MTLSharedMemory sharedMemory;
    sharedMemory.addSharedObject(std::move(myObj));
    MyRunnable myRunnable1(&sharedMemory);
    MyRunnable myRunnable2(&sharedMemory);

    MTL::MTLThread thread1(myRunnable1);
    MTL::MTLThread thread2(myRunnable2);
    thread1.run();
    thread2.run();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Suspend Thread 1" << std::endl;
    thread1.suspend();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Resume Thread 1" << std::endl;
    thread1.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Exit the Threads" << std::endl;
    thread1.clean_exit();
    thread2.clean_exit();

    thread1.join();
    thread2.join();

    std::cout << "Threads Joined" << std::endl;

    return 0;
}