#include "MTLOrderedTask.h"

namespace MTL
{
    MTLOrderedTask::MTLOrderedTask(const TaskName &taskName, MTLRunnableTask &runnableTask) : MTLTask(runnableTask), m_name(taskName), m_predecessor(), m_successor()
    {
    }

    MTLOrderedTask::~MTLOrderedTask()
    {
    }

    std::shared_ptr<void> MTLOrderedTask::run(MTLTaskInterface *interface)
    {
        m_future = std::async(std::launch::async, &MTLRunnableTask::run, &m_runnableTask, this);
        return std::shared_ptr<void>(nullptr);
    }

    TaskName MTLOrderedTask::getTaskName()
    {
        return m_name;
    }

    void MTLOrderedTask::addPredecessor(std::shared_ptr<MTLOrderedTask> task)
    {
        m_predecessor.insert(std::make_pair(task->getTaskName(), task));
    }

    void MTLOrderedTask::addSuccessor(std::shared_ptr<MTLOrderedTask> task)
    {
        m_successor.insert(std::make_pair(task->getTaskName(), task));
    }

    std::shared_ptr<void> MTLOrderedTask::getPredecessorResult(const TaskName &taskName)
    {
        if (m_predecessor.find(taskName) != m_predecessor.end())
        {
            return m_predecessor.at(taskName)->getResult();
        }
        return nullptr;
    }

    const std::unordered_map<TaskName, std::shared_ptr<void>> &MTLOrderedTask::getPredecessorsResults()
    {
        for (auto it = m_predecessor.begin(); it != m_predecessor.end(); ++it)
        {
            m_predecessorResults.insert(std::make_pair(it->first, it->second->getResult()));
        }
        return m_predecessorResults;
    }

    bool MTLOrderedTask::hasSuccessor()
    {
        return !m_successor.empty();
    }

}