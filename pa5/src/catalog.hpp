#ifndef CATALOG_HPP
#define CATALOG_HPP

#include "exceptions.hpp"
#include <string>

using std::string;
using Exceptions::BlankMethod;

namespace Catalog{

    // the sheer existence of this class is to satisfy the compiler
    // the member methods of this class won't ever execute with 
    // current state of the code
    // this class is needed for template functions to properly work
    // for book, music, and movie classes
    class CatalogBase{
	public:
	    string GetTitle() const{throw BlankMethod();}
	    string GetAuthors() const{throw BlankMethod();}
	    string GetYear() const{throw BlankMethod();}
	    string GetTags() const{throw BlankMethod();}
	    string GetArtists() const{throw BlankMethod();}
	    string GetGenre() const{throw BlankMethod();}
	    string GetDirector() const{throw BlankMethod();}
	    string GetStarring() const{throw BlankMethod();}

	    static bool CompareTitle(const CatalogBase &cb1, const CatalogBase &cb2) {throw BlankMethod();}
	    static bool CompareAuthors(const CatalogBase &cb1, const CatalogBase &cb2) {throw BlankMethod();}
	    static bool CompareYear(const CatalogBase &cb1, const CatalogBase &cb2) {throw BlankMethod();}
	    static bool CompareTags(const CatalogBase &cb1, const CatalogBase &cb2) {throw BlankMethod();}
	    static bool CompareArtists(const CatalogBase &cb1, const CatalogBase &cb2) {throw BlankMethod();}
	    static bool CompareGenre(const CatalogBase &cb1, const CatalogBase &cb2) {throw BlankMethod();}
	    static bool CompareDirector(const CatalogBase &cb1, const CatalogBase &cb2) {throw BlankMethod();}
	    static bool CompareStarring(const CatalogBase &cb1, const CatalogBase &cb2) {throw BlankMethod();}
    };

}

#endif//CATALOG_HPP
