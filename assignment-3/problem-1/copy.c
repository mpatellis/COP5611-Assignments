#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>


int main (int argc, char* argv[])
{
    int in_fd, out_fd;
    char* src;
    char* dst;
    char* in_file;
    char* out_file;
    struct stat buffer;
    int mode = 0x0777;

    // Make sure there is the appropriate number of arguments
    if (argc != 3)
    {
        printf("Please input path to file and file destination\n");
        return -1;
    }

    in_file = argv[1];
    out_file = argv[2];

    in_fd = open(in_file, O_RDONLY);
    out_fd = open(out_file, O_RDWR | O_CREAT | O_TRUNC, mode);

    // Ensure all the files were opened/created properly
    if (in_fd < 0 || out_fd < 0)
    {
        printf("Input or output file open failed. Please check the given path\n");
        return -1;
    }
 
    // Getting the file data
    if (fstat(in_fd, &buffer) < 0)
    {
        printf("fstat on to be copied file failed\n");
        return -1;
    }

    // Setting the file pointer to the necessary file length
    if (lseek(out_fd, buffer.st_size-1, SEEK_SET) < 0)
    {
        printf("lseek failed");
        return -1;
    }

    // Writing a trash byte to expand the file
    if (write(out_fd, "", 1) != 1)
    {
        printf("write error");
        return -1;
    }

    // Mapping the data into memory
    src = mmap((void*)0, buffer.st_size, PROT_READ, MAP_SHARED, in_fd, 0);
    dst = mmap((void*)0, buffer.st_size, PROT_READ| PROT_WRITE, MAP_SHARED, out_fd, 0);

    // Copying the memory from one file into the other
    memcpy(dst, src, buffer.st_size);

    exit(0);
}