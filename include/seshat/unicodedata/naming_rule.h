/*
//  unicodedata/naming_rule.h
//
//  Author:     Sophia Lee
//  Created:    2017. 04. 14. 15:31
//  Copyright (c) 2016 Sophia Lee. All rights reserved.
//
//
*/
#ifndef _UNICODEDATA_NAMING_RULE_H
#define _UNICODEDATA_NAMING_RULE_H

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>

namespace seshat {

// Unicode name prefix
#define PREFIX_YI_SYLLABLE      "YI SYLLABLE"       // A000-A48C
#define PREFIX_CANADIAN_SYLLABICS "CANADIAN SYLLABICS" // 1400-167F, 18B0-18F5
#define PREFIX_EGYPTIAN_HIEROGLYPH "EGYPTIAN HIEROGLYPH" // 13000-1342E
#define PREFIX_TANGUT_IDEOGRAPH "TANGUT IDEOGRAPH"
#define PREFIX_TANGUT_COMPONENT "TANGUT COMPONENT" // 18800-18AF2
#define PREFIX_CJK_COMPATIBILITY_IDEOGRAPH "CJK COMPATIBILITY IDEOGRAPH"
#define PREFIX_CJK_UNIFIED_IDEOGRAPH "CJK UNIFIED IDEOGRAPH"
#define PREFIX_BAMUM_LETTER_PHASE_A "BAMUM LETTER PHASE-A"
#define PREFIX_BAMUM_LETTER_PHASE_B "BAMUM LETTER PHASE-B"
#define PREFIX_BAMUM_LETTER_PHASE_C "BAMUM LETTER PHASE-C"
#define PREFIX_BAMUM_LETTER_PHASE_D "BAMUM LETTER PHASE-D"
#define PREFIX_BAMUM_LETTER_PHASE_E "BAMUM LETTER PHASE-E"
#define PREFIX_BAMUM_LETTER_PHASE_F "BAMUM LETTER PHASE-F"

// Unicode Area
enum class UnicodeArea {
    CanadianSyllabics,
    YiSyllable,
    EgyptianHieroglyph,
    BamumLetterPhaseA,
    BamumLetterPhaseB,
    BamumLetterPhaseC,
    BamumLetterPhaseD,
    BamumLetterPhaseE,
    BamumLetterPhaseF,
    TangutIdeograph,
    TangutComponent,
    CjkCompatibilityIdeograph,
    CjkUnifiedIdeograph
};

// Some prefix ranges from <Table 4-13> in 'The Unicode Standard'
// 4.8 Name, but not identical.
using CodePointRange = std::pair<uint32_t, uint32_t>;
const std::map<CodePointRange, UnicodeArea> range_table {
    { std::make_pair(0x3400, 0x4DB5), UnicodeArea::CjkUnifiedIdeograph },
    { std::make_pair(0x4E00, 0x9FD5), UnicodeArea::CjkUnifiedIdeograph },
    { std::make_pair(0x20000, 0x2A6D6), UnicodeArea::CjkUnifiedIdeograph },
    { std::make_pair(0x2A700, 0x2B734), UnicodeArea::CjkUnifiedIdeograph },
    { std::make_pair(0x2B740, 0x2B81D), UnicodeArea::CjkUnifiedIdeograph },
    { std::make_pair(0x2B820, 0x2CEA1), UnicodeArea::CjkUnifiedIdeograph },
    { std::make_pair(0x1400, 0x167F), UnicodeArea::CanadianSyllabics },
    { std::make_pair(0x18B0, 0x18F5), UnicodeArea::CanadianSyllabics },
    { std::make_pair(0xA000, 0xA48C), UnicodeArea::YiSyllable },
    { std::make_pair(0xF900, 0xFA6D), UnicodeArea::CjkCompatibilityIdeograph },
    { std::make_pair(0xFA70, 0xFAD9), UnicodeArea::CjkCompatibilityIdeograph },
    { std::make_pair(0x13000, 0x1342E), UnicodeArea::EgyptianHieroglyph },
    { std::make_pair(0x16800, 0x16856), UnicodeArea::BamumLetterPhaseA },
    { std::make_pair(0x16857, 0x1688E), UnicodeArea::BamumLetterPhaseB },
    { std::make_pair(0x1688F, 0x168F0), UnicodeArea::BamumLetterPhaseC },
    { std::make_pair(0x168F1, 0x16965), UnicodeArea::BamumLetterPhaseD },
    { std::make_pair(0x16966, 0x16A02), UnicodeArea::BamumLetterPhaseE },
    { std::make_pair(0x16A03, 0x16A38), UnicodeArea::BamumLetterPhaseF },
    { std::make_pair(0x17000, 0x187EC), UnicodeArea::TangutIdeograph },
    { std::make_pair(0x18800, 0x18AF2), UnicodeArea::TangutComponent },
    { std::make_pair(0x2F800, 0x2FA1D), UnicodeArea::CjkCompatibilityIdeograph }
};

// Unicode naming rules
class UnicodeNamingRule {
protected:
    const char *prefix;
    char separator;
    const char *unique;
    uint32_t code;
public:
    UnicodeNamingRule(const char *pre, char sep);
    void set(const char *unq, uint32_t code);
    virtual std::string name() const = 0;
};

class UniqueName : public UnicodeNamingRule {
public:
    UniqueName(const char *pre = nullptr);
    // void set(const char *unq, uint32_t code);
    std::string name() const;
};

class PrefixSpaceUniqueName : public UnicodeNamingRule {
public:
    PrefixSpaceUniqueName(const char *pre);
    // void set(const char *unq, uint32_t code);
    std::string name() const;
};

class PrefixDashUniqueName : public UnicodeNamingRule {
public:
    PrefixDashUniqueName(const char *pre);
    // void set(const char *unq, uint32_t code);
    std::string name() const;
};

class PrefixDashCodePoint : public UnicodeNamingRule {
public:
    PrefixDashCodePoint(const char *pre);
    // void set(const char *unq, uint32_t code);
    std::string name() const;
};

class PrefixDashSequentialNumber : public UnicodeNamingRule {
private:
    int32_t diff;
public:
    PrefixDashSequentialNumber(const char *pre, int32_t diff);
    // void set(const char *unq, uint32_t code);
    std::string name() const;
};

using UnicodeNamingRulePtr = std::unique_ptr<UnicodeNamingRule>;
UnicodeNamingRulePtr naming_rule(UnicodeArea area);

} // namespace seshat

#endif /* _UNICODEDATA_NAMING_RULE_H */
