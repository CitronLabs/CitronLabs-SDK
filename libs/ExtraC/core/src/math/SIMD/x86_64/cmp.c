#include "../../maths.h"
#include <immintrin.h>


static inline void SIMD_r512_u64_Cmp_Lt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epu64_mask(*val_a, *val_b, _MM_CMPINT_LT);
}
static inline void SIMD_r512_u32_Cmp_Lt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epu32_mask(*val_a, *val_b, _MM_CMPINT_LT);
}
static inline void SIMD_r512_u16_Cmp_Lt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epu16_mask(*val_a, *val_b, _MM_CMPINT_LT);
}
static inline void SIMD_r512_u8_Cmp_Lt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epu8_mask(*val_a, *val_b, _MM_CMPINT_LT);
}
static inline void SIMD_r512_i64_Cmp_Lt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epi64_mask(*val_a, *val_b, _MM_CMPINT_LT);
}
static inline void SIMD_r512_i32_Cmp_Lt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epi32_mask(*val_a, *val_b, _MM_CMPINT_LT);
}
static inline void SIMD_r512_i16_Cmp_Lt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epi16_mask(*val_a, *val_b, _MM_CMPINT_LT);
}
static inline void SIMD_r512_i8_Cmp_Lt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epi8_mask(*val_a, *val_b, _MM_CMPINT_LT);
}
static inline void SIMD_r512_f32_Cmp_Lt(void* a, void* b, void* result) {
    __m512* val_a = (__m512*)a;
    __m512* val_b = (__m512*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_ps_mask(*val_a, *val_b, _CMP_LT_OQ);
}
static inline void SIMD_r512_f64_Cmp_Lt(void* a, void* b, void* result) {
    __m512d* val_a = (__m512d*)a;
    __m512d* val_b = (__m512d*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_pd_mask(*val_a, *val_b, _CMP_LT_OQ);
}

// Greater Than (Gt)
static inline void SIMD_r512_u64_Cmp_Gt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epu64_mask(*val_a, *val_b, _MM_CMPINT_GT);
}
static inline void SIMD_r512_u32_Cmp_Gt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epu32_mask(*val_a, *val_b, _MM_CMPINT_GT);
}
static inline void SIMD_r512_u16_Cmp_Gt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epu16_mask(*val_a, *val_b, _MM_CMPINT_GT);
}
static inline void SIMD_r512_u8_Cmp_Gt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epu8_mask(*val_a, *val_b, _MM_CMPINT_GT);
}
static inline void SIMD_r512_i64_Cmp_Gt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epi64_mask(*val_a, *val_b, _MM_CMPINT_GT);
}
static inline void SIMD_r512_i32_Cmp_Gt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epi32_mask(*val_a, *val_b, _MM_CMPINT_GT);
}
static inline void SIMD_r512_i16_Cmp_Gt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epi16_mask(*val_a, *val_b, _MM_CMPINT_GT);
}
static inline void SIMD_r512_i8_Cmp_Gt(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epi8_mask(*val_a, *val_b, _MM_CMPINT_GT);
}
static inline void SIMD_r512_f32_Cmp_Gt(void* a, void* b, void* result) {
    __m512* val_a = (__m512*)a;
    __m512* val_b = (__m512*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_ps_mask(*val_a, *val_b, _CMP_GT_OQ);
}
static inline void SIMD_r512_f64_Cmp_Gt(void* a, void* b, void* result) {
    __m512d* val_a = (__m512d*)a;
    __m512d* val_b = (__m512d*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_pd_mask(*val_a, *val_b, _CMP_GT_OQ);
}

// Less Than or Equal (LtEq)
static inline void SIMD_r512_u64_Cmp_LtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epu64_mask(*val_a, *val_b, _MM_CMPINT_LE);
}
static inline void SIMD_r512_u32_Cmp_LtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epu32_mask(*val_a, *val_b, _MM_CMPINT_LE);
}
static inline void SIMD_r512_u16_Cmp_LtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epu16_mask(*val_a, *val_b, _MM_CMPINT_LE);
}
static inline void SIMD_r512_u8_Cmp_LtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epu8_mask(*val_a, *val_b, _MM_CMPINT_LE);
}
static inline void SIMD_r512_i64_Cmp_LtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epi64_mask(*val_a, *val_b, _MM_CMPINT_LE);
}
static inline void SIMD_r512_i32_Cmp_LtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epi32_mask(*val_a, *val_b, _MM_CMPINT_LE);
}
static inline void SIMD_r512_i16_Cmp_LtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epi16_mask(*val_a, *val_b, _MM_CMPINT_LE);
}
static inline void SIMD_r512_i8_Cmp_LtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epi8_mask(*val_a, *val_b, _MM_CMPINT_LE);
}
static inline void SIMD_r512_f32_Cmp_LtEq(void* a, void* b, void* result) {
    __m512* val_a = (__m512*)a;
    __m512* val_b = (__m512*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_ps_mask(*val_a, *val_b, _CMP_LE_OQ);
}
static inline void SIMD_r512_f64_Cmp_LtEq(void* a, void* b, void* result) {
    __m512d* val_a = (__m512d*)a;
    __m512d* val_b = (__m512d*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_pd_mask(*val_a, *val_b, _CMP_LE_OQ);
}

// Greater Than or Equal (GtEq)
static inline void SIMD_r512_u64_Cmp_GtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epu64_mask(*val_a, *val_b, _MM_CMPINT_GE);
}
static inline void SIMD_r512_u32_Cmp_GtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epu32_mask(*val_a, *val_b, _MM_CMPINT_GE);
}
static inline void SIMD_r512_u16_Cmp_GtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epu16_mask(*val_a, *val_b, _MM_CMPINT_GE);
}
static inline void SIMD_r512_u8_Cmp_GtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epu8_mask(*val_a, *val_b, _MM_CMPINT_GE);
}
static inline void SIMD_r512_i64_Cmp_GtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epi64_mask(*val_a, *val_b, _MM_CMPINT_GE);
}
static inline void SIMD_r512_i32_Cmp_GtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epi32_mask(*val_a, *val_b, _MM_CMPINT_GE);
}
static inline void SIMD_r512_i16_Cmp_GtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epi16_mask(*val_a, *val_b, _MM_CMPINT_GE);
}
static inline void SIMD_r512_i8_Cmp_GtEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epi8_mask(*val_a, *val_b, _MM_CMPINT_GE);
}
static inline void SIMD_r512_f32_Cmp_GtEq(void* a, void* b, void* result) {
    __m512* val_a = (__m512*)a;
    __m512* val_b = (__m512*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_ps_mask(*val_a, *val_b, _CMP_GE_OQ);
}
static inline void SIMD_r512_f64_Cmp_GtEq(void* a, void* b, void* result) {
    __m512d* val_a = (__m512d*)a;
    __m512d* val_b = (__m512d*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_pd_mask(*val_a, *val_b, _CMP_GE_OQ);
}

// Equal (Eq)
static inline void SIMD_r512_u64_Cmp_Eq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epu64_mask(*val_a, *val_b, _MM_CMPINT_EQ);
}
static inline void SIMD_r512_u32_Cmp_Eq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epu32_mask(*val_a, *val_b, _MM_CMPINT_EQ);
}
static inline void SIMD_r512_u16_Cmp_Eq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epu16_mask(*val_a, *val_b, _MM_CMPINT_EQ);
}
static inline void SIMD_r512_u8_Cmp_Eq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epu8_mask(*val_a, *val_b, _MM_CMPINT_EQ);
}
static inline void SIMD_r512_i64_Cmp_Eq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epi64_mask(*val_a, *val_b, _MM_CMPINT_EQ);
}
static inline void SIMD_r512_i32_Cmp_Eq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epi32_mask(*val_a, *val_b, _MM_CMPINT_EQ);
}
static inline void SIMD_r512_i16_Cmp_Eq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epi16_mask(*val_a, *val_b, _MM_CMPINT_EQ);
}
static inline void SIMD_r512_i8_Cmp_Eq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epi8_mask(*val_a, *val_b, _MM_CMPINT_EQ);
}
static inline void SIMD_r512_f32_Cmp_Eq(void* a, void* b, void* result) {
    __m512* val_a = (__m512*)a;
    __m512* val_b = (__m512*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_ps_mask(*val_a, *val_b, _CMP_EQ_OQ);
}
static inline void SIMD_r512_f64_Cmp_Eq(void* a, void* b, void* result) {
    __m512d* val_a = (__m512d*)a;
    __m512d* val_b = (__m512d*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_pd_mask(*val_a, *val_b, _CMP_EQ_OQ);
}

// Not Equal (NotEq)
static inline void SIMD_r512_u64_Cmp_NotEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epu64_mask(*val_a, *val_b, _MM_CMPINT_NE);
}
static inline void SIMD_r512_u32_Cmp_NotEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epu32_mask(*val_a, *val_b, _MM_CMPINT_NE);
}
static inline void SIMD_r512_u16_Cmp_NotEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epu16_mask(*val_a, *val_b, _MM_CMPINT_NE);
}
static inline void SIMD_r512_u8_Cmp_NotEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epu8_mask(*val_a, *val_b, _MM_CMPINT_NE);
}
static inline void SIMD_r512_i64_Cmp_NotEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_epi64_mask(*val_a, *val_b, _MM_CMPINT_NE);
}
static inline void SIMD_r512_i32_Cmp_NotEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_epi32_mask(*val_a, *val_b, _MM_CMPINT_NE);
}
static inline void SIMD_r512_i16_Cmp_NotEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask32* mask_result = (__mmask32*)result;
    *mask_result = _mm512_cmp_epi16_mask(*val_a, *val_b, _MM_CMPINT_NE);
}
static inline void SIMD_r512_i8_Cmp_NotEq(void* a, void* b, void* result) {
    __m512i* val_a = (__m512i*)a;
    __m512i* val_b = (__m512i*)b;
    __mmask64* mask_result = (__mmask64*)result;
    *mask_result = _mm512_cmp_epi8_mask(*val_a, *val_b, _MM_CMPINT_NE);
}
static inline void SIMD_r512_f32_Cmp_NotEq(void* a, void* b, void* result) {
    __m512* val_a = (__m512*)a;
    __m512* val_b = (__m512*)b;
    __mmask16* mask_result = (__mmask16*)result;
    *mask_result = _mm512_cmp_ps_mask(*val_a, *val_b, _CMP_NEQ_OQ);
}
static inline void SIMD_r512_f64_Cmp_NotEq(void* a, void* b, void* result) {
    __m512d* val_a = (__m512d*)a;
    __m512d* val_b = (__m512d*)b;
    __mmask8* mask_result = (__mmask8*)result;
    *mask_result = _mm512_cmp_pd_mask(*val_a, *val_b, _CMP_NEQ_OQ);
}

