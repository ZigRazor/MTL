#ifndef __MTL__RUNNABLE__
#define __MTL__RUNNABLE__

#pragma once

#include "MTLThreadInterface.h"

namespace MTL{

class Runnable{
    public:
    virtual void run(MTLThreadInterface* threadIf) = 0;
    virtual void suspend() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;
    virtual void clean_exit() = 0;
    virtual void force_exit() = 0;

    private:
    MTLThreadInterface* threadIf;
};

}

#endif // __MTL__RUNNABLE__