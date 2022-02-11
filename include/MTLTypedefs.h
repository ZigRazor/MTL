#ifndef __MTL__TYPEDEFS__
#define __MTL__TYPEDEFS__

#pragma once

#include <memory>

namespace MTL
{
    /**
     * @brief Thread State Enumeration
     *
     */
    enum MTLThreadState_Enumerated
    {
        CREATED = 0,     //!< Thread is created but not yet started.
        RUNNING = 1,     //!< Thread is running.
        SUSPENDED = 2,   //!< Thread is suspended.
        STOPPED = 3,     //!< Thread is stopped.
        EXITED = 4,      //!< Thread is exited.
        FORCE_EXITED = 5 //!< Thread is force exited.
    };

    /**
     * @brief Thread State Enumeration Type Definition
     *
     */
    typedef MTLThreadState_Enumerated E_MTLThreadState;

    /**
     * @brief Message Type Definition
     *
     */
    typedef std::shared_ptr<void> Message;
}

#endif // __MTL__TYPEDEFS__