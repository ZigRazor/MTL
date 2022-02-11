#ifndef __MTL__MTLTHREADMANAGER__
#define __MTL__MTLTHREADMANAGER__

#pragma once

#include "MTLThread.h"
#include <vector>
#include <mutex>

namespace MTL
{
    class MTLThreadManager : public Runnable
    {
    public:
        MTLThreadManager();
        virtual ~MTLThreadManager();

        virtual void run(MTLThreadInterface* threadIf);
        virtual void suspend();
        virtual void resume();
        virtual void stop();
        virtual void clean_exit();
        virtual void force_exit();

        void addThread(std::unique_ptr<MTLThread> thread);

        void setSleepTime(int sleep_time);

    protected:
        std::vector<std::unique_ptr<MTLThread>> m_threads;
        std::mutex m_threads_mutex;
    private:       

        unsigned int m_sleep_time;
    };
}

#endif // __MTL__MTLTHREADMANAGER__