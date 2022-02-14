#include "MTLSharedMemory.h"

namespace MTL
{
    MTLSharedMemory::MTLSharedMemory() : m_sharedObjects()
    {
    }

    MTLSharedMemory::~MTLSharedMemory()
    {
    }

    void MTLSharedMemory::addSharedObject(std::unique_ptr<MTLSharedObject> obj)
    {
        m_sharedObjects[obj->getObjId()] = std::move(obj);
    }

    void MTLSharedMemory::removeSharedObject(unsigned int id)
    {
        m_sharedObjects.erase(id);
    }

    MTLSharedObject &MTLSharedMemory::getSharedObjectById(unsigned int id)
    {
        if (m_sharedObjects.find(id) == m_sharedObjects.end())
        {
            throw std::runtime_error("MTLSharedMemory::getSharedObjectById: object not found");
        }
        return m_sharedObjects.at(id)->getObj();
    }

    void MTLSharedMemory::releaseSharedObject(MTLSharedObject &obj)
    {
        if (m_sharedObjects.find(obj.getObjId()) == m_sharedObjects.end())
        {
            throw std::runtime_error("MTLSharedMemory::releaseSharedObject: object not found");
        }
        m_sharedObjects.at(obj.getObjId())->releaseObj();
    }

    void MTLSharedMemory::clearSharedMemory()
    {
        m_sharedObjects.clear();
    }

}