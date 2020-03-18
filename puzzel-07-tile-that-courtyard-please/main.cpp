#include <iostream>

const int N = 16;

int tile_number = 1;

void tile_courtyard(int courtyard[N][N], int row, int col, int n);
void print_courtyard(int courtyard[N][N]);    

int main() {
    
    int courtyard[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            courtyard[i][j] = 0;
    courtyard[4][4] = -1;

    tile_courtyard(courtyard, 0, 0, N);

    print_courtyard(courtyard);

}

void tile_courtyard(int courtyard[N][N], int row, int col, int n) {

    std::pair<int, int> find_hole(int courtyard[N][N], int row, int col, int n);
    void place_tile(int courtyard[N][N], int row, int col, std::pair<int, int> hole);

    std::pair<int, int> hole = find_hole(courtyard, row, col, n);

    if (n == 2) {

        place_tile(courtyard, row, col, hole);

    } else {

        int half_n = n / 2;

        // Need to place hole in the three quadrants that dont have a hole already
        if (hole.first >= row + half_n || hole.second >= col + half_n)
            courtyard[row + half_n - 1][col + half_n - 1] = -1;

        if (hole.first < row + half_n || hole.second >= col + half_n)
            courtyard[row + half_n][col + half_n - 1] = -1;

        if (hole.first >= row + half_n || hole.second < col + half_n )
            courtyard[row + half_n - 1][col + half_n] = -1;

        if (hole.first < row + half_n || hole.second < col + half_n)
            courtyard[row + half_n][col + half_n    ] = -1;

        tile_courtyard(courtyard,   row,            col,            half_n);
        tile_courtyard(courtyard,   row + half_n,   col,            half_n);
        tile_courtyard(courtyard,   row,            col + half_n,   half_n);
        tile_courtyard(courtyard,   row + half_n,   col + half_n,   half_n);

        place_tile(courtyard, row + half_n - 1, col + half_n -1, std::make_pair(
            row + half_n + (hole.first / (row + half_n)) - 1, 
            col + half_n + (hole.second / (col + half_n)) - 1
        ));

    }

}

std::pair<int, int> find_hole(int courtyard[N][N], int row, int col, int n) {
        
    std::pair<int, int> hole = std::make_pair(-1, -1);

    for (int i = row; i < row + n; i++) {
        for (int j = col; j < col + n; j++) {
            if (courtyard[i][j] == -1) {
                hole.first = i;
                hole.second = j;
            }
        }
    }

    return hole;
}

void place_tile(int courtyard[N][N], int row, int col, std::pair<int, int> hole) {

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (row + i != hole.first || col + j != hole.second)
                courtyard[row + i][col + j] = tile_number;

    tile_number++;

}

void print_courtyard(int courtyard[N][N]) {
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if (courtyard[i][j] == -1) std::cout << "  \033[91mX\033[0m  ";
            else std::cout << "  " << (char) (65 + courtyard[i][j] % 26) << "  ";
        std::cout << std::endl << std::endl;
    }

}