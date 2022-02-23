#ifndef MTLTHREADPOOL_H
#define MTLTHREADPOOL_H

#pragma once

#include "MTLTypedefs.h"
#include "MTLThreadManager.h"
#include "MTLWorkerThread.h"

namespace MTL
{
    /**
     * @brief Class that implements a thread pool.
     *
     * This class is a thread pool that can be used to manage threads.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLThreadPool : public MTLThreadManager
    {

    public:
        /**
         * @brief Construct a new MTLThreadPool object
         *
         * @param worker worker thread for the thread pool.
         * @param num_threads number of threads in the thread pool.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLThreadPool(MTLWorkerThread &worker, unsigned int num_threads);
        /**
         * @brief Destroy the MTLThreadPool object
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        ~MTLThreadPool();

        /**
         * @brief Dispatch a message to the thread pool.
         *
         * @param message Message to dispatch.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void onMessage(Message &message);

    private:
        std::mutex m_onMessage_mutex;  /**< Mutex for the onMessage method. */
        unsigned int m_num_threads;    /**< Number of threads in the thread pool. */
        unsigned int m_current_thread; /**< Current thread in the thread pool. */
        MTLWorkerThread &worker;       /**< Worker thread for the thread pool. */
    };

}

#endif // MTLTHREADPOOL_H
