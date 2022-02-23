#ifndef MTLTYPEDEFS_H
#define MTLTYPEDEFS_H

#pragma once

#include <memory>

namespace MTL
{
    /**
     * @brief Thread State Enumeration
     *
     * This enum is used to represent the state of a thread.
     *
     * @author @ZigRazor
     * @date 2020-02-16
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
     * This typedef is used to represent the state of a thread.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    typedef MTLThreadState_Enumerated E_MTLThreadState;

    /**
     * @brief Message Type Definition
     *
     * This typedef is used to represent the message type.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    typedef std::shared_ptr<void> Message;

    /**
     * @brief Shared Object Id Type Definition
     *
     * This typedef is used to represent the shared object id.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    typedef unsigned int SharedObjectId;

    /**
     * @brief TaskName Type Definition
     *
     * This typedef is used to represent the task name.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    typedef std::string TaskName;
}

#endif // MTLTYPEDEFS_H
