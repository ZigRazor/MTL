#ifndef MTLTASKFLOW_H
#define MTLTASKFLOW_H

#pragma once

#include "MTLOrderedTask.h"

namespace MTL
{
    /**
     * @brief Task Flow Class
     *
     * This class implement MTLTaskFlow.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLTaskFlow : public MTLOrderedTask
    {
    public:
        /**
         * @brief Construct a new MTLTaskFlow object.
         *
         * @param taskName The task name.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLTaskFlow(const TaskName &taskName = "");
        /**
         * @brief Destroy the MTLTaskFlow object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual ~MTLTaskFlow();

        /**
         * @brief Run the Task Flow
         *
         * @param interface The task interface.
         * @return std::shared_ptr<void> The result of the run.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual std::shared_ptr<void> run(MTLTaskInterface *interface = nullptr);

        /**
         * @brief Get the Result object
         *
         * @return std::shared_ptr<void>  The result of the task execution.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual std::shared_ptr<void> getResult();

        /**
         * @brief Wait for the task to finish.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void waitResult();

        /**
         * @brief Declare the taskA as a predecessor of taskB
         *
         * @param taskA The predecessor task
         * @param taskB The successor task
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void precede(std::shared_ptr<MTLOrderedTask> taskA, std::shared_ptr<MTLOrderedTask> taskB);
        /**
         * @brief Declare the taskA as a successor of taskB
         *
         * @param taskA The successor task
         * @param taskB The predecessor task
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void succeed(std::shared_ptr<MTLOrderedTask> taskA, std::shared_ptr<MTLOrderedTask> taskB);

    private:
        std::unordered_map<TaskName, std::shared_ptr<MTLOrderedTask>> m_orderedTasks; //!< The ordered tasks
    };

}

#endif // MTLTASKFLOW_H
