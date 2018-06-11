#include <iostream>
#include "Auxiliary.h"
#include <fstream>
#include "BoardIO.h"
#include "GameManager.h"
#include "FilePlayerAlgorithm.h"
#include "AutoPlayerAlgorithm.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    print_line("---Program started---");
    init_global_rng();
    if (argc < 2) {
        printf("Usage: %s [auto/file]-vs-[auto/file]\n", argv[0]);
        return -1;
    }
    DEBUGGING_MODE = argc == 3;
    if (DEBUGGING_MODE)
        cout << "DEBUGGING_MODE: ON" << endl;

    std::string argument = argv[1];
    if (!(argument == "auto-vs-file" || argument == "auto-vs-auto"
          || argument == "file-vs-auto" || argument == "file-vs-file")) {
        printf("Usage: %s [auto/file]-vs-[auto/file]\n", argv[0]);
        return -1;
    }

    std::unique_ptr<PlayerAlgorithm> p1_algo = nullptr;
    std::unique_ptr<PlayerAlgorithm> p2_algo = nullptr;
    if (argument.substr(0, 4) == "file") {
        p1_algo = std::make_unique<FilePlayerAlgorithm>(1);
    } else {
        p1_algo = std::make_unique<AutoPlayerAlgorithm>(1);
    }
    if (argument.substr(8, 4) == "file") {
        p2_algo = std::make_unique<FilePlayerAlgorithm>(2);
    } else {
        p2_algo = std::make_unique<AutoPlayerAlgorithm>(2);
    }

    Game game = Game();
    NewGameManager gm = NewGameManager(game, std::move(p1_algo), std::move(p2_algo));
    gm.run_game();
    BoardIO::store_game(game);
    print_line("---Program ended---");
    std::cout << std::flush; // might be weird
}