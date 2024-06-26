#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <iomanip>
#include <sqlite3.h>


void print_board(std::vector<std::vector<char>>& board);
void addchar(std::vector<std::vector<char>>& board, int spot, char playerSymbol);
bool checkwin(std::vector<std::vector<char>>& board);
void PlayerVsPlayer();
int evaluate(std::vector<std::vector<char>>& board, char player);
struct Node;
bool game_over(std::vector<std::vector<char>>& board);
std::vector<std::pair<int, int>> get_possible_moves(std::vector<std::vector<char>>& board);
Node* buildTree(std::vector<std::vector<char>>& board, char player, bool isMaximizingPlayer, int depth);
int alphaBeta(Node* node, int depth, int alpha, int beta, bool isMaximizingPlayer);
std::pair<int, int> find_best_move(std::vector<std::vector<char>>& board, char player, int max_depth);
void PlayerVsAI();
int get_next_player_move(const std::vector<int>& moves, int& current_move_index);

#endif
