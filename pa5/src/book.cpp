#include "book.hpp"
#include <string>
#include <forward_list>
#include <sstream>

using std::stringstream;
using std::forward_list;
using std::string;

namespace Catalog{
    
    // No further explanation needed for implementations here, see header file for 3 lines of comment

    Book::Book() : title{}, authors{}, year{}, tags{}
    {
	// blank
    }

    Book::Book(const Book &book) : title(book.title), authors(book.authors), year(book.year), tags(book.tags)
    {
	// blank
    }
    
    Book::Book(const forward_list<string> *fields)
    {
	auto it = fields->begin();
	tags = *it++;
	year = std::stoi(*it++);
	authors = *it++;
	title = *it++;
    }

    bool Book::CompareTitle(const Book &book1, const Book &book2) {
	return book1.title < book2.title;
    }

    bool Book::CompareAuthors(const Book &book1, const Book &book2) {
	return book1.authors < book2.authors;
    }

    bool Book::CompareYear(const Book &book1, const Book &book2) {
	return book1.year < book2.year;
    }
    
    bool Book::CompareTags(const Book &book1, const Book &book2) {
	return book1.tags < book2.tags;
    }

    stringstream & operator<<(stringstream &out, const Book &book){
	out << '"' << book.title << "\" \"" << book.authors << "\" \"" << book.year << "\" \"" 
	    << book.tags << '"' << std::endl;
	return out;
    }
}
