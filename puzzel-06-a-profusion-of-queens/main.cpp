#include <iostream>

void n_queens(int n);
bool r_queens(int board[], int current_col, int n);
bool check_conflict(int board[], int n, int new_queen_col); 
void print_board(int board[], int dimension);

int main() {

    int n;

    std::cout << "Enter the dimension of the board: " << std::endl;
    std::cin >> n;

    n_queens(n);

}

void n_queens(int n) {
    
    int * board = new int[n];
    for (int i = 0; i < n; i++) board[i] = -1;
    
    if (r_queens(board, 0, n)) print_board(board, n);
    else std::cout << "No solution exists." << std::endl; 

}

bool r_queens(int board[], int current_col, int n) {

    if (current_col == n) return true;
    else {

        for (int i = 0; i < n; i++) {
            board[current_col] = i;
            if (!check_conflict(board, n, current_col)) {
                if (r_queens(board, current_col + 1, n)) return true;
            }
        }

        return false;
    }

}

bool check_conflict(int board[], int n, int new_queen_col) {
    // Checking row
    for (int i = 0; i < n; i++)
        if (i != new_queen_col && board[i] == board[new_queen_col])
            return true;

    // Checking diagnals to the left of new_queen_col
    for (int i = 0; i < new_queen_col; i++)
        if (std::abs(board[i] - board[new_queen_col]) == new_queen_col - i) return true;

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