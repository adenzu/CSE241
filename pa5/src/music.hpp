#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "catalog.hpp"
#include <string>
#include <forward_list>
#include <sstream>

using std::forward_list;
using std::string;
using std::stringstream;

namespace Catalog{

    class Music : public CatalogBase{
	public:
	    Music();
	    Music(const Music &music);
	    Music(const forward_list<string> *fields);
	    Music(const string &_title, const string &_artists, int _year, const string &_genre);
	    
	    // Getter functions
	    string GetTitle() const{return title;}
	    string GetArtists() const{return artists;}
	    int GetYear() const{return year;}
	    string GetGenre() const{return genre;}

	    // Number of properties of a Music instance, title, artists, year, genre, 4 in total
	    static int GetFieldCount() {return 4;}
	    
	    // Compare functions for forwar_list::sort()
	    static bool CompareTitle(const Music &music1, const Music &music2) ;
	    static bool CompareArtists(const Music &music1, const Music &music2) ;
	    static bool CompareYear(const Music &music1, const Music &music2) ;
	    static bool CompareGenre(const Music &music1, const Music &music2) ;

	    friend stringstream & operator<<(stringstream &out, const Music &music);
	private:
	    string title;
	    string artists;
	    int year;
	    string genre;
    };
}

#endif//MUSIC_HPP
