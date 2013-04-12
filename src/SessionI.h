#ifndef __SESSIONI_H__
#define __SESSIONI_H__

#include "LabrestAPI.h"

class SessionI : public ::LabrestAPI::Session
{
public:

    virtual ~SessionI();

    virtual void test(const ::Ice::Current&);
};

#endif /* __SESSION_IMPL_H__ */
