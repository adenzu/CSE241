#ifndef BOOK_HPP
#define BOOK_HPP

#include "catalog.hpp"
#include <forward_list>
#include <string>
#include <sstream>

using std::forward_list;
using std::string;
using std::stringstream;

namespace Catalog{

    class Book : public CatalogBase{
	public:
	    Book();
	    Book(const Book &book);
	    Book(const forward_list<string> *fields);
	    Book(const string &_title, const string &_authors, int _year, const string &_tags);
	    
	    // Getter functions
	    string GetTitle() const{return title;}
	    string GetAuthors() const{return authors;}
	    int GetYear() const{return year;}
	    string GetTags() const{return tags;}

	    // Number of properties of a Book instance, title, authors, year, tags, 4 in total
	    static int GetFieldCount() {return 4;}  

	    // Compare functions for forward_list::sort()
	    static bool CompareTitle(const Book &book1, const Book &book2) ;
	    static bool CompareAuthors(const Book &book1, const Book &book2) ;
	    static bool CompareYear(const Book &book1, const Book &book2) ;
	    static bool CompareTags(const Book &book1, const Book &book2) ;

	    friend stringstream & operator<<(stringstream &out, const Book &book);
	private:
	    string title;
	    string authors;
	    int year;
	    string tags;
    };
}

#endif//BOOK_HPP
