#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <utility>
#include "PlayerAlgorithm.h"

#ifndef CS_TAU_CPP_RPS_208940601_TOURNAMENTMANAGER_H
#define CS_TAU_CPP_RPS_208940601_TOURNAMENTMANAGER_H


class TournamentManager {
private:
    static TournamentManager theTournamentManager;
    std::set<std::string> IDs;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> algorithm_factories_by_ID;
    std::map<std::string, int> scores_by_ID;

    // private ctor
    TournamentManager() = default;

public:
    static TournamentManager &getTournamentManager() {
        return theTournamentManager;
    }

    void registerAlgorithm(const std::string &id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
        // warn if id is already registered
        if (algorithm_factories_by_ID.find(id) != algorithm_factories_by_ID.end())
            std::cout << "WARNING: Algorithm " << id << "already exists!" << std::endl;
        std::cout << "Registered:    " << id << std::endl;
        algorithm_factories_by_ID[id] = std::move(factoryMethod);
    }

    void run(const char *path, int num_threads);

    void battle_between(std::string p1_ID, std::string p2_ID);
};


#endif //CS_TAU_CPP_RPS_208940601_TOURNAMENTMANAGER_H