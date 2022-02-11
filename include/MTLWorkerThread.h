#ifndef __MTL__MTLWORKERTHREAD__
#define __MTL__MTLWORKERTHREAD__

#pragma once

#include "Runnable.h"
#include "MTLMessageQueue.h"
#include "MTLWorker.h"

namespace MTL{
    
    class MTLWorkerThread : public Runnable, public MTLWorker, public MTLMessageQueue{
        public:
            MTLWorkerThread();
            virtual ~MTLWorkerThread();
            virtual void run(MTLThreadInterface* threadIf);
            virtual void suspend();
            virtual void resume();
            virtual void stop();
            virtual void clean_exit();
            virtual void force_exit();

            void setSleepTime(int sleep_time);

        protected:
            virtual void processMessage(Message message) = 0;
        private:
            
            unsigned int m_sleep_time;
    };

}

#endif // __MTL__MTLWORKERTHREAD__