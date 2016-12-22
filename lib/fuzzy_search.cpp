#include "fuzzy_search.h"

#include <functional>
#include <istream>
#include <stdexcept>
#include <string>

namespace NLDistance {

    TFuzzySearch::TFuzzySearch(const std::string& needle, size_t maxDistance, TFuzzySearch::TCallback callback)
        : Needle(needle)
        , MaxDistance(maxDistance)
        , Callback(callback)
        , PosInHaystack(0)
        , State(needle.size() + 1)
        , Heads(needle.size() + 1, SIZE_MAX)
        , RingBuffer(needle.size() + maxDistance + 1)
    {
        if (maxDistance >= needle.size()) {
            throw std::range_error("TFuzzySearch require maxDistance < needle.size()");
        }
        Reset();
    }

    void TFuzzySearch::Feed(const std::string& str) {
        for (auto c : str) {
            Feed(c);
        }
    }

    void TFuzzySearch::Feed(std::istream& stream) {
        char c;
        while (stream.get(c)) {
            Feed(c);
        }
    }

    void TFuzzySearch::Feed(const char c) {
        std::vector<size_t> nextState(Needle.size() + 1, 0);
        std::vector<size_t> nextHeads(Needle.size() + 1, SIZE_MAX);
        for (size_t i = 1; i < Needle.size() + 1; ++i) {
            // delete from needle
            size_t bestDistance = nextState[i - 1] + 1;
            size_t bestHead = nextHeads[i - 1];
            // insert to needle
            size_t insertDistance = State[i] + 1;
            size_t insertHead = Heads[i] == SIZE_MAX ? PosInHaystack : Heads[i];
            Choose(bestDistance, bestHead, insertDistance, insertHead);
            // replace
            size_t replaceDistance = Needle[i - 1] == c ? State[i - 1] : (State[i - 1] + 1);
            size_t replaceHead = Heads[i - 1] == SIZE_MAX ? PosInHaystack : Heads[i - 1];
            Choose(bestDistance, bestHead, replaceDistance, replaceHead);

            nextState[i] = bestDistance;
            nextHeads[i] = bestHead;
        }
        std::swap(State, nextState);
        std::swap(Heads, nextHeads);
        ++PosInHaystack;
        RingBuffer.Insert(c);
        if (State.back() <= MaxDistance) {
            Callback(Heads.back(), std::string(RingBuffer.IteratorAt(Heads.back()), RingBuffer.End()));
        }
    }

    void TFuzzySearch::Reset() {
        PosInHaystack = 0;
        for (size_t i = 0; i < Needle.size() + 1; ++i) {
            State[i] = i;
            Heads[i] = SIZE_MAX; // SIZE_MAX means that this substring has not started yet
        }
        RingBuffer.Reset();
    }

    void TFuzzySearch::Choose(size_t& bestDistance, size_t& bestHead, size_t distance, size_t head) {
        if (distance > bestDistance) {
            return;
        }
        if (distance < bestDistance) {
            bestDistance = distance;
            bestHead = head;
            return;
        }
        // so distance == bestDistance
        if (head != SIZE_MAX && (bestHead == SIZE_MAX || head > bestHead)) {
            bestHead = head;
        }
    }

} // namespace NLDistance
