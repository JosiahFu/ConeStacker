#include <vector>
#include <string>

void saveScore(const char * name, int score);

std::vector<std::string> getNames();

std::vector<int> getScores();

std::vector<int> getTimestamps();

// Checks if a score is within the top 10 scores on the leaderboard
bool checkScore(int score);