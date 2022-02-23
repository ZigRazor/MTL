#include "MTLSharedObject.h"

namespace MTL
{

    MTLSharedObject::MTLSharedObject(SharedObjectId id) : objId(id), m_mutex()
    {
    }
    MTLSharedObject::~MTLSharedObject()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
    }
    SharedObjectId MTLSharedObject::getObjId()
    {
        return objId;
    }
    MTLSharedObject &MTLSharedObject::getObj()
    {
        m_mutex.lock();
        return *this;
    }
    void MTLSharedObject::releaseObj()
    {
        m_mutex.unlock();
    }
}