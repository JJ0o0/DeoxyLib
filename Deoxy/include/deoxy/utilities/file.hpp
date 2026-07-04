#pragma once

#include "../logging/enginelog.hpp"
#include <fstream>
#include <string>
#include <sstream>

namespace Deoxy::Utilities {
    /**
     * @ingroup Utilities
     * @brief Reads the contents of a text file into a string.
     *
     * @param filepath Path to the file.
     * @return File contents as a string, or an empty string if the file
     *         could not be opened.
     *
     * @note A warning is logged if the file cannot be opened.
     */
    inline std::string ReadFileAsString(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file) {
            DEOXY_WARN("Failed to read file at {}.", filepath);
            return {};
        }

        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
}