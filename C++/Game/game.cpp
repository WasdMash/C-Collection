#include "game.h"

// Initialize the static count variable to 0
int Game::count = 0;

// Default constructor: Initializes default values for the game
Game::Game() {
    cout << "Game object created" << endl;
    this->name = "Unknown";      // Default game name
    this->score = 0;             // Default score
    this->difficultyLevel = 1;   // Default difficulty (easy)
    this->timePlayed = 0.0;      // No time played initially
    this->highScore = 0;         // No high score initially
    this->genre = "Undefined";   // Default genre
    this->isMultiplayer = false; // Default to single player
    this->releaseYear = 2000;    // Default release year
    this->publisher = "Unknown"; // Default publisher
    count++;                     // Increment the count when an object is created
}

// Parameterized constructor: Sets initial values based on parameters
Game::Game(string nameValue, int scoreValue, int difficulty, string genreValue, bool multiplayer, int year, string publisherValue) {
    cout << "Game object created" << endl;
    this->name = nameValue;
    this->score = scoreValue;
    this->difficultyLevel = difficulty;
    this->timePlayed = 0.0;      // Initial time played is 0
    this->highScore = scoreValue; // Set high score to initial score
    this->genre = genreValue;
    this->isMultiplayer = multiplayer;
    this->releaseYear = year;
    this->publisher = publisherValue;
    count++;                     // Increment the count when an object is created
}

// Destructor: Called when the object is destroyed
Game::~Game() {
    cout << "Game object destructed." << endl;
    count--;  // Decrement the count when an object is destroyed
}

// Get the name of the game
string Game::getName() {
    return this->name;
}

// Get the current score in the game
int Game::getScore() {
    return this->score;
}

// Get the difficulty level of the game
int Game::getDifficultyLevel() {
    return this->difficultyLevel;
}

// Get the total time spent playing the game
double Game::getTimePlayed() {
    return this->timePlayed;
}

// Get the highest score ever achieved in the game
int Game::getHighScore() {
    return this->highScore;
}

// Get the genre of the game
string Game::getGenre() {
    return this->genre;
}

// Check if the game is multiplayer
bool Game::getIsMultiplayer() {
    return this->isMultiplayer;
}

// Get the release year of the game
int Game::getReleaseYear() {
    return this->releaseYear;
}

// Get the publisher of the game
string Game::getPublisher() {
    return this->publisher;
}

// Get the number of Game objects currently created
int Game::getCount() {
    return this->count;
}

// Set the attributes for the game
void Game::setAttributes(string nameValue, int scoreValue, int difficulty, string genreValue, bool multiplayer, int year, string publisherValue) {
    this->name = nameValue;
    this->score = scoreValue;
    this->difficultyLevel = difficulty;
    this->genre = genreValue;
    this->isMultiplayer = multiplayer;
    this->releaseYear = year;
    this->publisher = publisherValue;
}

// Simulate playing the game for a certain number of minutes
void Game::play(double minutes) {
    this->timePlayed += minutes;  // Add minutes to time played
    cout << "You played " << this->name << " for " << minutes << " minutes." << endl;
}

// Update the high score if a new score is higher than the current high score
void Game::updateHighScore(int newScore) {
    if (newScore > this->highScore) {
        this->highScore = newScore;
        cout << "New high score: " << this->highScore << endl;
    }
}

bool Game::operator>(const Game &other) const
{
    return this->highScore > other.highScore;
}

bool Game::operator<(const Game &other) const
{
    return this->highScore < other.highScore;
}

Game Game::operator+(const Game &other) const
{
    Game combined = *this;
    combined.score = this->score + other.score;
    combined.highScore = max(this->highScore,other.highScore);
    return combined;
}

Game& Game::operator=(const Game &other)
{
    name = other.name;
    score = other.score;
    highScore = other.highScore;
    // all values for variables will be the ones defined by the default constructor
    return *this;
}

Game::Game(const Game &other)
{
    cout << "Objected Created" << endl;
    name = other.name;
    score = other.score;
    highScore = other.highScore;
    // all values for variables will be the ones defined by the default constructor
    count++;
}

Game::operator string() const
{
    string tempstring;
    tempstring = "Name: " + name + " Score:" + to_string(score) + " HighScore: " + to_string(score);
    return tempstring;
}

ostream& operator<<(ostream &os, const Game &other)
{
    os << "Game: " << other.name << " with score " << other.score 
         << ". Number of Game objects: " << other.count << endl;

    return os;
}