#ifndef MTLWORKERTHREAD_H
#define MTLWORKERTHREAD_H

#pragma once

#include "MTLRunnable.h"
#include "MTLMessageQueue.h"
#include "MTLWorker.h"

namespace MTL
{
    /**
     * @brief Class that implements a Worker Thread.
     *
     * This class is a Worker Thread that can be used to run a task.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLWorkerThread : public MTLRunnable, public MTLWorker, public MTLMessageQueue
    {
    public:
        /**
         * @brief Construct a new MTLWorkerThread object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLWorkerThread();
        /**
         * @brief Destroy the MTLWorkerThread object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual ~MTLWorkerThread();
        /**
         * @brief Start the thread.
         *
         * @param threadIf The thread interface.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void run(MTLThreadInterface *threadIf);
        /**
         * @brief Suspend the thread.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void suspend();
        /**
         * @brief Resume the thread.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void resume();
        /**
         * @brief Stop the thread.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void stop();
        /**
         * @brief A clean Exit of the Thread.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void clean_exit();
        /**
         * @brief Force the thread to exit.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void force_exit();

        /**
         * @brief Set the Sleep Time
         *
         * @param sleep_time sleep time in milliseconds.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void setSleepTime(int sleep_time);

    protected:
        /**
         * @brief Process the message Message
         *
         * @param message The message to process.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void processMessage(Message message) = 0;

    private:
        unsigned int m_sleep_time; /**< Sleep time in milliseconds. */
    };

}

#endif // MTLWORKERTHREAD_H
