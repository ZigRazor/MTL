#ifndef MTLWORKER_H
#define MTLWORKER_H

#pragma once

#include "MTLTypedefs.h"

namespace MTL
{
    /**
     * @brief Worker Interface
     *
     * This class is the interface for the MTLWorker class.
     */
    class MTLWorker
    {
    protected:
        /**
         * @brief Process Message
         *
         * @param message The message to process.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void processMessage(Message message) = 0;
    };
}

#endif // MTLWORKER_H
