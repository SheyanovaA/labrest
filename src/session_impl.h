#ifndef __SESSION_IMPL_H__
#define __SESSION_IMPL_H__

#include "labrestapi.h"

class session_impl : public ::labrestapi::session
{
public:

    virtual ~session_impl();

    virtual void test(const ::Ice::Current&);
};

#endif /* __SESSION_IMPL_H__ */
