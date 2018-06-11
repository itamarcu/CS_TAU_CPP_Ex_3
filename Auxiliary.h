#ifndef CS_TAU_CPP_RPS_AUXILIARY_H
#define CS_TAU_CPP_RPS_AUXILIARY_H


#include <vector>
#include <string>
#include <memory>
#include <random>
#include <algorithm>
#include <chrono>

//DEBUG
extern bool DEBUGGING_MODE;
//DEBUG

#define MAX_CONSECUTIVE_TURNS_WITHOUT_FIGHT 100

#define M 10  // Rows
#define N 10  // Columns
#define R 2  // Rocks
#define P 5  // Papers
#define S 1  // Scissors
#define B 2  // Bombs
#define J 2  // Jokers
#define F 1  // Flags

#define MAX_POSSIBLE_PIECE_COUNT (R+P+S+B+J+F)

#define ROCK_CHAR 'R'
#define PAPER_CHAR 'P'
#define SCISSORS_CHAR 'S'
#define BOMB_CHAR 'B'
#define JOKER_CHAR 'J'
#define FLAG_CHAR 'F'

#define FIRST_PLAYER_CONST 1
#define SECOND_PLAYER_CONST 2

/**
 * print line
 * @param str string to print in a seaperate line
 */
void print_line(std::string str);


/**
 * split a sting with delimiter
 * @param stringToSplit string to split
 * @param delimiter delimiter to use
 * @return vector of strings splited form the original one
 */
std::unique_ptr<std::vector<std::string>>
split_string_using_delimiter(std::string &stringToSplit, std::string &delimiter);

/**
 * @param player true for player 1, false for player 2
 * @return 1 or 2
 */
int bool_to_player(bool player);

extern std::mt19937 global_rng;

void init_global_rng();

/**
 * generate number within [from, to]
 * @param from inclusive from
 * @param to inclusive to
 * @return random number in given range
 */
int random_number_in_range_inclusive(int from, int to);

template<typename T>
void shuffle_vector(std::vector<T> &vecToShuffle) {
    std::shuffle(vecToShuffle.begin(), vecToShuffle.end(), global_rng);
}

#endif //CS_TAU_CPP_RPS_AUXILIARY_H
