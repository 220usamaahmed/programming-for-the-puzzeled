#include <iostream>

void conform(char orientations[], int size);

int main() {

    //                      1    2    3    4    5    6    7    8    9    10   11   12   13
    char orientations[] = {'F', 'F', 'B', 'H', 'B', 'F', 'B', 'B', 'B', 'F', 'H', 'F', 'F'};

    conform(orientations, sizeof(orientations) / sizeof(orientations[0]));

}

void conform(char orientations[], int size) {

    if (size == 0) return;
    
    // The second group is the one to be flipped in any case
    char orientation_to_flip = orientations[0] == 'F' ? 'B' : 'F';

    int flip_group_start;
    for (int i = 1; i < size; i++) {
        // If the group to flip is beginning
        if (orientations[i - 1] != orientation_to_flip && orientations[i] == orientation_to_flip)
            flip_group_start = i;
        // If the group to flip is ending
        else if (orientations[i - 1] == orientation_to_flip && orientations[i] != orientation_to_flip) {
            if (i - flip_group_start == 1) std::cout << "Person " << flip_group_start << " flip your cap." << std::endl;
            else std::cout << "Person " << flip_group_start << " to " << i - 1 << " flip your cap." << std::endl;
        }
    }

}