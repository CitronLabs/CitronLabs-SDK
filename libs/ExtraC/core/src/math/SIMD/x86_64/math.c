#include "../../maths.h"
#include <immintrin.h>
#if defined(__AVX2__)
void SIMD_AddFlt_32_512(void* a, void* b, void* result){*((__m512*)result) = _mm512_add_ps(*((__m512*)a), *((__m512*)b));}
void SIMD_AddFlt_64_512(void* a, void* b, void* result){*((__m512d*)result) = _mm512_add_pd(*((__m512d*)a), *((__m512d*)b));}
void SIMD_AddInt_64_512(void* a, void* b, void* result){*((__m512i*)result) = _mm512_add_epi64(*((__m512i*)a), *((__m512i*)b));}
void SIMD_AddInt_32_512(void* a, void* b, void* result){*((__m512i*)result) = _mm512_add_epi32(*((__m512i*)a), *((__m512i*)b));}
void SIMD_AddInt_16_512(void* a, void* b, void* result){*((__m512i*)result) = _mm512_add_epi16(*((__m512i*)a), *((__m512i*)b));}
void SIMD_AddInt_8_512(void* a, void* b, void* result){*((__m512i*)result) = _mm512_add_epi8(*((__m512i*)a), *((__m512i*)b));}

void SIMD_SubFlt_32_512(void* a, void* b, void* result){*((__m512*)result) = _mm512_sub_ps(*((__m512*)a), *((__m512*)b));}
void SIMD_SubFlt_64_512(void* a, void* b, void* result){*((__m512d*)result) = _mm512_sub_pd(*((__m512d*)a), *((__m512d*)b));}
void SIMD_SubInt_64_512(void* a, void* b, void* result){*((__m512i*)result) = _mm512_sub_epi64(*((__m512i*)a), *((__m512i*)b));}
void SIMD_SubInt_32_512(void* a, void* b, void* result){*((__m512i*)result) = _mm512_sub_epi32(*((__m512i*)a), *((__m512i*)b));}
void SIMD_SubInt_16_512(void* a, void* b, void* result){*((__m512i*)result) = _mm512_sub_epi16(*((__m512i*)a), *((__m512i*)b));}
void SIMD_SubInt_8_512(void* a, void* b, void* result){*((__m512i*)result) = _mm512_sub_epi8(*((__m512i*)a), *((__m512i*)b));}

void SIMD_MulFlt_32_512(void* a, void* b, void* result){*((__m512*)result) = _mm512_mul_ps(*((__m512*)a), *((__m512*)b));}
void SIMD_MulFlt_64_512(void* a, void* b, void* result){*((__m512d*)result) = _mm512_mul_pd(*((__m512d*)a), *((__m512d*)b));}
void SIMD_MulInt_32_512(void* a, void* b, void* result){*((__m512i*)result) = _mm512_mul_epi32(*((__m512i*)a), *((__m512i*)b));}
void SIMD_DivFlt_32_512(void* a, void* b, void* result){*((__m512*)result) = _mm512_div_ps(*((__m512*)a), *((__m512*)b));}
void SIMD_DivFlt_64_512(void* a, void* b, void* result){*((__m512d*)result) = _mm512_div_pd(*((__m512d*)a), *((__m512d*)b));}


