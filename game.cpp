#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // Include this header for std::stringstream
#include <cctype>
#include <vector>
#include <limits>

using namespace std;

// Function to print the Tic-Tac-Toe board
void print_board(vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2)
                cout << " | ";
        }
        cout << endl;
        if (i < 2)
            cout << "---------" << endl;
    }
}

// Function to add a player's symbol to the board
void addchar(vector<vector<char>>& board, int spot, char playerSymbol) {
    int row = (spot - 1) / 3;
    int col = (spot - 1) % 3;

    if (board[row][col] == '-') {
        board[row][col] = playerSymbol;
        print_board(board);
    }
    else
    {
        cout << "Invalid spot, Try another one :";
        cin >> spot;
        addchar(board, spot, playerSymbol);
    }

}


// Function to check if there's a win
bool checkwin(vector<vector<char>>& board) {
    // Check rows and columns for a win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '-')
            return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '-')
            return true;
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-')
        return true;

    return false;
}

//Main function for PlayerVsPlayer
void PlayerVsPlayer() {

    int spot;
    char playAgain;

    char player1Symbol, player2Symbol;

    do {
        vector<vector<char>> board(3, vector<char>(3, '-'));

        print_board(board);

        bool check = false;

        // Player 1 chooses their symbol
        cout << "Player 1, choose your symbol (X or O): ";
        cin >> player1Symbol;

        player1Symbol = toupper(player1Symbol);
        // Assign opposite symbol to Player 2
        player2Symbol = (player1Symbol == 'X') ? 'O' : 'X';

        cout << "Player 2 uses " << player2Symbol << endl;

        char currentPlayerSymbol = player1Symbol;

        for (int round = 1; round <= 9; ++round) {
            cout << "Enter the spot you would like to add your character in: ";
            cin >> spot;

            while (spot > 9 || spot <= 0) {
                cout << "Invalid move. Try again: ";
                cin >> spot;
            }

            addchar(board, spot, currentPlayerSymbol);

            check = checkwin(board);

            if (check)
                break;
            else
                currentPlayerSymbol = (currentPlayerSymbol == player1Symbol) ? player2Symbol : player1Symbol;
        }

        if (check)
            cout << "The Winner is " << currentPlayerSymbol << endl;
        else
            cout << "The game is a tie" << endl;

        cout << "Do you want to play again (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');
}


// Function to evaluate the current state of the board
int evaluate(vector<vector<char>>& board) {
    // Checking rows for a win or loss
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'X')
                return 10;
            else if (board[row][0] == 'O')
                return -10;
        }
    }
    // Checking columns for a win or loss
    for (int col = 0; col < 3; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'X')
                return 10;
            else if (board[0][col] == 'O')
                return -10;
        }
    }
    // Checking main diagonal for a win or loss
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X')
            return 10;
        else if (board[0][0] == 'O')
            return -10;
    }
    // Checking the other diagonal for a win or loss
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X')
            return 10;
        else if (board[0][2] == 'O')
            return -10;
    }

    // If no one wins
    return 0;
}

struct Node {
    vector<vector<char>> state;
    vector<Node*> children;
    int score;
    bool isMaximizingPlayer;
};

bool game_over(vector<vector<char>>& board) {
    // Check rows for a win
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != '-')
            return true;
    }

    // Check columns for a win
    for (int col = 0; col < 3; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != '-')
            return true;
    }

    // Check diagonals for a win
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-'))
        return true;

    // Check if the board is full (draw)
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == '-')
                return false; // Game is not over yet
        }
    }

    // If none of the above conditions are met, the game is not over
    return true;
}

// Define a function to get all possible moves
vector<pair<int, int>> get_possible_moves(vector<vector<char>>& board) {
    vector<pair<int, int>> possible_moves;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == '-') {
                possible_moves.push_back({ i, j });
            }
        }
    }
    return possible_moves;
}

Node* buildTree(vector<vector<char>>& board, bool isMaximizingPlayer, int depth) {
    Node* node = new Node;
    node->state = board;
    node->isMaximizingPlayer = isMaximizingPlayer;

    if (depth == 0 || game_over(node->state)) {
        node->score = evaluate(node->state);
        return node;
    }

    vector<pair<int, int>> possible_moves = get_possible_moves(node->state);
    for (auto move : possible_moves) {
        vector<vector<char>> new_board = node->state;
        new_board[move.first][move.second] = (isMaximizingPlayer) ? 'X' : 'O';
        Node* child = buildTree(new_board, !isMaximizingPlayer, depth - 1);
        node->children.push_back(child);
    }

    return node;
}

int alphaBeta(Node* node, int depth, int alpha, int beta, bool isMaximizingPlayer) {
    if (depth == 0 || game_over(node->state)) {
        return node->score;
    }

    if (isMaximizingPlayer) {
        int value = INT_MIN;
        for (Node* child : node->children) {
            value = max(value, alphaBeta(child, depth - 1, alpha, beta, false));
            alpha = max(alpha, value);
            if (beta <= alpha)
                break;
        }
        return value;
    }
    else {
        int value = INT_MAX;
        for (Node* child : node->children) {
            value = min(value, alphaBeta(child, depth - 1, alpha, beta, true));
            beta = min(beta, value);
            if (beta <= alpha)
                break;
        }
        return value;
    }
}

