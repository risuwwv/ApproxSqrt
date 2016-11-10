//
// Copyright (c) 2016, RISUWWV (https://github.com/risuwwv). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef SIMD_HELPERS_H
#define SIMD_HELPERS_H

#ifdef __AVX2__
inline __m256 _mm256_abs_ps(__m256 a)//TODO move this
{
	const __m256i mask = _mm256_set1_epi32((1u << 31) - 1u);
	return _mm256_castsi256_ps(_mm256_and_si256(_mm256_castps_si256(a), mask));//bit_cast<__m256>(bit_cast<__m256i>(a) & 0b01...1)
}
#endif//__AVX2__

#endif//SIMD_HELPERS_H