// === 256-bit (AVX2) Functions ===

// Less Than (Lt)
static inline void SIMD_r256_u64_Cmp_Lt(void* a, void* b, void* result) {
    // Note: No direct unsigned compare for 64-bit on AVX2. This is a common workaround.
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i carry = _mm256_sub_epi64(_mm256_set1_epi64x(0), _mm256_cmpgt_epi64(*val_b, *val_a));
    __m256i a_xor_sign = _mm256_xor_si256(*val_a, _mm256_set1_epi64x(0x8000000000000000ULL));
    __m256i b_xor_sign = _mm256_xor_si256(*val_b, _mm256_set1_epi64x(0x8000000000000000ULL));
    __m256i result_signed = _mm256_cmpgt_epi64(b_xor_sign, a_xor_sign);
    __m256i result_with_borrow = _mm256_and_si256(carry, _mm256_cmpgt_epi64(a_xor_sign, b_xor_sign));
    *res = _mm256_or_si256(result_signed, result_with_borrow);
}
static inline void SIMD_r256_u32_Cmp_Lt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi32(_mm256_xor_si256(*val_a, _mm256_set1_epi32(0x80000000)), _mm256_xor_si256(*val_b, _mm256_set1_epi32(0x80000000)));
}
static inline void SIMD_r256_u16_Cmp_Lt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi16(_mm256_xor_si256(*val_a, _mm256_set1_epi16(0x8000)), _mm256_xor_si256(*val_b, _mm256_set1_epi16(0x8000)));
}
static inline void SIMD_r256_u8_Cmp_Lt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i cmp = _mm256_subs_epu8(*val_b, *val_a);
    *res = _mm256_cmpeq_epi8(cmp, _mm256_setzero_si256());
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0)); // invert result
}
static inline void SIMD_r256_i64_Cmp_Lt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi64(_mm256_setzero_si256(), _mm256_sub_epi64(*val_a, *val_b));
}
static inline void SIMD_r256_i32_Cmp_Lt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi32(_mm256_setzero_si256(), _mm256_sub_epi32(*val_a, *val_b));
}
static inline void SIMD_r256_i16_Cmp_Lt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi16(_mm256_setzero_si256(), _mm256_sub_epi16(*val_a, *val_b));
}
static inline void SIMD_r256_i8_Cmp_Lt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi8(_mm256_setzero_si256(), _mm256_sub_epi8(*val_a, *val_b));
}
static inline void SIMD_r256_f32_Cmp_Lt(void* a, void* b, void* result) {
    __m256* val_a = (__m256*)a;
    __m256* val_b = (__m256*)b;
    __m256* res = (__m256*)result;
    *res = _mm256_cmp_ps(*val_a, *val_b, _CMP_LT_OQ);
}
static inline void SIMD_r256_f64_Cmp_Lt(void* a, void* b, void* result) {
    __m256d* val_a = (__m256d*)a;
    __m256d* val_b = (__m256d*)b;
    __m256d* res = (__m256d*)result;
    *res = _mm256_cmp_pd(*val_a, *val_b, _CMP_LT_OQ);
}

