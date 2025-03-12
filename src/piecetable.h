#ifndef PIECETABLE_H
#define PIECETABLE_H

#include <stdint.h>

enum BufferType
{
    ORIGINAL,
    ADD
};

struct Piece
{
    enum BufferType type;
    uint32_t startIndex;
    uint32_t length;
};

struct PieceTable
{
    struct Piece* pieces; 
    char* originalBuffer;
    char* addBuffer;
    uint32_t totalLength;
    uint32_t pieceCount;
};

// pt_init
struct PieceTable* pt_init(const char* str);

// pt_deinit
bool pt_deinit(struct PieceTable* pt);

// pt_insert
bool pt_insert(struct PieceTable* pt, const char* str, uint32_t index);

// pt_erase
bool pt_erase(struct PieceTable* pt, const char* str, uint32_t index);

#endif
