#ifndef MTLTASKINTERFACE_H
#define MTLTASKINTERFACE_H

#pragma once

#include <memory>

namespace MTL
{
    /**
     * @brief The MTLTaskInterface Interface Class
     *
     * This class is the interface for the MTLTask class.
     *
     * @author @ZigRazor
     * @date 2022-02-16
     */
    class MTLTaskInterface
    {
    public:
        /**
         * @brief Get the Result object
         *
         * @return std::shared_ptr<void>  The result of the task
         *
         * @author @ZigRazor
         * @date 2022-02-16
         */
        virtual std::shared_ptr<void> getResult() = 0;
        /**
         * @brief Wait for the task to finish
         *
         * @author @ZigRazor
         * @date 2022-02-16
         */
        virtual void waitResult() = 0;
    };

}

#endif // MTLTASKINTERFACE_H
