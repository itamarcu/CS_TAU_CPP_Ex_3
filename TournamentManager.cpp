#include "TournamentManager.h"
#include "Auxiliary.h"
#include "Game.h"
#include "GameManager.h"
#include <dlfcn.h>
#include <dirent.h>

// defines the static variable
TournamentManager TournamentManager::theTournamentManager;

bool ends_with(std::string const &value, std::string const &ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void TournamentManager::battle_between(std::string p1_ID, std::string p2_ID) {
    std::cout << p1_ID << " VS " << p2_ID << std::endl;
    auto factory1 = algorithm_factories_by_ID[p1_ID];
    auto factory2 = algorithm_factories_by_ID[p2_ID];
    if (factory1 == nullptr) {
        std::cerr << "Algorithm " << p1_ID << " was not registered :(   one day we will fix this problem hopefully"
                  << std::endl;
    }
    if (factory2 == nullptr) {
        std::cerr << "Algorithm " << p2_ID << " was not registered :(   one day we will fix this problem hopefully"
                  << std::endl;
    }
    if (factory1 == nullptr || factory2 == nullptr) {
        exit(1);
    }
    std::unique_ptr<PlayerAlgorithm> p1_algo = factory1();
    std::unique_ptr<PlayerAlgorithm> p2_algo = factory2();
    Game game = Game();
    NewGameManager gm = NewGameManager(game, std::move(p1_algo), std::move(p2_algo));
    gm.run_game();

    switch (game.getGameWinner()) {
        case PLAYER_1_VICTORY:
            scores_by_ID[p1_ID] += 3;
            break;
        case PLAYER_2_VICTORY:
            scores_by_ID[p2_ID] += 3;
            break;
        case TIE:
            scores_by_ID[p1_ID] += 1;
            scores_by_ID[p1_ID] += 1;
            break;
        case GAME_NOT_ENDED:
            std::cerr << "ERROR: game hasn't ended but it did" << std::endl;
            break;
    }
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
            std::string file_path(path);
            file_path += std::string("/") + std::string(file_name);
            if (ends_with(file_name, ".so")) {
                //load SO file
                std::cout << "Loaded:    " << file_name << std::endl;
                void *dlh = dlopen(file_path.c_str(), RTLD_LAZY);
                if (dlh == nullptr) {
                    fprintf(stderr, "%s\n", dlerror());
                    exit(1);
                }
                IDs.insert(std::string(ent->d_name).substr(10, 9));
//                auto reg_2089 = (AlgorithmRegistration *) dlsym(dlh, "register_me_208940601");
//                (void) reg_2089;
            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "Error opening directory\n");
        exit(1);
    }

    int id_count = (int) IDs.size();

    if (DEBUGGING_MODE) {
        printf("Total number of algorithms loaded: %d\n", id_count);
    }

    if (id_count < 2) {
        std::cerr << "ERROR: less than 2 algorithms have registered. Cannot run a tournament. Shutting down."
                  << std::endl;
        return;
    }

    /*
     * Setup - reset scores
     */
    for (const auto &id : IDs) {
        scores_by_ID[id] = 0;
    }

    //TODO here: run all the battle threads
    // Each algorithm will play with the 15 algorithms in front of it and behind it, rotating around the
    // list in modulo, and skipping itself
    for (int id_index_1 = 0; id_index_1 < id_count; id_index_1++) {
        int id_index_2 = id_index_1;
        for (int game_count = 0; game_count < 15; game_count++) {
            id_index_2++;
            if (id_index_2 == id_index_1)
                id_index_2++;
            if (id_index_2 >= id_count)
                id_index_2 %= id_count;
            auto id_1 = *std::next(IDs.begin(), id_index_1);
            auto id_2 = *std::next(IDs.begin(), id_index_2);
            battle_between(id_1, id_2);
        }
    }

    //TODO here: wait for them all to finish

    /*
     * Print scores
     */

    // Declaring the type of the comparator predicate that accepts 2 pairs and returns a bool
    typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> ScoreComparator;

    // Defining a lambda function to compare two pairs. It will compare two pairs using second field

//    ScoreComparator compFunctor =
//            [](std::pair<std::string, int> elem1, std::pair<std::string, int> elem2) {
//                return elem1.second > elem2.second;  // 1 > 2 will sort by descending order (highest first)
//            };

    //TEMP:
    ScoreComparator compFunctor =
            [](std::pair<std::string, int> elem1, std::pair<std::string, int> elem2) {
                int diff = elem1.second - elem2.second;
                if (diff != 0)
                    return diff > 0;
                return elem1.first.compare(elem2.first) > 0;
            };


    std::set<std::pair<std::string, int>, ScoreComparator> sortedScoresByID(
            scores_by_ID.begin(), scores_by_ID.end(), compFunctor);

    for (std::pair<std::string, int> element : sortedScoresByID) // this is literally not a compilation bug, CLion, stop
        std::cout << element.first << " " << element.second << std::endl;
}
