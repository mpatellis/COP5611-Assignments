#include "word-count-thread.hpp"

void combine_maps(const std::map<std::pair<std::string, std::string>, int>& map)
{
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        final_map[it->first] = final_map[it->first] + it->second;
    }
}

void* count_words(void* void_pair)
{
    struct range* range = (struct range *)void_pair;
    std::fstream read_file;
    read_file.open(OUT_FILE);

    if (!read_file.is_open())
    {
        std::cout << "Count word read file failed to open\n" << std::endl;
        return NULL;
    }

    read_file.seekg(std::ios::beg);
    for (int i = 0; i <= range->begin-1; ++i)
    {
        read_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::map<std::pair<std::string, std::string>, int> map;
    std::string line;

    for (int line_index = range->begin; line_index < range->end; line_index++)
    {
        int len;
        std::vector<std::string> words;
        std::map<std::string, int> seen;

        getline(read_file, line);

        words = split(line);
        len = words.size();


        for (int i = 0; i < len; i++)
        {
            std::string first;
            
            first = words[i];
            if (!seen.count(first))
            {
                seen[first] = 1;

                for (int j = 0; j < len; j++)
                {
                    if (i == j)
                        continue;
                    std::string second = words[j];
                    std::pair<std::string, std::string> key (first, second);
                    map[key] = map[key] + 1;
                }

            }
        }
    }

    read_file.close();

    pthread_mutex_lock(&lock);
    combine_maps(map);
    pthread_mutex_unlock(&lock);
}

int get_num_cores()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

void print_output()
{
    std::ofstream output;
    output.open(OUT_FILE, std::ios::out | std::ios::trunc);

    if (output.is_open())
    {
        for (auto it = final_map.begin(); it != final_map.end(); ++it)
        {
            output << "<(" << it->first.first << ", " << it->first.second << "), "
                   << it->second << ">,";
        }
        output.close();
    }
    else
    {
        std::cout << "Printing output file failed to open";
    }   
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

        num_lines++;
        out_file << process_line << std::endl;
    }
    
    read_file.close();
    out_file.close();
    return num_lines;
}

std::vector<std::string> split(std::string str)
{
    std::vector<std::string> result;
    std::istringstream iss(str);

    for (std::string str; iss >> str;)
        result.push_back(str);

    return result;
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
    int file_length = process_file(file_name);

    if (num_cores > file_length)
        num_cores = file_length;

    std::vector<pthread_t> thread_id(num_cores);

    std::vector<int> num_lines(num_cores);
    int base = file_length / num_cores;
    int off = file_length % num_cores;

    for (int i = 0; i < num_lines.size(); i++)
    {
        if (off > 0)
            num_lines[i] = base + 1;
        else
            num_lines[i] = base;
        off += -1;
    }

    int sum = 0;

    std::vector<struct range> ranges(num_cores);
    for (int i = 0; i < num_cores; i++)
    {
        ranges[i] = {sum, sum + num_lines[i]};
        sum += num_lines[i];
        pthread_create(&thread_id[i], NULL, &count_words, (void*)&ranges[i]);
    }

    for (int i = 0; i < num_cores; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    print_output();

    return 0;
}