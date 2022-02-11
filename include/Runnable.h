#ifndef __MTL__RUNNABLE__
#define __MTL__RUNNABLE__

#pragma once

#include "MTLThreadInterface.h"

namespace MTL
{

    /**
     * @brief Runnable Interface
     *
     */
    class Runnable
    {
    public:
        /**
         * @brief Run the runnable
         *
         * @param threadIf The thread interface.
         */
        virtual void run(MTLThreadInterface *threadIf) = 0;
        /**
         * @brief Suspend the runnable
         *
         */
        virtual void suspend() = 0;
        /**
         * @brief Resume the runnable
         *
         */
        virtual void resume() = 0;
        /**
         * @brief Stop the runnable
         *
         */
        virtual void stop() = 0;
        /**
         * @brief A clean Exit of the runnable
         *
         */
        virtual void clean_exit() = 0;
        /**
         * @brief Force the runnable to exit
         *
         */
        virtual void force_exit() = 0;

    private:
        MTLThreadInterface *threadIf;
    };

}

#endif // __MTL__RUNNABLE__