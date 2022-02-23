#include "MTLThread.h"

namespace MTL
{
    MTLThread::MTLThread(MTLRunnable &runnable) : MTLRunnable(), MTLThreadInterface(), m_threadState(CREATED), m_threadState_mutex(), m_thread_ptr(nullptr), m_runnable(runnable)
    {
    }

    MTLThread::~MTLThread()
    {
        {
            std::lock_guard<std::mutex> lock(m_threadState_mutex);
            m_threadState = EXITED;
        }
        join();
    }

    void MTLThread::run(MTLThreadInterface *threadIf)
    {
        if (!isRunning())
        {
            std::lock_guard<std::mutex> lock(m_threadState_mutex);
            m_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&MTLRunnable::run, &m_runnable, this));
            m_threadState = RUNNING;
        }
    }

    void MTLThread::suspend()
    {
        if (isRunning())
        {
            std::lock_guard<std::mutex> lock(m_threadState_mutex);
            m_threadState = SUSPENDED;
            m_runnable.suspend();
        }
    }

    void MTLThread::resume()
    {
        if (isRunning())
        {
            std::lock_guard<std::mutex> lock(m_threadState_mutex);
            m_threadState = RUNNING;
            m_runnable.resume();
        }
    }

    void MTLThread::stop()
    {
        if (isRunning())
        {
            std::lock_guard<std::mutex> lock(m_threadState_mutex);
            m_threadState = STOPPED;
            m_runnable.stop();
        }
    }

    void MTLThread::clean_exit()
    {
        std::lock_guard<std::mutex> lock(m_threadState_mutex);
        m_threadState = EXITED;
        m_runnable.clean_exit();
    }

    void MTLThread::force_exit()
    {
        std::lock_guard<std::mutex> lock(m_threadState_mutex);
        m_threadState = FORCE_EXITED;
        m_runnable.force_exit();
    }

    bool MTLThread::isRunning()
    {
        std::lock_guard<std::mutex> lock(m_threadState_mutex);
        return m_threadState == RUNNING || m_threadState == SUSPENDED || m_threadState == STOPPED;
    }

    void MTLThread::join()
    {
        if (m_thread_ptr->joinable())
        {
            m_thread_ptr->join();
        }
    }

    MTLRunnable &MTLThread::getRunnableReference()
    {
        return m_runnable;
    }

    E_MTLThreadState MTLThread::getThreadState()
    {
        std::lock_guard<std::mutex> lock(m_threadState_mutex);
        return m_threadState;
    }

    void MTLThread::setThreadState(E_MTLThreadState threadState)
    {
        std::lock_guard<std::mutex> lock(m_threadState_mutex);
        m_threadState = threadState;
    }

}