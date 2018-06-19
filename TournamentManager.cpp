#include "TournamentManager.h"

// defines the static variable
TournamentManager TournamentManager::theTournamentManager;

void TournamentManager::run() const {
    //TODO here: run all the battle threads

    //TODO here: wait for them all to finish

    /*
     * Print scores
     */

    // Declaring the type of the comparator predicate that accepts 2 pairs and returns a bool
    typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> ScoreComparator;

    // Defining a lambda function to compare two pairs. It will compare two pairs using second field
    ScoreComparator compFunctor =
            [](std::pair<std::string, int> elem1, std::pair<std::string, int> elem2) {
                return elem1.second > elem2.second;  // 1 > 2 will sort by descending order (highest first)
            };

    std::set<std::pair<std::string, int>, ScoreComparator> sortedScoresByID(
            scoresByID.begin(), scoresByID.end(), compFunctor);

    for (std::pair<std::string, int> element : sortedScoresByID) // this is literally not a compilation bug, CLion, stop
        std::cout << element.first << " " << element.second << std::endl;
}
