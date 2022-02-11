#ifndef __MTL__MTLTHREADPOOL__
#define __MTL__MTLTHREADPOOL__

#pragma once

#include "MTLTypedefs.h"
#include "MTLThreadManager.h"
#include "MTLWorkerThread.h"

namespace MTL
{
    /**
     * @brief Class that implements a thread pool.
     *
     */
    class MTLThreadPool : public MTLThreadManager
    {

    public:
        /**
         * @brief Construct a new MTLThreadPool object
         *
         * @param worker worker thread for the thread pool.
         * @param num_threads number of threads in the thread pool.
         */
        MTLThreadPool(MTLWorkerThread &worker, unsigned int num_threads);
        /**
         * @brief Destroy the MTLThreadPool object
         *
         */
        ~MTLThreadPool();

        /**
         * @brief Dispatch a message to the thread pool.
         *
         * @param message Message to dispatch.
         */
        virtual void onMessage(Message &message);

    private:
        std::mutex m_onMessage_mutex;
        unsigned int m_num_threads;
        unsigned int m_current_thread;
        MTLWorkerThread &worker;
    };

}
#endif // __MTL__MTLTHREADPOOL__