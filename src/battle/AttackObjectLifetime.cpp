#include "AttackObject.hpp"

AttackObject::~AttackObject() throw()
{
    if (state_158.frame_03c != 0)
        delete static_cast<unsigned char *>(state_158.frame_03c);
}
