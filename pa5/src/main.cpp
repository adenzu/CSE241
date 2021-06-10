#include "functions.hpp"
#include "templates.hpp"
#include "book.hpp"
#include "music.hpp"
#include "movie.hpp"
#include <iostream>
#include <forward_list>
#include <string>
#include <fstream>

using namespace std;
using Catalog::Book;
using Catalog::Music;
using Catalog::Movie;

int main(){

    // Files needed for operation
    ifstream dataFile("data.txt");
    ofstream outputFile("output.txt");
    ifstream commandFile("commands.txt");

    // Catalog type has to be read beforehand
    string catalogType;
    getline(dataFile, catalogType);

    // Call functions correspondingly
    if(catalogType == "book"){
	outputFile << "Catalog Read: book\n";
	forward_list<Book> dataList;				    // List of books specified in data file
	ReadData<Book>(dataFile, dataList, outputFile);		    // Read data file and fill data list
	ExecuteCommands<Book>(commandFile, dataList, outputFile);   // Execute commands
    }// The rest of the cases are the same but for different types; music, and movie
    else if(catalogType == "music"){
	outputFile << "Catalog Read: music\n";
	forward_list<Music> dataList;
	ReadData<Music>(dataFile, dataList, outputFile);
	ExecuteCommands<Music>(commandFile, dataList, outputFile);
    }
    else if(catalogType == "movie"){
	outputFile << "Catalog Read: movie\n";
	forward_list<Movie> dataList;
	ReadData<Movie>(dataFile, dataList, outputFile);
	ExecuteCommands<Movie>(commandFile, dataList, outputFile);
    }
    else{// If catalog type doesn't match any of the types
	outputFile << "Invalid catalog type: " << catalogType << endl;
    }

    // Close files
    dataFile.close();
    outputFile.close();
    commandFile.close();
    return 0;
}
