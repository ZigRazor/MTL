#include "MTLThreadPool.h"
#include "MTLWorkerThread.h"
#include <limits>

namespace MTL
{
    MTLThreadPool::MTLThreadPool(MTLWorkerThread &worker, unsigned int num_threads) : MTLThreadManager(),
                                                                                      m_onMessage_mutex(),
                                                                                      worker(worker)
    {
        m_num_threads = num_threads;
        m_current_thread = 0;

        for (unsigned int i = 0; i < num_threads; i++)
        {
            std::unique_ptr<MTLThread> thread(new MTLThread(worker));
            addThread(std::move(thread));
        }
    }

    MTLThreadPool::~MTLThreadPool()
    {
    }

    void MTLThreadPool::onMessage(Message &message)
    {
        std::lock_guard<std::mutex> lock(m_onMessage_mutex);
        worker.pushMessage(message);
    }
}