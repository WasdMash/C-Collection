#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <iostream>

using namespace std;

/* TO DO
* Define attributes - DONE
* Getters and Setters - DONE
* Constructors and destructors  - DONE
* Use of static variables  - DONE
* Separate this into multiples file - DONE
* Operators overloads (>,<,=) - Done 
* Copy assign operator - Done
* Copy construtor - Done
* Type conversion - Done
* Friends functions - 
*/

class Game {
    private:
        string name;             // Name of the game
        int score;               // Current score in the game
        int difficultyLevel;     // Difficulty level of the game (1 = easy, 5 = hard)
        double timePlayed;       // Total time spent playing the game, in minutes
        int highScore;           // Highest score ever achieved in the game
        string genre;            // Genre of the game (e.g., sports, action)
        bool isMultiplayer;      // Whether the game supports multiplayer mode
        int releaseYear;         // Year the game was released
        string publisher;        // Name of the game's publisher
        static int count;        // Static variable to track the number of Game objects created

    public:
        Game();  // Default constructor
        Game(string nameValue, int scoreValue, int difficulty, string genreValue, bool multiplayer, int year, string publisherValue);  // Parameterized constructor
        void setAttributes(string nameValue, int scoreValue, int difficulty, string genreValue, bool multiplayer, int year, string publisherValue);  // Set the game's attributes
        string getName();           // Getter for the name
        int getScore();             // Getter for the score
        int getDifficultyLevel();   // Getter for the difficulty level
        double getTimePlayed();     // Getter for time played
        int getHighScore();         // Getter for the high score
        string getGenre();          // Getter for the genre
        bool getIsMultiplayer();    // Getter for multiplayer status
        int getReleaseYear();       // Getter for the release year
        string getPublisher();      // Getter for the publisher
        int getCount();             // Getter for the number of Game objects (static count)
        void play(double minutes);  // Simulate playing the game and update time played
        void updateHighScore(int newScore);  // Update the high score if a new score is higher

        // Operator Overloads (<,>,+,=)

        // Game1 > Game2 -> game1.operator>(Game2)

        bool operator>(const Game &other) const;
        bool operator<(const Game &other) const;

        // game1 + game2 -> game1.operator+(Game2)

        Game operator+(const Game &other) const;

        // THE BIG THREE FUNCTIONs

        //game1 = game2
        Game& operator=(const Game &other);

        Game(const Game &other);

        ~Game();  // Destructor


        // type conversion
        operator string() const;

        friend ostream& operator<<(ostream &os, const Game &other);

};
#endif