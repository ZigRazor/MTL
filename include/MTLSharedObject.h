#ifndef MTLSHAREDOBJECT_H
#define MTLSHAREDOBJECT_H

#pragma once

#include <mutex>
#include "MTLTypedefs.h"

namespace MTL
{

    /**
     * @brief Class that implements a shared object.
     *
     * This class is a shared object that can be used to share data between threads.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLSharedObject
    {
    public:
        /**
         * @brief Construct a new MTLSharedObject object.
         *
         * @param id The id of the object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLSharedObject(SharedObjectId id);
        /**
         * @brief Destroy the MTLSharedObject object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual ~MTLSharedObject();
        /**
         * @brief Get the id of the object.
         *
         * @return SharedObjectId The id of the object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        SharedObjectId getObjId();
        /**
         * @brief Lock the object and Get the object reference.
         *
         * @return MTLSharedObject& The object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLSharedObject &getObj();
        /**
         * @brief Release the object lock. ( this function should be used only after the end of the critical section that use the object )
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void releaseObj();

    private:
        SharedObjectId objId; /**< The id of the object. */
        std::mutex m_mutex;   /**< The mutex of the object. */
    };
}

#endif // MTLSHAREDOBJECT_H
