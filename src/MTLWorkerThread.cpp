#include "MTLWorkerThread.h"
#include <chrono>
#include <thread>

namespace MTL
{

    MTLWorkerThread::MTLWorkerThread() : MTLRunnable(), MTLWorker(), MTLMessageQueue(), m_sleep_time(100)
    {
    }

    MTLWorkerThread::~MTLWorkerThread()
    {
    }

    void MTLWorkerThread::run(MTLThreadInterface *threadIf)
    {
        while (threadIf->getThreadState() != E_MTLThreadState::FORCE_EXITED)
        {
            if (threadIf->getThreadState() == E_MTLThreadState::EXITED && isEmpty())
            {
                return;
            }
            if (isEmpty() || threadIf->getThreadState() == E_MTLThreadState::SUSPENDED || threadIf->getThreadState() == E_MTLThreadState::STOPPED)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(m_sleep_time));
            }
            else
            {
                Message message = popMessage();
                if (message != nullptr)
                {
                    processMessage(message);
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::microseconds(m_sleep_time));
                }
            }
        }
    }

    void MTLWorkerThread::suspend()
    {
    }

    void MTLWorkerThread::resume()
    {
    }

    void MTLWorkerThread::stop()
    {
    }

    void MTLWorkerThread::clean_exit()
    {
    }

    void MTLWorkerThread::force_exit()
    {
    }

    void MTLWorkerThread::setSleepTime(int sleep_time)
    {
        m_sleep_time = sleep_time;
    }
}