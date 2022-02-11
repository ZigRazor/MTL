#ifndef __MTL__MTLTHREAD__
#define __MTL__MTLTHREAD__

#pragma once

#include "Runnable.h"
#include "MTLThreadInterface.h"
#include <thread>
#include <mutex>

namespace MTL
{
    /**
     * @brief Class that implements a thread.
     *
     */
    class MTLThread : public Runnable, public MTLThreadInterface
    {
    public:
        /**
         * @brief Construct a new MTLThread object.
         *
         * @param runnable the runnable object to run.
         */
        MTLThread(Runnable &runnable);
        /**
         * @brief Destroy the MTLThread object.
         *
         */
        virtual ~MTLThread();

        /**
         * @brief Start the thread.
         *
         * @param threadIf The thread interface.
         */
        virtual void run(MTLThreadInterface *threadIf = nullptr);
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
         * @brief Check if the thread is running.
         *
         * @return true if the thread is running.
         * @return false if the thread is not running.
         */
        bool isRunning();

        /**
         * @brief Join the thread.
         *
         */
        void join();

        /**
         * @brief Get the Runnable Reference object
         *
         * @return Runnable& get the Runnable Reference object
         */
        Runnable &getRunnableReference();

        /**
         * @brief Get the Thread State
         *
         * @return E_MTLThreadState Thread State
         */
        E_MTLThreadState getThreadState();

        /**
         * @brief Set the Thread State object
         *
         * @param threadState the Thread State to set
         */
        void setThreadState(E_MTLThreadState threadState);

    private:
        E_MTLThreadState m_threadState;
        std::mutex m_threadState_mutex;
        std::unique_ptr<std::thread> m_thread_ptr;
        Runnable &m_runnable;
    };

}
#endif // __MTL__MTLTHREAD__