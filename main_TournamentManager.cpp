#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Auxiliary.h"
#include "BoardIO.h"
#include "FilePlayerAlgorithm.h"
#include "TournamentManager.h"

using std::cout;
using std::endl;

int wrong_usage(char *argv_0) {
    printf("Usage: %s [-threads <num_threads>] [-path <path>]\n", argv_0);
    return -1;
}

int main(int argc, char *argv[]) {
    init_global_rng();

    char working_directory_buffer[1000];
    char *working_directory = getcwd(working_directory_buffer, sizeof(working_directory_buffer));
    char *path = working_directory;
    if (argc >= 3 && std::string(argv[1]) == "-path")
        path = argv[2];
    if (argc >= 5 && std::string(argv[3]) == "-path")
        path = argv[4];
    int num_threads = 1;
    if (argc >= 3 && std::string(argv[1]) == "-threads")
        num_threads = atoi(argv[2]);
    if (argc >= 5 && std::string(argv[3]) == "-threads")
        num_threads = atoi(argv[4]);

//    DEBUGGING_MODE = std::find(argv, argv + argc, "DEBUG") != argv + argc;
    DEBUGGING_MODE = true;
    if (DEBUGGING_MODE)
        cout << "DEBUGGING_MODE: ON" << endl;

    if (DEBUGGING_MODE)
        print_line("--- Program started ---");

    TournamentManager::getTournamentManager().run(path, num_threads);

//    std::unique_ptr<PlayerAlgorithm> p1_algo = nullptr;
//    std::unique_ptr<PlayerAlgorithm> p2_algo = nullptr;
//    if (argument.substr(0, 4) == "file") {
//        p1_algo = std::make_unique<FilePlayerAlgorithm>();
//    } else {
//        p1_algo = std::make_unique<RSPPlayer_208940601>();
//    }
//    if (argument.substr(8, 4) == "file") {
//        p2_algo = std::make_unique<FilePlayerAlgorithm>();
//    } else {
//        p2_algo = std::make_unique<RSPPlayer_208940601>();
//    }
//
//    Game game = Game();
//    NewGameManager gm = NewGameManager(game, std::move(p1_algo), std::move(p2_algo));
//    gm.run_game();
//    BoardIO::store_game(game);
    if (DEBUGGING_MODE)
        print_line("--- Program ended ---");
    std::cout << std::flush; // might be weird
}