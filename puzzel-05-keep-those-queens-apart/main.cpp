#include <iostream>

void find_possible_boards(int dimension);

int main() {

    int dimension;
    std::cout << "Enter the board dimension: ";
    std::cin >> dimension;

    find_possible_boards(dimension);

}

void find_possible_boards(int dimension) {

    bool check_conflict(int board[], int dimension, int new_queen_row, int new_queen_col);
    void print_board(int board[], int dimension);

    // 1-D array representing each column. -1 if Queen not present in a column
    // Row number if Queen is present in column
    int * board = new int[dimension];
    
    board[0] = 0;
    int col = 1;
    bool further_solutions = true;
    int solution_counter = 0;

    // Need to keep going back to look for more solutions until
    // we don't have any more options left in the 0th column
    while (further_solutions) {

        // Printing solution if last column reached
        if (col == dimension) {
            print_board(board, dimension);
            std::cout << std::endl;
            solution_counter++;
        }

        // Checking if we can go forward or need to backtrack
        bool next_col = false;
        for (int i = 0; i < dimension; i++) {
            if (!check_conflict(board, dimension, i, col)) {
                board[col] = i;
                col++;
                next_col = true;
                break; // Look for next column now
            }
        }
        if (next_col) continue;

        // Looking for more options by back tracking        
        int option = col - 1;

        while (true) {

            // Checking if we are all out of options
            if (option == 0 && board[option] + 1 == dimension) { 
                further_solutions = false;
                break;
            }

            // Checking if current column provides any options
            bool next_col = false;
            for (int i = board[option] + 1; i < dimension; i++) {
                if (!check_conflict(board, dimension, i, option)) {
                    board[option] = i;
                    col = option + 1;
                    next_col = true;
                    break;
                }
            }
            if (next_col) break;

            // Going back further if no option found
            board[option] = -1;
            option--;

        }

    }

    if (solution_counter == 0) std::cout << "No solutions" << std::endl;
    else std::cout << solution_counter << " board(s) found." << std::endl;

}

bool check_conflict(int board[], int dimension, int new_queen_row, int new_queen_col) {

    // Not required in our approach
    // Checking column
    // if (board[new_queen_col] == -1) return false;

    // Checking row
    for (int i = 0; i < dimension; i++)
        if (i != new_queen_col && board[i] == new_queen_row)
            return true;

    // Checking diagnals to the left of new_queen_col
    for (int i = 0; i < new_queen_col; i++) {
        if (board[i] == new_queen_row + (i - new_queen_col)) return true;
        if (board[i] == new_queen_row - (i - new_queen_col)) return true;
    }

    // Not required in our approach
    // Checking right side
    // for (int i = new_queen_col + 1; i < dimension; i++) {
    //     if (board[i] == new_queen_row + (i - new_queen_col)) return false;
    //     if (board[i] == new_queen_row - (i - new_queen_col)) return false;
    // }

    return false;

}

void print_board(int board[], int dimension) {

    for (int r = 0; r < dimension; r++) {

        for (int c = 0; c < dimension; c++) {

            if (board[c] == r) std::cout << " Q ";
            else std::cout << " . ";

        }

        std::cout << std::endl;

    }

}