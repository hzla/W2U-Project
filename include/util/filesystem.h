#ifndef __FILE_SYSTEM_H
#define __FILE_SYSTEM_H

#include "swantypes.h"
#include "nds/fs.h"

namespace w2u {
    b32 ReadDataFromFile(const char* fileName, u32 bufferSize, u8 *buffer);
    b32 ReadDataFromFileAt(const char* fileName, u32 offset, u32 bufferSize, u8 *buffer);
    // A file kept open across reads (no path lookup per read): open once, read at offsets, close.
    b32 OpenFile(FSFile* file, const char* fileName);
    b32 ReadOpenFileAt(FSFile* file, u32 offset, u32 bufferSize, u8* buffer);
    void CloseFile(FSFile* file);
    b32 GetFileSize(const char* fileName, u32* fileSize);
    u8 ReadByteFromFile(const char* fileName, const u32 idx);
}

#endif
