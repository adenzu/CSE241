#include "music.hpp"
#include <string>
#include <forward_list>
#include <sstream>

using std::stringstream;
using std::forward_list;
using std::string;

namespace Catalog{
    
    // No further explanation needed for implementations here, see header file for 3 lines of comment

    Music::Music() : title{}, artists{}, year{}, genre{}
    {
	// blank
    }

    Music::Music(const Music &music) : title(music.title), artists(music.artists), year(music.year), genre(music.genre)
    {
	// blank
    }
    
    Music::Music(const forward_list<string> *fields)
    {
	auto it = fields->begin();
	genre = *it++;	
	year = std::stoi(*it++);	
	artists = *it++;	
	title = *it++;	
    }

    Music::Music(const string &_title, const string &_artists, int _year, const string &_genre)
	: title(_title), artists(_artists), year(_year), genre(_genre)
    {
	// blank
    }
    
    bool Music::CompareTitle(const Music &music1, const Music &music2) {
	return music1.title < music2.title;
    }

    bool Music::CompareArtists(const Music &music1, const Music &music2) {
	return music1.artists < music2.artists;
    }

    bool Music::CompareYear(const Music &music1, const Music &music2) {
	return music1.year < music2.year;
    }
    
    bool Music::CompareGenre(const Music &music1, const Music &music2) {
	return music1.genre < music2.genre;
    }

    stringstream & operator<<(stringstream &out, const Music &music){
	out << '"' << music.title << "\" \"" << music.artists << "\" \"" << music.year << "\" \"" 
	    << music.genre << '"' << std::endl;
	return out;
    }
}
