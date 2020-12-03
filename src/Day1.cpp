#include "Day1.h"
#include <set>

void Day1::run_day() {
    fs::ifstream inputfile(input / "day1.txt");
    if (!inputfile.is_open()) {
        AOC_ABORT("Unable to open day1.txt");
    }

    std::set<int> entries;

    std::string line;
    while (getline(inputfile, line)) {
        entries.insert(std::stoi(line));
    }
    inputfile.close();

    print_trivia("Entry count", entries.size());

    {
        int entry1 = -1;
        int entry2 = -1;
        for (auto &entry : entries) {
            auto match = entries.find(2020 - entry);
            if(match != entries.end()) {
                entry1 = entry;
                entry2 = *match;
                break;
            }
        }
        if(entry1 == -1 && entry2 == -1) {
            print_result("Part one", "2020 sum product", "<!>");
        } else {
            print_trivia("2020 sum entries", fmt::format("{} + {}", entry1, entry2));
            print_result("Part one", "2020 sum product", entry1 * entry2, 840324);
        }
    }

    {
        int entry1 = -1;
        int entry2 = -1;
        int entry3 = -1;
        for (auto &test1 : entries) {
            for (auto &test2 : entries) {
                if(test1 + test2 > 2020) {
                    goto next1;
                }
                for (auto &test3 : entries) {
                    if(test1 + test2 + test3 == 2020) {
                        entry1 = test1;
                        entry2 = test2;
                        entry3 = test3;
                        goto found;
                    }
                    if(test1 + test2 + test3 > 2020) {
                        goto next2;
                    }
                }
                next2:;
            }
            next1:;
        }
        found:;

        if(entry1 == -1 && entry2 == -1 && entry3 == -1) {
            print_result("Part one", "2020 triple-sum product", "<!>");
        } else {
            print_trivia("2020 triple-sum entries", fmt::format("{} + {} + {}", entry1, entry2, entry3));
            print_result("Part one", "2020 triple-sum product", entry1 * entry2 * entry3, 170098110);
        }
    }
}
