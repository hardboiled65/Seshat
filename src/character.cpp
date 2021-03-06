/*
//  character.cpp
//
//  Author:     Sophia Lee
//  Created:    2017. 03. 19. 12:28
//  Copyright (c) 2017 Sophia Lee. All rights reserved.
//
//
*/
#include <seshat/character.h>

#include <seshat/codepoint.h>
#include <seshat/unicode/normalize.h>
#include <seshat/unicode/segmentation.h>

#include <sstream>
#include <utility>

namespace seshat {

Character::Character(char a_char)
    : _code_points(decltype(_code_points)())
{
    CodePoint cp = CodePoint(static_cast<uint32_t>(a_char));
    _code_points.append(cp);
}

Character::Character(const CodePoint& code_point)
    : _code_points(decltype(_code_points)())
{
    // if (gc(code_point.code()) == Gc::Cs) {
    // For performance, Surrogate code points compared directly.
    if (0xD800 <= code_point && code_point <= 0xDFFF) {
        throw SurrogateIncluded();
    }
    _code_points.append(code_point);
}

Character::Character(const CodePointSequence &sequence)
    : _code_points(decltype(_code_points)())
{
    for (auto cp: sequence) {
        if (0xD800 <= cp && cp <= 0xDFFF) {
            throw SurrogateIncluded();
        }
    }
    // Check if not a single grapheme cluster (zero or greater than one)
    if (unicode::grapheme_bound(sequence.begin(), sequence.end()) + 1 !=
        sequence.end()) {
    // if ((unicode::grapheme_bound(sequence) + 1) != sequence.length()) {
        throw NotASingleCharacter();
    }
    for (auto cp: sequence) {
        _code_points.append(cp);
    }
}

Character::Character(const Character& origin)
    : _code_points(origin._code_points)
{}

Character::Character(Character&& origin)
    : _code_points(std::move(origin._code_points))
{}

Character::~Character()
{
}

size_t Character::size() const
{
    return _code_points.length();
}

const CodePointSequence& Character::sequence() const
{
    return _code_points;
}

std::string Character::to_utf8() const
{
    std::stringstream stream;

    // For all code points
    for (auto&& cp: _code_points) {
        if (0x0000 <= cp && cp <= 0x007F) {
            stream << static_cast<char>(cp);
        } else if (0x0080 <= cp && cp <= 0x07FF) {
            stream << static_cast<char>(0xC0 | (cp >> 6));
            stream << static_cast<char>(0x80 | (0x3F & (cp)));
        } else if (0x0800 <= cp && cp <= 0xFFFF) {
            stream << static_cast<char>(0xE0 | (cp >> 12));
            stream << static_cast<char>(0x80 | (0x3F & (cp >> 6)));
            stream << static_cast<char>(0x80 | (0x3F & (cp)));
        } else if (0x10000 <= cp && cp <= 0x10FFFF) {
            stream << static_cast<char>(0xF0 | (cp >> 18));
            stream << static_cast<char>(0x80 | (0x3F & (cp >> 12)));
            stream << static_cast<char>(0x80 | (0x3F & (cp >> 6)));
            stream << static_cast<char>(0x80 | (0x3F & (cp)));
        }
    }

    return stream.str();
}

Character& Character::operator=(const Character& origin)
{
    _code_points = origin._code_points;
    return *this;
}

Character& Character::operator=(Character&& origin)
{
    _code_points = std::move(origin._code_points);
    return *this;
}

bool Character::operator==(const Character& other) const
{
    return (unicode::nfd(_code_points) == unicode::nfd(other._code_points));
}

bool Character::operator!=(const Character& other) const
{
    return !(*this == other);
}

} // namespace seshat