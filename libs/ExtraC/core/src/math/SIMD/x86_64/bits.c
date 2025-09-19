#include "../../maths.h"
#include <immintrin.h>
// --- r512 (AVX-512) Bitwise Operations ---

static inline void SIMD_r512_And(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_and_si512(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_Or(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_or_si512(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512__Or(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_xor_si512(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_Not(void* a, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i ones = _mm512_set1_epi64(-1); // A vector of all ones
    __m512i vec_res = _mm512_xor_si512(vec_a, ones);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}


// --- r256 (AVX2) Bitwise Operations ---

static inline void SIMD_r256_And(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_and_si256(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_Or(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_or_si256(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256__Or(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_xor_si256(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_Not(void* a, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i ones = _mm256_set1_epi64x(-1); // A vector of all ones
    __m256i vec_res = _mm256_xor_si256(vec_a, ones);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}


// --- r128 (SSE/SSE2) Bitwise Operations ---

static inline void SIMD_r128_And(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_and_si128(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_Or(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_or_si128(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128__Or(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_xor_si128(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_Not(void* a, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i ones = _mm_set1_epi64x(-1); // A vector of all ones
    __m128i vec_res = _mm_xor_si128(vec_a, ones);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

