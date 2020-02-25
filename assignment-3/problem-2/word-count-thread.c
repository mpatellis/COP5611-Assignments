#include "word-count-thread.h"

int get_num_cores()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

int main(void)
{
    long num_cores = get_num_cores();
    printf("%ld", num_cores);
    // use c++ please dr wang pls
    // read file
    // process file
    // find num lines
    // set up threads
    // map for word occurences
    return 0;
}