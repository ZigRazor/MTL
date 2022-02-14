#ifndef __MTL__MTLTASK__
#define __MTL__MTLTASK__

#pragma once

#include <future>
#include "RunnableTask.h"

namespace MTL
{
    /**
     * @brief The Class that represent a task.
     *
     */
    class MTLTask
    {
    public:
        /**
         * @brief Construct a new MTLTask object.
         *
         * @param runnableTask The runnable task.
         */
        MTLTask(RunnableTask &runnableTask);
        /**
         * @brief Destroy the MTLTask object.
         *
         */
        virtual ~MTLTask();

        /**
         * @brief Get the result of the task. When the execution is finished and the result is available.
         *
         * @return std::shared_ptr<void> The result of the task.
         */
        std::shared_ptr<void> getFuture();

    private:
        std::future<std::shared_ptr<void>> m_future;
    };

}

#endif /* __MTL__MTLTASK__ */
