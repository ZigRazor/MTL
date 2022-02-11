#ifndef __MTL__MTLTHREADINTERFACE__
#define __MTL__MTLTHREADINTERFACE__

#pragma once

#include "MTLTypedefs.h"

namespace MTL
{
    /**
     * @brief Class that implements a thread interface.
     *
     */
    class MTLThreadInterface
    {
    public:
        /**
         * @brief Checl if the thread is running.
         *
         * @return true if the thread is running.
         * @return false if the thread is not running.
         */
        virtual bool isRunning() = 0;
        /**
         * @brief Get the Thread State object
         *
         * @return E_MTLThreadState the state of the thread.
         */
        virtual E_MTLThreadState getThreadState() = 0;
        /**
         * @brief Set the Thread State object
         *
         * @param threadState the Thread State to set
         */
        virtual void setThreadState(E_MTLThreadState threadState) = 0;
    };
}

#endif /* __MTL__MTLTHREADINTERFACE__ */