// Greater Than (Gt)
static inline void SIMD_r256_u64_Cmp_Gt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i carry = _mm256_sub_epi64(_mm256_set1_epi64x(0), _mm256_cmpgt_epi64(*val_a, *val_b));
    __m256i a_xor_sign = _mm256_xor_si256(*val_a, _mm256_set1_epi64x(0x8000000000000000ULL));
    __m256i b_xor_sign = _mm256_xor_si256(*val_b, _mm256_set1_epi64x(0x8000000000000000ULL));
    __m256i result_signed = _mm256_cmpgt_epi64(a_xor_sign, b_xor_sign);
    __m256i result_with_borrow = _mm256_and_si256(carry, _mm256_cmpgt_epi64(b_xor_sign, a_xor_sign));
    *res = _mm256_or_si256(result_signed, result_with_borrow);
}
static inline void SIMD_r256_u32_Cmp_Gt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi32(_mm256_xor_si256(*val_b, _mm256_set1_epi32(0x80000000)), _mm256_xor_si256(*val_a, _mm256_set1_epi32(0x80000000)));
}
static inline void SIMD_r256_u16_Cmp_Gt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi16(_mm256_xor_si256(*val_b, _mm256_set1_epi16(0x8000)), _mm256_xor_si256(*val_a, _mm256_set1_epi16(0x8000)));
}
static inline void SIMD_r256_u8_Cmp_Gt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i cmp = _mm256_subs_epu8(*val_a, *val_b);
    *res = _mm256_cmpeq_epi8(cmp, _mm256_setzero_si256());
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0)); // invert result
}
static inline void SIMD_r256_i64_Cmp_Gt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi64(*val_a, *val_b);
}
static inline void SIMD_r256_i32_Cmp_Gt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi32(*val_a, *val_b);
}
static inline void SIMD_r256_i16_Cmp_Gt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi16(*val_a, *val_b);
}
static inline void SIMD_r256_i8_Cmp_Gt(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpgt_epi8(*val_a, *val_b);
}
static inline void SIMD_r256_f32_Cmp_Gt(void* a, void* b, void* result) {
    __m256* val_a = (__m256*)a;
    __m256* val_b = (__m256*)b;
    __m256* res = (__m256*)result;
    *res = _mm256_cmp_ps(*val_a, *val_b, _CMP_GT_OQ);
}
static inline void SIMD_r256_f64_Cmp_Gt(void* a, void* b, void* result) {
    __m256d* val_a = (__m256d*)a;
    __m256d* val_b = (__m256d*)b;
    __m256d* res = (__m256d*)result;
    *res = _mm256_cmp_pd(*val_a, *val_b, _CMP_GT_OQ);
}

