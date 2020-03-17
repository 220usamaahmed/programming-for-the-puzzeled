#include <iostream>
#include <cmath>

void break_crystal(int n, int d);

int main() {

    int n, d;

    std::cout << "Enter the number of floors in the building: ";
    std::cin >> n;
    
    std::cout << "Enter the number of crystal balls available: ";
    std::cin >> d;

    break_crystal(n, d);

}

void break_crystal(int n, int d) {

    int convert_to_decimal(int r, int digits[], int n_digits);
    int print_radix_r_number(int digits[], int n_digits);
    std::pair<int, int> find_range(int r, int digits[], int n_digits, int phase, int n);

    // Finding what radix to use
    int r = 1;
    while (std::pow(++r, d) < n);

    std::cout << "Radix used: " << r << std::endl;

    // TODO: Read https://stackoverflow.com/questions/4029870/how-to-create-a-dynamic-array-of-integers
    int *digits = new int[d];
    for (int i = 0; i < d; i++) digits[i] = 0;

    // Where to start looking
    int phase = 0;
    digits[phase] = 1;
    while (convert_to_decimal(r, digits, d) >= n) {
        digits[phase] = 0;
        digits[++phase] = 1;
    }

    char broken = 'n';
    int broken_count = 0;

    while (phase < d) {

        std::pair<int, int> range = find_range(r, digits, d, phase, n);
        std::cout << "Looking at range [" << range.first << ", " << range.second << "]" << std::endl;
    
        std::cout << "Does ball " << broken_count + 1 << " break from floor " 
                  << convert_to_decimal(r, digits, d) << "? (y/n): ";
        std::cin >> broken;

        if (broken == 'n') {
    
            if (digits[phase] < r - 1) digits[phase]++;
            else {
                if (phase == d - 1) {
                    std::cout << "Hardness Coefficient: " << convert_to_decimal(r, digits, d) << std::endl;
                    break;
                }
                phase++;
                digits[phase] = 1;
            }
    
        } else if (broken == 'y') {

            broken_count++;
    
            digits[phase]--;
            if (phase == d - 1) {
                std::cout << "Hardness Coefficient: " << convert_to_decimal(r, digits, d) << std::endl;
                break;
            }
            phase++;
            digits[phase] = 1;
    
        }
    
    }

    std::cout << broken_count << " balls broken in the process." << std::endl;

}

int convert_to_decimal(int r, int digits[], int n_digits) {
    
    int decimal_num = 0;

    for (int i = 0; i < n_digits; i++)
        decimal_num += digits[i] * std::pow(r, n_digits - 1 - i);

    return decimal_num; 

}

void print_radix_r_number(int digits[], int n_digits) {

    for (int i = 0; i < n_digits; i++)
        std::cout << digits[i] << " ";
    std::cout << std::endl;

}

std::pair<int, int> find_range(int r, int digits[], int n_digits, int phase, int n) {

    std::pair<int, int> range;
    range.first = 1;

    for (int i = 0; i < n_digits; i++) {
        
        if (i < phase) {
            range.first += digits[i] * std::pow(r, n_digits - 1 - i);
            range.second += digits[i] * std::pow(r, n_digits - 1 - i);
        } else if (i == phase) {
            range.first += (digits[i] - 1) * std::pow(r, n_digits - 1 - i);
            range.second += (r - 1) * std::pow(r, n_digits - 1 - i);
        } else {
            range.second += (r - 1) * std::pow(r, n_digits - 1 - i);
        }

    }

    if (range.second > n) range.second = n;

    return range;

}