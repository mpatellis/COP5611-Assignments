#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <fstream>

#define OUT_FILE "output.txt"

int get_num_cores();
int process_file(std::string fn);
