#ifndef RUNNABLE_H
#define RUNNABLE_H

#pragma once

#include "MTLThreadInterface.h"

namespace MTL
{

    /**
     * @brief Runnable Interface
     *
     * This class is the interface for the Runnable class.
     *
     * @author @ZigRazor
     * @date 2020-02-16
     */
    class MTLRunnable
    {
    public:
        /**
         * @brief Run the runnable
         *
         * @param threadIf The thread interface.
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void run(MTLThreadInterface *threadIf) = 0;
        /**
         * @brief Suspend the runnable
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void suspend() = 0;
        /**
         * @brief Resume the runnable
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void resume() = 0;
        /**
         * @brief Stop the runnable
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void stop() = 0;
        /**
         * @brief A clean Exit of the runnable
         *
         * @author @ZigRazor
         * @date 2020-02-16
         */
        virtual void clean_exit() = 0;
        /**
         * @brief Force the runnable to exit
         *
         * @author @ZigRazor
         * @date 2020-02-16
         *
         */
        virtual void force_exit() = 0;

    private:
        MTLThreadInterface *threadIf; //!< The thread interface.
    };

}

#endif // RUNNABLE_H
