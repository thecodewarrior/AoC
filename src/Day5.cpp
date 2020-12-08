#include "Day5.h"

void Day5::run() {
    constexpr int rows = 128;
    constexpr int cols = 8;

    print_trivia("Seat count", fmt::format("{} x {} = {}", rows, cols, rows * cols));

    bool seats[rows * cols] = {};
    int boarding_passes = 0;

    for (auto &line : read_input_lines()) {
        boarding_passes++;
        int row = 0;
        int col = 0;
        int row_partition = rows / 2;
        int col_partition = cols / 2;
        for (auto &c : line) {
            switch (c) {
            case 'F':
                row_partition /= 2;
                break;
            case 'B':
                row += row_partition;
                row_partition /= 2;
                break;
            case 'L':
                col_partition /= 2;
                break;
            case 'R':
                col += col_partition;
                col_partition /= 2;
                break;
            default:
                break;
            }
        }
        seats[row * cols + col] = true;
    }

    print_trivia("Boarding pass count", boarding_passes);

    {
        int occupied_count = 0;
        for (bool seat : seats) {
            if (seat) {
                occupied_count++;
            }
        }
        print_trivia("Occupied seats", occupied_count);
    }

    {
        int highest_id = rows * cols - 1;
        while (highest_id > 0 && !seats[highest_id]) {
            highest_id--;
        }

        print_result("Part one", "Highest ID", highest_id, 991);
    }

    {
        int my_id = -1;

        int leading_empty = -1;
        int trailing_empty = 0;
        for (int i = 0; i < rows * cols; i++) {
            bool seat = seats[i];
            if (seat && leading_empty == -1) {
                leading_empty = i;
            }
            if (leading_empty == -1) {
                continue;
            }
            if (seat) {
                trailing_empty = 0;
            } else {
                trailing_empty++;
                if (my_id == -1) {
                    my_id = i;
                }
            }
        }

        print_trivia("Leading empty seats",
                     fmt::format("{} = {} rows + {}", leading_empty, leading_empty / cols, leading_empty % cols));
        print_result("Part one", "My ID", my_id);
        print_trivia("Trailing empty seats",
                     fmt::format("{} = {} rows + {}", trailing_empty, trailing_empty / cols, trailing_empty % cols));
    }
}
