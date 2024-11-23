#include <iostream>
#include <string>

using namespace std;
#include "ReadCatalog.h"

int main() {
	string catalogFileName;

	// Ask the user for the catalog file
	cout << "Enter the name of the catalog file: ";
	getline(cin, catalogFileName);
    //Don't forget to check if they have the .txt on the end
        //If so, I'll add it myself
    if(catalogFileName.substr(catalogFileName.length()-4, 4) != ".txt"){
        catalogFileName += ".txt";
    }

	// Create the ReadCatalog object
	ReadCatalog catalog(catalogFileName.c_str());

	// Write to both console and file
	cout << catalog;

	// Close the catalog
	catalog.close();

	return 0;
}
