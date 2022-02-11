#ifndef __MTL__MTLWORKERTHREAD__
#define __MTL__MTLWORKERTHREAD__

#pragma once

#include "Runnable.h"
#include "MTLMessageQueue.h"
#include "MTLWorker.h"

namespace MTL
{
    /**
     * @brief Class that implements a Worker Thread.
     *
     */
    class MTLWorkerThread : public Runnable, public MTLWorker, public MTLMessageQueue
    {
    public:
        /**
         * @brief Construct a new MTLWorkerThread object.
         *
         */
        MTLWorkerThread();
        /**
         * @brief Destroy the MTLWorkerThread object.
         *
         */
        virtual ~MTLWorkerThread();
        /**
         * @brief Start the thread.
         *
         * @param threadIf The thread interface.
         */
        virtual void run(MTLThreadInterface *threadIf);
        /**
         * @brief Suspend the thread.
         *
         */
        virtual void suspend();
        /**
         * @brief Resume the thread.
         *
         */
        virtual void resume();
        /**
         * @brief Stop the thread.
         *
         */
        virtual void stop();
        /**
         * @brief A clean Exit of the Thread.
         *
         */
        virtual void clean_exit();
        /**
         * @brief Force the thread to exit.
         *
         */
        virtual void force_exit();

        /**
         * @brief Set the Sleep Time
         *
         * @param sleep_time sleep time in milliseconds.
         */
        void setSleepTime(int sleep_time);

    protected:
        /**
         * @brief Process the message Message
         *
         * @param message The message to process.
         */
        virtual void processMessage(Message message) = 0;

    private:
        unsigned int m_sleep_time;
    };

}

#endif // __MTL__MTLWORKERTHREAD__