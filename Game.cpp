#include <iostream>
#include "Game.h"

GameWinner Game::getGameWinner() const {
    return gameWinner;
}

std::string Game::getGameEndReason() const {
    return gameEndReason;
}

void Game::endGame(const GameWinner gameWinner, const std::string gameEndReason) {
    Game::gameWinner = gameWinner;
    Game::gameEndReason = gameEndReason;
}

bool Game::checkWin() {
    int moveable_counts[] = {0, 0};
    int flag_counts[] = {0, 0};

    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            auto piece = board.grid[x][y];
            if (piece != nullptr) {
                if (piece->type == GamePiece::Type::Flag) {
                    flag_counts[1 - piece->player] += 1;
                }
                if (piece->canMove()) {
                    moveable_counts[1 - piece->player] += 1;
                }
            }
        }
    }

    if (moveable_counts[0] == 0 && moveable_counts[1] == 0) {
        gameWinner = TIE;
        gameEndReason = "A tie (this was not in the google doc)"
                " - moving PIECEs of the both players are eaten";
        return true;
    }
    if (moveable_counts[0] == 0) {
        gameWinner = PLAYER_2_VICTORY;
        gameEndReason = "All moving PIECEs of the opponent are eaten";
        return true;
    }
    if (moveable_counts[1] == 0) {
        gameWinner = PLAYER_1_VICTORY;
        gameEndReason = "All moving PIECEs of the opponent are eaten";
        return true;
    }
    if (flag_counts[0] == 0 && flag_counts[1] == 0) {
        gameWinner = TIE;
        gameEndReason = "A tie - all flags are eaten by both players"
                " in the position files";
        return true;
    }
    if (flag_counts[0] == 0) {
        gameWinner = PLAYER_2_VICTORY;
        gameEndReason = "All flags of the opponent are captured";
        return true;
    }
    if (flag_counts[1] == 0) {
        gameWinner = PLAYER_1_VICTORY;
        gameEndReason = "All flags of the opponent are captured";
        return true;
    }

    return false;
}

