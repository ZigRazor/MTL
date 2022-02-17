#ifndef RUNNABLETASK_H
#define RUNNABLETASK_H

#pragma once

#include <memory>
#include "MTLTaskInterface.h"

namespace MTL
{
    /**
     * @brief Runnable Task Interface
     *
     * This class is the interface for the RunnableTask class.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLRunnableTask
    {
    public:
        /**
         * @brief The function that represent the task.
         *
         * @return std::shared_ptr<void> the result of the task.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual std::shared_ptr<void> run(MTLTaskInterface *interface = nullptr) = 0;
    };

}

#endif // RUNNABLETASK_H
