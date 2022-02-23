#include "MTLTask.h"
#include <iostream>
namespace MTL
{
    MTLTask::MTLTask(MTLRunnableTask &runnableTask) : m_runnableTask(runnableTask), m_future(), m_futureMutex(), m_result(nullptr)
    {
    }

    MTLTask::~MTLTask()
    {
    }

    std::shared_ptr<void> MTLTask::run(MTLTaskInterface *interface)
    {
        m_future = std::async(std::launch::async, &MTLRunnableTask::run, &m_runnableTask, nullptr);
        return std::shared_ptr<void>(nullptr);
    }

    std::shared_ptr<void> MTLTask::getResult()
    {
        std::lock_guard<std::mutex> lock(m_futureMutex);
        if (m_future.valid())
        {
            m_result = m_future.get();
        }
        return m_result;
    }

    void MTLTask::waitResult()
    {
        m_future.wait();
    }

}