// Less Than or Equal (LtEq)
static inline void SIMD_r256_u64_Cmp_LtEq(void* a, void* b, void* result) {
    // Note: No direct unsigned compare for 64-bit on AVX2. This is a common workaround.
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_lt = _mm256_cmpgt_epi64(_mm256_xor_si256(*val_a, _mm256_set1_epi64x(0x8000000000000000ULL)), _mm256_xor_si256(*val_b, _mm256_set1_epi64x(0x8000000000000000ULL)));
    __m256i mask_eq = _mm256_cmpeq_epi64(*val_a, *val_b);
    *res = _mm256_or_si256(mask_lt, mask_eq);
}
static inline void SIMD_r256_u32_Cmp_LtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_lt = _mm256_cmpgt_epi32(_mm256_xor_si256(*val_a, _mm256_set1_epi32(0x80000000)), _mm256_xor_si256(*val_b, _mm256_set1_epi32(0x80000000)));
    __m256i mask_eq = _mm256_cmpeq_epi32(*val_a, *val_b);
    *res = _mm256_or_si256(mask_lt, mask_eq);
}
static inline void SIMD_r256_u16_Cmp_LtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_lt = _mm256_cmpgt_epi16(_mm256_xor_si256(*val_a, _mm256_set1_epi16(0x8000)), _mm256_xor_si256(*val_b, _mm256_set1_epi16(0x8000)));
    __m256i mask_eq = _mm256_cmpeq_epi16(*val_a, *val_b);
    *res = _mm256_or_si256(mask_lt, mask_eq);
}
static inline void SIMD_r256_u8_Cmp_LtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_lt = _mm256_cmpgt_epi8(_mm256_xor_si256(*val_a, _mm256_set1_epi8(0x80)), _mm256_xor_si256(*val_b, _mm256_set1_epi8(0x80)));
    __m256i mask_eq = _mm256_cmpeq_epi8(*val_a, *val_b);
    *res = _mm256_or_si256(mask_lt, mask_eq);
}
static inline void SIMD_r256_i64_Cmp_LtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_lt = _mm256_cmpgt_epi64(_mm256_setzero_si256(), _mm256_sub_epi64(*val_a, *val_b));
    __m256i mask_eq = _mm256_cmpeq_epi64(*val_a, *val_b);
    *res = _mm256_or_si256(mask_lt, mask_eq);
}
static inline void SIMD_r256_i32_Cmp_LtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_lt = _mm256_cmpgt_epi32(_mm256_setzero_si256(), _mm256_sub_epi32(*val_a, *val_b));
    __m256i mask_eq = _mm256_cmpeq_epi32(*val_a, *val_b);
    *res = _mm256_or_si256(mask_lt, mask_eq);
}
static inline void SIMD_r256_i16_Cmp_LtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_lt = _mm256_cmpgt_epi16(_mm256_setzero_si256(), _mm256_sub_epi16(*val_a, *val_b));
    __m256i mask_eq = _mm256_cmpeq_epi16(*val_a, *val_b);
    *res = _mm256_or_si256(mask_lt, mask_eq);
}
static inline void SIMD_r256_i8_Cmp_LtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_lt = _mm256_cmpgt_epi8(_mm256_setzero_si256(), _mm256_sub_epi8(*val_a, *val_b));
    __m256i mask_eq = _mm256_cmpeq_epi8(*val_a, *val_b);
    *res = _mm256_or_si256(mask_lt, mask_eq);
}
static inline void SIMD_r256_f32_Cmp_LtEq(void* a, void* b, void* result) {
    __m256* val_a = (__m256*)a;
    __m256* val_b = (__m256*)b;
    __m256* res = (__m256*)result;
    *res = _mm256_cmp_ps(*val_a, *val_b, _CMP_LE_OQ);
}
static inline void SIMD_r256_f64_Cmp_LtEq(void* a, void* b, void* result) {
    __m256d* val_a = (__m256d*)a;
    __m256d* val_b = (__m256d*)b;
    __m256d* res = (__m256d*)result;
    *res = _mm256_cmp_pd(*val_a, *val_b, _CMP_LE_OQ);
}

