#ifndef __SESSION_IMPL_H__
#define __SESSION_IMPL_H__

#include "labrestapi.h"

class Session_I : public ::LabrestAPI::Session
{
public:

    virtual ~Session_I();

    virtual void Test(const ::Ice::Current&);
};

#endif /* __SESSION_IMPL_H__ */
