#ifndef __MTL__MTLTHREADPOOL__
#define __MTL__MTLTHREADPOOL__

#pragma once

#include "MTLTypedefs.h"
#include "MTLThreadManager.h"
#include "MTLWorkerThread.h"

namespace MTL
{
    class MTLThreadPool : public MTLThreadManager
    {

    public:
        MTLThreadPool(MTLWorkerThread& worker, unsigned int num_threads);
        ~MTLThreadPool();

        virtual void onMessage(Message &message);

    private:
        std::mutex m_onMessage_mutex;
        unsigned int m_num_threads;
        unsigned int m_current_thread;
        MTLWorkerThread& worker;
    };
    
}
#endif // __MTL__MTLTHREADPOOL__