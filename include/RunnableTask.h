#ifndef __MTL__RUNNABLETASK__
#define __MTL__RUNNABLETASK__

#pragma once

#include <memory>

namespace MTL
{
    class RunnableTask
    {
    public:
        virtual std::shared_ptr<void> run() = 0;
    };

}

#endif /* __MTL__RUNNABLETASK__ */
