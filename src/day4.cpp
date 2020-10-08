#include <vector>
#include <array>
#include <string>
#include "days.h"

namespace day4 {
    aoc::DayResult run() {
        aoc::DayResult result;
        std::vector<std::string> possible_passwords;

        // input start is 147981, but 147999 is the first with no decreasing digits
        std::array<char, 6> current_password{'1', '4', '7', '9', '9', '9'};
        // input end is 691423, but 699999 is the next password with no decreasing digits
        std::array<char, 6> past_last_password{'6', '9', '9', '9', '9', '9'};

        while (current_password != past_last_password) {
            possible_passwords.emplace_back(current_password.data(), 6);
            for (int i = 5; i >= 0; --i) {
                if (current_password[i] != '9') {
                    current_password[i]++;
                    for (int j = i + 1; j < 6; ++j) {
                        current_password[j] = current_password[i];
                    }
                    break;
                }
            }
        }

        std::vector<std::string> part_one_passwords;
        std::vector<std::string> part_two_passwords;
        for (auto password : possible_passwords) {
            for (int i = 0; i < 5; ++i) {
                if (password[i] == password[i + 1]) {
                    part_one_passwords.push_back(password);
                    break;
                }
            }
            for (int i = 0; i < 5; ++i) {
                bool valid = password[i] == password[i + 1];
                valid = valid && (i - 1 < 0 ? '.' : password[i - 1]) != password[i];
                valid = valid && (i + 2 > 5 ? '.' : password[i + 2]) != password[i];
                if (valid) {
                    part_two_passwords.push_back(password);
                    break;
                }
            }
        }

        result.results.emplace_back("", true, "Possible passwords", possible_passwords.size());
        result.results.emplace_back("Part one", false, "Password count", part_one_passwords.size(), 1790);
        result.results.emplace_back("Part two", false, "Password count", part_two_passwords.size(), 1206);

        return result;
    }
}
