#include "functions.hpp"
#include <string>
#include <forward_list>

using std::string;
using std::forward_list;

// Creates a list of strings that are surrounded with given delimiter in given string
// and returns the pointer of the list
forward_list<string> * SplitStringEncapsulated(const string &str, char delimiter){
    forward_list<string> *split = new forward_list<string>();	// List of strings

    bool add = false;	// Should current character be added to current string in list

    for(auto it = str.begin(); it != str.end(); ++it){	// iterate through characters of string
	if(*it == delimiter){	// If delimiter is encountered
	    add = !add;		// reverse add status
	    if(add)		// If new status is as 'should be added'
		split->emplace_front("");   // add new string to list
	}	
	else if(add)	// If current character already should be added, thus not delimiter
	    split->front() += *it;  // just add to current string
    }

    return split;
}