pair<int, int> find_best_move(vector<vector<char>>& board, int max_depth) {
    Node* root = buildTree(board, true, max_depth);
    int bestScore = INT_MIN;
    pair<int, int> bestMove;
    for (Node* child : root->children) {
        int score = alphaBeta(child, max_depth, INT_MIN, INT_MAX, false);
        if (score > bestScore) {
            bestScore = score;
            // Assuming each child represents a move, you can get the move from the state
            // In this example, let's assume the child state has only one difference from the parent state
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[i].size(); ++j) {
                    if (board[i][j] != child->state[i][j]) {
                        bestMove = { i, j };
                        break;
                    }
                }
            }
        }
    }
    return bestMove;
}
/*
// Function for MinMax algorithm with alpha-beta pruning
int minmax_alphabeta(vector<vector<char>>& board, int depth, bool is_max, int alpha, int beta) {
    int score = evaluate(board);

    if (score == 10)
        return score - depth;

    if (score == -10)
        return score + depth;

    if (board[0][0] != '-' && board[0][1] != '-' && board[0][2] != '-' &&
        board[1][0] != '-' && board[1][1] != '-' && board[1][2] != '-' &&
        board[2][0] != '-' && board[2][1] != '-' && board[2][2] != '-')
        return 0;

    if (is_max) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '-') {
                    board[i][j] = 'X';
                    best = max(best, minmax_alphabeta(board, depth + 1, !is_max, alpha, beta));
                    board[i][j] = '-';
                    alpha = max(alpha, best);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '-') {
                    board[i][j] = 'O';
                    best = min(best, minmax_alphabeta(board, depth + 1, !is_max, alpha, beta));
                    board[i][j] = '-';
                    beta = min(beta, best);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;
    }
}

// Function to find the best move using MinMax with alpha-beta pruning
pair<int, int> find_best_move(vector<vector<char>>& board) {
    int best_val = numeric_limits<int>::min();
    pair<int, int> best_move = make_pair(-1, -1);
    int alpha = numeric_limits<int>::min();
    int beta = numeric_limits<int>::max();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '-') {
                board[i][j] = 'X';
                int move_val = minmax_alphabeta(board, 0, false, alpha, beta);
                board[i][j] = '-';
                if (move_val > best_val) {
                    best_move = make_pair(i, j);
                    best_val = move_val;
                }
            }
        }
    }
    return best_move;
}*/

// Main function of AI
void PlayerVsAI() {
    char playAgain;
    char currentPlayerSymbol;
    char playerSymbol = 'O';
    char aiSymbol = 'X';
    char startingPlayer = 'P'; // 'P' for player, 'A' for AI

    do {
        vector<vector<char>> board(3, vector<char>(3, '-'));

        print_board(board);

        currentPlayerSymbol = (startingPlayer == 'P') ? playerSymbol : aiSymbol;

        int spot;
        for (int round = 1; round <= 9; ++round) {
            if (currentPlayerSymbol == playerSymbol) {
                cout << "Enter the spot you would like to add your character in: ";
                cin >> spot;

                while (spot > 9 || spot <= 0) {
                    cout << "Invalid move. Try again: ";
                    cin >> spot;
                }

                addchar(board, spot, currentPlayerSymbol);

                // Check if human player wins
                if (evaluate(board) == -10) {
                    cout << "You win!" << endl;
                    break;
                }
            }
            else { // AI's turn
                // AI's move using MinMax
                auto ai_move = find_best_move(board, 1000);
                board[ai_move.first][ai_move.second] = aiSymbol;
                cout << "AI's move:" << endl;
                print_board(board);

                // Check if AI wins
                if (evaluate(board) == 10) {
                    cout << "AI wins!" << endl;
                    break;
                }
            }

            // Check if it's a draw
            if (board[0][0] != '-' && board[0][1] != '-' && board[0][2] != '-' &&
                board[1][0] != '-' && board[1][1] != '-' && board[1][2] != '-' &&
                board[2][0] != '-' && board[2][1] != '-' && board[2][2] != '-') {
                cout << "It's a draw!" << endl;
                break;
            }

            // Switch player
            currentPlayerSymbol = (currentPlayerSymbol == playerSymbol) ? aiSymbol : playerSymbol;
        }

        // Switch starting player for the next game
        startingPlayer = (startingPlayer == 'P') ? 'A' : 'P';

        cout << "Do you want to play again (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');
}


int main()
{
    cout << "-------Welcome To Tic Tac Toe Game-------" << endl;
    int choice;
    cout << "1.PlayerVsPlayer" << endl;
    cout << "2.PlayerVsAI" << endl;
    cout << "Choose a mode to play with:" << endl;
    cin >> choice;
    if (choice == 1)
    {
        PlayerVsPlayer();
    }
    else
    {
        PlayerVsAI();
    }


    return 0;
}


