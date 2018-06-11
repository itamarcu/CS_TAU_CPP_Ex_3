#include <iostream>
#include "AutoPlayerAlgorithm.h"
#include "MyPiecePosition.h"
#include "MyJokerChange.h"
#include "MyMove.h"

#define SIZE_OF_BIASED_JOKER_ARRAY 6
#define BIASED_JOKER_ARRAY {SCISSORS_CHAR, ROCK_CHAR, PAPER_CHAR, ROCK_CHAR, SCISSORS_CHAR, ROCK_CHAR}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<std::unique_ptr<FightInfo>> &fights) {
    (void) fights; // avoid compiler warning about unused parameter v__v
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            unsigned int res = (unsigned int) b.getPlayer(MyPoint(i, j));
            if (res == 0) {
                myBoard[i][j] = NoPlayer;
            } else if (res != player) {
                myBoard[i][j] = EnemyPlayer;
            }
        }
    }
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move &move) {
    int from_x = move.getFrom().getX() - 0; // TODO 1-indexing
    int from_y = move.getFrom().getY() - 0;
    int to_x = move.getTo().getX() - 0;
    int to_y = move.getTo().getY() - 0;
    enemyPieceWhichJustAttacked = myBoard[from_x][from_y] | CanMove;
    myBoard[from_x][from_y] = NoPlayer;
    if (myBoard[to_x][to_y] == NoPlayer) {
        myBoard[to_x][to_y] = enemyPieceWhichJustAttacked; // if there is no player in destination just move
        enemyPieceWhichJustAttacked = 0;
    } //else, there will be a fight and the knowledge will be updated then

    ourPieceWhichJustAttacked = 0;
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
    int fight_x = fightInfo.getPosition().getX() - 0; // TODO 1-indexing
    int fight_y = fightInfo.getPosition().getY() - 0;
    auto winner = (unsigned int) fightInfo.getWinner();
    if (winner == 0) {
        myBoard[fight_x][fight_y] = 0;
    } else if (winner == player) {
        if (ourPieceWhichJustAttacked != 0) {
            //we won and we attacked.
            myBoard[fight_x][fight_y] = ourPieceWhichJustAttacked;
        }

    } else  // enemy won, let's get some information
    {
        char enemy_piece_char = fightInfo.getPiece(
                player == FIRST_PLAYER_CONST ? SECOND_PLAYER_CONST : FIRST_PLAYER_CONST);
        unsigned int encoded_enemy_piece = encode_type_from_char(enemy_piece_char) | EnemyPlayer | CanMove;
        // TODO joker smartness later
        if (ourPieceWhichJustAttacked != 0) {
            // We attacked and failed, so we can get extra information
            myBoard[fight_x][fight_y] = myBoard[fight_x][fight_y] | encoded_enemy_piece;
        } else {
            //Enemy attacked and succeeded
            myBoard[fight_x][fight_y] = encoded_enemy_piece | enemyPieceWhichJustAttacked;
        }
    }
    ourPieceWhichJustAttacked = 0;
    enemyPieceWhichJustAttacked = 0;
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove() {
    enemyPieceWhichJustAttacked = 0;
    std::unique_ptr<std::vector<MyPoint>> couldBeEnemyFlagPointsVector = get_by_filter(EnemyPlayer, CanMove);
    std::unique_ptr<std::vector<MyPoint>> myScissors = get_by_filter(Scissors | OurPlayer);
    std::unique_ptr<std::vector<MyPoint>> myRocks = get_by_filter(Rock | OurPlayer);
    std::unique_ptr<std::vector<MyPoint>> myPapers = get_by_filter(Paper | OurPlayer);

    // if we can be sure about a flag/bomb - attack that thing
    if (couldBeEnemyFlagPointsVector->size() <= F + B) {
        MyPoint &enemyFlagOrBomb = (*couldBeEnemyFlagPointsVector)[0];
        if (!myPapers->empty()) {
            MyPoint &paperPoint = (*myPapers)[0];
            return make_move(paperPoint, enemyFlagOrBomb);
        } else if (!myRocks->empty()) {
            MyPoint &rockPoint = (*myRocks)[0];
            return make_move(rockPoint, enemyFlagOrBomb);
        } else if (!myScissors->empty()) {
            MyPoint &scissorsPoint = (*myScissors)[0];
            return make_move(scissorsPoint, enemyFlagOrBomb);
        } else { // joker can't be bomb in our implementation(of the auto)
            std::cout << "Error SDKD-DSDS-SADD-DYSD-213SHD9403: shouldn't reach here  " << std::endl;
            return nullptr;
        }
    }
    std::unique_ptr<std::vector<MyPoint>> enemyScissors = get_by_filter(Scissors | EnemyPlayer);
    std::unique_ptr<std::vector<MyPoint>> enemyRocks = get_by_filter(Rock | EnemyPlayer);
    std::unique_ptr<std::vector<MyPoint>> enemyPapers = get_by_filter(Paper | EnemyPlayer);
    if (!enemyScissors->empty() && !myRocks->empty()) {
        MyPoint &rockPoint = (*myRocks)[0];
        MyPoint &enemyPiece = (*enemyScissors)[0];
        return make_move(rockPoint, enemyPiece);
    } else if (!enemyPapers->empty() && !myScissors->empty()) {
        MyPoint &scissorPoint = (*myScissors)[0];
        MyPoint &attackPoint = (*enemyPapers)[0];
        return make_move(scissorPoint, attackPoint);
    } else if (!enemyRocks->empty() && !myPapers->empty()) {
        MyPoint &paperPoint = (*myPapers)[0];
        MyPoint &attackPoint = (*enemyRocks)[0];
        return make_move(paperPoint, attackPoint);
    }
    if (random_number_in_range_inclusive(1, 10) <= 3) // 30% chance of picking a fight with someone anyways
    {
        std::unique_ptr<std::vector<MyPoint>> enemySpaces = get_by_filter(EnemyPlayer); //TODO prefer non-movers
        shuffle_vector(*enemySpaces); // random enemy, gives us more info
        MyPoint &enemyPiece = (*enemySpaces)[0];
        if (!myPapers->empty()) {
            MyPoint &paperPoint = (*myPapers)[0];
            return make_move(paperPoint, enemyPiece);
        } else if (!myRocks->empty()) {
            MyPoint &rockPoint = (*myRocks)[0];
            return make_move(rockPoint, enemyPiece);
        } else if (!myScissors->empty()) {
            MyPoint &scissorsPoint = (*myScissors)[0];
            return make_move(scissorsPoint, enemyPiece);
        } else {
            std::cout << "Error Jhllllllrbkjlv6lks: shouldn't reach here  " << std::endl;
            return nullptr;
        }
    }

    // go to an empty space
    std::unique_ptr<std::vector<MyPoint>> emptySpaces = get_by_filter(NoPlayer);
    shuffle_vector(*emptySpaces);

    auto emptySpace = (*emptySpaces)[0];
    unique_ptr<Move> move;
    if (!myPapers->empty()) {
        move = make_move((*myPapers)[0], emptySpace);
    } else if (!myRocks->empty()) {
        move = make_move((*myRocks)[0], (*emptySpaces)[0]);
    } else if (!myScissors->empty()) {
        move = make_move((*myScissors)[0], (*emptySpaces)[0]);
    } else {
        std::cout << "ERROR [3213TVJ]: shouldn't reach here" << std::endl;
        return nullptr;
    }
    myBoard[emptySpace.getX()][emptySpace.getY()] = ourPieceWhichJustAttacked;
    ourPieceWhichJustAttacked = 0;
    return move;


}

unique_ptr<Move> AutoPlayerAlgorithm::make_move(const MyPoint &from,
                                                const MyPoint &to) {
    this->ourPieceWhichJustAttacked = this->myBoard[from.getX()][from.getY()];
    this->myBoard[from.getX()][from.getY()] = NoPlayer;
    return std::make_unique<MyMove>(from, to);
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange() {
    int random = random_number_in_range_inclusive(1, 10);
    std::unique_ptr<std::vector<MyPoint>> jokerPositions = get_by_filter(Joker & OurPlayer);
    //in 70% probability
    if (random <= 7) {
        if (jokerPositions->size() == J) {
            return select_joker_change(jokerPositions, random / 4);
        } else if (jokerPositions->size() == 1) {
            return select_joker_change(jokerPositions, 0);
        }
    }
    //otherwise no change
    return nullptr;
}

unique_ptr<JokerChange>
AutoPlayerAlgorithm::select_joker_change(const unique_ptr<std::vector<MyPoint>> &jokerPositions, int pos) {
    char c;
    MyPoint &jokerPoint = (*jokerPositions)[pos];
    c = this->select_new_joker_repr(jokerPoint);

    unique_ptr<JokerChange> change = std::make_unique<MyJokerChange>(jokerPoint, c);
    return std::move(change);
}

char AutoPlayerAlgorithm::select_new_joker_repr(const MyPoint &jokerPoint) {
    char c = PAPER_CHAR;// default
    if (myBoard[jokerPoint.getX()][jokerPoint.getY()] && Scissors) {
        myBoard[jokerPoint.getX()][jokerPoint.getY()] &= ~Scissors;
        myBoard[jokerPoint.getX()][jokerPoint.getY()] |= Paper;
        c = PAPER_CHAR;
    } else if (myBoard[jokerPoint.getX()][jokerPoint.getY()] && Rock) {
        myBoard[jokerPoint.getX()][jokerPoint.getY()] &= ~Rock;
        myBoard[jokerPoint.getX()][jokerPoint.getY()] |= Scissors;
        c = SCISSORS_CHAR;
    } else if (myBoard[jokerPoint.getX()][jokerPoint.getY()] && Paper) {
        myBoard[jokerPoint.getX()][jokerPoint.getY()] &= ~Paper;
        myBoard[jokerPoint.getX()][jokerPoint.getY()] |= Rock;
        c = ROCK_CHAR;
    } else {
        std::cout << "ERROR: 32321 - should not reach here" << std::endl;
    }
    return c;
}

AutoPlayerAlgorithm::AutoPlayerAlgorithm(int player) : player((unsigned int) player),
                                                       enemyPieceWhichJustAttacked(NoPlayer) {}

AutoPlayerAlgorithm::~AutoPlayerAlgorithm() = default;

unsigned int AutoPlayerAlgorithm::encode_type_from_char(char c) const {
    switch (toupper(c)) {
        case BOMB_CHAR:
            return Bomb;
        case FLAG_CHAR:
            return Flag;
        case JOKER_CHAR:
            return Joker;
        case SCISSORS_CHAR:
            return Scissors;
        case PAPER_CHAR:
            return Paper;
        case ROCK_CHAR:
            return Rock;
        default:
            std::cout << "Error [ESFR-GPDR-MLSQ-NRTS-KLMR.743480193.PC]: AutoPlayer get piece default reached."
                      << std::endl;
            return 0;//shouldn't get here
    }

}

unique_ptr<std::vector<MyPoint>>
AutoPlayerAlgorithm::get_by_filter(unsigned int filter_in, unsigned int filter_out) const {
    std::unique_ptr<std::vector<MyPoint>> vector = std::make_unique<std::vector<MyPoint>>();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if ((myBoard[i][j] & filter_in) == filter_in) {
                if ((myBoard[i][j] & filter_out) == 0) {
                    vector->emplace_back(i, j);
                }
            }
        }
    }
    return vector;
}

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
    (void) player; // avoid compiler warning about unused parameter v__v
    std::vector<MyPoint> availableSpots;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            availableSpots.emplace_back(i, j);
        }
    }
    shuffle_vector(availableSpots);
    availableSpots.erase(availableSpots.begin() + MAX_POSSIBLE_PIECE_COUNT);
    //bias for joker
    char wantedJokerChars[SIZE_OF_BIASED_JOKER_ARRAY] = BIASED_JOKER_ARRAY;
    for (int i = 0; i < J; i++) {
        char chr = wantedJokerChars[random_number_in_range_inclusive(0, SIZE_OF_BIASED_JOKER_ARRAY - 1)];
        MyPiecePosition myPiecePosition(JOKER_CHAR, chr, availableSpots[i]);
        unsigned int value = Joker | OurPlayer |
                             encode_type_from_char(chr);
        myBoard[availableSpots[i].getX()][availableSpots[i].getY()] = value;
        vectorToFill.push_back(std::make_unique<MyPiecePosition>(myPiecePosition));
    }
    availableSpots.erase(availableSpots.begin(), availableSpots.begin() + J);

    select_non_joker_piece_to_add(vectorToFill, availableSpots, B, BOMB_CHAR, false);
    select_non_joker_piece_to_add(vectorToFill, availableSpots, S, SCISSORS_CHAR, true);
    select_non_joker_piece_to_add(vectorToFill, availableSpots, R, ROCK_CHAR, true);
    select_non_joker_piece_to_add(vectorToFill, availableSpots, P, PAPER_CHAR, true);
    select_non_joker_piece_to_add(vectorToFill, availableSpots, F, FLAG_CHAR, false);

}

void AutoPlayerAlgorithm::select_non_joker_piece_to_add(std::vector<unique_ptr<PiecePosition>> &vectorToFill,
                                                        std::vector<MyPoint> &availableSpots, int count, char chr,
                                                        bool movable) {
    for (int i = 0; i < count; i++) {
        MyPiecePosition myPiecePosition(chr, NON_JOKER_REPR_DEFAULT, availableSpots[i]);
        unsigned int value =
                OurPlayer | encode_type_from_char(chr) | (movable ? CanMove : 0);
        myBoard[availableSpots[i].getX()][availableSpots[i].getY()] = value;
        vectorToFill.push_back(std::make_unique<MyPiecePosition>(myPiecePosition));
    }
    availableSpots.erase(availableSpots.begin(), availableSpots.begin() + count);
}

