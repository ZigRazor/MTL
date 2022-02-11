#ifndef __MTL__MTLTHREADMANAGER__
#define __MTL__MTLTHREADMANAGER__

#pragma once

#include "MTLThread.h"
#include <vector>
#include <mutex>

namespace MTL
{
    /**
     * @brief Class that implements a thread manager.
     *
     */
    class MTLThreadManager : public Runnable
    {
    public:
        /**
         * @brief Construct a new MTLThreadManager object.
         *
         */
        MTLThreadManager();
        /**
         * @brief Destroy the MTLThreadManager object.
         *
         */
        virtual ~MTLThreadManager();

        /**
         * @brief Start the thread manager.
         *
         * @param threadIf the thread interface.
         */
        virtual void run(MTLThreadInterface *threadIf);
        /**
         * @brief Suspend the thread manager.
         *
         */
        virtual void suspend();
        /**
         * @brief Resume the thread manager.
         *
         */
        virtual void resume();
        /**
         * @brief Stop the thread manager.
         *
         */
        virtual void stop();
        /**
         * @brief A clean Exit of the thread manager.
         *
         */
        virtual void clean_exit();
        /**
         * @brief Force the thread manager to exit.
         *
         */
        virtual void force_exit();

        /**
         * @brief Add a thread to the thread manager.
         *
         * @param thread the thread to add.
         */
        void addThread(std::unique_ptr<MTLThread> thread);

        /**
         * @brief Set the Sleep Time object
         *
         * @param sleep_time Sleep time in milliseconds.
         */
        void setSleepTime(int sleep_time);

    protected:
        std::vector<std::unique_ptr<MTLThread>> m_threads;
        std::mutex m_threads_mutex;

    private:
        unsigned int m_sleep_time;
    };
}

#endif // __MTL__MTLTHREADMANAGER__