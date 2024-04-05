#pragma once
#ifndef FINITY_GUI_STRUTIL_H
#define FINITY_GUI_STRUTIL_H

#include <vector>
#include <strstream>

std::vector<uint32_t> tokenize(const std::string& line, const char token) {
    std::vector<uint32_t> res;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, token))
        if (!item.empty())
            res.push_back(std::stoi(item));

    return res;
}

#endif //FINITY_GUI_STRUTIL_H
