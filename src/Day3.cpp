#include "Day3.h"

void Day3::run_day() {
    fs::ifstream inputfile(input / "day3.txt");
    if (!inputfile.is_open()) {
        AOC_ABORT("Unable to open day3.txt");
    }

    TreeMap map;

    std::string line;
    while (getline(inputfile, line)) {
        map.add_line(line);
    }
    inputfile.close();

    print_trivia("Map size", fmt::format("({}, {})", map.width, map.height));
    int total_trees = 0;
    for (auto cell : map.map) {
        if (cell)
            total_trees++;
    }
    print_trivia("Tree count", total_trees);

    long trees_11 = map.trees_for_slope(1, 1);
    long trees_31 = map.trees_for_slope(3, 1);
    long trees_51 = map.trees_for_slope(5, 1);
    long trees_71 = map.trees_for_slope(7, 1);
    long trees_12 = map.trees_for_slope(1, 2);

    print_trivia("Encountered trees @ 1,1", trees_11);
    print_result("Part one", "Encountered trees @ 3,1", trees_31, 265);
    print_trivia("Encountered trees @ 5,1", trees_51);
    print_trivia("Encountered trees @ 7,1", trees_71);
    print_trivia("Encountered trees @ 1,2", trees_12);
    print_result("Part two", "Product of samples", trees_11 * trees_31 * trees_51 * trees_71 * trees_12, 3154761400l);
}

void Day3::TreeMap::add_line(const std::string &line) {
    if (height == 0)
        width = line.size();
    ++height;
    if (line.size() != width)
        AOC_ABORT(fmt::format("Line {} has length {}, but map width is {}", height, line.size(), width))
    for (auto &c : line) {
        map.push_back(c == '#');
    }
}

bool Day3::TreeMap::has_tree(int x, int y) {
    int wrapped_x = x % width;
    if (wrapped_x < 0 || wrapped_x >= width || y < 0 || y >= height)
        return false;
    return map[y * width + wrapped_x];
}

int Day3::TreeMap::trees_for_slope(int dx, int dy) {
    int trees = 0;
    int x = 0;
    int y = 0;

    while (y < height) {
        if (has_tree(x, y)) {
            trees++;
        }
        x += dx;
        y += dy;
    }

    return trees;
}
