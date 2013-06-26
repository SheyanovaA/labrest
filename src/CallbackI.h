#ifndef CallbackI_H
#define	CallbackI_H

#include "LabrestAPI.h"

namespace LabrestAPI
{

class CallbackI : virtual public Callback
{
public:

    virtual void doCallback(const ::LabrestAPI::Event&,
                            const Ice::Current&);
};

}


#endif	/* CallbackI_H */

