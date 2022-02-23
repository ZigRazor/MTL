#include "MTLTaskFlow.h"

namespace MTL
{
    MTLTaskFlow::MTLTaskFlow(const TaskName &taskName) : MTLOrderedTask(taskName, *this)
    {
    }

    MTLTaskFlow::~MTLTaskFlow()
    {
    }

    std::shared_ptr<void> MTLTaskFlow::run(MTLTaskInterface *interface)
    {
        for (auto &task : m_orderedTasks)
        {
            task.second->run();
        }
        return std::shared_ptr<void>(nullptr);
    }

    std::shared_ptr<void> MTLTaskFlow::getResult()
    {
        for (auto &task : m_orderedTasks)
        {
            if (!task.second->hasSuccessor())
            {
                return task.second->getResult();
            }
        }
        return std::shared_ptr<void>(nullptr);
    }

    void MTLTaskFlow::waitResult()
    {
        for (auto &task : m_orderedTasks)
        {
            if (!task.second->hasSuccessor())
            {
                return task.second->waitResult();
            }
        }
    }

    void MTLTaskFlow::precede(std::shared_ptr<MTLOrderedTask> taskA, std::shared_ptr<MTLOrderedTask> taskB)
    {
        taskB->addPredecessor(taskA);
        taskA->addSuccessor(taskB);
        if (m_orderedTasks.find(taskA->getTaskName()) == m_orderedTasks.end())
        {
            m_orderedTasks.insert(std::make_pair(taskA->getTaskName(), taskA));
        }
        if (m_orderedTasks.find(taskB->getTaskName()) == m_orderedTasks.end())
        {
            m_orderedTasks.insert(std::make_pair(taskB->getTaskName(), taskB));
        }
    }

    void MTLTaskFlow::succeed(std::shared_ptr<MTLOrderedTask> taskA, std::shared_ptr<MTLOrderedTask> taskB)
    {
        taskB->addSuccessor(taskA);
        taskA->addPredecessor(taskB);

        if (m_orderedTasks.find(taskA->getTaskName()) == m_orderedTasks.end())
        {
            m_orderedTasks.insert(std::make_pair(taskA->getTaskName(), taskA));
        }
        if (m_orderedTasks.find(taskB->getTaskName()) == m_orderedTasks.end())
        {
            m_orderedTasks.insert(std::make_pair(taskB->getTaskName(), taskB));
        }
    }
}