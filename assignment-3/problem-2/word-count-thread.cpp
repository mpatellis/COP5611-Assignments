#include "word-count-thread.hpp"

int get_num_cores()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

int process_file(std::string fn)
{
    int num_lines = 0;
    std::ifstream read_file;
    std::ofstream out_file;

    read_file.open(fn);
    if (!read_file.is_open())
    {
        std::cout << "Opening read file failed\n";
        return -1;
    }

    out_file.open(OUT_FILE, std::ios::in | std::ios::trunc);
    if (!out_file.is_open())
    {
        std::cout << "Opening output file failed\n";
        read_file.close();
        return -1;
    }

    std::string line;
    while (getline(read_file,line))
    {
        std::string process_line;
        int str_len = line.size();

        for (int i = 0; i < str_len; i++)
        {
            if (isalpha(line[i]))
                process_line = process_line + (char)tolower(line[i]);
            else if (line[i] == ' ')
                process_line = process_line + line[i];
        }

        process_line.append("\n");
        out_file << process_line;
        num_lines++;
    }

    read_file.close();
    out_file.close();
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

    std::string file_name = argv[1];
    int num_lines = process_file(file_name);


    // set up threads
    // map for word occurences
    return 0;
}