#include "ReadCatalog.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// Helper function to extract the author's name from a line
string extractAuthor(string line)
{
    // The line is expected to be in the format "Book Title by Author Name".
    string delimiter = " by ";
    //This should, in theory, get the string by starting from the by until the end of the line
    string authorName = line.substr(s.find(delimiter), line.length-1);
    //The graph uses the surname, which is separated by a single space
    string authorSurname = authorName.substr(s.find(" "), authorName.length-1)
    return authorName;
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

string removePunct(string &author){
    string newAuthString = "";
    int check = 0;
    for(int i=0;i<author.length();i++){
        //Checks if each character in the author name is a letter
        check = isalpha(author[i]);
        //If so, then the letter is converted to lowercase
        if(check) newAuthString += to_lower(author[i]);
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
    string authorsToFind[5];
    int authorOccurrences[5] = {0};
    for(int i=0;i<5;i++){
        cout << endl << "Please enter your author #" << i << "'s name: ";
        cin >> authorsToFind[i];
    }

    ReadCatalog catalogue("book_catalog.txt");
    //Go search through the whole file and find the occurrences of each author name
        //Perhaps store them in an array of equal length and indices

    //I should overload the << to show the data as shown on the PDF
        //cout << catalogue << endl;
    //Use the formula:
        /*
        Bar chart ratio = (numAuthorOccurrences[i] / allAuthorsOccurrencces) * max=sToDraw
        //Could also replace the max=sToDraw with *100 to show the percentages to each one
         */
}