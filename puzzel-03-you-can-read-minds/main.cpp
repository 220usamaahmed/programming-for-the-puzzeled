#include <iostream>
#include <string>
#include <algorithm>

int * select_5_cards(int seed);
std::pair<int, int> find_duplicate_suit_pair(int * cards);
void find_ordering(int * cards, std::pair<int, int> duplicate_suit_pair);

const std::string deck[] = {
    "A_C",  "A_D",  "A_H",  "A_S",  "2_C", "2_D", "2_H", "2_S", "3_C", "3_D", "3_H", "3_S",
    "4_C",  "4_D",  "4_H",  "4_S",  "5_C", "5_D", "5_H", "5_S", "6_C", "6_D", "6_H", "6_S",
    "7_C",  "7_D",  "7_H",  "7_S",  "8_C", "8_D", "8_H", "8_S", "9_C", "9_D", "9_H", "9_S",
    "10_C", "10_D", "10_H", "10_S", "J_C", "J_D", "J_H", "J_S", "Q_C", "Q_D", "Q_H", "Q_S",    
    "K_C",  "K_D",  "K_H",  "K_S"
};

const int possible_orders[][3] = {
    {0, 1, 2}, // D -> 1
    {0, 2, 1}, // D -> 2
    {1, 0, 2}, // D -> 3
    {1, 2, 0}, // D -> 4
    {2, 0, 1}, // D -> 5
    {2, 1, 0}  // D -> 6
};

int main() {

    int seed_input;
    std::cout << "Enter seed to generate random selection: ";
    std::cin >> seed_input;

    int * cards = select_5_cards(seed_input);
    for (int i = 0; i < 5; i++) std::cout << cards[i] << ":\t" << deck[cards[i]] << std::endl;
    
    std::pair<int, int> duplicate_suit_card = find_duplicate_suit_pair(cards);
    std::cout  << "Cards with same suit: " << deck[duplicate_suit_card.first] 
               << " " << deck[duplicate_suit_card.second] << std::endl;

    find_ordering(cards, duplicate_suit_card);

}

int * select_5_cards(int seed) {

    // This only works if seed has no factors in common with 52 i.e. 2, 2, 13
    int seed_choices[] = { 1, 3, 5, 7, 9, 11, 15, 17, 
                           19, 21, 23, 25, 27, 29, 31, 33, 
                           35, 37, 41, 43, 45, 47, 49, 51 };
    seed = seed_choices[seed % 24]; // Check this.

    int idx = seed;

    static int card_idxs[5];
    for (int i = 0; i < 5; i++) {
        card_idxs[i] = idx;
        idx += seed;
        if (idx > 51) idx %= 52;
    }

    return card_idxs;

}

std::pair<int, int> find_duplicate_suit_pair(int * cards) {

    int suit_ids[5];
    for (int i = 0; i < 5; i++) suit_ids[i] = cards[i] % 4;

    std::pair<int, int> duplicate_suit_pair = std::make_pair(-1, -1);
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (suit_ids[i] == suit_ids[j]) {
                duplicate_suit_pair.first = cards[i];
                duplicate_suit_pair.second = cards[j];
                break;
            }
        }
        if (duplicate_suit_pair.first != -1) break;
    }

    return duplicate_suit_pair;

}

void find_ordering(int * cards, std::pair<int, int> duplicate_suit_pair) {

    // Finding card to hide and first card to show
    int a = duplicate_suit_pair.first / 4 + 1;
    int b = duplicate_suit_pair.second / 4 + 1;

    int card_to_hide;
    int first_card_to_show;

    if (std::abs(b - a) < 13 - std::abs(b - a)) {
        card_to_hide = duplicate_suit_pair.second;
        first_card_to_show = duplicate_suit_pair.first;
    } else {
        card_to_hide = duplicate_suit_pair.first;
        first_card_to_show = duplicate_suit_pair.second;
    }

    // Finding remaining cards
    int remaining_cards[3];
    int cards_found = 0;
    for (int i = 0; i < 5; i++)
        if (cards[i] != card_to_hide && cards[i] != first_card_to_show)
            remaining_cards[cards_found++] = cards[i];

    // Sorting remaining cards
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i - 1; j++) {
            if (remaining_cards[j] > remaining_cards[j + 1]) {
                int temp = remaining_cards[j];
                remaining_cards[j] = remaining_cards[j + 1];
                remaining_cards[j + 1] = temp;
            }
        }
    }

    // Ordering remaining cards
    int ordering[3];
    int d = std::min(std::abs(b - a), 13 - std::abs(b - a));

    for (int i = 0; i < 3; i++) ordering[i] = remaining_cards[possible_orders[d - 1][i]];

    // Printing cards
    std::cout << "Ordering: "
              << deck[first_card_to_show] << " | "
              << deck[ordering[0]] << " | "
              << deck[ordering[1]] << " | "
              << deck[ordering[2]]
              << "\n\nHidden Card: " << deck[card_to_hide] << std::endl;

}