// Greater Than or Equal (GtEq)
static inline void SIMD_r256_u64_Cmp_GtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_gt = _mm256_cmpgt_epi64(_mm256_xor_si256(*val_b, _mm256_set1_epi64x(0x8000000000000000ULL)), _mm256_xor_si256(*val_a, _mm256_set1_epi64x(0x8000000000000000ULL)));
    __m256i mask_eq = _mm256_cmpeq_epi64(*val_a, *val_b);
    *res = _mm256_or_si256(mask_gt, mask_eq);
}
static inline void SIMD_r256_u32_Cmp_GtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_gt = _mm256_cmpgt_epi32(_mm256_xor_si256(*val_b, _mm256_set1_epi32(0x80000000)), _mm256_xor_si256(*val_a, _mm256_set1_epi32(0x80000000)));
    __m256i mask_eq = _mm256_cmpeq_epi32(*val_a, *val_b);
    *res = _mm256_or_si256(mask_gt, mask_eq);
}
static inline void SIMD_r256_u16_Cmp_GtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_gt = _mm256_cmpgt_epi16(_mm256_xor_si256(*val_b, _mm256_set1_epi16(0x8000)), _mm256_xor_si256(*val_a, _mm256_set1_epi16(0x8000)));
    __m256i mask_eq = _mm256_cmpeq_epi16(*val_a, *val_b);
    *res = _mm256_or_si256(mask_gt, mask_eq);
}
static inline void SIMD_r256_u8_Cmp_GtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_gt = _mm256_cmpgt_epi8(_mm256_xor_si256(*val_b, _mm256_set1_epi8(0x80)), _mm256_xor_si256(*val_a, _mm256_set1_epi8(0x80)));
    __m256i mask_eq = _mm256_cmpeq_epi8(*val_a, *val_b);
    *res = _mm256_or_si256(mask_gt, mask_eq);
}
static inline void SIMD_r256_i64_Cmp_GtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_gt = _mm256_cmpgt_epi64(*val_a, *val_b);
    __m256i mask_eq = _mm256_cmpeq_epi64(*val_a, *val_b);
    *res = _mm256_or_si256(mask_gt, mask_eq);
}
static inline void SIMD_r256_i32_Cmp_GtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_gt = _mm256_cmpgt_epi32(*val_a, *val_b);
    __m256i mask_eq = _mm256_cmpeq_epi32(*val_a, *val_b);
    *res = _mm256_or_si256(mask_gt, mask_eq);
}
static inline void SIMD_r256_i16_Cmp_GtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_gt = _mm256_cmpgt_epi16(*val_a, *val_b);
    __m256i mask_eq = _mm256_cmpeq_epi16(*val_a, *val_b);
    *res = _mm256_or_si256(mask_gt, mask_eq);
}
static inline void SIMD_r256_i8_Cmp_GtEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    __m256i mask_gt = _mm256_cmpgt_epi8(*val_a, *val_b);
    __m256i mask_eq = _mm256_cmpeq_epi8(*val_a, *val_b);
    *res = _mm256_or_si256(mask_gt, mask_eq);
}
static inline void SIMD_r256_f32_Cmp_GtEq(void* a, void* b, void* result) {
    __m256* val_a = (__m256*)a;
    __m256* val_b = (__m256*)b;
    __m256* res = (__m256*)result;
    *res = _mm256_cmp_ps(*val_a, *val_b, _CMP_GE_OQ);
}
static inline void SIMD_r256_f64_Cmp_GtEq(void* a, void* b, void* result) {
    __m256d* val_a = (__m256d*)a;
    __m256d* val_b = (__m256d*)b;
    __m256d* res = (__m256d*)result;
    *res = _mm256_cmp_pd(*val_a, *val_b, _CMP_GE_OQ);
}

// Equal (Eq)
static inline void SIMD_r256_u64_Cmp_Eq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi64(*val_a, *val_b);
}
static inline void SIMD_r256_u32_Cmp_Eq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi32(*val_a, *val_b);
}
static inline void SIMD_r256_u16_Cmp_Eq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi16(*val_a, *val_b);
}
static inline void SIMD_r256_u8_Cmp_Eq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi8(*val_a, *val_b);
}
static inline void SIMD_r256_i64_Cmp_Eq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi64(*val_a, *val_b);
}
static inline void SIMD_r256_i32_Cmp_Eq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi32(*val_a, *val_b);
}
static inline void SIMD_r256_i16_Cmp_Eq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi16(*val_a, *val_b);
}
static inline void SIMD_r256_i8_Cmp_Eq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi8(*val_a, *val_b);
}
static inline void SIMD_r256_f32_Cmp_Eq(void* a, void* b, void* result) {
    __m256* val_a = (__m256*)a;
    __m256* val_b = (__m256*)b;
    __m256* res = (__m256*)result;
    *res = _mm256_cmp_ps(*val_a, *val_b, _CMP_EQ_OQ);
}
static inline void SIMD_r256_f64_Cmp_Eq(void* a, void* b, void* result) {
    __m256d* val_a = (__m256d*)a;
    __m256d* val_b = (__m256d*)b;
    __m256d* res = (__m256d*)result;
    *res = _mm256_cmp_pd(*val_a, *val_b, _CMP_EQ_OQ);
}

// Not Equal (NotEq)
static inline void SIMD_r256_u64_Cmp_NotEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi64(*val_a, *val_b);
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0));
}
static inline void SIMD_r256_u32_Cmp_NotEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi32(*val_a, *val_b);
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0));
}
static inline void SIMD_r256_u16_Cmp_NotEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi16(*val_a, *val_b);
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0));
}
static inline void SIMD_r256_u8_Cmp_NotEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi8(*val_a, *val_b);
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0));
}
static inline void SIMD_r256_i64_Cmp_NotEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi64(*val_a, *val_b);
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0));
}
static inline void SIMD_r256_i32_Cmp_NotEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi32(*val_a, *val_b);
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0));
}
static inline void SIMD_r256_i16_Cmp_NotEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi16(*val_a, *val_b);
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0));
}
static inline void SIMD_r256_i8_Cmp_NotEq(void* a, void* b, void* result) {
    __m256i* val_a = (__m256i*)a;
    __m256i* val_b = (__m256i*)b;
    __m256i* res = (__m256i*)result;
    *res = _mm256_cmpeq_epi8(*val_a, *val_b);
    *res = _mm256_xor_si256(*res, _mm256_set1_epi32(~0));
}
static inline void SIMD_r256_f32_Cmp_NotEq(void* a, void* b, void* result) {
    __m256* val_a = (__m256*)a;
    __m256* val_b = (__m256*)b;
    __m256* res = (__m256*)result;
    *res = _mm256_cmp_ps(*val_a, *val_b, _CMP_NEQ_OQ);
}
static inline void SIMD_r256_f64_Cmp_NotEq(void* a, void* b, void* result) {
    __m256d* val_a = (__m256d*)a;
    __m256d* val_b = (__m256d*)b;
    __m256d* res = (__m256d*)result;
    *res = _mm256_cmp_pd(*val_a, *val_b, _CMP_NEQ_OQ);
}

