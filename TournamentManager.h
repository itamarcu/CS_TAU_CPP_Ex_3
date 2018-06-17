#include <map>
#include <iostream>
#include "PlayerAlgorithm.h"

#ifndef CS_TAU_CPP_RPS_TOURNAMENTMANAGER_H
#define CS_TAU_CPP_RPS_TOURNAMENTMANAGER_H


class TournamentManager {
    static TournamentManager theTournamentManager;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;

    // private ctor
    TournamentManager() = default;

public:
    static TournamentManager &getTournamentManager() {
        return theTournamentManager;
    }

    void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
        // TODO: should warn if id is already registered
        id2factory[id] = factoryMethod;
    }

    void run() const {
        for (auto &pair : id2factory) {
            const auto &id = pair.first;
            std::cout << id << ": ";
            const auto &factoryMethod = pair.second;
//            factoryMethod()->foo(); // TODO ???
        }
    }
};


#endif //CS_TAU_CPP_RPS_TOURNAMENTMANAGER_H