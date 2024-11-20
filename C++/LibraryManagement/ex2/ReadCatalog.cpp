#include "ReadCatalog.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Helper function to extract the author's name from a line
    //If I really cared about multiple authors, I could create and return an array/vector of strings
string ReadCatalog::extractAuthor(string line)
{
    // The line is expected to be in the format "Book Title by Author Name".
    string delimiter = " by ";
    //This should, in theory, get the string by starting from the by until the end of the line
    string authorName = line.substr(line.rfind(delimiter)+delimiter.length(), line.length()-1);
    //The graph uses the surname, which is separated by a single space
    //Annoyingly, some of these books have multiple authors which I should take into consideration
    string authorSurname = authorName.substr(authorName.rfind(" ")+1, authorName.length()-1);
    return authorSurname;
}

ReadCatalog::ReadCatalog(const char *fname)
{
    // Open the catalog file.
    catalogFile.open(fname);
    if (!catalogFile)
    {
        cout << "Failed to open " << fname << endl;
        exit(1);
    }
    // Read the first line for lookahead.
    getline(catalogFile, nextLine);
    eofFound = false;
}

//This is the function which should automatically create the output of the program
    //It should be both printed to the console and to a text file

/*
ostream& operator<<(ostream &os, const ReadCatalog& other){
    return os;
}
*/

string removePunct(string &author){
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

string ReadCatalog::getNextAuthor()
{

    // Uses a one-word lookahead to avoid any problems relating to when end-of-file
    // is detected due to absence/presence of newline at end of file.


    string line = nextLine;
    getline(catalogFile, nextLine);

    if (catalogFile.eof()) eofFound = true;

    string author = extractAuthor(line);
    author = removePunct(author);
    return author;
}

bool ReadCatalog::isNextAuthor()
{
    return !eofFound;
}

void ReadCatalog::close()
{
    catalogFile.close();
}

int main(){
    
    //Don't forget that the user should ask for the name of the file containing the search authors
    string authorFileName;
    cout << "Please enter the name of the file containing the search authors: ";
    getline(cin, authorFileName); //Don't forget to add the .txt if they forget to add it
    //The user should ask for the name of the catalogue file to be analysed
    string catalogueFileName; //By default, should be "book_catalog.txt"
    cout << "Please enter the name of the catalogue file:";
    getline(cin, catalogueFileName);
    //The user should ask for the name of the output file
    string outputFileName;
    cout << "Please enter the name of the output file: ";
    getline(cin, outputFileName);

    //Don't forget to check if they have the .txt on the end
        //If so, I'll add it myself

    if(authorFileName.substr(authorFileName.length() - 4, 4) != ".txt"){
        authorFileName += ".txt";
    }
    if(catalogueFileName.substr(catalogueFileName.length() - 4, 4) != ".txt"){
        catalogueFileName += ".txt";
    }
    if(outputFileName.substr(outputFileName.length() - 4, 4) != ".txt"){
        outputFileName += ".txt";
    }

    //Now, try using these file names to open their respective files
    ifstream authorReader(authorFileName);
    ReadCatalog catalogue(catalogueFileName.c_str());
    ofstream outputWriter(outputFileName);
    if(!authorReader || !outputWriter){
        //Then, clearly neither of these files exist and the code should terminate cleanly
        abort();
    }
    //Go search through the whole file and find the occurrences of each author name
    
    string authorsToFind[5];
    int authorOccurrences[5] = {0};
    for(int i=0;i<5;i++){
        getline(authorReader, authorsToFind[i]);
    }
    //Prints out the searched authors line in the PDF
        //Don't forget to have this saved to the output file also
    cout << "Searched authors: " << authorsToFind[0].substr(authorsToFind[0].rfind(" ")+1, authorsToFind[0].length()-1);
    for(int i=1;i<5;i++){
        cout << ", " << authorsToFind[i].substr(authorsToFind[i].rfind(" ")+1, authorsToFind[i].length()-1);
    }
    cout << endl;

    //Write this information to the output file too
    outputWriter << "Searched authors: " << authorsToFind[0].substr(authorsToFind[0].rfind(" ")+1, authorsToFind[0].length()-1);
    for(int i=1;i<5;i++){
        outputWriter << ", " << authorsToFind[i].substr(authorsToFind[i].rfind(" ")+1, authorsToFind[i].length()-1);
    }
    outputWriter << endl;

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
            if(lineAuthor == removePunct(authorToCompare)){
                //We've found yet another, so log this
                authorOccurrences[i]++;
            }
        }

        //Calculating the total number of authors in the catalogue file
        maxAuthorOccurrences++;
    }

    //Start dealing with printing out the bar chart;
    cout << "Author Occurrence (*not representative)" << endl;
    outputWriter << "Author Occurrence (*not representative)" << endl;
    
    //Creating the actual bar chart now
        //Now figure out how to write this to a text file
        //Maybe store the values in a string and then write this line to the console and the output file
    int barsToDraw;
    for(int i=0;i<5;i++){
        //This will dictate how many bars are drawn for each author in the bar chart
        barsToDraw = authorOccurrences[i] % maxBarChartSigns ;
        authorToCompare = authorsToFind[i].substr(authorsToFind[i].find(" ")+1, authorsToFind[i].length()-1);

        //This code writes it to the console
        //The string(barsToDraw, "=") tells the code to create of length barsToDraw made of just the = symbol
        cout << setw(15) << left << authorToCompare << string(barsToDraw, '=') << " ";
        cout << authorOccurrences[i] << " (" << (authorOccurrences[i]*100 / maxAuthorOccurrences) << "%)" << endl;

        //This code writes it to the text file
        outputWriter << setw(15) << left << authorToCompare << string(barsToDraw, '=') << " ";
        outputWriter << to_string(authorOccurrences[i]) << " (" << to_string((authorOccurrences[i]*100 / maxAuthorOccurrences)) << "%)" << endl;
    }

    outputWriter.close();
    authorReader.close();
    catalogue.close();
}