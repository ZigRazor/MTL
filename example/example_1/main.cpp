#include <iostream>
#include "MTL.h"

class MyRunnable : public MTL::MTLRunnable
{
public:
    MyRunnable() = default;
    virtual ~MyRunnable() = default;
    void run(MTL::MTLThreadInterface *threadIf)
    {
        std::cout << "Hello World!" << std::endl;
        int counter = 0;
        while (true)
        {
            if (threadIf->getThreadState() == MTL::E_MTLThreadState::STOPPED)
            {
                std::cout << "Stopped" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else if (threadIf->getThreadState() == MTL::E_MTLThreadState::SUSPENDED)
            {
                std::cout << "Suspended" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else if (threadIf->getThreadState() == MTL::E_MTLThreadState::EXITED)
            {
                std::cout << "Exited" << std::endl;
                break;
            }
            else if (threadIf->getThreadState() == MTL::E_MTLThreadState::RUNNING)
            {
                if (counter == 20)
                {
                    threadIf->setThreadState(MTL::E_MTLThreadState::EXITED);
                }
                std::cout << "Running" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                counter++;
            }
        }
    }

    void stop()
    {
        std::cout << "Stop!" << std::endl;
    }

    void suspend()
    {
        std::cout << "Pause!" << std::endl;
    }

    void resume()
    {
        std::cout << "Resume!" << std::endl;
    }

    void clean_exit()
    {
        std::cout << "Clean Exit!" << std::endl;
    }

    void force_exit()
    {
        std::cout << "Force Exit!" << std::endl;
        ::exit(0); // clean Exit
    }
};

int main()
{
    std::cout << "Running Example 1 for MTL Version " << MTL_VERSION_MAJOR << "." << MTL_VERSION_MINOR << "." << MTL_VERSION_PATCH << std::endl;
    MyRunnable myRunnable;
    MTL::MTLThread thread(myRunnable);
    thread.run();
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    thread.suspend();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    thread.resume();
    // thread.force_exit();
    int counter = 0;
    while (thread.isRunning())
    {
        if (counter == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Counter: " << counter << std::endl;
        counter++;
    }
    return 0;
}