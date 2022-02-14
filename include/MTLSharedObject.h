#ifndef __MTL__MTLSHAREDOBJECT__
#define __MTL__MTLSHAREDOBJECT__

#include <mutex>
#include "MTLTypedefs.h"

namespace MTL{

    /**
     * @brief Class that implements a shared object.
     *
     */
    class MTLSharedObject
    {
        public:
            /**
             * @brief Construct a new MTLSharedObject object.
             *
             * @param id The id of the object.
             */
            MTLSharedObject(SharedObjectId id);
            /**
             * @brief Destroy the MTLSharedObject object.
             *
             */
            virtual ~MTLSharedObject();         
            /**
             * @brief Get the id of the object.
             *
             * @return SharedObjectId The id of the object.
             */
            SharedObjectId getObjId();
            /**
             * @brief Lock the object and Get the object reference.
             *
             * @return MTLSharedObject& The object.
             */
            MTLSharedObject& getObj();
            /**
             * @brief Release the object lock. ( this function should be used only after the end of the critical section that use the object )
             *
             */
            void releaseObj();

        private:
            SharedObjectId objId;
            std::mutex m_mutex;
            
            
    };
}

#endif /* __MTL__MTLSHAREDOBJECT__ */
