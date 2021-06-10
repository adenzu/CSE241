#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>

using std::string;

namespace Exceptions{

    // base class for exceptions
    class Exception{
	public:
	    string what() const {return "base exception";}
    };

    // missing field exception
    class MissingField : public Exception{
	public:
	    string what() const {return "missing field";}
    };

    // duplicate entry exception
    class DuplicateEntry : public Exception{
	public:
	    string what() const {return "duplicate entry";}
    };

    // wrong command exception
    class WrongCommand : public Exception{
	public:
	    string what() const {return "command is wrong";}
    };
    
    // blank method exception
    class BlankMethod : public Exception{
	public:
	    string what() const {return "blank method";}
    };
}

#endif//EXCEPTIONS_HPP
