#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cstring>


template <typename T>
std::string toString(const T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

int ft_stoi(std::string str);
unsigned int fromHexToDec(const std::string& nb);
std::string statusCodeString(short statusCode);
std::string getErrorPage(short statusCode);
int buildHtmlIndex(std::string &dir_name, std::vector<unsigned char> &body, size_t &body_len);

#endif