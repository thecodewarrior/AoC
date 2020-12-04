#include "Day2.h"
#include <regex>

void Day2::run() {
    std::vector<PasswordEntry> passwords;

    std::regex parse_pattern(R"(^(\d+)-(\d+) (.): (.*)$)");
    for(auto &line : read_input_lines()) {
        std::smatch match;
        if (std::regex_match(line, match, parse_pattern)) {
            passwords.push_back(
                {std::stoi(match[1].str()), std::stoi(match[2].str()), match[3].str()[0], match[4].str()});
        } else {
            AOC_ABORT(fmt::format("Invalid line `{}`", line))
        }
    }

    print_trivia("Password count", passwords.size());

    {
        int invalid_passwords = 0;
        for (auto &password : passwords) {
            int check_count = 0;
            for (auto &character : password.password) {
                if(character == password.check) {
                    check_count++;
                }
            }
            if(check_count < password.min_occurrences || check_count > password.max_occurrences) {
                invalid_passwords++;
            }
        }
        print_trivia("Invalid passwords", invalid_passwords);
        print_result("Part one", "Valid passwords", passwords.size() - invalid_passwords, 655);
    }

    {
        int invalid_passwords = 0;
        for (auto &password : passwords) {
            bool at_min = password.password[password.min_occurrences - 1] == password.check;
            bool at_max = password.password[password.max_occurrences - 1] == password.check;
            if(at_min == at_max) {
                invalid_passwords++;
            }
        }
        print_trivia("Invalid passwords", invalid_passwords);
        print_result("Part two", "Valid passwords", passwords.size() - invalid_passwords, 673);
    }
}
