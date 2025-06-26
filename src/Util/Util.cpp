//
// Created by suaio on 2025-06-26.
//
#include "../../include/Util/Util.h"
#include <iostream>
#include <regex>

namespace Util {
    // 체크 하자?
    int ReadNumberInput() {
        std::string input;
        std::getline(std::cin, input);

        // 앞뒤 공백 제거
        input.erase(0, input.find_first_not_of(" \t\r\n"));
        input.erase(input.find_last_not_of(" \t\r\n") + 1);

        // 숫자 형태인지 검사 (빈 문자열 포함 X)
        if (!std::regex_match(input, std::regex(R"(\d+)"))) {
            return -1;
        }

        try {
            return std::stoi(input);
        } catch (...) {
            return -1; // 변환 실패
        }
    }
}