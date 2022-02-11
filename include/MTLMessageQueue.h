#ifndef __MTL__MTLMESSAGEQUEUE__
#define __MTL__MTLMESSAGEQUEUE__

#pragma once

#include <mutex>
#include <queue>
#include "MTLTypedefs.h"

namespace MTL
{
    class MTLMessageQueue
    {
    public:
        MTLMessageQueue();
        virtual ~MTLMessageQueue();

        virtual void pushMessage(Message message);
        virtual Message popMessage();
        virtual bool isEmpty();
        virtual void clear();
        virtual unsigned int getQueueSize();

    private:
        std::mutex m_queue_mutex;
        std::queue<Message> m_queue;
    };
}

#endif // __MTL__MTLMESSAGEQUEUE__