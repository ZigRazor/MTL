#ifndef MTLTASK_H
#define MTLTASK_H

#pragma once

#include <future>
#include "MTLTaskInterface.h"
#include "MTLRunnableTask.h"

namespace MTL
{
    /**
     * @brief The Class that represent a task.
     *
     * This class is the base class for all the task.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLTask : public MTLTaskInterface, public MTLRunnableTask
    {
    public:
        /**
         * @brief Construct a new MTLTask object.
         *
         * @param runnableTask The runnable task.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLTask(MTLRunnableTask &runnableTask);
        /**
         * @brief Destroy the MTLTask object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual ~MTLTask();

        /**
         * @brief Execute the task.
         *
         * @return std::shared_ptr<void> The result of the run.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual std::shared_ptr<void> run(MTLTaskInterface *interface = nullptr);

        /**
         * @brief Get the result of the task. When the execution is finished and the result is available.
         *
         * @return std::shared_ptr<void> The result of the task
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual std::shared_ptr<void> getResult();

        /**
         * @brief Wait for the result of the task
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void waitResult();

    protected:
        MTLRunnableTask &m_runnableTask;             //!< The runnable task.
        std::future<std::shared_ptr<void>> m_future; //!< The future object.
        std::mutex m_futureMutex;                    //!< The mutex for the future object.
        std::shared_ptr<void> m_result;              //!< The result of the task.
    };

}

#endif // MTLTASK_H
