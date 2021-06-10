#include "movie.hpp"
#include <string>
#include <forward_list>
#include <sstream>

using std::stringstream;
using std::forward_list;
using std::string;

namespace Catalog{
    
    Movie::Movie() : title{}, director{}, year{}, genre{}, starring{}
    {
	// blank
    }

    Movie::Movie(const Movie &movie) 
	: title(movie.title), director(movie.director), year(movie.year), genre(movie.genre), starring(movie.starring)
    {
	// blank
    }
    
    Movie::Movie(const forward_list<string> *fields)
    {
	auto it = fields->begin();
	starring = *it++;
	genre = *it++;
	year = std::stoi(*it++);
	director = *it++;
	title = *it++;
    }

    Movie::Movie(const string &_title, const string &_director, int _year, const string &_genre, const string &_starring)
	: title(_title), director(_director), year(_year), genre(_genre), starring(_starring)
    {
	// blank
    }
    
    bool Movie::CompareTitle(const Movie &movie1, const Movie &movie2) {
	return movie1.title < movie2.title;
    }

    bool Movie::CompareDirector(const Movie &movie1, const Movie &movie2) {
	return movie1.director < movie2.director;
    }

    bool Movie::CompareYear(const Movie &movie1, const Movie &movie2) {
	return movie1.year < movie2.year;
    }
    
    bool Movie::CompareGenre(const Movie &movie1, const Movie &movie2) {
	return movie1.genre < movie2.genre;
    }

    bool Movie::CompareStarring(const Movie &movie1, const Movie &movie2) {
	return movie1.starring < movie2.starring;
    }

    stringstream & operator<<(stringstream &out, const Movie &movie){
	out << '"' << movie.title << "\" \"" << movie.director << "\" \"" << movie.year << "\" \"" 
	    << movie.genre << "\" \"" << movie.starring << '"' << std::endl;
	return out;
    }
}
