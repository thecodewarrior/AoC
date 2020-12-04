#include "Day4.h"
#include <algorithm>
#include <regex>
#include <set>
#include <sstream>

void Day4::run() {

    std::vector<Passport> passports;
    Passport current_passport;

    for (auto &line : read_input_lines()) {
        if (line.empty()) {
            passports.push_back(current_passport);
            current_passport = {};
            continue;
        }

        std::stringstream line_stream(line);
        std::string field;
        while (getline(line_stream, field, ' ')) {
            auto split_point = field.find(':');
            if (split_point == -1)
                AOC_ABORT(fmt::format("Invalid field '{}' contains no ':'", field));
            auto field_name = field.substr(0, split_point);
            auto field_value = field.substr(split_point + 1);
            current_passport.fields[field_name] = field_value;
        }
    }
    if (!current_passport.fields.empty()) {
        passports.push_back(current_passport);
    }

    print_trivia("Total passports", passports.size());

    int valid_basic = 0;
    int valid_basic_no_cid = 0;
    int valid_strict = 0;
    int valid_strict_no_cid = 0;

    for (auto &passport : passports) {
        bool has_cid = passport.has_cid();

        if (!passport.validate_basic())
            continue;

        valid_basic_no_cid++;
        if (has_cid)
            valid_basic++;

        if(!passport.validate_strict())
            continue;

        valid_strict_no_cid++;
        if (has_cid)
            valid_strict++;
    }

    print_trivia("Valid passports (basic)", valid_basic);
    print_result("Part one", "Valid passports (basic, no cid)", valid_basic_no_cid, 235);
    print_trivia("Valid passports (strict)", valid_strict);
    print_result("Part two", "Valid passports (strict, no cid)", valid_strict_no_cid, 194);
}

bool Day4::Passport::has_fields(const std::vector<std::string> &required_fields) const {
    return std::all_of(required_fields.begin(), required_fields.end(),
                       [this](const auto &field) { return fields.count(field) != 0; });
}

bool Day4::Passport::validate_basic() const {
    static const std::vector<std::string> required_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    return has_fields(required_fields);
}

bool Day4::Passport::validate_strict() const {
    static const std::regex year_pattern(R"(^\d{4}$)");
    static const std::regex height_in_pattern(R"(^\d+in$)");
    static const std::regex height_cm_pattern(R"(^\d+cm$)");
    static const std::regex color_pattern(R"(^#[0-9a-f]{6}$)");
    static const std::set<std::string> valid_eye_colors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    static const std::regex passport_id_pattern(R"(^\d{9}$)");

    if (!validate_basic())
        return false;

    auto byr = fields.at("byr");
    auto iyr = fields.at("iyr");
    auto eyr = fields.at("eyr");
    auto hgt = fields.at("hgt");
    auto hcl = fields.at("hcl");
    auto ecl = fields.at("ecl");
    auto pid = fields.at("pid");
    // auto cid = fields.at("cid");

    if (std::regex_match(byr, year_pattern)) {
        int year = std::stoi(byr);
        if (year < 1920 || year > 2002)
            return false;
    } else {
        return false;
    }

    if (std::regex_match(iyr, year_pattern)) {
        int year = std::stoi(iyr);
        if (year < 2010 || year > 2020)
            return false;
    } else {
        return false;
    }

    if (std::regex_match(eyr, year_pattern)) {
        int year = std::stoi(eyr);
        if (year < 2020 || year > 2030)
            return false;
    } else {
        return false;
    }

    if (std::regex_match(hgt, height_in_pattern)) {
        int height = std::stoi(hgt.substr(0, hgt.size() - 2));
        if (height < 59 || height > 76)
            return false;
    } else if (std::regex_match(hgt, height_cm_pattern)) {
        int height = std::stoi(hgt.substr(0, hgt.size() - 2));
        if (height < 150 || height > 193)
            return false;
    } else {
        return false;
    }

    if (!std::regex_match(hcl, color_pattern)) {
        return false;
    }

    if (valid_eye_colors.count(ecl) == 0) {
        return false;
    }

    if (!std::regex_match(pid, passport_id_pattern)) {
        return false;
    }

    return true;
}

bool Day4::Passport::has_cid() const { return fields.count("cid") != 0; }
