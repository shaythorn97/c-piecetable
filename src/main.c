#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// what is a piece table? 
// write some stuff about them here

typedef enum
{
    ORIGINAL,
    ADDED,
} BufferType;

typedef struct
{
    BufferType type;
    uint32_t startIndex;
    uint32_t length;
} Piece;

typedef struct
{
    Piece* pieces;
    char* originalBuffer;
    char* addedBuffer;
    uint32_t totalLength;
    uint16_t pieceCount;
} PieceTable;

PieceTable pt_init(const char* str)
{
    PieceTable pt = 
    {
        .pieces = malloc(sizeof(Piece)), 
        .originalBuffer = malloc(strlen(str) + 1),
        .addedBuffer = NULL,
        .totalLength = strlen(str),
        .pieceCount = 0
    };

    Piece piece = 
    {
        .type = ORIGINAL,
        .startIndex = 0,
        .length = strlen(str) 
    };

    pt.pieces[pt.pieceCount] = piece;
    pt.pieceCount++;

    strcpy(pt.originalBuffer, str);

    return pt;
}

// this needs to be refactored with some logging and better error handling
bool pt_deinit(PieceTable* table)
{
    if (!table)
        return false;

    if (table->pieces)
        free(table->pieces);

    if (table->originalBuffer)
        free(table->originalBuffer);

    if (table->addedBuffer)
        free(table->addedBuffer);

    return true;
}

bool pt_insert(PieceTable* table, uint32_t pos, const char* str)
{
    // we need to do some null and safety checks here
    if (!table || !table->pieces || !table->originalBuffer || pos > table->totalLength || strlen(str) < 1)
        return false;

    // append the str to the addedBuffer
    uint32_t originalBufferLen = strlen(table->originalBuffer);
    uint32_t appendStringLen = strlen(str);

    uint32_t addedBufferLen = 0;

    if (!table->addedBuffer)
        table->addedBuffer = malloc(appendStringLen + 1);
    else
        addedBufferLen = strlen(table->addedBuffer);

    char* tempAddedBuf = realloc(table->addedBuffer, addedBufferLen + appendStringLen + 1);

    if (!tempAddedBuf)
        return false;

    table->addedBuffer = tempAddedBuf;
    table->totalLength += addedBufferLen;

    strcpy(table->addedBuffer + addedBufferLen, str);
    table->addedBuffer[addedBufferLen + appendStringLen] = '\0';

    // here we need to potentially split the piece


    // append to the piece table with the correct description
    Piece* tempPieceBuf = realloc(table->pieces, table->pieceCount * sizeof(Piece));

    if (!tempPieceBuf)
        return false;

    table->pieces = tempPieceBuf;

    Piece tempPiece = 
    {
        .type = ADDED,
        .startIndex = pos,
        .length = appendStringLen
    };

    table->pieces[table->pieceCount] = tempPiece;
    table->pieceCount++;

    return true;
}

void pt_index_at(PieceTable* table, uint32_t pos)
{}

void pt_print(const PieceTable* table)
{

}
bool pt_erase(PieceTable* table, uint32_t begin, uint32_t end)
{
    return false;
}

bool pt_copy(PieceTable* table, uint32_t begin, uint32_t end, uint32_t dest)
{
    return false;
}

bool pt_move(PieceTable* table, uint32_t begin, uint32_t end, uint32_t dest)
{
    return false;
}

bool pt_replace(PieceTable* table, uint32_t begin, uint32_t end, const char* str)
{
    return false;
}

int main()
{
    PieceTable pt = pt_init("Hello");

    printf("%s\n", pt.addedBuffer);

    pt_insert(&pt, 0, " world");

    printf("%s\n", pt.addedBuffer);

    pt_insert(&pt, 0, "!");

    printf("%s\n", pt.addedBuffer);

    pt_deinit(&pt);

    return 0;
}
