#ifndef __MTL__MTLTASK__
#define __MTL__MTLTASK__

#pragma once

#include <future>
#include "MTLTaskInterface.h"
#include "RunnableTask.h"

namespace MTL
{
    /**
     * @brief The Class that represent a task.
     *
     */
    class MTLTask : public MTLTaskInterface, public RunnableTask
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
         * @brief Execute the task.
         *
         */
        virtual std::shared_ptr<void> run(MTLTaskInterface* interface = nullptr);

        /**
         * @brief Get the result of the task. When the execution is finished and the result is available.
         *
         * @return std::shared_ptr<void> The result of the task.
         */
        virtual std::shared_ptr<void> getResult();

        /**
         * @brief Wait for the result of the task
         *
         */
        virtual void waitResult();

    protected:
        RunnableTask& m_runnableTask;
        std::future<std::shared_ptr<void>> m_future;
        std::mutex m_futureMutex;
        std::shared_ptr<void> m_result;
    };

}

#endif /* __MTL__MTLTASK__ */
