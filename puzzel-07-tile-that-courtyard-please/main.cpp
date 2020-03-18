/**
 * VERY DISGUSTING SOLUTION
 */ 

#include <iostream>

const int N = 8;

int tile_number = 0;

void tile_courtyard(int courtyard[N][N], int row, int col, int sRow, int sCol, int n);
void print_courtyard(int courtyard[N][N]);    

int main() {
    

    int courtyard[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            courtyard[i][j] = 0;

    courtyard[3][0] = -1;

    tile_courtyard(courtyard, 0, 0, 3, 0, N);

    print_courtyard(courtyard);

}

void tile_courtyard(int courtyard[N][N], int row, int col, int sRow, int sCol, int n) {

    bool contains_hole(int courtyard[N][N], int row, int col, int n);

    if (n == 2) {

        courtyard[row][col] = tile_number;
        courtyard[row + 1][col] = tile_number;
        courtyard[row][col + 1] = tile_number;
        courtyard[row + 1][col + 1] = tile_number;
        
        courtyard[sRow][sCol] = -1;
        
        tile_number++;

    } else {

        int half_n = n / 2;

        if (contains_hole(courtyard, row, col, half_n)) { // A

            courtyard[row + half_n    ][col + half_n - 1] = -1;
            courtyard[row + half_n - 1][col + half_n    ] = -1;
            courtyard[row + half_n    ][col + half_n    ] = -1;

            tile_courtyard(courtyard,   row,            col,            sRow,                   sCol,                   half_n); // A
            tile_courtyard(courtyard,   row + half_n,   col,            row + half_n,           col + half_n - 1,       half_n); // B
            tile_courtyard(courtyard,   row,            col + half_n,   row + half_n - 1,       col + half_n,           half_n); // C
            tile_courtyard(courtyard,   row + half_n,   col + half_n,   row + half_n,           col + half_n,           half_n); // D
            
            courtyard[row + half_n    ][col + half_n - 1] = tile_number;
            courtyard[row + half_n - 1][col + half_n    ] = tile_number;
            courtyard[row + half_n    ][col + half_n    ] = tile_number;

            tile_number++;

        } else if (contains_hole(courtyard, row + half_n, col, half_n)) { // B

            courtyard[row + half_n - 1][col + half_n - 1] = -1;
            courtyard[row + half_n - 1][col + half_n    ] = -1;
            courtyard[row + half_n    ][col + half_n    ] = -1;

            tile_courtyard(courtyard,   row,            col,            row + half_n - 1,       col + half_n - 1,       half_n); // A
            tile_courtyard(courtyard,   row + half_n,   col,            sRow,                   sCol,                   half_n); // B
            tile_courtyard(courtyard,   row,            col + half_n,   row + half_n - 1,       col + half_n,           half_n); // C
            tile_courtyard(courtyard,   row + half_n,   col + half_n,   row + half_n,           col + half_n,           half_n); // D

            courtyard[row + half_n - 1][col + half_n - 1] = tile_number;
            courtyard[row + half_n - 1][col + half_n    ] = tile_number;
            courtyard[row + half_n    ][col + half_n    ] = tile_number;

            tile_number++;


        } else if (contains_hole(courtyard, row, col + half_n, half_n)) { // C

            courtyard[row + half_n - 1][col + half_n - 1] = -1;
            courtyard[row + half_n    ][col + half_n - 1] = -1;
            courtyard[row + half_n    ][col + half_n    ] = -1;

            tile_courtyard(courtyard,   row,            col,            row + half_n - 1,       col + half_n - 1,       half_n); // A
            tile_courtyard(courtyard,   row + half_n,   col,            row + half_n,           col + half_n - 1,       half_n); // B
            tile_courtyard(courtyard,   row,            col + half_n,   sRow,                   sCol,                   half_n); // C
            tile_courtyard(courtyard,   row + half_n,   col + half_n,   row + half_n,           col + half_n,           half_n); // D

            courtyard[row + half_n - 1][col + half_n - 1] = tile_number;
            courtyard[row + half_n    ][col + half_n - 1] = tile_number;
            courtyard[row + half_n    ][col + half_n    ] = tile_number;

            tile_number++;

        } else if (contains_hole(courtyard, row + half_n, col + half_n, half_n)) { // D

            courtyard[row + half_n - 1][col + half_n - 1] = -1;
            courtyard[row + half_n    ][col + half_n - 1] = -1;
            courtyard[row + half_n - 1][col + half_n    ] = -1;

            tile_courtyard(courtyard,   row,            col,            row + half_n - 1,       col + half_n - 1,       half_n); // A
            tile_courtyard(courtyard,   row + half_n,   col,            row + half_n,           col + half_n - 1,       half_n); // B
            tile_courtyard(courtyard,   row,            col + half_n,   row + half_n - 1,       col + half_n,           half_n); // C
            tile_courtyard(courtyard,   row + half_n,   col + half_n,   sRow,                   sCol,  half_n); // D

            courtyard[row + half_n - 1][col + half_n - 1] = tile_number;
            courtyard[row + half_n    ][col + half_n - 1] = tile_number;
            courtyard[row + half_n - 1][col + half_n    ] = tile_number;

            tile_number++;

        }
    }


}

bool contains_hole(int courtyard[N][N], int row, int col, int n) {
    
    // A C
    // B D
    
    for (int i = row; i < row + n; i++) {
        for (int j = col; j < col + n; j++) {
            if (courtyard[i][j] == -1) return true;
        }
    }

    return false;
}

void print_courtyard(int courtyard[N][N]) {
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if (courtyard[i][j] == -1) std::cout << "  X  ";
            else std::cout << "  " << (char) (65 + courtyard[i][j]) << "  ";
        std::cout << std::endl << std::endl;
    }

}