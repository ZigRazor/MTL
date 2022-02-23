#ifndef MTLTHREADMANAGER_H
#define MTLTHREADMANAGER_H

#pragma once

#include "MTLThread.h"
#include <vector>
#include <mutex>

namespace MTL
{
    /**
     * @brief Class that implements a thread manager.
     *
     * This class is a thread manager that can be used to manage threads.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLThreadManager : public MTLRunnable
    {
    public:
        /**
         * @brief Construct a new MTLThreadManager object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLThreadManager();
        /**
         * @brief Destroy the MTLThreadManager object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual ~MTLThreadManager();

        /**
         * @brief Start the thread manager.
         *
         * @param threadIf the thread interface.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void run(MTLThreadInterface *threadIf);
        /**
         * @brief Suspend the thread manager.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void suspend();
        /**
         * @brief Resume the thread manager.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void resume();
        /**
         * @brief Stop the thread manager.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void stop();
        /**
         * @brief A clean Exit of the thread manager.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void clean_exit();
        /**
         * @brief Force the thread manager to exit.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void force_exit();

        /**
         * @brief Add a thread to the thread manager.
         *
         * @param thread the thread to add.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void addThread(std::unique_ptr<MTLThread> thread);

        /**
         * @brief Set the Sleep Time object
         *
         * @param sleep_time Sleep time in milliseconds.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void setSleepTime(int sleep_time);

    protected:
        std::vector<std::unique_ptr<MTLThread>> m_threads; /**< The threads vector. */
        std::mutex m_threads_mutex;                        /**< The threads mutex. */

    private:
        unsigned int m_sleep_time; /**< The sleep time. */
    };
}

#endif // MTLTHREADMANAGER_H
