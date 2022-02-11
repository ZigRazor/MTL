#ifndef __MTL__MTLWORKER__
#define __MTL__MTLWORKER__

#pragma once

#include "MTLTypedefs.h"

namespace MTL{
    class MTLWorker{
        protected:
            virtual void processMessage(Message message) = 0;
        
    };
}

#endif // __MTL__MTLWORKER__