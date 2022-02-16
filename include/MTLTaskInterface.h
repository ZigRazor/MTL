#ifndef __MTL__MTLTASKINTERFACE__
#define __MTL__MTLTASKINTERFACE__


#pragma once

#include <memory>


namespace MTL{
    class MTLTaskInterface {
    public:
        virtual std::shared_ptr<void> getResult() = 0;
        virtual void waitResult() = 0;
    };
 
}

#endif /* __MTL__MTLTASKINTERFACE__ */
