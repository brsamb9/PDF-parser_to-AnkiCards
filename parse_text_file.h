#ifndef PARSE_TEXT_FILE_H
#define PARSE_TEXT_FILE_H
#include <bits/stdc++.h>

void parse_file(const char *file_name, std::vector<std::string> &filler);
bool cmp_line(const std::string &, const std::vector<std::string> &, size_t = std::string::npos);

#endif