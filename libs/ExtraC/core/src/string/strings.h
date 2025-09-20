#pragma once
#include "../../include/stringutils.h"
#include "../../include/data.h"

private(StringBuilder,
	List(char) data;
	u64 max_len;
);
private(String,
	u8  inline_alloc : 1;
	u64 len_bytes;
);

// Helper macro to get the size of a UTF-8 character in bytes
#define UTF8_CHAR_SIZE(c) \
    ((c) <= 0x7F ? 1 : \
     ((c) <= 0x7FF ? 2 : \
      ((c) <= 0xFFFF ? 3 : 4)))


#define UTF8_1BYTE_MASK 0b10000000
#define UTF8_2BYTE_MASK 0b11100000
#define UTF8_3BYTE_MASK 0b11110000
#define UTF8_4BYTE_MASK 0b11111000

#define UTF8_1BYTE_HEADER 0b00000000
#define UTF8_2BYTE_HEADER 0b11000000
#define UTF8_3BYTE_HEADER 0b11100000
#define UTF8_4BYTE_HEADER 0b11110000

#define UTF8_CONT_MASK    0b00111111
#define UTF8_2BYTE_PREFIX 0b00011111
#define UTF8_3BYTE_PREFIX 0b00001111
#define UTF8_4BYTE_PREFIX 0b00000111

#include "encodings/utf8.c"
#include "encodings/utf16.c"
#include "encodings/utf32.c"






