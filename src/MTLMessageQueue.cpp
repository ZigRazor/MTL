#include "MTLMessageQueue.h"

namespace MTL
{

    MTLMessageQueue::MTLMessageQueue() : m_queue_mutex(), m_queue()
    {
    }

    MTLMessageQueue::~MTLMessageQueue()
    {
    }

    void MTLMessageQueue::pushMessage(Message message)
    {
        std::lock_guard<std::mutex> lock(m_queue_mutex);
        m_queue.push(message);
    }

    Message MTLMessageQueue::popMessage()
    {
        std::lock_guard<std::mutex> lock(m_queue_mutex);
        Message message = m_queue.front();
        m_queue.pop();
        return message;
    }

    bool MTLMessageQueue::isEmpty()
    {
        std::lock_guard<std::mutex> lock(m_queue_mutex);
        return m_queue.empty();
    }

    void MTLMessageQueue::clear()
    {
        std::lock_guard<std::mutex> lock(m_queue_mutex);
        while (!m_queue.empty())
        {
            m_queue.pop();
        }
    }

    unsigned int MTLMessageQueue::getQueueSize()
    {
        std::lock_guard<std::mutex> lock(m_queue_mutex);
        return m_queue.size();
    }

}