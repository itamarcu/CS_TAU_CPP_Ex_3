#include "TournamentManager.h"
#include "AlgorithmRegistration.h"
#include <dlfcn.h>
#include <dirent.h>

// defines the static variable
TournamentManager TournamentManager::theTournamentManager;

bool ends_with(std::string const &value, std::string const &ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void TournamentManager::run(const char *path, int num_threads) {
    (void) num_threads;
    /*
     * Setup - dynamically load all the things
     */
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != nullptr) {
            const char *file_name = (char *) (ent->d_name);
            auto file_path = (path + std::string("/") + file_name).c_str();
            if (ends_with(file_name, "so")) {
                //load SO file
                std::cout << "Loaded:    " << file_name << std::endl;
                void *dlh = dlopen(file_path, RTLD_LAZY);
                if (dlh == nullptr) {
                    fprintf(stderr, "%s\n", dlerror());
                    exit(1);
                }
                IDs.insert(std::string(ent->d_name).substr(10, 9));
                auto reg_2089 = (AlgorithmRegistration *) dlsym(dlh, "register_me_208940601");
                (void) reg_2089;
            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "Error opening directory\n");
        exit(1);
    }

    printf("Total algorithms loaded: %d\n", (int) IDs.size());

    /*
     * Setup - reset scores
     */
    for (const auto &id : IDs) {
        scores_by_ID[id] = 0;
    }

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
            scores_by_ID.begin(), scores_by_ID.end(), compFunctor);

    for (std::pair<std::string, int> element : sortedScoresByID) // this is literally not a compilation bug, CLion, stop
        std::cout << element.first << " " << element.second << std::endl;

    printf("Total algorithms remaining: %d\n", (int) sortedScoresByID.size());
}
