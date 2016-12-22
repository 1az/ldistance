#pragma once

#ifndef RING_BUFFER_INL_H_
#error "Direct inclusion of this file is not allowed, use ring_buffer.h"
#endif
#undef RING_BUFFER_INL_H_

#include <cassert>
#include <iterator>
#include <stdexcept>

namespace NLDistance {

    template<class T>
    class TRingBuffer<T>::TIterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        using TBase = std::iterator<std::random_access_iterator_tag, T>;
        using TSelf = TRingBuffer<T>::TIterator;
        using typename TBase::value_type;
        using typename TBase::difference_type;
        using typename TBase::pointer;
        using typename TBase::reference;

    private:
        TIterator(const TRingBuffer<T>* rBuf, size_t pos)
            : RBuf(rBuf)
            , Pos(pos)
        {
        }

    public:
        const value_type& operator*() const { return (*RBuf)[Pos]; }
        const pointer operator->() const { return &(*RBuf)[Pos]; }
        const value_type& operator[](const difference_type& diff) const { return (*RBuf)[Pos + diff]; }

        TRingBuffer<T>::TIterator& operator++() { ++Pos; return *this; }
        TRingBuffer<T>::TIterator  operator++(int) { auto temp(*this); ++Pos; return temp; }
        TRingBuffer<T>::TIterator& operator+=(const difference_type& diff) { Pos += diff; return *this; }
        TRingBuffer<T>::TIterator  operator+(const difference_type& diff) { return TSelf(RBuf, Pos + diff); }

        TRingBuffer<T>::TIterator& operator--() { --Pos; return *this; }
        TRingBuffer<T>::TIterator  operator--(int) { auto temp(*this); --Pos; return temp; }
        TRingBuffer<T>::TIterator& operator-=(const difference_type& diff) { Pos -= diff; return *this; }
        TRingBuffer<T>::TIterator  operator-(const difference_type& diff) { return TSelf(RBuf, Pos - diff); }

        difference_type operator-(const TSelf& other) { return Pos - other.Pos; }

        bool operator==(const TSelf& other) const { return RBuf == other.RBuf && Pos == other.Pos; }
        bool operator!=(const TSelf& other) const { return RBuf == other.RBuf && Pos != other.Pos; }
        bool operator<(const TSelf& other) const { return RBuf == other.RBuf && Pos < other.Pos; }
        bool operator>(const TSelf& other) const { return RBuf == other.RBuf && Pos > other.Pos; }
        bool operator<=(const TSelf& other) const { return RBuf == other.RBuf && Pos <= other.Pos; }
        bool operator>=(const TSelf& other) const { return RBuf == other.RBuf && Pos >= other.Pos; }

    private:
        friend class TRingBuffer<T>;

        const TRingBuffer<T>* RBuf;
        size_t Pos;
    };

    template <class T>
    TRingBuffer<T>::TRingBuffer(size_t capacity)
        : Buffer(capacity)
        , StartPos(0)
        , EndPos(0)
        , EndInBuffer(0)
    {
        if (!capacity) {
            throw std::range_error("Zero capacity in TRingBuffer");
        }
    }

    template <class T>
    void TRingBuffer<T>::Insert(const T& item) {
        Buffer[EndInBuffer] = item;
        ++EndPos;
        ++EndInBuffer;
        if (EndInBuffer == Buffer.size()) {
            EndInBuffer = 0;
        }
        if (EndPos - StartPos > Buffer.size()) {
            ++StartPos;
        }
    }

    template <class T>
    const T& TRingBuffer<T>::operator[](size_t pos) const {
        VerifyPos(pos);
        return Buffer[(EndInBuffer + Buffer.size() - (EndPos - pos)) % Buffer.size()];
    }

    template <class T>
    typename TRingBuffer<T>::TIterator TRingBuffer<T>::Begin() const {
        return TRingBuffer<T>::TIterator(this, StartPos);
    }

    template <class T>
    typename TRingBuffer<T>::TIterator TRingBuffer<T>::End() const {
        return TRingBuffer<T>::TIterator(this, EndPos);
    }

    template <class T>
    typename TRingBuffer<T>::TIterator TRingBuffer<T>::IteratorAt(size_t pos) const {
        VerifyPos(pos);
        return TRingBuffer<T>::TIterator(this, pos);
    }

    template <class T>
    size_t TRingBuffer<T>::Capacity() const {
        return Buffer.size();
    }

    template <class T>
    size_t TRingBuffer<T>::Size() const {
        return EndPos - StartPos;
    }

    template <class T>
    void TRingBuffer<T>::Reset() {
        StartPos = 0;
        EndPos = 0;
        EndInBuffer = 0;
    }

    template <class T>
    void TRingBuffer<T>::VerifyPos(size_t pos) const {
        if (pos < StartPos || pos >= EndPos) {
            throw std::range_error("Out of range in TRingBuffer");
        }
    }

} // namespace NLDistance
