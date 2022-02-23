#ifndef MTLMESSAGEQUEUE_H
#define MTLMESSAGEQUEUE_H

#pragma once

#include <mutex>
#include <queue>
#include "MTLTypedefs.h"

namespace MTL
{
    /**
     * @brief Class that implements a message queue.
     *
     * This class is a message queue that can be used to send messages to a thread.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLMessageQueue
    {
    public:
        /**
         * @brief Construct a new MTLMessageQueue object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         *
         */
        MTLMessageQueue();
        /**
         * @brief Destroy the MTLMessageQueue object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual ~MTLMessageQueue();
        /**
         * @brief Add a message to the queue.
         *
         * @param message The message to add.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void pushMessage(Message message);
        /**
         * @brief Get the next message from the queue.
         *
         * @return Message The next message.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual Message popMessage();
        /**
         * @brief Check if the queue is empty.
         *
         * @return true The queue is empty.
         * @return false The queue is not empty.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual bool isEmpty();
        /**
         * @brief Clear the Queue
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void clear();
        /**
         * @brief Get the Queue Size object
         *
         * @return unsigned int The size of the queue.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual unsigned int getQueueSize();

    private:
        std::mutex m_queue_mutex;    //!< The mutex for the queue.
        std::queue<Message> m_queue; //!< The queue.
    };
}

#endif // MTLMESSAGEQUEUE_H
