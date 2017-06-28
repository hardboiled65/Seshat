/*
//  ucd/properties.h
//
//  Author:     Sophia Lee
//  Created:    2017. 06. 23. 18:29
//  Copyright (c) 2016 Sophia Lee. All rights reserved.
//
//  Unicode property functions that using Seshat UCD table to get
//  properties.
*/
#ifndef _SESHAT_UCD_PROPERTIES_H
#define _SESHAT_UCD_PROPERTIES_H

#include <seshat/unicode/properties.h>

namespace seshat {
namespace unicode {
namespace ucd {

Block block(uint32_t cp);
uint8_t ccc(uint32_t cp);
Dt dt(uint32_t cp);
Gc gc(uint32_t cp);
Gcb gcb(uint32_t cp);
bool grapheme_extend(uint32_t cp);
bool variation_selector(uint32_t cp);
bool odi(uint32_t cp);
bool ogr_ext(uint32_t cp);
bool prepended_concatenation_mark(uint32_t cp);
bool white_space(uint32_t cp);

} // namespace ucd
} // namespace unicode
} // namespace seshat

#endif /* _SESHAT_UCD_PROPERTIES_H */