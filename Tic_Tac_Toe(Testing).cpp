#include <gtest/gtest.h>
#include "tictactoe.h"
#include <sstream>
// Helper function to capture the output of print_board

std::string capturePrintBoardOutput(std::vector<std::vector<char>>& board) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    print_board(board);
    std::cout.rdbuf(old);
    return buffer.str();
}

// Test for checkwin function
TEST(TicTacToeTest, CheckWin) {
    std::vector<std::vector<char>> board = {
        {'X', 'X', 'X'},
        {'-', 'O', '-'},
        {'-', 'O', '-'}
    };
    EXPECT_TRUE(checkwin(board));
}

// Test for evaluate function
TEST(TicTacToeTest, Evaluate) {
    std::vector<std::vector<char>> board = {
        {'X', 'X', 'X'},
        {'-', 'O', '-'},
        {'-', 'O', '-'}
    };
    EXPECT_EQ(evaluate(board, 'X'), 10);
    EXPECT_EQ(evaluate(board, 'O'), -10);
}

// Test for game_over function
TEST(TicTacToeTest, GameOver) {
    std::vector<std::vector<char>> board = {
        {'X', 'X', 'X'},
        {'-', 'O', '-'},
        {'-', 'O', '-'}
    };
    EXPECT_TRUE(game_over(board));

    std::vector<std::vector<char>> board2 = {
        {'X', 'X', '-'},
        {'-', 'O', '-'},
        {'-', 'O', '-'}
    };
    EXPECT_FALSE(game_over(board2));
}

// Test for find_best_move function
TEST(TicTacToeTest, FindBestMove) {
    std::vector<std::vector<char>> board = {
        {'X', 'X', '-'},
        {'-', 'O', '-'},
        {'-', '-', '-'}
    };
    std::pair<int, int> best_move = find_best_move(board, 'X', 10);
    EXPECT_EQ(best_move.first, 0);
    EXPECT_EQ(best_move.second, 2);
}

// Test for print_board function
TEST(TicTacToeTest, PrintBoard) {
    std::vector<std::vector<char>> board = {
        {'X', 'O', 'X'},
        {'-', 'X', 'O'},
        {'O', '-', 'X'}
    };
    std::string expectedOutput =
        "X | O | X\n"
        "---------\n"
        "- | X | O\n"
        "---------\n"
        "O | - | X\n";

    EXPECT_EQ(capturePrintBoardOutput(board), expectedOutput);
}

// Test for addchar function
TEST(TicTacToeTest, AddChar) {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '-'));
    addchar(board, 1, 'X');
    addchar(board, 5, 'O');
    addchar(board, 9, 'X');

    std::vector<std::vector<char>> expectedBoard = {
        {'X', '-', '-'},
        {'-', 'O', '-'},
        {'-', '-', 'X'}
    };

    EXPECT_EQ(board, expectedBoard);
}

// Test for PlayerVsPlayer function
TEST(TicTacToeTest, PlayerVsPlayer1) {
    // Simulate the player vs player game
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '-'));
    char player1Symbol = 'X';
    char player2Symbol = 'O';

    addchar(board, 1, player1Symbol); // Player 1 move
    addchar(board, 2, player2Symbol); // Player 2 move
    addchar(board, 3, player1Symbol); // Player 1 move
    addchar(board, 5, player2Symbol); // Player 2 move
    addchar(board, 4, player1Symbol); // Player 1 move
    addchar(board, 6, player2Symbol); // Player 2 move
    addchar(board, 7, player1Symbol); // Player 1 move - Player 1 wins

    EXPECT_TRUE(checkwin(board));
    EXPECT_EQ(evaluate(board, player1Symbol), 10);
    EXPECT_EQ(evaluate(board, player2Symbol), -10);
}
// Test for PlayerVsPlayer function
TEST(TicTacToeTest, PlayerVsPlayer2) {
    // Simulate the player vs player game
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '-'));
    char player1Symbol = 'O';
    char player2Symbol = 'X';

    addchar(board, 5, player1Symbol); // Player 1 move
    addchar(board, 2, player2Symbol); // Player 2 move
    addchar(board, 9, player1Symbol); // Player 1 move
    addchar(board, 1, player2Symbol); // Player 2 move
    addchar(board, 3, player1Symbol); // Player 1 move
    addchar(board, 6, player2Symbol); // Player 2 move
    addchar(board, 7, player1Symbol); // Player 1 move - Player 1 wins

    EXPECT_TRUE(checkwin(board));
    EXPECT_EQ(evaluate(board, player1Symbol), 10);
    EXPECT_EQ(evaluate(board, player2Symbol), -10);
}

