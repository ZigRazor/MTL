#ifndef __MTL__TYPEDEFS__
#define __MTL__TYPEDEFS__

#pragma once

#include <memory>

namespace MTL
{
    enum MTLThreadState_Enumerated
    {
        CREATED = 0,
        RUNNING = 1,
        SUSPENDED = 2,
        STOPPED = 3,
        EXITED = 4,
        FORCE_EXITED = 5
    };

    typedef MTLThreadState_Enumerated E_MTLThreadState;

    typedef std::shared_ptr<void> Message;
}

#endif // __MTL__TYPEDEFS__