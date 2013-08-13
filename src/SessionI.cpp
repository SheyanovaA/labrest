#include "SessionI.h"

LabrestAPI::SessionI::SessionI(::std::string sessionId, ::std::string username) : Session() 
{
    ::std::cout<<"SessionI::SessionI() called"<<::std::endl;
    
    current_user = dbPtr->getUser(username);
    
    this->sessionId = sessionId;

    this->hasRsMgrPrx = false;

    this->hasUsMgrPrx = false;
    
    this->hasCbMgrPrx = false;
    
    this->_timestamp = IceUtil::Time::now(IceUtil::Time::Monotonic);

    this->_destroy = false;
}

LabrestAPI::SessionI::~SessionI()
{
    while (!this->lock.tryLock()) {};
    

    ::std::cout<<"SessionI::~SessionI() called"<<::std::endl;
    
    this->lock.unlock();
}


::LabrestAPI::ResourceManagerPrx
LabrestAPI::SessionI::getResourceManager(const Ice::Current& current)
{
    while (!this->lock.tryLock()) {};
    
    ::std::cout<<"SessionI::getResourceManager() called"<<::std::endl;
    
    if(_destroy)
    {
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }

    if(!hasRsMgrPrx) 
    {
        Ice::ObjectPtr object = new ::LabrestAPI::ResourceManagerI(current_user);

        rsMgrPrx = ::LabrestAPI::ResourceManagerPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId + "-ResourceManager")));

        hasRsMgrPrx = true;
    }
    
    this->lock.unlock();

    return rsMgrPrx;
}

::LabrestAPI::UserManagerPrx
LabrestAPI::SessionI::getUserManager(const Ice::Current& current)
{
    while (!this->lock.tryLock()) {};
    
    ::std::cout<<"SessionI::getUserManager() called"<<::std::endl;
    
    if(_destroy)
    {
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }

    if(!hasUsMgrPrx) 
    {
        Ice::ObjectPtr object = new ::LabrestAPI::UserManagerI(current_user);

        usMgrPrx = ::LabrestAPI::UserManagerPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId + "-UserManager")));

        hasUsMgrPrx = true;
    }
    
    this->lock.unlock();

    return usMgrPrx;
}

::LabrestAPI::CallbackManagerPrx
LabrestAPI::SessionI::getCallbackManager(const Ice::Current& current)
{
    while (!this->lock.tryLock()) {};
    
    ::std::cout<<"SessionI::getCallbackManager() called"<<::std::endl;
    
    if(_destroy)
    {
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }

    if(!hasCbMgrPrx) 
    {
        Ice::ObjectPtr object = new ::LabrestAPI::CallbackManagerI(current_user);
        
        cbMgrPrx = ::LabrestAPI::CallbackManagerPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId + "-CallBackManager")));

        hasCbMgrPrx = true;
    }
    
    this->lock.unlock();

    return cbMgrPrx;
}

void
LabrestAPI::SessionI::Refresh(const Ice::Current& current)
{
    while (!this->lock.tryLock()) {};
    
    ::std::cout<<"SessionI::Refresh() called"<<::std::endl;
    
    if(_destroy)
    {
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }

    _timestamp = IceUtil::Time::now(IceUtil::Time::Monotonic);
    
    this->lock.unlock();
}

void
LabrestAPI::SessionI::destroy(const Ice::Current& current)
{
    while (!this->lock.tryLock()) {};
    
    ::std::cout<<"SessionI::destroy() called"<<::std::endl;
    
    if(_destroy)
    {
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }

    _destroy = true;

    ::std::cout << "The session  is now destroyed." << ::std::endl;
    try
    {
        current.adapter->remove(current.id);
        if (this->hasRsMgrPrx) {
            current.adapter->remove(rsMgrPrx->ice_getIdentity());
            hasRsMgrPrx = false;
        };
         if (this->hasUsMgrPrx) {
            current.adapter->remove(usMgrPrx->ice_getIdentity());
            hasUsMgrPrx = false;
        };
        if (this->hasCbMgrPrx) {
            current.adapter->remove(cbMgrPrx->ice_getIdentity());
            hasCbMgrPrx = false;
        };
    }
    catch(const Ice::ObjectAdapterDeactivatedException&)
    {
        // This method is called on shutdown of the server, in which
        // case this exception is expected.
    }
    
    this->lock.unlock();    
}

IceUtil::Time
LabrestAPI::SessionI::timestamp() const
{
    while (!this->lock.tryLock()) {};
    
    if(_destroy)
    {
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }
    
    this->lock.unlock();
    
    return _timestamp;
}