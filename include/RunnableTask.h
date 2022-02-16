#ifndef __MTL__RUNNABLETASK__
#define __MTL__RUNNABLETASK__

#pragma once

#include <memory>
#include "MTLTaskInterface.h"

namespace MTL
{
    /**
     * @brief Runnable Task Interface
     *
     */
    class RunnableTask
    {
    public:
        /**
         * @brief The function that represent the task.
         * 
         * @return std::shared_ptr<void> the result of the task.
         */
        virtual std::shared_ptr<void> run(MTLTaskInterface* interface = nullptr) = 0;
    };

}

#endif /* __MTL__RUNNABLETASK__ */
