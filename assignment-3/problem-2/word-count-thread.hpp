#include <pthread.h>
#include <unistd.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

#define OUT_FILE "output.txt"
 

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
std::map<std::pair<std::string, std::string>, int> final_map;

struct range
{
    int begin;
    int end;
};

void combine_maps(const std::map<std::pair<std::string, std::string>, int>& map);
void* count_words(void* void_pair);
int get_num_cores();
void print_output();
int process_file(std::string fn);
std::vector<std::string> split(std::string str);
