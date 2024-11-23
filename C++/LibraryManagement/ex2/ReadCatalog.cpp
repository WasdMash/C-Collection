#include "ReadCatalog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include <algorithm>

using namespace std;

// Constructor: Opens the catalog file
ReadCatalog::ReadCatalog(const char *filename) {
	catalogFile.open(filename);
	if (!catalogFile) {
		cerr << "Error: Unable to open catalog file: " << filename << endl;
		exit(1);
	}
	// Initialize for reading authors
	getline(catalogFile, nextLine);
	eofFound = false;
}

string ReadCatalog::removePunct(string &author){
    string newAuthString = "";
    int check = 0;
    for(int i=0;i<author.length();i++){
        //Checks if each character in the author name is a letter
        check = isalpha(author[i]);
        //If so, then the letter is converted to lowercase
        if(check) newAuthString += tolower(author[i]);
    }
    //Returns an empty string if there are no letters
    return newAuthString;
}

// Closes the catalog file
void ReadCatalog::close() {
	if (catalogFile.is_open()) {
		catalogFile.close();
	}
}

// Returns true if there are more authors in the file
bool ReadCatalog::isNextAuthor() {
	return !eofFound;
}

// Returns the next author in the file or an empty string if none found
string ReadCatalog::getNextAuthor() {
	string line = nextLine;
	if (getline(catalogFile, nextLine).eof()) {
		eofFound = true;
	}
	return extractAuthor(line);
}

// Extracts the author's name from a line (helper function)
string ReadCatalog::extractAuthor(string line) {
	// The line is expected to be in the format "Book Title by Author Name".
    string delimiter = " by ";
    //This should, in theory, get the string by starting from the by until the end of the line
    string authorName = line.substr(line.rfind(delimiter)+delimiter.length());
    //The graph uses the surname, which is separated by a single space
    //Annoyingly, some of these books have multiple authors which I should take into consideration
    string authorSurname = authorName.substr(authorName.rfind(" ")+1);
    return authorSurname;
}

// Overloaded << operator for ReadCatalog
ostream &operator<<(ostream &os, ReadCatalog &catalogue) {
	// Get author list from the user
	string authorFileName, outputFileName;
	cout << "Enter the name of the file containing authors: ";
	getline(cin, authorFileName);
    if(authorFileName.substr(authorFileName.length() - 4, 4) != ".txt"){
    authorFileName += ".txt";
    }

    // Ask the user for the output file name
	cout << "Enter the name of the output file: ";
	getline(cin, outputFileName);
     if(outputFileName.substr(outputFileName.length() - 4, 4) != ".txt"){
        outputFileName += ".txt";
    }

    // Redirect output to the specified file
	ofstream outputWriter(outputFileName);

	ifstream authorReader(authorFileName);
	if (!authorReader) {
		cout << "Error: Unable to open author file: " << authorFileName << endl;
		exit(1);
	}

	    //Go search through the whole file and find the occurrences of each author name
    
    string authorsToFind[5];
    int authorOccurrences[5] = {0};
    for(int i=0;i<5;i++){
        getline(authorReader, authorsToFind[i]);
    }
    //Prints out the searched authors line in the PDF
        //Don't forget to have this saved to the output file also
    string authorOutput = "";
    authorOutput += string("Searched authors: ") + authorsToFind[0].substr(authorsToFind[0].rfind(" ")+1, authorsToFind[0].length()-1);
    for(int i=1;i<5;i++){
        authorOutput += string(", ") + authorsToFind[i].substr(authorsToFind[i].rfind(" ")+1, authorsToFind[i].length()-1);
    }
    authorOutput += string("\n") + string("\n");

    string lineAuthor;
    string authorToCompare;
    int maxAuthorOccurrences = 0;
    //Max length of the bar 
    int maxBarChartSigns = 10;

    //Stops at the second-to-last line
    while(catalogue.isNextAuthor()){
        //Gets the next author in the file
        lineAuthor = catalogue.getNextAuthor();
        //Searches to find which author it is and logs relevant information
        for(int i=0;i<5;i++){
            authorToCompare = authorsToFind[i].substr(authorsToFind[i].find(" ")+1, authorsToFind[i].length()-1);
            if(catalogue.removePunct(lineAuthor) == catalogue.removePunct(authorToCompare)){
                //We've found yet another, so log this
                authorOccurrences[i]++;
            }
        }
    }


    //Start dealing with printing out the bar chart;
    authorOutput += "Author Occurrence:" + string("\n");

    //Calculating the total number of authors in the catalogue file
    for(int i=0;i<5;i++){
        maxAuthorOccurrences += authorOccurrences[i];
    }
    
    //Creating the actual bar chart now
        //Now figure out how to write this to a text file
        //Maybe store the values in a string and then write this line to the console and the output file
    int barsToDraw;
    int spacesToDraw = 0;
    for(int i=0;i<5;i++){
        //This will dictate how many bars are drawn for each author in the bar chart
        barsToDraw = (authorOccurrences[i] * maxBarChartSigns / maxAuthorOccurrences);
        authorToCompare = authorsToFind[i].substr(authorsToFind[i].find(" ")+1, authorsToFind[i].length()-1);

        //This code writes it to the console
        //The string(barsToDraw, "=") tells the code to create of length barsToDraw made of just the = symbol
        spacesToDraw = 15-authorToCompare.length();

        authorOutput +=  authorToCompare + string(spacesToDraw, ' ') + string(barsToDraw, '=') + " ";
        authorOutput += to_string(authorOccurrences[i]) + string(" (") + to_string(authorOccurrences[i]*100 / maxAuthorOccurrences) + string("%) \n");
    }

    //This code writes it to the text file
    os << authorOutput;
    outputWriter << authorOutput;
    authorReader.close();
    outputWriter.close();

	return os;
}
