#include <cstdio>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// what is a piece table? 
//  
// this is a data structure that keeps the text as a sequence of pieces of text from either the original file and an added text file

typedef enum BufferType
{
    ORIGINAL,
    ADDED,
    MAX_TYPES
} BufferType;

typedef struct Piece
{
    BufferType type;
    uint32_t startIndex;
    uint32_t length;
} Piece;

typedef struct PieceTable
{
    Piece pieces[10];
    char* originalBuffer;
    char* addedBuffer;
    uint16_t count;
} PieceTable;

bool pc_insert(PieceTable* table, uint32_t pos, const char* str)
{
    // if the originalBuffer is null then we dont need to split the piece
    if (table->originalBuffer == NULL)
    {
        // set the originalBuffer to the str 
        // append to the piece table the piece data
        return true;
    }
    // take in the piece table
    // append str to the addedBuffer
    // extend the piece table with the new piece
    return false;
}



int main()
{
    const char* file = "Hello World";

    PieceTable table = 
    {
        .pieces = {0},
        .originalBuffer = NULL,
        .addedBuffer = NULL,
        .count = 0,
    };

    // insert into the piece table our file 
    pc_insert(&table, 0, file); 

    return 0;
}
