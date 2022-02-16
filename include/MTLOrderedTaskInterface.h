#ifndef __MTL__MTLORDEREDTASKINTERFACE__
#define __MTL__MTLORDEREDTASKINTERFACE__

#include "MTLTypedefs.h"
#include <unordered_map>

namespace MTL{
    class MTLOrderedTaskInterface{
        
    public:
        virtual std::shared_ptr<void> getPredecessorResult(const TaskName &taskName) = 0;
        virtual const std::unordered_map<TaskName, std::shared_ptr<void>>& getPredecessorsResults() = 0;
        virtual TaskName getTaskName() = 0;
    private:
        
    };
}

#endif /* __MTL__MTLORDEREDTASKINTERFACE__ */
