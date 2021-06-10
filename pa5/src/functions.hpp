#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <forward_list>
#include <string>

using std::forward_list;
using std::string;

// see functions.cpp for explanation on the functions
forward_list<string> * SplitStringEncapsulated(const string &str, char delimiter);

#endif//FUNCTIONS_HPP
