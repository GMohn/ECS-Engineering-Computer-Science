#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GenericTraits.h"


DECLARE_STRUCT(Rectangle, {
    GenericTraits *impl;
    int height;
    int width;
})


#endif