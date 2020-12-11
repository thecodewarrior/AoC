#include "Day1.h"
#include <set>

void Day1::run() {
    std::set<int> entries;
    for(auto &line : read_input_lines()) {
        entries.insert(std::stoi(line));
    }

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
            print_trivia_fmt("2020 sum entries", {entry1, " + ", entry2});
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
            print_trivia_fmt("2020 triple-sum entries", {entry1, " + ", entry2, " + ", entry3});
            print_result("Part one", "2020 triple-sum product", entry1 * entry2 * entry3, 170098110);
        }
    }
}
