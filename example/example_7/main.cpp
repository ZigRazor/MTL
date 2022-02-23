#include <iostream>
#include "MTL.h"

class Var2Task : public MTL::MTLRunnableTask
{
public:
    Var2Task() = default;
    virtual ~Var2Task() = default;
    std::shared_ptr<void> run(MTL::MTLTaskInterface *interface = nullptr)
    {
        MTL::MTLOrderedTaskInterface *orderedTaskIf = dynamic_cast<MTL::MTLOrderedTaskInterface *>(interface);
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Start Task " << std::endl
                  << std::flush;
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Simulating Working for 3 seconds" << std::endl
                  << std::flush;

        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << std::endl;

        auto previousResult = orderedTaskIf->getPredecessorsResults();

        std::shared_ptr<void> result(new int(2));
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Result = " << *((int *)(result.get())) << std::endl
                  << std::flush;
        return result;
    }
};

class SumTask : public MTL::MTLRunnableTask
{
public:
    SumTask() = default;
    virtual ~SumTask() = default;
    std::shared_ptr<void> run(MTL::MTLTaskInterface *interface = nullptr)
    {
        MTL::MTLOrderedTaskInterface *orderedTaskIf = dynamic_cast<MTL::MTLOrderedTaskInterface *>(interface);
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Start Task " << std::endl
                  << std::flush;
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Simulating Working for 3 seconds" << std::endl
                  << std::flush;

        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << std::endl;

        auto predecessorsResults = orderedTaskIf->getPredecessorsResults();
        std::shared_ptr<void> result(new int(0));
        if (predecessorsResults.empty())
        {
            std::shared_ptr<void> result(new int(0));
            return result;
        }
        else
        {
            auto it = predecessorsResults.begin();
            std::shared_ptr<void> result((int *)it->second.get());
            ++it;
            for (it; it != predecessorsResults.end(); ++it)
            {
                int *previousResult = (int *)(it->second.get());
                int *currentResult = (int *)(result.get());
                *currentResult = (*currentResult) + (*previousResult);
            }
            std::cout << orderedTaskIf->getTaskName() << ": "
                      << "Result = " << *((int *)(result.get())) << std::endl
                      << std::flush;
            return result;
        }
    }
};

class MulTask : public MTL::MTLRunnableTask
{
public:
    MulTask() = default;
    virtual ~MulTask() = default;
    std::shared_ptr<void> run(MTL::MTLTaskInterface *interface = nullptr)
    {
        MTL::MTLOrderedTaskInterface *orderedTaskIf = dynamic_cast<MTL::MTLOrderedTaskInterface *>(interface);
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Start Task " << std::endl
                  << std::flush;
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Simulating Working for 3 seconds" << std::endl
                  << std::flush;

        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << std::endl
                  << std::flush;

        auto predecessorsResults = orderedTaskIf->getPredecessorsResults();
        std::shared_ptr<void> result(new int(0));
        if (predecessorsResults.empty())
        {
            std::shared_ptr<void> result(new int(0));
            return result;
        }
        else
        {
            auto it = predecessorsResults.begin();
            std::shared_ptr<void> result((int *)it->second.get());
            ++it;
            for (it; it != predecessorsResults.end(); ++it)
            {
                int *previousResult = (int *)(it->second.get());
                int *currentResult = (int *)(result.get());
                *currentResult = (*currentResult) * (*previousResult);
            }
            std::cout << orderedTaskIf->getTaskName() << ": "
                      << "Result = " << *((int *)(result.get())) << std::endl
                      << std::flush;
            return result;
        }
    }
};

// This Example simulate the execution of the following expression ((a+b)+c)*(d+e) where a,b,c,d,e are value 2
int main()
{
    std::cout << "Running Example 7 for MTL Version " << MTL_VERSION_MAJOR << "." << MTL_VERSION_MINOR << "." << MTL_VERSION_PATCH << std::endl;
    Var2Task var2Task;
    SumTask sum2Task;
    MulTask mul2Task;

    auto taskA = std::make_shared<MTL::MTLOrderedTask>("a", var2Task);
    auto taskB = std::make_shared<MTL::MTLOrderedTask>("b", var2Task);
    auto taskC = std::make_shared<MTL::MTLOrderedTask>("c", var2Task);
    auto taskD = std::make_shared<MTL::MTLOrderedTask>("d", var2Task);
    auto taskE = std::make_shared<MTL::MTLOrderedTask>("e", var2Task);

    auto taskF = std::make_shared<MTL::MTLOrderedTask>("f", sum2Task);
    auto taskG = std::make_shared<MTL::MTLOrderedTask>("g", sum2Task);
    auto taskH = std::make_shared<MTL::MTLOrderedTask>("h", sum2Task);

    auto taskI = std::make_shared<MTL::MTLOrderedTask>("i", mul2Task);

    MTL::MTLTaskFlow taskFlow;
    taskFlow.precede(taskA, taskF);
    taskFlow.precede(taskB, taskF);
    taskFlow.precede(taskC, taskG);
    taskFlow.precede(taskF, taskG);
    taskFlow.precede(taskD, taskH);
    taskFlow.precede(taskE, taskH);
    taskFlow.precede(taskG, taskI);
    taskFlow.precede(taskH, taskI);

    taskFlow.run();
    std::shared_ptr<void> result = taskFlow.getResult();
    std::cout << "Result: " << *(static_cast<int *>(result.get())) << std::endl;
    return 0;
}