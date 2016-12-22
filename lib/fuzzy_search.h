#pragma once

#include "ring_buffer.h"

#include <functional>
#include <istream>
#include <string>
#include <vector>

namespace NLDistance {

    class TFuzzySearch {
    public:
        // first argument is start position in the whole haystack through all feeds
        // second argument is matched haystack substring
        using TCallback = std::function<void(int, const std::string&)>;

    public:
        // Require maxDistance < needle.size()
        TFuzzySearch(const std::string& needle, size_t maxDistance, TCallback callback);

        void Feed(const std::string& str);
        void Feed(std::istream& stream);
        void Feed(const char c);

        // Restart search with a clear state
        void Reset();

    private:
        static void Choose(size_t& bestDistance, size_t& bestHead, size_t distance, size_t head);

    private:
        std::string Needle;
        size_t MaxDistance;
        TCallback Callback;

        size_t PosInHaystack;
        std::vector<size_t> State;
        std::vector<size_t> Heads;
        TRingBuffer<char> RingBuffer;
    };

} // namespace NLDistance
