#include "MTLTask.h"

namespace MTL
{
    MTLTask::MTLTask(RunnableTask &runnableTask)
    {
        m_future = std::async(std::launch::async, &RunnableTask::run, &runnableTask);
    }

    MTLTask::~MTLTask()
    {
    }

    std::shared_ptr<void> MTLTask::getFuture()
    {
        return m_future.get();
    }

}