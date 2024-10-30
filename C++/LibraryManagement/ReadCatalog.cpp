// Replace the comments with your own, except you can use the comment about one-word lookahead.

// You may modify this code that I have supplied if you wish.

#include "ReadCatalog.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// Helper function to extract the author's name from a line
string extractAuthor(string line)
{
    // Should return the author's name extracted from the line.
    // The line is expected to be in the format "Book Title by Author Name".
    // You need to write this.
    string delimiter = " by ";
    //This should, in theory, get the string by starting from the by until the end of the line
    string authorName = line.substr(s.find(delimiter), line.length-1);

    return authorName; // Placeholder return
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

string ReadCatalog::getNextAuthor()
{
    // Should return the next author in the file, converted to lower case.
    // An empty string should be returned if the next author contains no letters.

    // Uses a one-word lookahead to avoid any problems relating to when end-of-file
    // is detected due to absence/presence of newline at end of file.

    // Incomplete.

    string line = nextLine;
    getline(catalogFile, nextLine);

    if (catalogFile.eof())
        eofFound = true;

    // Extract the author's name from the line.
    string author = extractAuthor(line);

    author = removePunct(author); // This is optional

    // Need to check that author contains a letter, and if not return an empty string.
        //Maybe loop through the string, checking isalpha() for every letter and converting it into lower-case if it is
    // Also need to convert to lower case before returning.

    return author;
}

bool ReadCatalog::isNextAuthor()
{
    return !eofFound;
}

void ReadCatalog::close()
{
    // Close the catalog file.
    // You must write this.
}
