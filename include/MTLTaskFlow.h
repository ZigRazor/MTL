#ifndef __MTL__MTLTASKFLOW__
#define __MTL__MTLTASKFLOW__

#pragma once

#include "MTLOrderedTask.h"

namespace MTL{

    class MTLTaskFlow : public MTLOrderedTask{
    public:
        MTLTaskFlow(const TaskName& taskName = "");
        virtual ~MTLTaskFlow();
        
        virtual std::shared_ptr<void> run(MTLTaskInterface* interface = nullptr);
        virtual std::shared_ptr<void> getResult();
        virtual void waitResult();

        void precede(std::shared_ptr<MTLOrderedTask> taskA, std::shared_ptr<MTLOrderedTask> taskB);
        void succeed(std::shared_ptr<MTLOrderedTask> taskA, std::shared_ptr<MTLOrderedTask> taskB);
        
    private:

        std::unordered_map<TaskName, std::shared_ptr<MTLOrderedTask>> m_orderedTasks;        
    };

}


#endif /* __MTL__MTLTASKFLOW__ */
