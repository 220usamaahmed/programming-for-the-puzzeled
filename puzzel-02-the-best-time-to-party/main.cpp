#include <iostream>
#include <vector>
#include <algorithm>

void find_best_time_discrete(std::vector<std::pair<int, int>> &time_intervals, int allowed_start, int allowed_end);
void find_best_time_contineous(std::vector<std::pair<int, int>> &time_intervals, int allowed_start, int allowed_end);

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

    // find_best_time_discrete(time_intervals, 4, 16);
    find_best_time_contineous(time_intervals, 4, 16);

}

void find_best_time_discrete(std::vector<std::pair<int, int>> &time_intervals, int allowed_start, int allowed_end) {

    if (allowed_end < allowed_start) {
        std::cout << "Invalid allowed time." << std::endl;
        return;
    }

    // Finding start and ending time over all time intervals
    int start = time_intervals[0].first;
    int end = time_intervals[1].second;
    for (int i = 1; i < time_intervals.size(); i++) {
        start = std::min(start, time_intervals[i].first);
        end = std::max(end, time_intervals[i].second);
    }

    // Creating vector to record what happens at each hour, +1 for arrival, -1 for departure
    std::vector<int> hours(end - start + 1, 0);
    for (int i = 0; i < time_intervals.size(); i++) {
        hours[time_intervals[i].first - start]++;
        hours[time_intervals[i].second - start]--;
    }

    // Calculating number of celebrities at each hour
    for (int i = 1; i < hours.size(); i++) hours[i] += hours[i - 1];

    // Finding best hour in the allowed range
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

void find_best_time_contineous(std::vector<std::pair<int, int>> &time_intervals, int allowed_start, int allowed_end) {
    
    // Recording the number of celeb at the arrival times of each celebrity as the best time is bound to be a arrival time
    std::vector<int> celeb_count(time_intervals.size(), 0);
    for (int i = 0; i < time_intervals.size(); i++) {
        for (int j = 0; j < time_intervals.size(); j++) {
            if (time_intervals[i].first >= time_intervals[j].first && time_intervals[i].first < time_intervals[j].second)
                celeb_count[i]++;
        }
    }

    // Picking the celeb with the best start time within allowed range
    int max_so_far = 0;
    int celeb_to_pick = 0;
    for (int i = 0; i < time_intervals.size(); i++) {
        if (celeb_count[i] > max_so_far && time_intervals[i].first >= allowed_start && time_intervals[i].second < allowed_end) {
            max_so_far = celeb_count[i];
            celeb_to_pick = i;
        }
    }

    std::cout << "Best time to visit: " << time_intervals[celeb_to_pick].first << " to " << time_intervals[celeb_to_pick].first + 1 << std::endl;

}

