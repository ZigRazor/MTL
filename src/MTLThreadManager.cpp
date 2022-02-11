#include "MTLThreadManager.h"

namespace MTL
{
    MTLThreadManager::MTLThreadManager() : m_threads(), m_threads_mutex(), m_sleep_time(100)
    {
    }

    MTLThreadManager::~MTLThreadManager()
    {
    }

    void MTLThreadManager::run(MTLThreadInterface *threadIf)
    {
        while (threadIf->getThreadState() != E_MTLThreadState::FORCE_EXITED && threadIf->getThreadState() != E_MTLThreadState::EXITED)
        {

            if (threadIf->getThreadState() == E_MTLThreadState::SUSPENDED || threadIf->getThreadState() == E_MTLThreadState::STOPPED)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(m_sleep_time));
            }
            else // RUNNING
            {
                std::lock_guard<std::mutex> lock(m_threads_mutex);
                for (auto it = m_threads.begin(); it != m_threads.end();)
                {
                    if ((*it)->getThreadState() == E_MTLThreadState::CREATED)
                    {
                        // if a thread is added to the thread manager, it is automatically started
                        (*it)->run(it->get());
                    }
                    else if (!(*it)->isRunning())
                    {
                        // if a thread is not running delete it!
                        it = m_threads.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(m_sleep_time));
            }
        }
        std::lock_guard<std::mutex> lock(m_threads_mutex);
        for (auto it = m_threads.begin(); it != m_threads.end(); ++it)
        {
            (*it)->join();
        }
        for (auto it = m_threads.begin(); it != m_threads.end();)
        {
            if (!(*it)->isRunning())
            {
                it = m_threads.erase(it);
            }
            else
            {
                ++it;
            }
        }
        return;
    }

    void MTLThreadManager::suspend()
    {
    }

    void MTLThreadManager::resume()
    {
    }

    void MTLThreadManager::stop()
    {
    }

    void MTLThreadManager::clean_exit()
    {
        std::lock_guard<std::mutex> lock(m_threads_mutex);
        for (auto it = m_threads.begin(); it != m_threads.end(); ++it)
        {
            if ((*it)->getThreadState() == E_MTLThreadState::CREATED)
            {
                // if a thread is added to the thread manager, it is automatically started
                (*it)->run(it->get());
            }
        }
        for (auto it = m_threads.begin(); it != m_threads.end(); ++it)
        {
            (*it)->clean_exit();
        }
    }

    void MTLThreadManager::force_exit()
    {
        std::lock_guard<std::mutex> lock(m_threads_mutex);
        for (auto it = m_threads.begin(); it != m_threads.end(); ++it)
        {
            (*it)->force_exit();
        }
    }

    void MTLThreadManager::setSleepTime(int sleep_time)
    {
        m_sleep_time = sleep_time;
    }

    void MTLThreadManager::addThread(std::unique_ptr<MTLThread> thread)
    {
        std::lock_guard<std::mutex> lock(m_threads_mutex);
        m_threads.push_back(std::move(thread));
    }

}