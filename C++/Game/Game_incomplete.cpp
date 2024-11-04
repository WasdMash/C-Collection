#include "game.h"

// Main function: Create and manipulate Game objects
int main() {
    // Create two Game objects with initial values
    Game g1("Football", 100, 3, "Sports", true, 2020, "EA Sports");
    Game g2("Basketball", 200, 4, "Sports", true, 2021, "2K Games");

    g1.play(45);  // Simulate playing the first game
    g1.updateHighScore(150);  // Update the high score for the first game

    g2.updateHighScore(250);

    // Print details for the first game
    cout << "Game: " << g1.getName() << " with score " << g1.getScore() 
         << ". Number of Game objects: " << g1.getCount() << endl;
    
    // // Print details for the second game
    // cout << "Game: " << g2.getName() << " with score " << g2.getScore() 
    //      << ". Number of Game objects: " << g2.getCount() << endl;


    if(g1 > g2)
    {
        cout << "First object is larger than the second." << endl;
    } 
    if(g1 < g2)
    {
        cout << "First object is less then the second." << endl;
    }

    Game g3(g1);

    g3 = g1 + g2;

    cout << g3;       

    return 0;  // End of program
}
