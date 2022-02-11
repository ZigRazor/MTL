#ifndef __MTL__MTLTHREAD__
#define __MTL__MTLTHREAD__

#pragma once

#include "Runnable.h"
#include "MTLThreadInterface.h"
#include <thread>
#include <mutex>

namespace MTL
{

    class MTLThread : public Runnable, public MTLThreadInterface
    {
    public:
        MTLThread(Runnable &runnable);
        virtual ~MTLThread();

        virtual void run(MTLThreadInterface* threadIf = nullptr);
        virtual void suspend();
        virtual void resume();
        virtual void stop();
        virtual void clean_exit();
        virtual void force_exit();

        bool isRunning();

        void join();

        Runnable &getRunnableReference();

        E_MTLThreadState getThreadState();
        void setThreadState(E_MTLThreadState threadState);

    private:
        E_MTLThreadState m_threadState;
        std::mutex m_threadState_mutex;
        std::unique_ptr<std::thread> m_thread_ptr;
        Runnable &m_runnable;
    };

}
#endif // __MTL__MTLTHREAD__