// === 128-bit (SSE/SSE4.1) Functions ===

// Less Than (Lt)
static inline void SIMD_r128_u64_Cmp_Lt(void* a, void* b, void* result) {
    // Note: No direct unsigned compare for 64-bit on SSE.
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i gt_result = _mm_cmpgt_epi64(*val_b, *val_a);
    __m128i eq_result = _mm_cmpeq_epi64(*val_a, *val_b);
    __m128i lt_result = _mm_xor_si128(_mm_xor_si128(gt_result, eq_result), _mm_set1_epi64x(-1LL));
    *res = lt_result;
}
static inline void SIMD_r128_u32_Cmp_Lt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi32(_mm_xor_si128(*val_a, _mm_set1_epi32(0x80000000)), _mm_xor_si128(*val_b, _mm_set1_epi32(0x80000000)));
}
static inline void SIMD_r128_u16_Cmp_Lt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi16(_mm_xor_si128(*val_a, _mm_set1_epi16(0x8000)), _mm_xor_si128(*val_b, _mm_set1_epi16(0x8000)));
}
static inline void SIMD_r128_u8_Cmp_Lt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i cmp = _mm_subs_epu8(*val_b, *val_a);
    *res = _mm_cmpeq_epi8(cmp, _mm_setzero_si128());
    *res = _mm_xor_si128(*res, _mm_set1_epi32(~0)); // invert result
}
static inline void SIMD_r128_i64_Cmp_Lt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi64(_mm_setzero_si128(), _mm_sub_epi64(*val_a, *val_b));
}
static inline void SIMD_r128_i32_Cmp_Lt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmplt_epi32(*val_a, *val_b);
}
static inline void SIMD_r128_i16_Cmp_Lt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmplt_epi16(*val_a, *val_b);
}
static inline void SIMD_r128_i8_Cmp_Lt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmplt_epi8(*val_a, *val_b);
}
static inline void SIMD_r128_f32_Cmp_Lt(void* a, void* b, void* result) {
    __m128* val_a = (__m128*)a;
    __m128* val_b = (__m128*)b;
    __m128* res = (__m128*)result;
    *res = _mm_cmplt_ps(*val_a, *val_b);
}
static inline void SIMD_r128_f64_Cmp_Lt(void* a, void* b, void* result) {
    __m128d* val_a = (__m128d*)a;
    __m128d* val_b = (__m128d*)b;
    __m128d* res = (__m128d*)result;
    *res = _mm_cmplt_pd(*val_a, *val_b);
}

// Greater Than (Gt)
static inline void SIMD_r128_u64_Cmp_Gt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi64(*val_a, *val_b);
}
static inline void SIMD_r128_u32_Cmp_Gt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi32(_mm_xor_si128(*val_b, _mm_set1_epi32(0x80000000)), _mm_xor_si128(*val_a, _mm_set1_epi32(0x80000000)));
}
static inline void SIMD_r128_u16_Cmp_Gt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi16(_mm_xor_si128(*val_b, _mm_set1_epi16(0x8000)), _mm_xor_si128(*val_a, _mm_set1_epi16(0x8000)));
}
static inline void SIMD_r128_u8_Cmp_Gt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i cmp = _mm_subs_epu8(*val_a, *val_b);
    *res = _mm_cmpeq_epi8(cmp, _mm_setzero_si128());
    *res = _mm_xor_si128(*res, _mm_set1_epi32(~0)); // invert result
}
static inline void SIMD_r128_i64_Cmp_Gt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi64(*val_a, *val_b);
}
static inline void SIMD_r128_i32_Cmp_Gt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi32(*val_a, *val_b);
}
static inline void SIMD_r128_i16_Cmp_Gt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi16(*val_a, *val_b);
}
static inline void SIMD_r128_i8_Cmp_Gt(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpgt_epi8(*val_a, *val_b);
}
static inline void SIMD_r128_f32_Cmp_Gt(void* a, void* b, void* result) {
    __m128* val_a = (__m128*)a;
    __m128* val_b = (__m128*)b;
    __m128* res = (__m128*)result;
    *res = _mm_cmpgt_ps(*val_a, *val_b);
}
static inline void SIMD_r128_f64_Cmp_Gt(void* a, void* b, void* result) {
    __m128d* val_a = (__m128d*)a;
    __m128d* val_b = (__m128d*)b;
    __m128d* res = (__m128d*)result;
    *res = _mm_cmpgt_pd(*val_a, *val_b);
}

// Less Than or Equal (LtEq)
static inline void SIMD_r128_u64_Cmp_LtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i mask_gt = _mm_cmpgt_epi64(*val_a, *val_b);
    *res = _mm_xor_si128(mask_gt, _mm_set1_epi64x(-1LL));
}
static inline void SIMD_r128_u32_Cmp_LtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i mask_gt = _mm_cmpgt_epi32(_mm_xor_si128(*val_b, _mm_set1_epi32(0x80000000)), _mm_xor_si128(*val_a, _mm_set1_epi32(0x80000000)));
    *res = _mm_xor_si128(mask_gt, _mm_set1_epi32(~0));
}
static inline void SIMD_r128_u16_Cmp_LtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i mask_gt = _mm_cmpgt_epi16(_mm_xor_si128(*val_b, _mm_set1_epi16(0x8000)), _mm_xor_si128(*val_a, _mm_set1_epi16(0x8000)));
    *res = _mm_xor_si128(mask_gt, _mm_set1_epi16(~0));
}
static inline void SIMD_r128_u8_Cmp_LtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i mask_gt = _mm_cmpgt_epi8(_mm_xor_si128(*val_b, _mm_set1_epi8(0x80)), _mm_xor_si128(*val_a, _mm_set1_epi8(0x80)));
    *res = _mm_xor_si128(mask_gt, _mm_set1_epi8(~0));
}
static inline void SIMD_r128_i64_Cmp_LtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i mask_gt = _mm_cmpgt_epi64(*val_a, *val_b);
    *res = _mm_xor_si128(mask_gt, _mm_set1_epi64x(-1LL));
}
// Less Than or Equal (LtEq)
// Corrected logic for 32-bit signed integers
// Implemented as NOT(a > b)
static inline void SIMD_r128_i32_Cmp_LtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    // _mm_cmple_epi32 does not exist. Use _mm_cmpgt_epi32 and invert the result.
    __m128i mask_gt = _mm_cmpgt_epi32(*val_a, *val_b);
    *res = _mm_xor_si128(mask_gt, _mm_set1_epi32(-1));
}

