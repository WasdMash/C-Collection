#include "ReadCatalog.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// Helper function to extract the author's name from a line
string ReadCatalog::extractAuthor(string line)
{
    // The line is expected to be in the format "Book Title by Author Name".
    string delimiter = " by ";
    //This should, in theory, get the string by starting from the by until the end of the line
    string authorName = line.substr(line.rfind(delimiter)+delimiter.length(), line.length()-1);
    //The graph uses the surname, which is separated by a single space
    string authorSurname = authorName.substr(authorName.find(" ")+1, authorName.length()-1);
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
    string authorsToFind[5];
    int authorOccurrences[5] = {0};
    for(int i=0;i<5;i++){
        cout << "Please enter your author #" << i+1 << "'s name: ";
        getline(cin, authorsToFind[i]);
    }

    ReadCatalog catalogue("book_catalog.txt");
    //Go search through the whole file and find the occurrences of each author name
        //Perhaps store them in an array of equal length and indices
    string lineAuthor;
    //Stops at the second-to-last line
    while(catalogue.isNextAuthor()){
        //Gets the next author in the file
        lineAuthor = catalogue.getNextAuthor();
        cout << "The current line author is: " << lineAuthor << endl;
        //Searches to find which author it is and logs relevant information
        for(int i=0;i<5;i++){
            cout << "\tWe are comparing this author with " << removePunct(authorsToFind[i]) << endl;
            if(lineAuthor == removePunct(authorsToFind[i])){
                //We've found yet another, so log this
                authorOccurrences[i]++;
            }
        }
    }

    for(int i=0;i<5;i++){
        cout << "The number of occurrences of " << authorsToFind[i] << " are " << authorOccurrences[i] << endl;
    }

    //I should overload the << to show the data as shown on the PDF
        //cout << setw(some_random_num) << catalogue << endl;
    //Use the formula:
        /*
        Bar chart ratio = (numAuthorOccurrences[i] / allAuthorsOccurrencces) * max=sToDraw
        //Could also replace the max=sToDraw with *100 to show the percentages to each one
         */
}