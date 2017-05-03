/*
//  codepoint.cpp
//
//  Author:     Sophia Lee
//  Created:    2017. 03. 19. 12:37
//  Copyright (c) 2016 Sophia Lee. All rights reserved.
//
//
*/
#include <seshat/codepoint.h>

#include <seshat/utils.h>

#include <algorithm>

namespace seshat {

CodePoint::CodePoint(uint32_t code)
    : _code(code)
{
    if (code > 0x10FFFF) {
        throw IllegalCodePoint();
    }
}

CodePoint::~CodePoint()
{
}

uint32_t CodePoint::code() const
{
    return _code;
}

/*
Gc CodePoint::gc() const
{
    auto category = gc_table.find(_code);
    if (category != gc_table.end()) {
        return category->second;
    } else {
        if (CJK_IDEO_EXT_A_FRST <= _code && _code <= CJK_IDEO_EXT_A_LAST) {
            return Gc::Lo;
        }
        if (CJK_IDEO_FRST <= _code && _code <= CJK_IDEO_LAST) {
            return Gc::Lo;
        }
        if (HANGUL_SYLLAB_FRST <= _code && _code <= HANGUL_SYLLAB_LAST) {
            return Gc::Lo;
        }
        if (NON_PU_HIGH_SRG_FRST <= _code && _code <= NON_PU_HIGH_SRG_LAST) {
            return Gc::Cs;
        }
        if (PU_HIGH_SRG_FRST <= _code && _code <= PU_HIGH_SRG_LAST) {
            return Gc::Cs;
        }
        if (LOW_SRG_FRST <= _code && _code <= LOW_SRG_LAST) {
            return Gc::Cs;
        }
        if (PU_FRST <= _code && _code <= PU_LAST) {
            return Gc::Co;
        }
        if (TANGUT_IDEO_FRST <= _code && _code <= TANGUT_IDEO_LAST) {
            return Gc::Lo;
        }
        if (CJK_IDEO_EXT_B_FRST <= _code && _code <= CJK_IDEO_EXT_B_LAST) {
            return Gc::Lo;
        }
        if (CJK_IDEO_EXT_C_FRST <= _code && _code <= CJK_IDEO_EXT_C_LAST) {
            return Gc::Lo;
        }
        if (CJK_IDEO_EXT_D_FRST <= _code && _code <= CJK_IDEO_EXT_D_LAST) {
            return Gc::Lo;
        }
        if (CJK_IDEO_EXT_E_FRST <= _code && _code <= CJK_IDEO_EXT_E_LAST) {
            return Gc::Lo;
        }
        if (PLANE_15_PU_FRST <= _code && _code <= PLANE_15_PU_LAST) {
            return Gc::Co;
        }
        if (PLANE_16_PU_FRST <= _code && _code <= PLANE_16_PU_LAST) {
            return Gc::Co;
        }
        return Gc::Cn;
    }
}
*/

std::string CodePoint::to_string() const
{
    return code_point_to_string(_code);
}

CodePoint& CodePoint::operator=(const CodePoint& origin)
{
    _code = origin._code;
    return *this;
}

CodePoint& CodePoint::operator=(uint32_t code)
{
    _code = code;
    return *this;
}

bool CodePoint::operator==(const CodePoint& other) const
{
    return _code == other._code;
}

bool CodePoint::operator!=(const CodePoint& other) const
{
    return _code != other._code;
}

// class CodePointSequence
CodePointSequence::CodePointSequence()
    : _codes(std::vector<CodePoint>())
{
}

CodePointSequence::CodePointSequence(const CodePointSequence& origin)
    : _codes(std::vector<CodePoint>(origin._codes))
{
}

CodePointSequence::CodePointSequence(iterator first, iterator last)
    : _codes(std::vector<CodePoint>())
{
    for (auto it = first; it != last; it++) {
        this->_codes.push_back(*it);
    }
}

CodePointSequence::CodePointSequence(std::initializer_list<CodePoint> init)
    : _codes(init)
{
}

CodePointSequence::~CodePointSequence()
{
}

size_t CodePointSequence::length() const
{
    return this->_codes.size();
}

void CodePointSequence::append(const CodePoint& cp)
{
    this->_codes.push_back(cp);
}

CodePointSequence::iterator CodePointSequence::begin()
{
    iterator it = iterator(&*(_codes.begin()));
    return it;
}

CodePointSequence::const_iterator CodePointSequence::begin() const
{
    const_iterator it = const_iterator(&*(_codes.cbegin()));
    return it;
}

CodePointSequence::iterator CodePointSequence::end()
{
    iterator it = iterator(&*(_codes.end()));
    return it;
}

CodePointSequence::const_iterator CodePointSequence::end() const
{
    const_iterator it = const_iterator(&*(_codes.cend()));
    return it;
}

// class CodePointSequenceIter
CodePointSequenceIter::CodePointSequenceIter(pointer ptr)
    : _ptr(ptr)
{
}

bool
CodePointSequenceIter::operator==(const CodePointSequenceIter& other) const
{
    return this->_ptr == other._ptr;
}

bool
CodePointSequenceIter::operator!=(const CodePointSequenceIter& other) const
{
    return this->_ptr != other._ptr;
}

bool
CodePointSequenceIter::operator<(const CodePointSequenceIter& other) const
{
    return this->_ptr < other._ptr;
}

bool
CodePointSequenceIter::operator>(const CodePointSequenceIter& other) const
{
    return this->_ptr > other._ptr;
}

bool
CodePointSequenceIter::operator<=(const CodePointSequenceIter& other) const
{
    return this->_ptr <= other._ptr;
}

bool
CodePointSequenceIter::operator>=(const CodePointSequenceIter& other) const
{
    return this->_ptr >= other._ptr;
}

CodePointSequenceIter& CodePointSequenceIter::operator++()
{
    this->_ptr++;
    return *this;
}

CodePointSequenceIter CodePointSequenceIter::operator++(int)
{
    CodePointSequenceIter ret = *this;
    this->_ptr++;
    return ret;
}

CodePointSequenceIter& CodePointSequenceIter::operator--()
{
    this->_ptr--;
    return *this;
}

CodePointSequenceIter CodePointSequenceIter::operator--(int)
{
    CodePointSequenceIter ret = *this;
    this->_ptr--;
    return ret;
}

CodePointSequenceIter&
CodePointSequenceIter::operator+=(CodePointSequenceIter::difference_type n)
{
    auto m = n;
    if (m >= 0) {
        while (m--) ++(*this);
    } else {
        while (m++) --(*this);
    }
    return *this;
}

CodePointSequenceIter&
CodePointSequenceIter::operator-=(CodePointSequenceIter::difference_type n)
{
    return *this += -n;
}

CodePointSequenceIter CodePointSequenceIter::operator+(
        CodePointSequenceIter::difference_type n) const
{
    auto ret = *this;
    return ret += n;
}

CodePointSequenceIter CodePointSequenceIter::operator-(
        CodePointSequenceIter::difference_type n) const
{
    auto ret = *this;
    return ret -= n;
}

CodePointSequenceIter::difference_type
CodePointSequenceIter::operator-(const CodePointSequenceIter& other) const
{
    difference_type n = 0;
    auto temp = *this;
    if (*this > other) {
        while (temp != other) {
            --temp;
            ++n;
        }
    } else {
        while (temp != other) {
            ++temp;
            --n;
        }
    }
    return n;
}

CodePointSequenceIter::reference
CodePointSequenceIter::operator[](CodePointSequenceIter::difference_type n)
{
    return *(this->_ptr + n);
}

CodePoint& CodePointSequenceIter::operator*()
{
    return *_ptr;
}

// class CodePointSequenceConstIter
CodePointSequenceConstIter::CodePointSequenceConstIter(pointer ptr)
    : _ptr(ptr)
{}

bool
CodePointSequenceConstIter::operator==(
        const CodePointSequenceConstIter& other) const
{
    return this->_ptr == other._ptr;
}

bool
CodePointSequenceConstIter::operator!=(
        const CodePointSequenceConstIter& other) const
{
    return this->_ptr != other._ptr;
}

CodePointSequenceConstIter& CodePointSequenceConstIter::operator++()
{
    this->_ptr++;
    return *this;
}

CodePointSequenceConstIter CodePointSequenceConstIter::operator++(int)
{
    CodePointSequenceConstIter ret = *this;
    this->_ptr++;
    return ret;
}

const CodePoint& CodePointSequenceConstIter::operator*() const
{
    return *_ptr;
}

// Misc

} // namespace seshat