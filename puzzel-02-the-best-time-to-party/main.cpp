#include <iostream>
#include <vector>
#include <algorithm>

void find_best_time(std::vector<std::pair<int, int>> &time_intervals, int allowed_start, int allowed_end);

int main() {

    std::vector<std::pair<int, int>> time_intervals = {
        std::make_pair(6, 7),
        std::make_pair(7, 9),
        std::make_pair(10, 11),
        std::make_pair(10, 12),
        std::make_pair(8, 10),
        std::make_pair(9, 11),
        std::make_pair(6, 8),
    };

    find_best_time(time_intervals, 4, 16);

}

void find_best_time(std::vector<std::pair<int, int>> &time_intervals, int allowed_start, int allowed_end) {

    if (allowed_end < allowed_start) {
        std::cout << "Invalid allowed time." << std::endl;
        return;
    }

    int start = time_intervals[0].first;
    int end = time_intervals[1].second;
    for (int i = 1; i < time_intervals.size(); i++) {
        start = std::min(start, time_intervals[i].first);
        end = std::max(end, time_intervals[i].second);
    }

    std::vector<int> hours(end - start + 1, 0);

    for (int i = 0; i < time_intervals.size(); i++) {
        hours[time_intervals[i].first - start]++;
        hours[time_intervals[i].second - start]--;
    }

    for (int i = 1; i < hours.size(); i++)
        hours[i] += hours[i - 1];

    int max_celeb_count = 0;
    int hour;
    for (int i = std::max(0, allowed_start - start); i < std::min(static_cast<int>(hours.size()), allowed_end - start); i++) {
        if (hours[i] > max_celeb_count) {
            max_celeb_count = hours[i];
            hour = i;
        }
    }
    hour += start;

    std::cout << "Best hour to visit: " << hour << " to " << hour + 1 << std::endl; 

}

