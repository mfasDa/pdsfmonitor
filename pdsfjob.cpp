#include "pdsfjob.h"

#include <cstring>

namespace NEWT{

PDSFJob::PDSFJob():
    fJobID(0),
    fUser(""),
    fName(""),
    fQueue(""),
    fStatus(""),
    fPriority(0.),
    fStartTime()
{
    memset(fSlots, 0, sizeof(int) * 2);
}

}
