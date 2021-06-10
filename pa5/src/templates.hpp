#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include "exceptions.hpp"
#include "functions.hpp"
#include <fstream>
#include <forward_list>
#include <string>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::forward_list;
using std::getline;
using std::string;
using std::stringstream;
using Exceptions::MissingField;
using Exceptions::DuplicateEntry;
using Exceptions::WrongCommand;
using Exceptions::BlankMethod;

// Reads lines from given file and fills given list with data from read lines
template <typename T>
void ReadData(ifstream &in, forward_list<T> &list, ofstream &out) {
    string readLine;		    // read line
    int uniqueEntries = 0;	    // number of unique entries
    string firstField;		    // first read field
    forward_list<string> *fields;   // fields
    int fieldCount;		    // number of fields
    while(getline(in, readLine)){
	fields = SplitStringEncapsulated(readLine, '"');    // get fields
	fieldCount = 0;	// reset number of fields

	try{
	    for(auto it = fields->begin(); it != fields->end(); ++it){	// iterate through field list
		firstField = *it;   // first field is at the end of the list, so update each iteration
		++fieldCount;	    // increase number of fields each time, basically size of field list
	    }
	    if(fieldCount != T::GetFieldCount())    // if number of fields doesn't match with specified class's
		throw MissingField();		    // there's a missing field
	}
	catch(MissingField e){			    // inform about the missing field error
	    out << "Exception: " << e.what() << std::endl
		<< readLine << std::endl;
	    delete fields;			    // deallocate
	    continue;				    // get to next line of data file
	}

	try{
	    for(auto it = list.begin(); it != list.end(); ++it){    // for each element of the list
		if(it->GetTitle() == firstField)		    // check if current instance's title matches any 
		    throw DuplicateEntry();			    // if so there's duplicate entry error
	    }
	}
	catch(DuplicateEntry e){		    // inform about the duplicate entry error
	    out << "Exception: " << e.what() << std::endl
		<< readLine << std::endl;
	    delete fields;			    // deallocate
	    continue;				    // get to next line of data file
	}

	++uniqueEntries;	    // increase number of unique entries
	list.emplace_front(fields); // add instance to list
	delete fields;		    // deallocate 
    }
    out << uniqueEntries << " unique entries\n";    // inform about number of unique entries
}

// Reads command file and executes with given list of data
template <typename T>
void ExecuteCommands(ifstream &in, forward_list<T> &dataList, ofstream &out){
    string readLine;	// read line from data file

    forward_list<string> *fields;   // field list of read line
    while(getline(in, readLine)){
	stringstream streamReadLine(readLine);	// create stream of read line to get what command is written, since it's not surrounded by quotation marks
	stringstream commandResult;		// result string of the command
	fields = SplitStringEncapsulated(readLine, '"');    // get fields
	auto commandArg = fields->begin();	// command's argument iterator

	string command;			    // command
	streamReadLine >> command;	    // get command
	string searchField = *commandArg++; // the field in which search or sort will be done
	try{
	    if(command == "search"){	// if command is to search
		string searched = *commandArg++;    // what will be searched
		// search in corresponding field
		// basically iterates through list elements and if 
		// any element matches it is added to command result string
		if(searchField == "title"){
		    for(auto it = dataList.begin(); it != dataList.end(); ++it){
			if(it->GetTitle().find(searched) != string::npos)
			    commandResult << *it;
		    }
		}
		else if(searchField == "authors"){
		    for(auto it = dataList.begin(); it != dataList.end(); ++it){
			if(it->GetAuthors().find(searched) != string::npos)
			    commandResult << *it;
		    }
		}
		else if(searchField == "year"){
		    for(auto it = dataList.begin(); it != dataList.end(); ++it){
			if(std::to_string(it->GetYear()).find(searched) != string::npos)
			    commandResult << *it;
		    }
		}
		else if(searchField == "tags"){
		    for(auto it = dataList.begin(); it != dataList.end(); ++it){
			if(it->GetTags().find(searched) != string::npos)
			    commandResult << *it;
		    }
		}
		else if(searchField == "artists"){
		    for(auto it = dataList.begin(); it != dataList.end(); ++it){
			if(it->GetArtists().find(searched) != string::npos)
			    commandResult << *it;
		    }
		}
		else if(searchField == "genre"){
		    for(auto it = dataList.begin(); it != dataList.end(); ++it){
			if(it->GetGenre().find(searched) != string::npos)
			    commandResult << *it;
		    }
		}
		else if(searchField == "director"){
		    for(auto it = dataList.begin(); it != dataList.end(); ++it){
			if(it->GetDirector().find(searched) != string::npos)
			    commandResult << *it;
		    }
		}
		else if(searchField == "starring"){
		    for(auto it = dataList.begin(); it != dataList.end(); ++it){
			if(it->GetStarring().find(searched) != string::npos)
			    commandResult << *it;
		    }
		}
		else	// if search field is something different
		    throw WrongCommand();   // then command is wrong
	    }
	    else if(command == "sort"){	// if command is sort
		
		// sort data list correspondingly
		if(searchField == "title")
		    dataList.sort(T::CompareTitle);
		else if(searchField == "authors")
		    dataList.sort(T::CompareAuthors);
		else if(searchField == "year")
		    dataList.sort(T::CompareYear);
		else if(searchField == "tags")
		    dataList.sort(T::CompareTags);
		else if(searchField == "artists")
		    dataList.sort(T::CompareArtists);
		else if(searchField == "genre")
		    dataList.sort(T::CompareGenre);
		else if(searchField == "director")
		    dataList.sort(T::CompareTitle);
		else if(searchField == "starring")
		    dataList.sort(T::CompareTitle);
		else	// if field is something else
		    throw WrongCommand();   // then command is wrong
		
		// iterate through sorted list and add instances to the command result
		for(auto it = dataList.begin(); it != dataList.end(); ++it)
		    commandResult << *it;
	    }
	}
	// book, music, and movie classes are child classes of the same class
	// this is because not every function is member of every three of
	// them, but since this function is a template it should work for
	// each of them thus to satisfy the compiler the base class has
	// every getter and compare function in it with nothing but
	// blank method throw, this catch is for that, but this exception
	// won't ever execute with current state of the code
	catch(BlankMethod e){
	    throw WrongCommand();
	}
	catch(WrongCommand e){	// inform about wrong comman error
	    out << "Exception: " << e.what() << std::endl
		<< readLine << std::endl;
	    delete fields;	// deallocate
	    continue;		// get to next line of command file
	}

	out << readLine << std::endl	// write read line that is the command
	    << commandResult.str();	// write command result
	delete fields;			// deallocate
    }
}
#endif//TEMPLATES_HPP