void SIMD_MulInt_64_512(void* a, void* b, void* result){
    // Load eight 64-bit integers from the arrays
    __m512i vec_a = _mm512_loadu_si512((__m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((__m512i*)b);

    // Multiply the 64-bit elements
    __m512i prod = _mm512_mullo_epi64(vec_a, vec_b);

    // Store the result
    _mm512_storeu_si512((__m512i*)result, prod);
}
void SIMD_MulInt_16_512(void* a, void* b, void* result){
    // Load thirty-two 16-bit integers
    __m512i vec_a = _mm512_loadu_si512((__m512i*)a);
    __m512i vec_b = _mm512_loadu_si512((__m512i*)b);

    // Multiply the 16-bit elements
    __m512i prod = _mm512_mullo_epi16(vec_a, vec_b);

    // Store the result
    _mm512_storeu_si512((__m512i*)result, prod);
}
void SIMD_MulInt_8_512(void* a, void* b, void* result){
    __m128i a_v1 = _mm512_castsi512_si128(vec_a);
    __m128i a_v2 = _mm512_extracti32x4_epi32(vec_a, 1);
    __m128i a_v3 = _mm512_extracti32x4_epi32(vec_a, 2);
    __m128i a_v4 = _mm512_extracti32x4_epi32(vec_a, 3);
    
    __m128i b_v1 = _mm512_castsi512_si128(vec_b);
    __m128i b_v2 = _mm512_extracti32x4_epi32(vec_b, 1);
    __m128i b_v3 = _mm512_extracti32x4_epi32(vec_b, 2);
    __m128i b_v4 = _mm512_extracti32x4_epi32(vec_b, 3);

    // Widen 8-bit integers to 16-bit integers
    __m512i w_a1 = _mm512_cvtepi8_epi16(a_v1);
    __m512i w_a2 = _mm512_cvtepi8_epi16(a_v2);
    __m512i w_a3 = _mm512_cvtepi8_epi16(a_v3);
    __m512i w_a4 = _mm512_cvtepi8_epi16(a_v4);
    
    __m512i w_b1 = _mm512_cvtepi8_epi16(b_v1);
    __m512i w_b2 = _mm512_cvtepi8_epi16(b_v2);
    __m512i w_b3 = _mm512_cvtepi8_epi16(b_v3);
    __m512i w_b4 = _mm512_cvtepi8_epi16(b_v4);

    // Multiply the 16-bit integers (products are 32 bits, but we store the low 16)
    __m512i p1 = _mm512_mullo_epi16(w_a1, w_b1);
    __m512i p2 = _mm512_mullo_epi16(w_a2, w_b2);
    __m512i p3 = _mm512_mullo_epi16(w_a3, w_b3);
    __m512i p4 = _mm512_mullo_epi16(w_a4, w_b4);

    // Pack the 16-bit results back down to 8-bit integers
    __m512i packed1 = _mm512_packs_epi16(p1, p2);
    __m512i packed2 = _mm512_packs_epi16(p3, p4);
    __m512i final_res = _mm512_packs_epi16(packed1, packed2);
}

//First   Convert packed 32-bit floats back to packed 32-bit integers
//Then    Perform floating-point division
//Finally Convert packed 32-bit integers to packed 32-bit floats
void SIMD_DivInt_64_512(void* a, void* b, void* result){
	*(__m512i*)result = _mm512_cvttpd_epi64(
		_mm512_div_pd(
		    _mm512_cvtepi64_pd(*(__m512i*)a), 
		    _mm512_cvtepi64_pd(*(__m512i*)b)
		)
	);
}
void SIMD_DivInt_32_512(void* a, void* b, void* result){
	*(__m512i*)result = _mm512_cvttps_epi32(
		_mm512_div_ps(
		    _mm512_cvtepi32_ps(*(__m512i*)a), 
		    _mm512_cvtepi32_ps(*(__m512i*)b)
		)
	);
}
void SIMD_DivInt_16_512(void* a, void* b, void* result){
	*(__m512i*)result = _mm512_cvttph_epi16(
		_mm512_div_ph(
		    _mm512_cvtepi16_ph(*(__m512i*)a), 
		    _mm512_cvtepi16_ph(*(__m512i*)b)
		)
	);
}
   	// 2. Extract four 128-bit vectors from each 512-bit vector
   	// 3. Widen 8-bit integers to 32-bit integers
   	// 4. Convert 32-bit integers to 32-bit floats
   	// 5. Perform the floating-point division
	// 6. Convert the float results back to 32-bit integers (with truncation)
   	// 7. Pack the 32-bit integers down to 16-bit integers
void SIMD_DivInt_8_512(void* a, void* b, void* result){

	__m512 
	    a_f1 = _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_castsi512_si128(*(__m512i*)a))),
	    a_f2 = _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(*(__m512i*)a, 1))),
	    a_f3 = _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(*(__m512i*)a, 2))),
	    a_f4 = _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(*(__m512i*)a, 3))),
	                                                                                                
	    b_f1 = _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_castsi512_si128(*(__m512i*)b))),
	    b_f2 = _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(*(__m512i*)b, 1))),
	    b_f3 = _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(*(__m512i*)b, 2))),
	    b_f4 = _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_extracti32x4_epi32(*(__m512i*)b, 3))),

	    res_1 = _mm512_div_ps(a_f1, b_f1),
	    res_2 = _mm512_div_ps(a_f2, b_f2),
	    res_3 = _mm512_div_ps(a_f3, b_f3),
	    res_4 = _mm512_div_ps(a_f4, b_f4)
	;


   	res_1 = _mm512_cvttps_epi32(res_1);
   	res_2 = _mm512_cvttps_epi32(res_2);
   	res_3 = _mm512_cvttps_epi32(res_3);
   	res_4 = _mm512_cvttps_epi32(res_4);

	*(__m512i*)result = _mm512_packs_epi16(
		_mm512_packs_epi32(res_1, res_2),
		_mm512_packs_epi32(res_3, res_4)
	);
}
#endif

