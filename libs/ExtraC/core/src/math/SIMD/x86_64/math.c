#include "../../maths.h"
#include <immintrin.h>
/* ================== r512 (AVX-512) Addition ================== */

static inline void SIMD_r512_u64_Add(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_add_epi64(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_u32_Add(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_add_epi32(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_u16_Add(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_add_epi16(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_u8_Add(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_add_epi8(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i64_Add(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_add_epi64(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i32_Add(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_add_epi32(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i16_Add(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_add_epi16(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i8_Add(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_add_epi8(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_f32_Add(void* a, void* b, void* result) {
    __m512 vec_a = _mm512_loadu_ps((const float*)a);
    __m512 vec_b = _mm512_loadu_ps((const float*)b);
    __m512 vec_res = _mm512_add_ps(vec_a, vec_b);
    _mm512_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r512_f64_Add(void* a, void* b, void* result) {
    __m512d vec_a = _mm512_loadu_pd((const double*)a);
    __m512d vec_b = _mm512_loadu_pd((const double*)b);
    __m512d vec_res = _mm512_add_pd(vec_a, vec_b);
    _mm512_storeu_pd((double*)result, vec_res);
}


/* ================== r256 (AVX2) Addition ================== */

static inline void SIMD_r256_u64_Add(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_add_epi64(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_u32_Add(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_add_epi32(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_u16_Add(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_add_epi16(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_u8_Add(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_add_epi8(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i64_Add(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_add_epi64(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i32_Add(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_add_epi32(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i16_Add(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_add_epi16(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i8_Add(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_add_epi8(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_f32_Add(void* a, void* b, void* result) {
    __m256 vec_a = _mm256_loadu_ps((const float*)a);
    __m256 vec_b = _mm256_loadu_ps((const float*)b);
    __m256 vec_res = _mm256_add_ps(vec_a, vec_b);
    _mm256_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r256_f64_Add(void* a, void* b, void* result) {
    __m256d vec_a = _mm256_loadu_pd((const double*)a);
    __m256d vec_b = _mm256_loadu_pd((const double*)b);
    __m256d vec_res = _mm256_add_pd(vec_a, vec_b);
    _mm256_storeu_pd((double*)result, vec_res);
}


/* ================== r128 (SSE/SSE2) Addition ================== */

static inline void SIMD_r128_u64_Add(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_add_epi64(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_u32_Add(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_add_epi32(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_u16_Add(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_add_epi16(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_u8_Add(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_add_epi8(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i64_Add(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_add_epi64(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i32_Add(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_add_epi32(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i16_Add(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_add_epi16(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i8_Add(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_add_epi8(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_f32_Add(void* a, void* b, void* result) {
    __m128 vec_a = _mm_loadu_ps((const float*)a);
    __m128 vec_b = _mm_loadu_ps((const float*)b);
    __m128 vec_res = _mm_add_ps(vec_a, vec_b);
    _mm_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r128_f64_Add(void* a, void* b, void* result) {
    __m128d vec_a = _mm_loadu_pd((const double*)a);
    __m128d vec_b = _mm_loadu_pd((const double*)b);
    __m128d vec_res = _mm_add_pd(vec_a, vec_b);
    _mm_storeu_pd((double*)result, vec_res);
}

/* ================== r512 (AVX-512) Subtraction ================== */

static inline void SIMD_r512_u64_Sub(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_sub_epi64(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_u32_Sub(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_sub_epi32(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_u16_Sub(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_sub_epi16(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_u8_Sub(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_sub_epi8(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i64_Sub(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_sub_epi64(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i32_Sub(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_sub_epi32(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i16_Sub(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_sub_epi16(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i8_Sub(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_sub_epi8(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_f32_Sub(void* a, void* b, void* result) {
    __m512 vec_a = _mm512_loadu_ps((const float*)a);
    __m512 vec_b = _mm512_loadu_ps((const float*)b);
    __m512 vec_res = _mm512_sub_ps(vec_a, vec_b);
    _mm512_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r512_f64_Sub(void* a, void* b, void* result) {
    __m512d vec_a = _mm512_loadu_pd((const double*)a);
    __m512d vec_b = _mm512_loadu_pd((const double*)b);
    __m512d vec_res = _mm512_sub_pd(vec_a, vec_b);
    _mm512_storeu_pd((double*)result, vec_res);
}


/* ================== r256 (AVX2) Subtraction ================== */

static inline void SIMD_r256_u64_Sub(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_sub_epi64(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_u32_Sub(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_sub_epi32(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_u16_Sub(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_sub_epi16(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_u8_Sub(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_sub_epi8(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i64_Sub(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_sub_epi64(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i32_Sub(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_sub_epi32(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i16_Sub(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_sub_epi16(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i8_Sub(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_sub_epi8(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_f32_Sub(void* a, void* b, void* result) {
    __m256 vec_a = _mm256_loadu_ps((const float*)a);
    __m256 vec_b = _mm256_loadu_ps((const float*)b);
    __m256 vec_res = _mm256_sub_ps(vec_a, vec_b);
    _mm256_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r256_f64_Sub(void* a, void* b, void* result) {
    __m256d vec_a = _mm256_loadu_pd((const double*)a);
    __m256d vec_b = _mm256_loadu_pd((const double*)b);
    __m256d vec_res = _mm256_sub_pd(vec_a, vec_b);
    _mm256_storeu_pd((double*)result, vec_res);
}


/* ================== r128 (SSE/SSE2) Subtraction ================== */

static inline void SIMD_r128_u64_Sub(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_sub_epi64(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_u32_Sub(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_sub_epi32(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_u16_Sub(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_sub_epi16(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_u8_Sub(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_sub_epi8(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i64_Sub(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_sub_epi64(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i32_Sub(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_sub_epi32(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i16_Sub(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_sub_epi16(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i8_Sub(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_sub_epi8(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_f32_Sub(void* a, void* b, void* result) {
    __m128 vec_a = _mm_loadu_ps((const float*)a);
    __m128 vec_b = _mm_loadu_ps((const float*)b);
    __m128 vec_res = _mm_sub_ps(vec_a, vec_b);
    _mm_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r128_f64_Sub(void* a, void* b, void* result) {
    __m128d vec_a = _mm_loadu_pd((const double*)a);
    __m128d vec_b = _mm_loadu_pd((const double*)b);
    __m128d vec_res = _mm_sub_pd(vec_a, vec_b);
    _mm_storeu_pd((double*)result, vec_res);
}

/* ================== r512 (AVX-512) Multiplication ================== */

static inline void SIMD_r512_u64_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 64-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r512_u32_Mul(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_mullo_epi32(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_u16_Mul(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_mullo_epi16(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_u8_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 8-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r512_i64_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 64-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r512_i32_Mul(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_mullo_epi32(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i16_Mul(void* a, void* b, void* result) {
    __m512i vec_a = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((const __m512i*)b);
    __m512i vec_res = _mm512_mullo_epi16(vec_a, vec_b);
    _mm512_storeu_si512((__m512i*)result, vec_res);
}

static inline void SIMD_r512_i8_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 8-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r512_f32_Mul(void* a, void* b, void* result) {
    __m512 vec_a = _mm512_loadu_ps((const float*)a);
    __m512 vec_b = _mm512_loadu_ps((const float*)b);
    __m512 vec_res = _mm512_mul_ps(vec_a, vec_b);
    _mm512_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r512_f64_Mul(void* a, void* b, void* result) {
    __m512d vec_a = _mm512_loadu_pd((const double*)a);
    __m512d vec_b = _mm512_loadu_pd((const double*)b);
    __m512d vec_res = _mm512_mul_pd(vec_a, vec_b);
    _mm512_storeu_pd((double*)result, vec_res);
}


/* ================== r256 (AVX2) Multiplication ================== */

static inline void SIMD_r256_u64_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 64-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r256_u32_Mul(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_mullo_epi32(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_u16_Mul(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_mullo_epi16(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_u8_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 8-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r256_i64_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 64-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r256_i32_Mul(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_mullo_epi32(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i16_Mul(void* a, void* b, void* result) {
    __m256i vec_a = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b = _mm256_loadu_si256((const __m256i*)b);
    __m256i vec_res = _mm256_mullo_epi16(vec_a, vec_b);
    _mm256_storeu_si256((__m256i*)result, vec_res);
}

static inline void SIMD_r256_i8_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 8-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r256_f32_Mul(void* a, void* b, void* result) {
    __m256 vec_a = _mm256_loadu_ps((const float*)a);
    __m256 vec_b = _mm256_loadu_ps((const float*)b);
    __m256 vec_res = _mm256_mul_ps(vec_a, vec_b);
    _mm256_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r256_f64_Mul(void* a, void* b, void* result) {
    __m256d vec_a = _mm256_loadu_pd((const double*)a);
    __m256d vec_b = _mm256_loadu_pd((const double*)b);
    __m256d vec_res = _mm256_mul_pd(vec_a, vec_b);
    _mm256_storeu_pd((double*)result, vec_res);
}


/* ================== r128 (SSE/SSE2) Multiplication ================== */

static inline void SIMD_r128_u64_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 64-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r128_u32_Mul(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_mullo_epi32(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_u16_Mul(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_mullo_epi16(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_u8_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 8-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r128_i64_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 64-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r128_i32_Mul(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_mullo_epi32(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i16_Mul(void* a, void* b, void* result) {
    __m128i vec_a = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b = _mm_loadu_si128((const __m128i*)b);
    __m128i vec_res = _mm_mullo_epi16(vec_a, vec_b);
    _mm_storeu_si128((__m128i*)result, vec_res);
}

static inline void SIMD_r128_i8_Mul(void* a, void* b, void* result) {
    // No direct intrinsic for 8-bit integer multiplication,
    // a more complex implementation is required.
    // This function is provided as a placeholder.
}

static inline void SIMD_r128_f32_Mul(void* a, void* b, void* result) {
    __m128 vec_a = _mm_loadu_ps((const float*)a);
    __m128 vec_b = _mm_loadu_ps((const float*)b);
    __m128 vec_res = _mm_mul_ps(vec_a, vec_b);
    _mm_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r128_f64_Mul(void* a, void* b, void* result) {
    __m128d vec_a = _mm_loadu_pd((const double*)a);
    __m128d vec_b = _mm_loadu_pd((const double*)b);
    __m128d vec_res = _mm_mul_pd(vec_a, vec_b);
    _mm_storeu_pd((double*)result, vec_res);
}

/* ================== r512 (AVX-512) Division ================== */

static inline void SIMD_r512_i64_Div(void* a, void* b, void* result) {
    __m512i vec_a_i64 = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b_i64 = _mm512_loadu_si512((const __m512i*)b);
    __m512d vec_a_f64 = _mm512_cvtepi64_pd(vec_a_i64);
    __m512d vec_b_f64 = _mm512_cvtepi64_pd(vec_b_i64);
    __m512d vec_res_f64 = _mm512_div_pd(vec_a_f64, vec_b_f64);
    __m512i vec_res_i64 = _mm512_cvttpd_epi64(vec_res_f64);
    _mm512_storeu_si512((__m512i*)result, vec_res_i64);
}

static inline void SIMD_r512_u64_Div(void* a, void* b, void* result) {
    __m512i vec_a_u64 = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b_u64 = _mm512_loadu_si512((const __m512i*)b);
    __m512d vec_a_f64 = _mm512_cvtepu64_pd(vec_a_u64);
    __m512d vec_b_f64 = _mm512_cvtepu64_pd(vec_b_u64);
    __m512d vec_res_f64 = _mm512_div_pd(vec_a_f64, vec_b_f64);
    __m512i vec_res_i64 = _mm512_cvttpd_epu64(vec_res_f64);
    _mm512_storeu_si512((__m512i*)result, vec_res_i64);
}

static inline void SIMD_r512_i32_Div(void* a, void* b, void* result) {
    __m512i vec_a_i32 = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b_i32 = _mm512_loadu_si512((const __m512i*)b);
    __m512 vec_a_f32 = _mm512_cvtepi32_ps(vec_a_i32);
    __m512 vec_b_f32 = _mm512_cvtepi32_ps(vec_b_i32);
    __m512 vec_res_f32 = _mm512_div_ps(vec_a_f32, vec_b_f32);
    __m512i vec_res_i32 = _mm512_cvttps_epi32(vec_res_f32);
    _mm512_storeu_si512((__m512i*)result, vec_res_i32);
}

static inline void SIMD_r512_u32_Div(void* a, void* b, void* result) {
    __m512i vec_a_u32 = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b_u32 = _mm512_loadu_si512((const __m512i*)b);
    __m512 vec_a_f32 = _mm512_cvtepu32_ps(vec_a_u32);
    __m512 vec_b_f32 = _mm512_cvtepu32_ps(vec_b_u32);
    __m512 vec_res_f32 = _mm512_div_ps(vec_a_f32, vec_b_f32);
    __m512i vec_res_i32 = _mm512_cvttps_epu32(vec_res_f32);
    _mm512_storeu_si512((__m512i*)result, vec_res_i32);
}

static inline void SIMD_r512_i16_Div(void* a, void* b, void* result) {
    __m512i vec_a_i16 = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b_i16 = _mm512_loadu_si512((const __m512i*)b);

    // Split the 512-bit vectors into low and high 256-bit halves
    __m256i vec_a_i16_low = _mm512_extracti64x4_epi64(vec_a_i16, 0);
    __m256i vec_a_i16_high = _mm512_extracti64x4_epi64(vec_a_i16, 1);
    __m256i vec_b_i16_low = _mm512_extracti64x4_epi64(vec_b_i16, 0);
    __m256i vec_b_i16_high = _mm512_extracti64x4_epi64(vec_b_i16, 1);

    // Convert each 16-element half from 16-bit to 32-bit integers
    __m512i vec_a_i32_low = _mm512_cvtepi16_epi32(vec_a_i16_low);
    __m512i vec_a_i32_high = _mm512_cvtepi16_epi32(vec_a_i16_high);
    __m512i vec_b_i32_low = _mm512_cvtepi16_epi32(vec_b_i16_low);
    __m512i vec_b_i32_high = _mm512_cvtepi16_epi32(vec_b_i16_high);

    // Convert to floats and perform division on each half
    __m512 vec_res_f32_low = _mm512_div_ps(_mm512_cvtepi32_ps(vec_a_i32_low), _mm512_cvtepi32_ps(vec_b_i32_low));
    __m512 vec_res_f32_high = _mm512_div_ps(_mm512_cvtepi32_ps(vec_a_i32_high), _mm512_cvtepi32_ps(vec_b_i32_high));

    // Convert back to 32-bit integers
    __m512i res_i32_low = _mm512_cvttps_epi32(vec_res_f32_low);
    __m512i res_i32_high = _mm512_cvttps_epi32(vec_res_f32_high);
    
    // Pack the two 512-bit vectors of 32-bit integers into one 512-bit vector of 16-bit integers
    __m512i final_result = _mm512_packs_epi32(res_i32_low, res_i32_high);

    _mm512_storeu_si512((__m512i*)result, final_result);
}

static inline void SIMD_r512_u16_Div(void* a, void* b, void* result) {
    __m512i vec_a_u16 = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b_u16 = _mm512_loadu_si512((const __m512i*)b);

    // Split the 512-bit vectors into low and high 256-bit halves
    __m256i vec_a_u16_low = _mm512_extracti64x4_epi64(vec_a_u16, 0);
    __m256i vec_a_u16_high = _mm512_extracti64x4_epi64(vec_a_u16, 1);
    __m256i vec_b_u16_low = _mm512_extracti64x4_epi64(vec_b_u16, 0);
    __m256i vec_b_u16_high = _mm512_extracti64x4_epi64(vec_b_u16, 1);

    // Convert each 16-element half from unsigned 16-bit to 32-bit integers
    __m512i vec_a_u32_low = _mm512_cvtepu16_epi32(vec_a_u16_low);
    __m512i vec_a_u32_high = _mm512_cvtepu16_epi32(vec_a_u16_high);
    __m512i vec_b_u32_low = _mm512_cvtepu16_epi32(vec_b_u16_low);
    __m512i vec_b_u32_high = _mm512_cvtepu16_epi32(vec_b_u16_high);

    // Convert to floats and perform division on each half
    __m512 vec_res_f32_low = _mm512_div_ps(_mm512_cvtepu32_ps(vec_a_u32_low), _mm512_cvtepu32_ps(vec_b_u32_low));
    __m512 vec_res_f32_high = _mm512_div_ps(_mm512_cvtepu32_ps(vec_a_u32_high), _mm512_cvtepu32_ps(vec_b_u32_high));

    // Convert back to 32-bit unsigned integers
    __m512i res_i32_low = _mm512_cvttps_epu32(vec_res_f32_low);
    __m512i res_i32_high = _mm512_cvttps_epu32(vec_res_f32_high);

    // Pack the two 512-bit vectors of 32-bit unsigned integers into one 512-bit vector of 16-bit unsigned integers
    __m512i final_result = _mm512_packus_epi32(res_i32_low, res_i32_high);

    _mm512_storeu_si512((__m512i*)result, final_result);
}

static inline void SIMD_r512_i8_Div(void* a, void* b, void* result) {
    __m512i vec_a_i8 = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b_i8 = _mm512_loadu_si512((const __m512i*)b);

    // Convert 8-bit to 32-bit integers using two 256-bit halves.
    __m512i vec_a_i32_low = _mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(vec_a_i8, 0));
    __m512i vec_a_i32_high = _mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(vec_a_i8, 1));
    __m512i vec_b_i32_low = _mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(vec_b_i8, 0));
    __m512i vec_b_i32_high = _mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(vec_b_i8, 1));

    // Convert to floats and divide
    __m512 vec_a_f32_low = _mm512_cvtepi32_ps(vec_a_i32_low);
    __m512 vec_a_f32_high = _mm512_cvtepi32_ps(vec_a_i32_high);
    __m512 vec_b_f32_low = _mm512_cvtepi32_ps(vec_b_i32_low);
    __m512 vec_b_f32_high = _mm512_cvtepi32_ps(vec_b_i32_high);
    __m512 vec_res_f32_low = _mm512_div_ps(vec_a_f32_low, vec_b_f32_low);
    __m512 vec_res_f32_high = _mm512_div_ps(vec_a_f32_high, vec_b_f32_high);

    // Convert back to 32-bit integers
    __m512i vec_res_i32_low = _mm512_cvttps_epi32(vec_res_f32_low);
    __m512i vec_res_i32_high = _mm512_cvttps_epi32(vec_res_f32_high);

    // This intrinsic packs 32-bit integers into 8-bit integers
    __m128i vec_res_i8_low = _mm512_cvtepi32_epi8(vec_res_i32_low);
    __m128i vec_res_i8_high = _mm512_cvtepi32_epi8(vec_res_i32_high);

	    // Create a zero-initialized __m256i vector
    __m256i m256_val = _mm256_setzero_si256();

    // Insert the __m128i value into the lower 128-bit lane (lane 0) of the __m256i
    m256_val = _mm256_insertf128_si256(m256_val, vec_res_i8_high, 0);

    // This intrinsic combines the two 256-bit vectors into a single 512-bit vector.
    __m512i final_result = _mm512_inserti64x4(_mm512_castsi128_si512(vec_res_i8_low), m256_val, 1);
    _mm512_storeu_si512((__m512i*)result, final_result);
}

static inline void SIMD_r512_u8_Div(void* a, void* b, void* result) {
    __m512i vec_a_u8 = _mm512_loadu_si512((const __m512i*)a);
    __m512i vec_b_u8 = _mm512_loadu_si512((const __m512i*)b);

    __m512i vec_a_u32_low = _mm512_cvtepu8_epi32(_mm512_extracti32x4_epi32(vec_a_u8, 0));
    __m512i vec_a_u32_high = _mm512_cvtepu8_epi32(_mm512_extracti32x4_epi32(vec_a_u8, 1));
    __m512i vec_b_u32_low = _mm512_cvtepu8_epi32(_mm512_extracti32x4_epi32(vec_b_u8, 0));
    __m512i vec_b_u32_high = _mm512_cvtepu8_epi32(_mm512_extracti32x4_epi32(vec_b_u8, 1));
    
    __m512 vec_a_f32_low = _mm512_cvtepu32_ps(vec_a_u32_low);
    __m512 vec_a_f32_high = _mm512_cvtepu32_ps(vec_a_u32_high);
    __m512 vec_b_f32_low = _mm512_cvtepu32_ps(vec_b_u32_low);
    __m512 vec_b_f32_high = _mm512_cvtepu32_ps(vec_b_u32_high);
    __m512 vec_res_f32_low = _mm512_div_ps(vec_a_f32_low, vec_b_f32_low);
    __m512 vec_res_f32_high = _mm512_div_ps(vec_a_f32_high, vec_b_f32_high);

    __m512i vec_res_u32_low = _mm512_cvttps_epu32(vec_res_f32_low);
    __m512i vec_res_u32_high = _mm512_cvttps_epu32(vec_res_f32_high);

    // This intrinsic packs 32-bit integers into 8-bit integers
    __m128i vec_res_i8_low = _mm512_cvtepi32_epi8(vec_res_u32_low);
    __m128i vec_res_i8_high = _mm512_cvtepi32_epi8(vec_res_u32_high);

	    // Create a zero-initialized __m256i vector
    __m256i m256_val = _mm256_setzero_si256();

    // Insert the __m128i value into the lower 128-bit lane (lane 0) of the __m256i
    m256_val = _mm256_insertf128_si256(m256_val, vec_res_i8_high, 0);

    // This intrinsic combines the two 256-bit vectors into a single 512-bit vector.
    __m512i final_result = _mm512_inserti64x4(_mm512_castsi128_si512(vec_res_i8_low), m256_val, 1);
    _mm512_storeu_si512((__m512i*)result, final_result);
}

static inline void SIMD_r512_f32_Div(void* a, void* b, void* result) {
    __m512 vec_a = _mm512_loadu_ps((const float*)a);
    __m512 vec_b = _mm512_loadu_ps((const float*)b);
    __m512 vec_res = _mm512_div_ps(vec_a, vec_b);
    _mm512_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r512_f64_Div(void* a, void* b, void* result) {
    __m512d vec_a = _mm512_loadu_pd((const double*)a);
    __m512d vec_b = _mm512_loadu_pd((const double*)b);
    __m512d vec_res = _mm512_div_pd(vec_a, vec_b);
    _mm512_storeu_pd((double*)result, vec_res);
}


/* ================== r256 (AVX2) Division ================== */

static inline void SIMD_r256_i64_Div(void* a, void* b, void* result) {
    __m256d vec_a_f64 = _mm256_cvtepi64_pd(_mm256_loadu_si256((const __m256i*)a));
    __m256d vec_b_f64 = _mm256_cvtepi64_pd(_mm256_loadu_si256((const __m256i*)b));
    __m256d vec_res_f64 = _mm256_div_pd(vec_a_f64, vec_b_f64);
    __m256i vec_res_i64 = _mm256_cvttpd_epi64(vec_res_f64);
    _mm256_storeu_si256((__m256i*)result, vec_res_i64);
}

static inline void SIMD_r256_u64_Div(void* a, void* b, void* result) {
    __m256i vec_a_u64 = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b_u64 = _mm256_loadu_si256((const __m256i*)b);
    __m256d vec_a_f64 = _mm256_cvtepi64_pd(vec_a_u64); // Signed conversion as a workaround
    __m256d vec_b_f64 = _mm256_cvtepi64_pd(vec_b_u64);
    __m256d vec_res_f64 = _mm256_div_pd(vec_a_f64, vec_b_f64);
    __m256i vec_res_i64 = _mm256_cvttpd_epu64(vec_res_f64);
    _mm256_storeu_si256((__m256i*)result, vec_res_i64);
}

static inline void SIMD_r256_i32_Div(void* a, void* b, void* result) {
    __m256i vec_a_i32 = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b_i32 = _mm256_loadu_si256((const __m256i*)b);
    __m256 vec_a_f32 = _mm256_cvtepi32_ps(vec_a_i32);
    __m256 vec_b_f32 = _mm256_cvtepi32_ps(vec_b_i32);
    __m256 vec_res_f32 = _mm256_div_ps(vec_a_f32, vec_b_f32);
    __m256i vec_res_i32 = _mm256_cvttps_epi32(vec_res_f32);
    _mm256_storeu_si256((__m256i*)result, vec_res_i32);
}

static inline void SIMD_r256_u32_Div(void* a, void* b, void* result) {
    __m256i vec_a_u32 = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b_u32 = _mm256_loadu_si256((const __m256i*)b);
    __m256 vec_a_f32 = _mm256_cvtepu32_ps(vec_a_u32);
    __m256 vec_b_f32 = _mm256_cvtepu32_ps(vec_b_u32);
    __m256 vec_res_f32 = _mm256_div_ps(vec_a_f32, vec_b_f32);
    __m256i vec_res_i32 = _mm256_cvttps_epu32(vec_res_f32);
    _mm256_storeu_si256((__m256i*)result, vec_res_i32);
}

static inline void SIMD_r256_i16_Div(void* a, void* b, void* result) {
    __m256i vec_a_i16 = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b_i16 = _mm256_loadu_si256((const __m256i*)b);

    // Split the 256-bit vectors into two 128-bit halves
    __m128i vec_a_i16_low = _mm256_extracti128_si256(vec_a_i16, 0);
    __m128i vec_a_i16_high = _mm256_extracti128_si256(vec_a_i16, 1);
    __m128i vec_b_i16_low = _mm256_extracti128_si256(vec_b_i16, 0);
    __m128i vec_b_i16_high = _mm256_extracti128_si256(vec_b_i16, 1);
    
    // Convert 16-bit halves to 32-bit and perform division
    __m256i vec_a_i32_low = _mm256_cvtepi16_epi32(vec_a_i16_low);
    __m256i vec_a_i32_high = _mm256_cvtepi16_epi32(vec_a_i16_high);
    __m256i vec_b_i32_low = _mm256_cvtepi16_epi32(vec_b_i16_low);
    __m256i vec_b_i32_high = _mm256_cvtepi16_epi32(vec_b_i16_high);
    
    __m256 vec_res_f32_low = _mm256_div_ps(_mm256_cvtepi32_ps(vec_a_i32_low), _mm256_cvtepi32_ps(vec_b_i32_low));
    __m256 vec_res_f32_high = _mm256_div_ps(_mm256_cvtepi32_ps(vec_a_i32_high), _mm256_cvtepi32_ps(vec_b_i32_high));

    // Convert back to 32-bit integers
    __m256i vec_res_i32_low = _mm256_cvttps_epi32(vec_res_f32_low);
    __m256i vec_res_i32_high = _mm256_cvttps_epi32(vec_res_f32_high);

    // Pack the two 256-bit vectors of 32-bit integers into one 256-bit vector of 16-bit integers
    __m256i final_result = _mm256_packs_epi32(vec_res_i32_low, vec_res_i32_high);
    
    _mm256_storeu_si256((__m256i*)result, final_result);
}

static inline void SIMD_r256_u16_Div(void* a, void* b, void* result) {
    __m256i vec_a_u16 = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b_u16 = _mm256_loadu_si256((const __m256i*)b);

    // Split the 256-bit vectors into two 128-bit halves
    __m128i vec_a_u16_low = _mm256_extracti128_si256(vec_a_u16, 0);
    __m128i vec_a_u16_high = _mm256_extracti128_si256(vec_a_u16, 1);
    __m128i vec_b_u16_low = _mm256_extracti128_si256(vec_b_u16, 0);
    __m128i vec_b_u16_high = _mm256_extracti128_si256(vec_b_u16, 1);
    
    // Convert 16-bit halves to 32-bit and perform division
    __m256i vec_a_u32_low = _mm256_cvtepu16_epi32(vec_a_u16_low);
    __m256i vec_a_u32_high = _mm256_cvtepu16_epi32(vec_a_u16_high);
    __m256i vec_b_u32_low = _mm256_cvtepu16_epi32(vec_b_u16_low);
    __m256i vec_b_u32_high = _mm256_cvtepu16_epi32(vec_b_u16_high);
    
    __m256 vec_res_f32_low = _mm256_div_ps(_mm256_cvtepu32_ps(vec_a_u32_low), _mm256_cvtepu32_ps(vec_b_u32_low));
    __m256 vec_res_f32_high = _mm256_div_ps(_mm256_cvtepu32_ps(vec_a_u32_high), _mm256_cvtepu32_ps(vec_b_u32_high));

    // Convert back to 32-bit integers
    __m256i vec_res_i32_low = _mm256_cvttps_epu32(vec_res_f32_low);
    __m256i vec_res_i32_high = _mm256_cvttps_epu32(vec_res_f32_high);

    // Pack the two 256-bit vectors of 32-bit unsigned integers into one 256-bit vector of 16-bit unsigned integers
    __m256i final_result = _mm256_packus_epi32(vec_res_i32_low, vec_res_i32_high);
    
    _mm256_storeu_si256((__m256i*)result, final_result);
}

static inline void SIMD_r256_i8_Div(void* a, void* b, void* result) {
    __m256i vec_a_i8 = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b_i8 = _mm256_loadu_si256((const __m256i*)b);
    __m128i vec_a_i8_low = _mm256_castsi256_si128(vec_a_i8);
    __m128i vec_a_i8_high = _mm256_extracti128_si256(vec_a_i8, 1);
    __m128i vec_b_i8_low = _mm256_castsi256_si128(vec_b_i8);
    __m128i vec_b_i8_high = _mm256_extracti128_si256(vec_b_i8, 1);
    
    __m256i vec_a_i32_low = _mm256_cvtepi8_epi32(vec_a_i8_low);
    __m256i vec_a_i32_high = _mm256_cvtepi8_epi32(vec_a_i8_high);
    __m256i vec_b_i32_low = _mm256_cvtepi8_epi32(vec_b_i8_low);
    __m256i vec_b_i32_high = _mm256_cvtepi8_epi32(vec_b_i8_high);
    
    __m256 vec_a_f32_low = _mm256_cvtepi32_ps(vec_a_i32_low);
    __m256 vec_a_f32_high = _mm256_cvtepi32_ps(vec_a_i32_high);
    __m256 vec_b_f32_low = _mm256_cvtepi32_ps(vec_b_i32_low);
    __m256 vec_b_f32_high = _mm256_cvtepi32_ps(vec_b_i32_high);
    
    __m256 vec_res_f32_low = _mm256_div_ps(vec_a_f32_low, vec_b_f32_low);
    __m256 vec_res_f32_high = _mm256_div_ps(vec_a_f32_high, vec_b_f32_high);

    __m256i vec_res_i32_low = _mm256_cvttps_epi32(vec_res_f32_low);
    __m256i vec_res_i32_high = _mm256_cvttps_epi32(vec_res_f32_high);
    
    __m128i res_i8_low = _mm256_cvtepi32_epi8(vec_res_i32_low);
    __m128i res_i8_high = _mm256_cvtepi32_epi8(vec_res_i32_high);
    
    __m256i final_result = _mm256_inserti128_si256(_mm256_castsi128_si256(res_i8_low), res_i8_high, 1);
    _mm256_storeu_si256((__m256i*)result, final_result);
}

static inline void SIMD_r256_u8_Div(void* a, void* b, void* result) {
    __m256i vec_a_u8 = _mm256_loadu_si256((const __m256i*)a);
    __m256i vec_b_u8 = _mm256_loadu_si256((const __m256i*)b);
    __m128i vec_a_u8_low = _mm256_castsi256_si128(vec_a_u8);
    __m128i vec_a_u8_high = _mm256_extracti128_si256(vec_a_u8, 1);
    __m128i vec_b_u8_low = _mm256_castsi256_si128(vec_b_u8);
    __m128i vec_b_u8_high = _mm256_extracti128_si256(vec_b_u8, 1);
    
    __m256i vec_a_u32_low = _mm256_cvtepu8_epi32(vec_a_u8_low);
    __m256i vec_a_u32_high = _mm256_cvtepu8_epi32(vec_a_u8_high);
    __m256i vec_b_u32_low = _mm256_cvtepu8_epi32(vec_b_u8_low);
    __m256i vec_b_u32_high = _mm256_cvtepu8_epi32(vec_b_u8_high);
    
    __m256 vec_a_f32_low = _mm256_cvtepu32_ps(vec_a_u32_low);
    __m256 vec_a_f32_high = _mm256_cvtepu32_ps(vec_a_u32_high);
    __m256 vec_b_f32_low = _mm256_cvtepu32_ps(vec_b_u32_low);
    __m256 vec_b_f32_high = _mm256_cvtepu32_ps(vec_b_u32_high);
    
    __m256 vec_res_f32_low = _mm256_div_ps(vec_a_f32_low, vec_b_f32_low);
    __m256 vec_res_f32_high = _mm256_div_ps(vec_a_f32_high, vec_b_f32_high);

    __m256i vec_res_u32_low = _mm256_cvttps_epu32(vec_res_f32_low);
    __m256i vec_res_u32_high = _mm256_cvttps_epu32(vec_res_f32_high);
    
    __m128i res_u8_low = _mm256_cvtepi32_epi8(vec_res_u32_low);
    __m128i res_u8_high = _mm256_cvtepi32_epi8(vec_res_u32_high);
    
    __m256i final_result = _mm256_inserti128_si256(_mm256_castsi128_si256(res_u8_low), res_u8_high, 1);
    _mm256_storeu_si256((__m256i*)result, final_result);
}

static inline void SIMD_r256_f32_Div(void* a, void* b, void* result) {
    __m256 vec_a = _mm256_loadu_ps((const float*)a);
    __m256 vec_b = _mm256_loadu_ps((const float*)b);
    __m256 vec_res = _mm256_div_ps(vec_a, vec_b);
    _mm256_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r256_f64_Div(void* a, void* b, void* result) {
    __m256d vec_a = _mm256_loadu_pd((const double*)a);
    __m256d vec_b = _mm256_loadu_pd((const double*)b);
    __m256d vec_res = _mm256_div_pd(vec_a, vec_b);
    _mm256_storeu_pd((double*)result, vec_res);
}


/* ================== r128 (SSE/SSE2) Division ================== */

static inline void SIMD_r128_i64_Div(void* a, void* b, void* result) {
    __m128i vec_a_i64 = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b_i64 = _mm_loadu_si128((const __m128i*)b);
    __m128d vec_a_f64 = _mm_cvtepi64_pd(vec_a_i64);
    __m128d vec_b_f64 = _mm_cvtepi64_pd(vec_b_i64);
    __m128d vec_res_f64 = _mm_div_pd(vec_a_f64, vec_b_f64);
    __m128i vec_res_i64 = _mm_cvttpd_epi64(vec_res_f64);
    _mm_storeu_si128((__m128i*)result, vec_res_i64);
}

static inline void SIMD_r128_u64_Div(void* a, void* b, void* result) {
    __m128i vec_a_u64 = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b_u64 = _mm_loadu_si128((const __m128i*)b);
    __m128d vec_a_f64 = _mm_cvtepi64_pd(vec_a_u64); // Signed conversion as a workaround
    __m128d vec_b_f64 = _mm_cvtepi64_pd(vec_b_u64);
    __m128d vec_res_f64 = _mm_div_pd(vec_a_f64, vec_b_f64);
    __m128i vec_res_i64 = _mm_cvttpd_epu64(vec_res_f64);
    _mm_storeu_si128((__m128i*)result, vec_res_i64);
}

static inline void SIMD_r128_i32_Div(void* a, void* b, void* result) {
    __m128i vec_a_i32 = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b_i32 = _mm_loadu_si128((const __m128i*)b);
    __m128 vec_a_f32 = _mm_cvtepi32_ps(vec_a_i32);
    __m128 vec_b_f32 = _mm_cvtepi32_ps(vec_b_i32);
    __m128 vec_res_f32 = _mm_div_ps(vec_a_f32, vec_b_f32);
    __m128i vec_res_i32 = _mm_cvttps_epi32(vec_res_f32);
    _mm_storeu_si128((__m128i*)result, vec_res_i32);
}

static inline void SIMD_r128_u32_Div(void* a, void* b, void* result) {
    __m128i vec_a_u32 = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b_u32 = _mm_loadu_si128((const __m128i*)b);
    __m128 vec_a_f32 = _mm_cvtepi32_ps(vec_a_u32); // Signed conversion
    __m128 vec_b_f32 = _mm_cvtepi32_ps(vec_b_u32);
    __m128 vec_res_f32 = _mm_div_ps(vec_a_f32, vec_b_f32);
    __m128i vec_res_i32 = _mm_cvttps_epu32(vec_res_f32);
    _mm_storeu_si128((__m128i*)result, vec_res_i32);
}

static inline void SIMD_r128_i16_Div(void* a, void* b, void* result) {
    __m128i vec_a_i16 = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b_i16 = _mm_loadu_si128((const __m128i*)b);
    __m128 vec_a_f32 = _mm_cvtepi32_ps(_mm_cvtepi16_epi32(vec_a_i16));
    __m128 vec_b_f32 = _mm_cvtepi32_ps(_mm_cvtepi16_epi32(vec_b_i16));
    __m128 vec_res_f32 = _mm_div_ps(vec_a_f32, vec_b_f32);
    __m128i vec_res_i32 = _mm_cvttps_epi32(vec_res_f32);
    __m128i vec_res_i16 = _mm_cvtepi32_epi16(vec_res_i32);
    _mm_storeu_si128((__m128i*)result, vec_res_i16);
}

static inline void SIMD_r128_u16_Div(void* a, void* b, void* result) {
    __m128i vec_a_u16 = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b_u16 = _mm_loadu_si128((const __m128i*)b);
    __m128 vec_a_f32 = _mm_cvtepi32_ps(_mm_cvtepu16_epi32(vec_a_u16));
    __m128 vec_b_f32 = _mm_cvtepi32_ps(_mm_cvtepu16_epi32(vec_b_u16));
    __m128 vec_res_f32 = _mm_div_ps(vec_a_f32, vec_b_f32);
    __m128i vec_res_i32 = _mm_cvttps_epu32(vec_res_f32);
    __m128i vec_res_i16 = _mm_cvtepi32_epi16(vec_res_i32);
    _mm_storeu_si128((__m128i*)result, vec_res_i16);
}

static inline void SIMD_r128_i8_Div(void* a, void* b, void* result) {
    __m128i vec_a_i8 = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b_i8 = _mm_loadu_si128((const __m128i*)b);
    __m128 vec_a_f32 = _mm_cvtepi32_ps(_mm_cvtepi8_epi32(vec_a_i8));
    __m128 vec_b_f32 = _mm_cvtepi32_ps(_mm_cvtepi8_epi32(vec_b_i8));
    __m128 vec_res_f32 = _mm_div_ps(vec_a_f32, vec_b_f32);
    __m128i vec_res_i32 = _mm_cvttps_epi32(vec_res_f32);
    __m128i vec_res_i8 = _mm_cvtepi32_epi8(vec_res_i32);
    _mm_storeu_si128((__m128i*)result, vec_res_i8);
}

static inline void SIMD_r128_u8_Div(void* a, void* b, void* result) {
    __m128i vec_a_u8 = _mm_loadu_si128((const __m128i*)a);
    __m128i vec_b_u8 = _mm_loadu_si128((const __m128i*)b);
    __m128 vec_a_f32 = _mm_cvtepi32_ps(_mm_cvtepu8_epi32(vec_a_u8));
    __m128 vec_b_f32 = _mm_cvtepi32_ps(_mm_cvtepu8_epi32(vec_b_u8));
    __m128 vec_res_f32 = _mm_div_ps(vec_a_f32, vec_b_f32);
    __m128i vec_res_i32 = _mm_cvttps_epu32(vec_res_f32);
    __m128i vec_res_i8 = _mm_cvtepi32_epi8(vec_res_i32);
    _mm_storeu_si128((__m128i*)result, vec_res_i8);
}

static inline void SIMD_r128_f32_Div(void* a, void* b, void* result) {
    __m128 vec_a = _mm_loadu_ps((const float*)a);
    __m128 vec_b = _mm_loadu_ps((const float*)b);
    __m128 vec_res = _mm_div_ps(vec_a, vec_b);
    _mm_storeu_ps((float*)result, vec_res);
}

static inline void SIMD_r128_f64_Div(void* a, void* b, void* result) {
    __m128d vec_a = _mm_loadu_pd((const double*)a);
    __m128d vec_b = _mm_loadu_pd((const double*)b);
    __m128d vec_res = _mm_div_pd(vec_a, vec_b);
    _mm_storeu_pd((double*)result, vec_res);
}