// Corrected logic for 16-bit signed integers
// Implemented as NOT(a > b)
static inline void SIMD_r128_i16_Cmp_LtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    // _mm_cmple_epi16 does not exist. Use _mm_cmpgt_epi16 and invert the result.
    __m128i mask_gt = _mm_cmpgt_epi16(*val_a, *val_b);
    *res = _mm_xor_si128(mask_gt, _mm_set1_epi16(-1));
}

// Corrected logic for 8-bit signed integers
// Implemented as NOT(a > b)
static inline void SIMD_r128_i8_Cmp_LtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    // _mm_cmple_epi8 does not exist. Use _mm_cmpgt_epi8 and invert the result.
    __m128i mask_gt = _mm_cmpgt_epi8(*val_a, *val_b);
    *res = _mm_xor_si128(mask_gt, _mm_set1_epi8(-1));
}
static inline void SIMD_r128_f32_Cmp_LtEq(void* a, void* b, void* result) {
    __m128* val_a = (__m128*)a;
    __m128* val_b = (__m128*)b;
    __m128* res = (__m128*)result;
    *res = _mm_cmple_ps(*val_a, *val_b);
}
static inline void SIMD_r128_f64_Cmp_LtEq(void* a, void* b, void* result) {
    __m128d* val_a = (__m128d*)a;
    __m128d* val_b = (__m128d*)b;
    __m128d* res = (__m128d*)result;
    *res = _mm_cmple_pd(*val_a, *val_b);
}

// Greater Than or Equal (GtEq)
// Corrected logic for 64-bit unsigned integers
// Implemented as NOT(a < b), which is NOT(b > a)
static inline void SIMD_r128_u64_Cmp_GtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    // To perform 'less than' for unsigned 64-bit, we must rely on a different approach.
    // The SSE2 set does not have _mm_cmplt_epu64 or _mm_cmpge_epu64.
    // This implementation uses a combination of cmpgt and cmpeq.
    __m128i mask_gt = _mm_cmpgt_epi64(*val_a, *val_b);
    __m128i mask_eq = _mm_cmpeq_epi64(*val_a, *val_b);
    *res = _mm_or_si128(mask_gt, mask_eq);
}

static inline void SIMD_r128_u32_Cmp_GtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i mask_lt = _mm_cmpgt_epi32(_mm_xor_si128(*val_a, _mm_set1_epi32(0x80000000)), _mm_xor_si128(*val_b, _mm_set1_epi32(0x80000000)));
    *res = _mm_xor_si128(mask_lt, _mm_set1_epi32(~0));
}
static inline void SIMD_r128_u16_Cmp_GtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i mask_lt = _mm_cmpgt_epi16(_mm_xor_si128(*val_a, _mm_set1_epi16(0x8000)), _mm_xor_si128(*val_b, _mm_set1_epi16(0x8000)));
    *res = _mm_xor_si128(mask_lt, _mm_set1_epi16(~0));
}
static inline void SIMD_r128_u8_Cmp_GtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i mask_lt = _mm_cmpgt_epi8(_mm_xor_si128(*val_a, _mm_set1_epi8(0x80)), _mm_xor_si128(*val_b, _mm_set1_epi8(0x80)));
    *res = _mm_xor_si128(mask_lt, _mm_set1_epi8(~0));
}
// Corrected logic for 64-bit signed integers
// Implemented as NOT(a < b), which is NOT(b > a)
static inline void SIMD_r128_i64_Cmp_GtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    // _mm_cmplt_epi64 does not exist. A common workaround is to use _mm_cmpgt_epi64
    // and swap the operands. The logic 'a >= b' is equivalent to 'NOT (a < b)'.
    // 'a < b' is the same as 'b > a', so we use _mm_cmpgt_epi64(*val_b, *val_a).
    __m128i mask_lt = _mm_cmpgt_epi64(*val_b, *val_a);
    // Invert the mask to get 'greater than or equal to'.
    *res = _mm_xor_si128(mask_lt, _mm_set1_epi64x(-1LL));
}

// Corrected logic for 32-bit signed integers
// Implemented as NOT(a < b), which is NOT(b > a)
static inline void SIMD_r128_i32_Cmp_GtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    // _mm_cmpge_epi32 does not exist. Use the same logical trick as above.
    __m128i mask_lt = _mm_cmpgt_epi32(*val_b, *val_a);
    *res = _mm_xor_si128(mask_lt, _mm_set1_epi32(-1));
}

