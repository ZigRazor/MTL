#ifndef MTLORDEREDTASKINTERFACE_H
#define MTLORDEREDTASKINTERFACE_H

#pragma once

#include "MTLTypedefs.h"
#include <unordered_map>

namespace MTL
{
    /**
     * @brief The MTLOrderedTaskInterface Interface Class
     *
     * This class is the interface for the MTLOrderedTask class.
     *
     * @author @ZigRazor
     * @date 2022-02-16
     */
    class MTLOrderedTaskInterface
    {

    public:
        /**
         * @brief Get the Predecessor Result object
         *
         * @param taskName The name of the predecessor task
         * @return std::shared_ptr<void>  The result of the predecessor task
         *
         * @author @ZigRazor
         * @date 2022-02-16
         */
        virtual std::shared_ptr<void> getPredecessorResult(const TaskName &taskName) = 0;

        /**
         * @brief Get the Predecessors Results object
         *
         * @return const std::unordered_map<TaskName, std::shared_ptr<void>>& The predecessors results
         *
         * @author @ZigRazor
         * @date 2022-02-16
         */
        virtual const std::unordered_map<TaskName, std::shared_ptr<void>> &getPredecessorsResults() = 0;

        /**
         * @brief Get the Task Name
         *
         * @return const TaskName& The name of the task
         *
         * @author @ZigRazor
         * @date 2022-02-16
         */
        virtual TaskName getTaskName() = 0;
    };
}

#endif // MTLORDEREDTASKINTERFACE_H
