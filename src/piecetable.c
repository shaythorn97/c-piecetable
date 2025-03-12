#include "piecetable.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

struct PieceTable* pt_init(const char* str)
{
    struct PieceTable* pt = malloc(sizeof(struct PieceTable));
    if (!pt)
        return nullptr;

    if (!str || strlen(str) == 0)
    {
        pt->pieces = nullptr;
        pt->originalBuffer = nullptr;
        pt->addBuffer = nullptr;
        pt->totalLength = 0;
        pt->pieceCount = 0;

        return pt;
    }

    pt->pieces = malloc(sizeof(struct Piece));
    if (!pt->pieces)
    {
        pt_deinit(pt);
        return nullptr;
    }

    pt->originalBuffer = malloc(strlen(str) + 1);
    if (!pt->originalBuffer)
    {
        pt_deinit(pt);
        return nullptr;
    }

    pt->addBuffer = nullptr;
    pt->totalLength = strlen(str);
    pt->pieceCount = 0;

    strcpy(pt->originalBuffer, str);

    pt->pieces[pt->pieceCount] = (struct Piece) 
    {
        .type = ORIGINAL,
        .startIndex = 0,
        .length = strlen(str)
    };
    pt->pieceCount++;

    return pt;
}

bool pt_deinit(struct PieceTable* pt)
{
    // should be logging as debug here
    if (!pt)
        return false;

    if (pt->pieces)
        free(pt->pieces);

    if (pt->originalBuffer)
        free(pt->originalBuffer);

    if (pt->addBuffer)
        free(pt->addBuffer);

    free(pt);

    return true;
}

bool pt_insert(struct PieceTable* pt, const char* str, uint32_t index)
{
    if (!pt || !str || strlen(str) == 0 || index < 0 || index > pt->totalLength)
        return false;

    if (!pt->addBuffer)
    {
        pt->addBuffer = malloc(strlen(str) + 1);
        if (!pt->addBuffer)
            return false;

        pt->addBuffer[0] = '\0';
    }
    else 
    {
        pt->addBuffer = realloc(pt->addBuffer, strlen(pt->addBuffer) + strlen(str) + 1); 
        if (!pt->addBuffer)
            return false;
    }

    strcat(pt->addBuffer, str);

    if (!pt->pieces)
        pt->pieces = malloc(sizeof(struct Piece));
    else
        pt->pieces = realloc(pt->pieces, sizeof(struct Piece) * (pt->pieceCount + 1));

    if (!pt->pieces)
        return false;

    pt->pieces[pt->pieceCount] = (struct Piece) 
    {
        .type = ADD,
        .startIndex = index,
        .length = strlen(str)
    };
    pt->pieceCount++;

    return true;
}

bool pt_erase(struct PieceTable* pt, const char* str, uint32_t index)
{
    return false;
}
