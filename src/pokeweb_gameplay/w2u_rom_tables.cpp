// Lookups in the read-only tables kept in ROM files (include/w2u_rom_tables.h).
#include "w2u_rom_tables.h"
#include "util/filesystem.h"

namespace {
constexpr u32 W2U_ROM_TABLE_CHUNK = 208u;   // stack buffer: 8 terrain mappings / 26 glyph places per read
}

extern "C" bool W2U_RomTable_Find(
    const char* path, u32 recordSize, bool (*match)(const void* record, u32 key), u32 key, void* out)
{
    u32 fileSize = 0;
    if (!path || !match || !out || !recordSize || recordSize > W2U_ROM_TABLE_CHUNK ||
        !w2u::GetFileSize(path, &fileSize)) {
        return false;
    }
    FSFile file;
    if (!w2u::OpenFile(&file, path)) {
        return false;
    }
    u8 chunk[W2U_ROM_TABLE_CHUNK] __attribute__((aligned(4)));
    bool found = false;
    for (u32 offset = 0; offset < fileSize && !found;) {
        u32 size = 0;                           // whole records only (no division: PMC lacks __aeabi_uidiv)
        while (size + recordSize <= W2U_ROM_TABLE_CHUNK && recordSize <= fileSize - offset - size) {
            size += recordSize;
        }
        if (!size || !w2u::ReadOpenFileAt(&file, offset, size, chunk)) {
            break;
        }
        for (u32 at = 0; at < size; at += recordSize) {
            if (match(chunk + at, key)) {
                u8* to = static_cast<u8*>(out);
                for (u32 index = 0; index < recordSize; ++index) {
                    to[index] = chunk[at + index];
                }
                found = true;
                break;
            }
        }
        offset += size;
    }
    w2u::CloseFile(&file);
    return found;
}
