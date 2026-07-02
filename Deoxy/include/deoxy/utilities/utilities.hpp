#pragma once

#include "../logging/enginelog.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace Deoxy::Utilities {
    inline std::string ReadFileAsString(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file) {
            DEOXY_WARN("Failed to read file at {}.", filepath);
            return {};
        }

        std::string line, result;
        while (std::getline(file, line)) {
            result += line;
            result += '\n';
        }

        return result;
    }
}