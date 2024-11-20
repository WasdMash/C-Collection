/**
 * ReadCatalog Interface for the Assignment
 * Do not modify the class definition, but you may add other helper functions outside the class
 */

#ifndef READCATALOG_H
#define READCATALOG_H

/**
 * ReadCatalog class. Provides mechanisms to read a catalog file and return
 * lower-case versions of author names from that file.
 */

#include <string>
#include <fstream>

using namespace std;

class ReadCatalog
{
  public:

    /**
     * Constructor. Opens the file with the given filename and associates it
     * with the catalogFile stream.
     * Initializes the other members.
     * Prints an error message then terminates the program if the file cannot be opened.
     * Must not perform any other processing.
     * @param filename - a C string naming the file to read.
     */
     ReadCatalog(const char *filename);

    /**
     * Closes the file.
     */
     void close();

    /**
     * Returns a string, being the next author in the file.
     * Returns an empty string if the next author contains no letters.
     * @return - string - next author name.
     */
     string getNextAuthor();

    /**
     * Returns true if there is a further author in the file, false if we have reached the
     * end of file.
     * @return - bool - !eof
     */
     bool isNextAuthor();

     //returns the catalo

  private:
     ifstream catalogFile;
     string nextLine;
     bool eofFound;

     /**
      * Helper function to extract the author's name from a line.
      * @param line - the line from which to extract the author.
      * @return - string - the extracted author name.
      */
     string extractAuthor(string line);

     void createOutput(); //might need a const rightafter to prevent issues with const &ReadCatalog in << overload

     friend ostream& operator<< (ostream &os, const ReadCatalog &other);

};

#endif
