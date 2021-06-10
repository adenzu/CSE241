#ifndef MOVIE_HPP
#define MOVIE_HPP

#include "catalog.hpp"
#include <string>
#include <forward_list>
#include <sstream>

using std::forward_list;
using std::string;
using std::stringstream;

namespace Catalog{

    class Movie : public CatalogBase{
	public:
	    Movie();
	    Movie(const Movie &movie);
	    Movie(const forward_list<string> *fields);
	    Movie(const string &_title, const string &_director, int _year, const string &_genre, const string &_starring);
	    
	    // Getter functions
	    string GetTitle() const{return title;}
	    string GetDirector() const{return director;}
	    int GetYear() const{return year;}
	    string GetGenre() const{return genre;}
	    string GetStarring() const{return starring;}

	    // Number of properties of Movie instance, title, director, year, genre, starring, 5 in total
	    static int GetFieldCount() {return 5;}

	    // Compare functions for forward_list::sort()
	    static bool CompareTitle(const Movie &movie1, const Movie &movie2);
	    static bool CompareDirector(const Movie &movie1, const Movie &movie2);
	    static bool CompareYear(const Movie &movie1, const Movie &movie2);
	    static bool CompareGenre(const Movie &movie1, const Movie &movie2);
	    static bool CompareStarring(const Movie &movie1, const Movie &movie2);

	    friend stringstream & operator<<(stringstream &out, const Movie &movie);
	private:
	    string title;
	    string director;
	    int year;
	    string genre;
	    string starring;
    };
}

#endif//MOVIE_HPP
