#pragma once
#ifndef MAIN
#define MAIN
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <iostream>
void read_txt(std:: ifstream &afile, std::ofstream &bfile,std::string names);
void stop_words();
void get_text_name(std::vector<std::string> &NYT, std::vector<std::string> &APW);

#endif // !MAIN
