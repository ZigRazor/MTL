#ifndef __MTL__MTLWORKER__
#define __MTL__MTLWORKER__

#pragma once

#include "MTLTypedefs.h"

namespace MTL
{
    /**
     * @brief Worker Interface
     *
     */
    class MTLWorker
    {
    protected:
        /**
         * @brief Process Message
         *
         * @param message The message to process.
         */
        virtual void processMessage(Message message) = 0;
    };
}

#endif // __MTL__MTLWORKER__