// Corrected logic for 16-bit signed integers
// Implemented as NOT(a < b), which is NOT(b > a)
static inline void SIMD_r128_i16_Cmp_GtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    // _mm_cmpge_epi16 does not exist. Use the same logical trick as above.
    __m128i mask_lt = _mm_cmpgt_epi16(*val_b, *val_a);
    *res = _mm_xor_si128(mask_lt, _mm_set1_epi16(-1));
}

// Corrected logic for 8-bit signed integers
// Implemented as NOT(a < b), which is NOT(b > a)
static inline void SIMD_r128_i8_Cmp_GtEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    // _mm_cmpge_epi8 does not exist. Use the same logical trick as above.
    __m128i mask_lt = _mm_cmpgt_epi8(*val_b, *val_a);
    *res = _mm_xor_si128(mask_lt, _mm_set1_epi8(-1));
}
static inline void SIMD_r128_f32_Cmp_GtEq(void* a, void* b, void* result) {
    __m128* val_a = (__m128*)a;
    __m128* val_b = (__m128*)b;
    __m128* res = (__m128*)result;
    *res = _mm_cmpge_ps(*val_a, *val_b);
}
static inline void SIMD_r128_f64_Cmp_GtEq(void* a, void* b, void* result) {
    __m128d* val_a = (__m128d*)a;
    __m128d* val_b = (__m128d*)b;
    __m128d* res = (__m128d*)result;
    *res = _mm_cmpge_pd(*val_a, *val_b);
}

// Equal (Eq)
static inline void SIMD_r128_u64_Cmp_Eq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpeq_epi64(*val_a, *val_b);
}
static inline void SIMD_r128_u32_Cmp_Eq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpeq_epi32(*val_a, *val_b);
}
static inline void SIMD_r128_u16_Cmp_Eq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpeq_epi16(*val_a, *val_b);
}
static inline void SIMD_r128_u8_Cmp_Eq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpeq_epi8(*val_a, *val_b);
}
static inline void SIMD_r128_i64_Cmp_Eq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpeq_epi64(*val_a, *val_b);
}
static inline void SIMD_r128_i32_Cmp_Eq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpeq_epi32(*val_a, *val_b);
}
static inline void SIMD_r128_i16_Cmp_Eq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpeq_epi16(*val_a, *val_b);
}
static inline void SIMD_r128_i8_Cmp_Eq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    *res = _mm_cmpeq_epi8(*val_a, *val_b);
}
static inline void SIMD_r128_f32_Cmp_Eq(void* a, void* b, void* result) {
    __m128* val_a = (__m128*)a;
    __m128* val_b = (__m128*)b;
    __m128* res = (__m128*)result;
    *res = _mm_cmpeq_ps(*val_a, *val_b);
}
static inline void SIMD_r128_f64_Cmp_Eq(void* a, void* b, void* result) {
    __m128d* val_a = (__m128d*)a;
    __m128d* val_b = (__m128d*)b;
    __m128d* res = (__m128d*)result;
    *res = _mm_cmpeq_pd(*val_a, *val_b);
}

// Not Equal (NotEq)
static inline void SIMD_r128_u64_Cmp_NotEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i eq_result = _mm_cmpeq_epi64(*val_a, *val_b);
    *res = _mm_xor_si128(eq_result, _mm_set1_epi64x(-1LL));
}
static inline void SIMD_r128_u32_Cmp_NotEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i eq_result = _mm_cmpeq_epi32(*val_a, *val_b);
    *res = _mm_xor_si128(eq_result, _mm_set1_epi32(~0));
}
static inline void SIMD_r128_u16_Cmp_NotEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i eq_result = _mm_cmpeq_epi16(*val_a, *val_b);
    *res = _mm_xor_si128(eq_result, _mm_set1_epi16(~0));
}
static inline void SIMD_r128_u8_Cmp_NotEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i eq_result = _mm_cmpeq_epi8(*val_a, *val_b);
    *res = _mm_xor_si128(eq_result, _mm_set1_epi8(~0));
}
static inline void SIMD_r128_i64_Cmp_NotEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i eq_result = _mm_cmpeq_epi64(*val_a, *val_b);
    *res = _mm_xor_si128(eq_result, _mm_set1_epi64x(-1LL));
}
static inline void SIMD_r128_i32_Cmp_NotEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i eq_result = _mm_cmpeq_epi32(*val_a, *val_b);
    *res = _mm_xor_si128(eq_result, _mm_set1_epi32(~0));
}
static inline void SIMD_r128_i16_Cmp_NotEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i eq_result = _mm_cmpeq_epi16(*val_a, *val_b);
    *res = _mm_xor_si128(eq_result, _mm_set1_epi16(~0));
}
static inline void SIMD_r128_i8_Cmp_NotEq(void* a, void* b, void* result) {
    __m128i* val_a = (__m128i*)a;
    __m128i* val_b = (__m128i*)b;
    __m128i* res = (__m128i*)result;
    __m128i eq_result = _mm_cmpeq_epi8(*val_a, *val_b);
    *res = _mm_xor_si128(eq_result, _mm_set1_epi8(~0));
}
static inline void SIMD_r128_f32_Cmp_NotEq(void* a, void* b, void* result) {
    __m128* val_a = (__m128*)a;
    __m128* val_b = (__m128*)b;
    __m128* res = (__m128*)result;
    *res = _mm_cmpneq_ps(*val_a, *val_b);
}
static inline void SIMD_r128_f64_Cmp_NotEq(void* a, void* b, void* result) {
    __m128d* val_a = (__m128d*)a;
    __m128d* val_b = (__m128d*)b;
    __m128d* res = (__m128d*)result;
    *res = _mm_cmpneq_pd(*val_a, *val_b);
}
