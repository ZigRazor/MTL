#ifndef MTLTHREADINTERFACE_H
#define MTLTHREADINTERFACE_H

#pragma once

#include "MTLTypedefs.h"

namespace MTL
{
    /**
     * @brief Class that implements a thread interface.
     *
     * This class is a thread interface that can be used to run a task.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLThreadInterface
    {
    public:
        /**
         * @brief Check if the thread is running.
         *
         * @return true if the thread is running.
         * @return false if the thread is not running.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual bool isRunning() = 0;
        /**
         * @brief Get the Thread State object
         *
         * @return E_MTLThreadState the state of the thread.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual E_MTLThreadState getThreadState() = 0;
        /**
         * @brief Set the Thread State object
         *
         * @param threadState the Thread State to set
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void setThreadState(E_MTLThreadState threadState) = 0;
    };
}

#endif // MTLTHREADINTERFACE_H
