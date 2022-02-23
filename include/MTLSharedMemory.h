#ifndef MTLSHAREDMEMORY_H
#define MTLSHAREDMEMORY_H

#pragma once

#include "MTLSharedObject.h"
#include <map>
#include <memory>

namespace MTL
{

    /**
     * @brief Class that implements a shared memory.
     *
     * This class is a shared memory that can be used to share data between threads.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLSharedMemory
    {
    public:
        /**
         * @brief Construct a new MTLSharedMemory object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLSharedMemory();
        /**
         * @brief Destroy the MTLSharedMemory object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual ~MTLSharedMemory();

        /**
         * @brief Add a shared object to the shared memory.
         *
         * @param obj The shared object to add.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void addSharedObject(std::unique_ptr<MTLSharedObject> obj);
        /**
         * @brief Remove a shared object from the shared memory.
         *
         * @param id The id of the shared object to remove.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void removeSharedObject(SharedObjectId id);
        /**
         * @brief Get a shared object from the shared memory.
         *
         * @param id The id of the shared object to get.
         * @return MTLSharedObject& The shared object.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        MTLSharedObject &getSharedObjectById(SharedObjectId id);
        /**
         * @brief Release a shared object from the shared memory.
         *
         * @param obj The shared object to release.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void releaseSharedObject(MTLSharedObject &obj);

        /**
         * @brief Clear the shared memory.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        void clearSharedMemory();

    private:
        std::map<SharedObjectId, std::unique_ptr<MTLSharedObject>> m_sharedObjects; //!< The shared objects.
    };
}

#endif // MTLSHAREDMEMORY_H
