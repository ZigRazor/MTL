#ifndef __MTL__MTLMESSAGEQUEUE__
#define __MTL__MTLMESSAGEQUEUE__

#pragma once

#include <mutex>
#include <queue>
#include "MTLTypedefs.h"

namespace MTL
{
    /**
     * @brief Class that implements a message queue.
     *
     */
    class MTLMessageQueue
    {
    public:
        /**
         * @brief Construct a new MTLMessageQueue object.
         *
         */
        MTLMessageQueue();
        /**
         * @brief Destroy the MTLMessageQueue object.
         *
         */
        virtual ~MTLMessageQueue();
        /**
         * @brief Add a message to the queue.
         *
         * @param message The message to add.
         */
        virtual void pushMessage(Message message);
        /**
         * @brief Get the next message from the queue.
         *
         * @return Message The next message.
         */
        virtual Message popMessage();
        /**
         * @brief Check if the queue is empty.
         *
         * @return true The queue is empty.
         * @return false The queue is not empty.
         */
        virtual bool isEmpty();
        /**
         * @brief Clear the Queue
         *
         */
        virtual void clear();
        /**
         * @brief Get the Queue Size object
         *
         * @return unsigned int The size of the queue.
         */
        virtual unsigned int getQueueSize();

    private:
        std::mutex m_queue_mutex;
        std::queue<Message> m_queue;
    };
}

#endif // __MTL__MTLMESSAGEQUEUE__