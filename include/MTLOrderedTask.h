#ifndef __MTL__MTLORDEREDTASK__
#define __MTL__MTLORDEREDTASK__

#pragma once

#include "MTLTask.h"
#include "MTLOrderedTaskInterface.h"
#include "MTLTypedefs.h"
#include <unordered_map>

namespace MTL{
    class MTLOrderedTask : public MTLTask, public MTLOrderedTaskInterface{
    
    public:
        MTLOrderedTask(const TaskName& taskname,RunnableTask &runnableTask);
        virtual ~MTLOrderedTask();
        
        virtual std::shared_ptr<void> run(MTLTaskInterface* interface = nullptr);

        TaskName getTaskName();
        
        void addPredecessor(std::shared_ptr<MTLOrderedTask> task);
        void addSuccessor(std::shared_ptr<MTLOrderedTask> task);

        std::shared_ptr<void> getPredecessorResult(const TaskName &taskName);
        const std::unordered_map<TaskName, std::shared_ptr<void>>& getPredecessorsResults();
        bool hasSuccessor();

    private:
        TaskName m_name;
        std::unordered_map<TaskName, std::shared_ptr<MTLOrderedTask>> m_predecessor;
        std::unordered_map<TaskName, std::shared_ptr<MTLOrderedTask>> m_successor;
        std::unordered_map<TaskName, std::shared_ptr<void>> m_predecessorResults;
    };
}

#endif /*__MTL__MTLORDEREDTASK__*/