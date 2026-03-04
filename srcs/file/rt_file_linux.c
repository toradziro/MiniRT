#include "rt_file.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <alloca.h>

str8 read_full_file(str8 path)
{
    str8 ret = {0};

    char* linux_capable_str = alloca(sizeof(char) * path.size + 1);
    memcpy(linux_capable_str, path.mem, path.size);
    linux_capable_str[path.size] = '\0';
    int fd                       = open(linux_capable_str, O_RDONLY);

    ret.mem  = NULL;
    ret.size = 0;

    if (fd < 0)
    {
        printf("Error opening a file read_full_file %s", path.mem);
        return ret;
    }

    struct stat st;
    fstat(fd, &st);

    ret.mem  = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    ret.size = st.st_size;
    close(fd);

    if (ret.mem == MAP_FAILED)
    {
        printf("Error opening a file read_full_file %s", path.mem);
        return ret;
    }

    return ret;
}

void clean_file(str8* file)
{
    if (file->mem != NULL)
    {
        munmap(file->mem, file->size);
    }

    file->mem  = NULL;
    file->size = 0;
}
