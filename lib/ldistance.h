#pragma once

#include <cstddef>

namespace NLDistance {

    // Use it like this:
    //   distance = LDistance("abc", "bcd");
    //   distance = LDistance(std::string("abc"), std::string("bcd"));
    // Look into ut/ldistance_ut.cpp for more examples

    template <class TContainerLeft, class TContainerRight>
    size_t LDistance(const TContainerLeft& left, const TContainerRight& right);

    template <class TIteratorLeft, class TIteratorRight>
    size_t LDistance(TIteratorLeft lBegin, TIteratorLeft lEnd, TIteratorRight rBegin, TIteratorRight rEnd);

    template <class TIteratorLeft, class TIteratorRight>
    size_t LDistance(TIteratorLeft lBegin, size_t lCount, TIteratorRight rBegin, size_t rCount);


    // C strings don't work like containers, so we need some overloaded versions of LDistance for "const char*" arguments

    size_t LDistance(const char* left, const char* right);

    template <class TContainer>
    size_t LDistance(const char* left, const TContainer& right);

    template <class TContainer>
    size_t LDistance(const TContainer& left, const char* right);

} // namespace NLDistance

#define LDISTANCE_INL_H_
#include "ldistance-inl.h"
#undef LDISTANCE_INL_H_
