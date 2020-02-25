#include "word-count-thread.hpp"

int get_num_cores()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

void process_file(FILE* file)
{

}

int count_lines(FILE* file)
{
    int num_lines = 0;
    int nl;

    while (EOF != (nl=getc(file)))
    {
        if ('\n' == nl)
            num_lines++;
    }
    return num_lines;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Please include path to text file\n";
        return -1;
    }

    long num_cores = get_num_cores();
    std::cout << "Number of cores: " << num_cores << std::endl;

    FILE* file = fopen(argv[1], "r");
    process_file(file);
    printf("%d\n", count_lines(file));


    // read file
    // process file
    // find num lines
    // set up threads
    // map for word occurences
    return 0;
}