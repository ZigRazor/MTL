#ifndef __MTL__MTLTHREADINTERFACE__
#define __MTL__MTLTHREADINTERFACE__

#pragma once

#include "MTLTypedefs.h"

namespace MTL
{
    class MTLThreadInterface
    {
    public:
        virtual bool isRunning() = 0;
        virtual E_MTLThreadState getThreadState() = 0;
        virtual void setThreadState(E_MTLThreadState threadState) = 0;
    };
}

#endif /* __MTL__MTLTHREADINTERFACE__ */
