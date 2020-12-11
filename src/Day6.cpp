#include "Day6.h"
#include <vector>
#include <map>
#include <algorithm>

void Day6::run() {
    std::vector<int> group_counts;
    std::vector<std::map<char, int>> group_answers;
    int current_count;
    std::map<char, int> current_answers;

    for (auto &line : read_input_lines()) {
        if(line.empty()) {
            group_counts.push_back(current_count);
            group_answers.push_back(current_answers);
            current_count = 0;
            current_answers.clear();
            continue;
        }
        current_count++;
        for(auto &a : line) {
            current_answers[a]++;
        }
    }
    if(!current_answers.empty()) {
        group_counts.push_back(current_count);
        group_answers.push_back(current_answers);
        current_count = 0;
        current_answers.clear();
    }

    print_trivia("Group count", group_counts.size());

    {
        int answer_count = 0;
        for (auto &answers : group_answers) {
            answer_count += answers.size();
        }
        print_result("Part one", "Total anyone answered count", answer_count, 6763);
    }

    {
        int answer_count = 0;
        for (int i = 0; i < group_counts.size(); i++) {
            int count = group_counts[i];
            auto &answers = group_answers[i];
            answer_count += std::count_if(answers.begin(), answers.end(),
                          [count](const auto &entry) { return entry.second == count; });
        }
        print_result("Part two", "Total everyone answered count", answer_count);
    }

}
