#include <iostream>
#include "MTL.h"

class MyRunnableTask : public MTL::MTLRunnableTask
{
public:
    MyRunnableTask() = default;
    virtual ~MyRunnableTask() = default;
    std::shared_ptr<void> run(MTL::MTLTaskInterface *interface = nullptr)
    {
        std::cout << "Hello World!" << std::endl;
        std::cout << "Simulating Working for 3 seconds" << std::endl;

        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << std::endl;
        std::cout << "This is a Task that return 1" << std::endl;

        int i = 1;
        std::shared_ptr<void> result(new int(i));
        return result;
    }
};

int main()
{
    std::cout << "Running Example 6 for MTL Version " << MTL_VERSION_MAJOR << "." << MTL_VERSION_MINOR << "." << MTL_VERSION_PATCH << std::endl;
    MyRunnableTask myRunnableTask;
    MTL::MTLTask task(myRunnableTask);
    task.run();
    std::shared_ptr<void> result = task.getResult();
    std::cout << "Result: " << *(static_cast<int *>(result.get())) << std::endl;
    return 0;
}