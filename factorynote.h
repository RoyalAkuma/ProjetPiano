#ifndef FACTORYNOTE_H
#define FACTORYNOTE_H

#include "note.h"
#include "string"

class FactoryNote
{
public:
    FactoryNote();
    Note* faireNote(std::string,int,int=0);
};

#endif // FACTORYNOTE_H
