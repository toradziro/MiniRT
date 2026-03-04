#include "rt_file.h"
#include <windows.h>

str8 read_full_file(str8 path)
{
    str8 ret = {0};

    char* win_capable_str = _alloca(sizeof(char) * path.size + 1);
    memcpy(win_capable_str, path.mem, path.size);
    win_capable_str[path.size] = '\0';
    HANDLE hFile = CreateFileA(win_capable_str, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return ret;
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize))
    {
        CloseHandle(hFile);
        return ret;
    }

    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == NULL)
    {
        CloseHandle(hFile);
        return ret;
    }

    ret.mem  = (u8*)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    ret.size = (u32)fileSize.QuadPart;

    CloseHandle(hMapping);
    CloseHandle(hFile);

    return ret;
}

void clean_file(str8* file)
{
    if (file->mem != NULL)
    {
        UnmapViewOfFile(file->mem);
    }

    file->mem  = NULL;
    file->size = 0;
}
