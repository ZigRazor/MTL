#ifndef __MTL__MTLTASK__
#define __MTL__MTLTASK__

#pragma once

#include <future>
#include "RunnableTask.h"

namespace MTL
{

    class MTLTask
    {
    public:
        MTLTask(RunnableTask &runnableTask);
        virtual ~MTLTask();

        std::shared_ptr<void> getFuture();

    private:
        std::future<std::shared_ptr<void>> m_future;
    };

}

#endif /* __MTL__MTLTASK__ */
