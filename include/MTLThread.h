#ifndef MTLTHREAD_H
#define MTLTHREAD_H

#pragma once

#include "MTLRunnable.h"
#include "MTLThreadInterface.h"
#include <thread>
#include <mutex>

namespace MTL
{
    /**
     * @brief Class that implements a thread.
     *
     * This class is a thread that can be used to run a task.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLThread : public MTLRunnable, public MTLThreadInterface
    {
    public:
        /**
         * @brief Construct a new MTLThread object.
         *
         * @param runnable the runnable object to run.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLThread(MTLRunnable &runnable);
        /**
         * @brief Destroy the MTLThread object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual ~MTLThread();

        /**
         * @brief Start the thread.
         *
         * @param threadIf The thread interface.
         *
         * @author @ZigRazor
         *  @date 2020-02-16
         */
        virtual void run(MTLThreadInterface *threadIf = nullptr);
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
         * @brief Check if the thread is running.
         *
         * @return true if the thread is running.
         * @return false if the thread is not running.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        bool isRunning();

        /**
         * @brief Join the thread.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void join();

        /**
         * @brief Get the Runnable Reference object
         *
         * @return Runnable& get the Runnable Reference object
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLRunnable &getRunnableReference();

        /**
         * @brief Get the Thread State
         *
         * @return E_MTLThreadState Thread State
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        E_MTLThreadState getThreadState();

        /**
         * @brief Set the Thread State object
         *
         * @param threadState the Thread State to set
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void setThreadState(E_MTLThreadState threadState);

    private:
        E_MTLThreadState m_threadState;            //!< The thread state.
        std::mutex m_threadState_mutex;            //!< The mutex for the thread state.
        std::unique_ptr<std::thread> m_thread_ptr; //!< The thread pointer.
        MTLRunnable &m_runnable;                   //!< The runnable object.
    };

}

#endif // MTLTHREAD_H
