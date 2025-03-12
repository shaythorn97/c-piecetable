#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piecetable.h"

int main()
{
    struct PieceTable* pt = pt_init("Hello");

    pt_deinit(pt);

    return 0;
}