#if defined(__AVX__)
void SIMD_AddFlt_32_256(void* a, void* b, void* result){*((__m256*)result) = _mm256_add_ps(*((__m256*)a), *((__m256*)b));}
void SIMD_AddFlt_64_256(void* a, void* b, void* result){*((__m256d*)result) = _mm256_add_pd(*((__m256d*)a), *((__m256d*)b));}
void SIMD_AddInt_64_256(void* a, void* b, void* result){*((__m256i*)result) = _mm256_add_epi64(*((__m256i*)a), *((__m256i*)b));}
void SIMD_AddInt_32_256(void* a, void* b, void* result){*((__m256i*)result) = _mm256_add_epi32(*((__m256i*)a), *((__m256i*)b));}
void SIMD_AddInt_16_256(void* a, void* b, void* result){*((__m256i*)result) = _mm256_add_epi16(*((__m256i*)a), *((__m256i*)b));}
void SIMD_AddInt_8_256(void* a, void* b, void* result){*((__m256i*)result) = _mm256_add_epi8(*((__m256i*)a), *((__m256i*)b));}

void SIMD_SubFlt_32_256(void* a, void* b, void* result){*((__m256*)result) = _mm256_sub_ps(*((__m256*)a), *((__m256*)b));}
void SIMD_SubFlt_64_256(void* a, void* b, void* result){*((__m256d*)result) = _mm256_sub_pd(*((__m256d*)a), *((__m256d*)b));}
void SIMD_SubInt_64_256(void* a, void* b, void* result){*((__m256i*)result) = _mm256_sub_epi64(*((__m256i*)a), *((__m256i*)b));}
void SIMD_SubInt_32_256(void* a, void* b, void* result){*((__m256i*)result) = _mm256_sub_epi32(*((__m256i*)a), *((__m256i*)b));}
void SIMD_SubInt_16_256(void* a, void* b, void* result){*((__m256i*)result) = _mm256_sub_epi16(*((__m256i*)a), *((__m256i*)b));}
void SIMD_SubInt_8_256(void* a, void* b, void* result){*((__m256i*)result) = _mm256_sub_epi8(*((__m256i*)a), *((__m256i*)b));}

void SIMD_MulFlt_32_256(void* a, void* b, void* result){*((__m256*)result) = _mm256_mul_ps(*((__m256*)a), *((__m256*)b));}
void SIMD_MulFlt_64_256(void* a, void* b, void* result){*((__m256d*)result) = _mm256_mul_pd(*((__m256d*)a), *((__m256d*)b));}
void SIMD_MulInt_32_256(void* a, void* b, void* result){*((__m256i*)result) = _mm256_mul_epi32(*((__m256i*)a), *((__m256i*)b));}
void SIMD_DivFlt_32_256(void* a, void* b, void* result){*((__m256*)result) = _mm256_div_ps(*((__m256*)a), *((__m256*)b));}
void SIMD_DivFlt_64_256(void* a, void* b, void* result){*((__m256d*)result) = _mm256_div_pd(*((__m256d*)a), *((__m256d*)b));}


void SIMD_MulInt_64_256(void* a, void* b, void* result){
	*((__m256i*)result) = _mm256_mul_epi64(*((__m256i*)a), *((__m256i*)b));
}
void SIMD_MulInt_16_256(void* a, void* b, void* result){
	*((__m256i*)result) = _mm256_mul_epi16(*((__m256i*)a), *((__m256i*)b));
}
void SIMD_MulInt_8_256(void* a, void* b, void* result){
	*((__m256i*)result) = _mm256_mul_epi8(*((__m256i*)a), *((__m256i*)b));
}
void SIMD_DivInt_64_256(void* a, void* b, void* result){
	*((__m256i*)result) = _mm256_div_epi64(*((__m256i*)a), *((__m256i*)b));
}
void SIMD_DivInt_32_256(void* a, void* b, void* result){
	*((__m256i*)result) = _mm256_div_epi32(*((__m256i*)a), *((__m256i*)b));
}
void SIMD_DivInt_16_256(void* a, void* b, void* result){
	*((__m256i*)result) = _mm256_div_epi16(*((__m256i*)a), *((__m256i*)b));
}
void SIMD_DivInt_8_256(void* a, void* b, void* result){
	*((__m256i*)result) = _mm256_div_epi8(*((__m256i*)a), *((__m256i*)b));
}

