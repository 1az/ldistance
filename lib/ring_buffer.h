#pragma once

#include <cstddef>
#include <vector>

namespace NLDistance {

    // Store last "capacity" inserted element and return elements by their position in insert order
    // Look into ut/ring_buffer_ut.cpp for examples

    template <class T>
    class TRingBuffer {
    public:
        using TItem = T;

        // Const random access iterator
        class TIterator;

    public:
        // Capacity should net be zero
        TRingBuffer(size_t capacity);

        // Insert invalidates iterators
        void Insert(const TItem& item);

        const TItem& operator[](size_t pos) const;

        TIterator Begin() const;
        TIterator End() const;
        TIterator IteratorAt(size_t pos) const;

        size_t Capacity() const;
        size_t Size() const;

        void Reset();

    private:
        void VerifyPos(size_t pos) const;

    private:
        std::vector<TItem> Buffer;
        size_t StartPos;
        size_t EndPos;
        size_t EndInBuffer;
    };

} // namespace NLDistance

#define RING_BUFFER_INL_H_
#include "ring_buffer-inl.h"
#undef RING_BUFFER_INL_H_
