#ifndef MTLORDEREDTASK_H
#define MTLORDEREDTASK_H

#pragma once

#include "MTLTask.h"
#include "MTLOrderedTaskInterface.h"
#include "MTLTypedefs.h"
#include <unordered_map>

namespace MTL
{
    /**
     * @brief Ordered Task
     *
     * This class is the implementation of the MTLOrderedTask.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLOrderedTask : public MTLTask, public MTLOrderedTaskInterface
    {

    public:
        /**
         * @brief Constructor
         *
         * @param taskName The name of the task.
         * @param runnableTask The runnable task.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLOrderedTask(const TaskName &taskname, MTLRunnableTask &runnableTask);

        /**
         * @brief Destructor
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual ~MTLOrderedTask();

        /**
         * @brief Run the task
         *
         * @param interface Task Interface
         * @return std::shared_ptr<void> The result of the run
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual std::shared_ptr<void> run(MTLTaskInterface *interface = nullptr);

        /**
         * @brief Get the Task Name
         *
         * @return TaskName The Task Name
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        TaskName getTaskName();

        /**
         * @brief Add a predecessor task
         *
         * @param task The predecessor task
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void addPredecessor(std::shared_ptr<MTLOrderedTask> task);

        /**
         * @brief Add a successor task
         *
         * @param task The successor task
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void addSuccessor(std::shared_ptr<MTLOrderedTask> task);

        /**
         * @brief Get the Predecessor Result object
         *
         * @param taskName The name of the predecessor task
         * @return std::shared_ptr<void>  The result of the predecessor task
         *
         * @author @ZigRazor
         * @date 2022-02-16
         */
        std::shared_ptr<void> getPredecessorResult(const TaskName &taskName);

        /**
         * @brief Get the Predecessors Results object
         *
         * @return const std::unordered_map<TaskName, std::shared_ptr<void>>& The predecessors results
         *
         * @author @ZigRazor
         * @date 2022-02-16
         */
        const std::unordered_map<TaskName, std::shared_ptr<void>> &getPredecessorsResults();

        /**
         * @brief Check if the task has Successors
         *
         * @return true If the task has successors
         * @return false Otherwise
         */
        bool hasSuccessor();

    private:
        TaskName m_name;                                                             /**< The name of the task */
        std::unordered_map<TaskName, std::shared_ptr<MTLOrderedTask>> m_predecessor; /**< The predecessor tasks */
        std::unordered_map<TaskName, std::shared_ptr<MTLOrderedTask>> m_successor;   /**< The successor tasks */
        std::unordered_map<TaskName, std::shared_ptr<void>> m_predecessorResults;    /**< The predecessor results */
    };
}

#endif // MTLORDEREDTASK_H
