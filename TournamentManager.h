#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include "PlayerAlgorithm.h"

#ifndef CS_TAU_CPP_RPS_TOURNAMENTMANAGER_H
#define CS_TAU_CPP_RPS_TOURNAMENTMANAGER_H


class TournamentManager {
private:
    static TournamentManager theTournamentManager;
    std::set<std::string> IDs;
    std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> algorithm_factories_by_ID;
    std::map<std::string, int> scoresByID;

    // private ctor
    TournamentManager() = default;

public:
    static TournamentManager &getTournamentManager() {
        return theTournamentManager;
    }

    void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
        // TODO: should warn if id is already registered
        algorithm_factories_by_ID[id] = factoryMethod;
    }

    void run() const;
};


#endif //CS_TAU_CPP_RPS_TOURNAMENTMANAGER_H