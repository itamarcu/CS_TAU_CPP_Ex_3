#include "AlgorithmRegistration.h"
#include "TournamentManager.h"

AlgorithmRegistration::AlgorithmRegistration(std::string id,
                                             std::function<std::unique_ptr<PlayerAlgorithm>()> factory) {
    TournamentManager::getTournamentManager().registerAlgorithm(id, std::move(factory));

}