#endif

#if defined(__SSE__)
void SIMD_AddFlt_32_128(void* a, void* b, void* result){*((__m128*)result) = _mm_add_ps(*((__m128*)a), *((__m128*)b));}
void SIMD_AddFlt_64_128(void* a, void* b, void* result){*((__m128d*)result) = _mm_add_pd(*((__m128d*)a), *((__m128d*)b));}
void SIMD_AddInt_64_128(void* a, void* b, void* result){*((__m128i*)result) = _mm_add_epi64(*((__m128i*)a), *((__m128i*)b));}
void SIMD_AddInt_32_128(void* a, void* b, void* result){*((__m128i*)result) = _mm_add_epi32(*((__m128i*)a), *((__m128i*)b));}
void SIMD_AddInt_16_128(void* a, void* b, void* result){*((__m128i*)result) = _mm_add_epi16(*((__m128i*)a), *((__m128i*)b));}
void SIMD_AddInt_8_128(void* a, void* b, void* result){*((__m128i*)result) = _mm_add_epi8(*((__m128i*)a), *((__m128i*)b));}

void SIMD_SubFlt_32_128(void* a, void* b, void* result){*((__m128*)result) = _mm_sub_ps(*((__m128*)a), *((__m128*)b));}
void SIMD_SubFlt_64_128(void* a, void* b, void* result){*((__m128d*)result) = _mm_sub_pd(*((__m128d*)a), *((__m128d*)b));}
void SIMD_SubInt_64_128(void* a, void* b, void* result){*((__m128i*)result) = _mm_sub_epi64(*((__m128i*)a), *((__m128i*)b));}
void SIMD_SubInt_32_128(void* a, void* b, void* result){*((__m128i*)result) = _mm_sub_epi32(*((__m128i*)a), *((__m128i*)b));}
void SIMD_SubInt_16_128(void* a, void* b, void* result){*((__m128i*)result) = _mm_sub_epi16(*((__m128i*)a), *((__m128i*)b));}
void SIMD_SubInt_8_128(void* a, void* b, void* result){*((__m128i*)result) = _mm_sub_epi8(*((__m128i*)a), *((__m128i*)b));}

void SIMD_MulFlt_32_128(void* a, void* b, void* result){*((__m128*)result) = _mm_mul_ps(*((__m128*)a), *((__m128*)b));}
void SIMD_MulFlt_64_128(void* a, void* b, void* result){*((__m128d*)result) = _mm_mul_pd(*((__m128d*)a), *((__m128d*)b));}
void SIMD_MulInt_32_128(void* a, void* b, void* result){*((__m128i*)result) = _mm_mul_epi32(*((__m128i*)a), *((__m128i*)b));}
void SIMD_DivFlt_32_128(void* a, void* b, void* result){*((__m128*)result) = _mm_div_ps(*((__m128*)a), *((__m128*)b));}
void SIMD_DivFlt_64_128(void* a, void* b, void* result){*((__m128d*)result) = _mm_div_pd(*((__m128d*)a), *((__m128d*)b));}



void SIMD_MulInt_64_128(void* a, void* b, void* result){
	*((__m128i*)result) = _mm_mul_epi64(*((__m128i*)a), *((__m128i*)b));
}
void SIMD_MulInt_16_128(void* a, void* b, void* result){
	*((__m128i*)result) = _mm_mul_epi16(*((__m128i*)a), *((__m128i*)b));
}
void SIMD_MulInt_8_128(void* a, void* b, void* result){
	*((__m128i*)result) = _mm_mul_epi8(*((__m128i*)a), *((__m128i*)b));
}

void SIMD_DivInt_64_128(void* a, void* b, void* result){
	*((__m128i*)result) = _mm_div_epi64(*((__m128i*)a), *((__m128i*)b));
}
void SIMD_DivInt_32_128(void* a, void* b, void* result){
	*((__m128i*)result) = _mm_div_epi32(*((__m128i*)a), *((__m128i*)b));
}
void SIMD_DivInt_16_128(void* a, void* b, void* result){
	*((__m128i*)result) = _mm_div_epi16(*((__m128i*)a), *((__m128i*)b));
}
void SIMD_DivInt_8_128(void* a, void* b, void* result){
	*((__m128i*)result) = _mm_div_epi8(*((__m128i*)a), *((__m128i*)b));
}
#endif