// Test for PlayerVsAI function with player as 'X'
TEST(TicTacToeTest, PlayerVsAI_PlayerX) {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '-'));
    char playerSymbol = 'X';
    char aiSymbol = 'O';

    std::vector<int> player_moves = {8, 7, 5, 6, 9}; // Predefined player moves
    int current_move_index = 0;

    while (!game_over(board)) {
        int player_move = get_next_player_move(player_moves, current_move_index);
        if (player_move != -1) {
            addchar(board, player_move, playerSymbol);
        }

        if (game_over(board)) break;

        auto ai_move = find_best_move(board, aiSymbol, 10);
        addchar(board, ai_move.first * 3 + ai_move.second + 1, aiSymbol);
    }

    EXPECT_TRUE(game_over(board));
}



TEST(TicTacToeTest, PlayerVsAI_PlayerO) {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '-'));
    char playerSymbol = 'O';
    char aiSymbol = 'X';

    std::vector<int> player_moves = {1, 2, 5, 6, 9}; // Predefined player moves
    int current_move_index = 0;

    while (!game_over(board)) {
        int player_move = get_next_player_move(player_moves, current_move_index);
        if (player_move != -1) {
            addchar(board, player_move, playerSymbol);
        }

        if (game_over(board)) break;

        auto ai_move = find_best_move(board, aiSymbol, 10);
        addchar(board, ai_move.first * 3 + ai_move.second + 1, aiSymbol);
    }

    EXPECT_TRUE(game_over(board));
}

TEST(TicTacToeTest, AIStartsAsX) {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '-'));
    char aiSymbol = 'X';
    char playerSymbol = 'O';

    std::vector<int> player_moves = {9, 3, 5, 6, 7}; // Predefined player moves
    int current_move_index = 0;

    auto ai_move = find_best_move(board, aiSymbol, 10);
    addchar(board, ai_move.first * 3 + ai_move.second + 1, aiSymbol);

    while (!game_over(board)) {
        int player_move = get_next_player_move(player_moves, current_move_index);
        if (player_move != -1) {
            addchar(board, player_move, playerSymbol);
        }

        if (game_over(board)) break;

        ai_move = find_best_move(board, aiSymbol, 10);
        addchar(board, ai_move.first * 3 + ai_move.second + 1, aiSymbol);
    }

    EXPECT_TRUE(game_over(board));
}

// Test for AI starting as 'O'
TEST(TicTacToeTest, AIStartsAsO) {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '-'));
    char aiSymbol = 'O';
    char playerSymbol = 'X';

    std::vector<int> player_moves = {6, 8, 5, 7, 9}; // Predefined player moves
    int current_move_index = 0;

    auto ai_move = find_best_move(board, aiSymbol, 10);
    addchar(board, ai_move.first * 3 + ai_move.second + 1, aiSymbol);

    while (!game_over(board)) {
        int player_move = get_next_player_move(player_moves, current_move_index);
        if (player_move != -1) {
            addchar(board, player_move, playerSymbol);
        }

        if (game_over(board)) break;

        ai_move = find_best_move(board, aiSymbol, 10);
        addchar(board, ai_move.first * 3 + ai_move.second + 1, aiSymbol);
    }

    EXPECT_TRUE(game_over(board));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
