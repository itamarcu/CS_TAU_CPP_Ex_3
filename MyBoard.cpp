#include "MyBoard.h"
#include "Point.h"

/*
 * MyBoard
 */
int MyBoard::getPlayer(const Point &pos) const {
    std::shared_ptr<GamePiece> piece = grid[pos.getX()][pos.getY()];
    if (piece == nullptr)
        return 0;
    return bool_to_player(piece->player);
}

MyBoard::MyBoard(const std::vector<std::vector<std::shared_ptr<GamePiece>>> &grid) : grid(grid) {}

MyBoard::MyBoard() {
    initEmptyGrid();
}

void MyBoard::initEmptyGrid() {
    for (int i = 0; i < N; i++) {
        std::vector<std::shared_ptr<GamePiece>> column;
        for (int j = 0; j < M; j++) {
            column.push_back(nullptr);
        }
        grid.push_back(column);
    }
}

MyBoard::~MyBoard() = default; // vector of vectors is freed on its own
