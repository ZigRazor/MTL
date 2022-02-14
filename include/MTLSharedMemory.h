#ifndef __MTL__MTLSHAREDMEMORY__
#define __MTL__MTLSHAREDMEMORY__

#include "MTLSharedObject.h"
#include <map>
#include <memory>

namespace MTL {
    
        /**
        * @brief Class that implements a shared memory.
        *
        */
        class MTLSharedMemory {
        public:
            /**
            * @brief Construct a new MTLSharedMemory object.
            *
            */
            MTLSharedMemory();
            /**
            * @brief Destroy the MTLSharedMemory object.
            *
            */
            virtual ~MTLSharedMemory();
            
            /**
             * @brief Add a shared object to the shared memory.
             * 
             * @param obj The shared object to add.
             */
            void addSharedObject(std::unique_ptr<MTLSharedObject> obj);
            /**
             * @brief Remove a shared object from the shared memory.
             * 
             * @param id The id of the shared object to remove.
             */
            void removeSharedObject(SharedObjectId id);
            /**
             * @brief Get a shared object from the shared memory.
             * 
             * @param id The id of the shared object to get.
             * @return MTLSharedObject& The shared object.
             */
            MTLSharedObject& getSharedObjectById(SharedObjectId id);
            /**
             * @brief Release a shared object from the shared memory.
             * 
             * @param obj The shared object to release.
             */
            void releaseSharedObject(MTLSharedObject& obj);

            /**
             * @brief Clear the shared memory.
             * 
             */
            void clearSharedMemory();


        private:
            std::map<SharedObjectId, std::unique_ptr<MTLSharedObject>> m_sharedObjects;
        };
}

#endif /* __MTL__MTLSHAREDMEMORY__ */
