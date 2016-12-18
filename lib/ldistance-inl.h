#pragma once

#ifndef LDISTANCE_INL_H_
#error "Direct inclusion of this file is not allowed, use ldistance.h"
#endif
#undef LDISTANCE_INL_H_

#include <algorithm>
#include <cstring>
#include <iterator>
#include <utility>
#include <vector>

namespace NLDistance {

    template <class TContainerLeft, class TContainerRight>
    size_t LDistance(const TContainerLeft& left, const TContainerRight& right) {
        return LDistance(std::begin(left), std::end(left), std::begin(right), std::end(right));
    }

    template <class TIteratorLeft, class TIteratorRight>
    size_t LDistance(TIteratorLeft lBegin, TIteratorLeft lEnd, TIteratorRight rBegin, TIteratorRight rEnd) {
        return LDistance(lBegin, std::distance(lBegin, lEnd), rBegin, std::distance(rBegin, rEnd));
    }

    template <class TIteratorLeft, class TIteratorRight>
    size_t LDistance(TIteratorLeft lBegin, size_t lCount, TIteratorRight rBegin, size_t rCount) {
        if (lCount > rCount) {
            // Iterating throw a vector is faster than jumping between vectors
            return LDistance(rBegin, rCount, lBegin, lCount);
        }
        // Classic dynamic programing algorithm with storing two lines of DP table in memory
        std::vector<int> prevLine(rCount + 1);
        std::vector<int> currentLine(rCount + 1);
        for (size_t j = 0; j <= rCount; ++j) {
            currentLine[j] = j;
        }
        TIteratorLeft lIt = lBegin;
        for (size_t i = 1; i <= lCount; ++i, ++lIt) {
            std::swap(prevLine, currentLine);
            currentLine[0] = i;
            TIteratorRight rIt = rBegin;
            for (size_t j = 1; j <= rCount; ++j, ++rIt) {
                int insertDist = currentLine[j - 1] + 1;
                int deleteDist = prevLine[j] + 1;
                int replaceDist = prevLine[j - 1] + (*lIt == *rIt ? 0 : 1);
                currentLine[j] = std::min({insertDist, deleteDist, replaceDist});
            }
        }
        return currentLine.back();
    }

    size_t LDistance(const char* left, const char* right) {
        return LDistance(left, strlen(left), right, strlen(right));
    }

    template <class TContainer>
    size_t LDistance(const char* left, const TContainer& right) {
        return LDistance(left, strlen(left), std::begin(right), std::distance(std::begin(right), std::end(right)));
    }

    template <class TContainer>
    size_t LDistance(const TContainer& left, const char* right) {
        return LDistance(std::begin(left), std::distance(std::begin(left), std::end(left)), right, strlen(right));
    }


} // namespace NLDistance
