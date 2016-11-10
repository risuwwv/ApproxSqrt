//
// Copyright (c) 2016, RISUWWV (https://github.com/risuwwv). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include <cmath>
#include <chrono>

#include "approxSqrt.h"
#include "bit_cast.h"

#ifdef __AVX2__
#include "immintrin.h"//TODO add AVX2 checks
#endif//__AVX2__

using std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

namespace risuwwv
{
	//always overestimates
	float testSqrt1(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + (1 << 29) - (1 << 22);

		res = bit_cast<float>(bits);

		return res;
	}

	float testSqrt2(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + (1 << 29) - (1 << 22);

		res = bit_cast<float>(bits);
		res = (res + x / res) * 0.5f;

		return res;
	}

	float testSqrt3(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + (1 << 29) - (1 << 22);

		res = bit_cast<float>(bits);
		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;

		return res;
	}

	float testSqrt4(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + (1 << 29) - (1 << 22);

		res = bit_cast<float>(bits);
		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;

		return res;
	}

	float testSqrt5(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + (1 << 29) - (1 << 22);

		res = bit_cast<float>(bits);
		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;

		return res;
	}

	float testSqrt6(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + 532362861;

		res = bit_cast<float>(bits);

		return res;
	}

#ifdef __AVX2__
	__m256 testSqrt6(__m256 x) noexcept
	{
		__m256i bits = _mm256_add_epi32(_mm256_srli_epi32(_mm256_castps_si256(x), 1), _mm256_set1_epi32(532362861));//(bit_cast<uint32_t>(x) >> 1) + 532362861
		__m256 res = _mm256_castsi256_ps(bits);

		return res;
	}

	__m256 testSqrt7(__m256 x) noexcept 
	{
		__m256i bits = _mm256_add_epi32(_mm256_srli_epi32(_mm256_castps_si256(x), 1), _mm256_set1_epi32(532362861));//(bit_cast<uint32_t>(x) >> 1) + 532362861
		__m256 res = _mm256_castsi256_ps(bits);
		
		const __m256 half = _mm256_set1_ps(0.5f);

		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f
		return res;
	}

	__m256 testSqrt8(__m256 x) noexcept 
	{
		__m256i bits = _mm256_add_epi32(_mm256_srli_epi32(_mm256_castps_si256(x), 1), _mm256_set1_epi32(532362861));//(bit_cast<uint32_t>(x) >> 1) + 532362861
		__m256 res = _mm256_castsi256_ps(bits);

		const __m256 half = _mm256_set1_ps(0.5f);

		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f
		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f

		return res;
	}

	__m256 testSqrt9(__m256 x) noexcept 
	{
		__m256i bits = _mm256_add_epi32(_mm256_srli_epi32(_mm256_castps_si256(x), 1), _mm256_set1_epi32(532362861));//(bit_cast<uint32_t>(x) >> 1) + 532362861
		__m256 res = _mm256_castsi256_ps(bits);

		const __m256 half = _mm256_set1_ps(0.5f);

		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f
		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f
		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f

		return res;
	}

	__m256 testSqrt10(__m256 x) noexcept 
	{
		__m256i bits = _mm256_add_epi32(_mm256_srli_epi32(_mm256_castps_si256(x), 1), _mm256_set1_epi32(532362861));//(bit_cast<uint32_t>(x) >> 1) + 532362861
		__m256 res = _mm256_castsi256_ps(bits);

		const __m256 half = _mm256_set1_ps(0.5f);

		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f
		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f
		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f
		res = _mm256_mul_ps(_mm256_add_ps(res, _mm256_div_ps(x, res)), half);//res = (res + x / res) * 0.5f

		return res;
	}

#endif//__AVX2__

	float testSqrt7(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + 532362861;

		res = bit_cast<float>(bits);

		res = (res + x / res) * 0.5f;

		return res;
	}

	float testSqrt8(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + 532362861;

		res = bit_cast<float>(bits);

		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;

		return res;
	}

	float testSqrt9(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + 532362861;

		res = bit_cast<float>(bits);

		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;

		return res;
	}

	float testSqrt10(float x) noexcept
	{
		float res = 0.0f;

		uint32_t bits = (bit_cast<uint32_t>(x) >> 1) + 532362861;

		res = bit_cast<float>(bits);

		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;
		res = (res + x / res) * 0.5f;

		return res;
	}

	float localSearch(float x, uint32_t bits) noexcept
	{
		float res = bit_cast<float>(bits);

		double tmp = static_cast<double>(res);
		double diff = x - tmp*tmp;//if x - res*res == 0 as float, the direction to search is unclear

		if (diff < 0)
		{
			--bits;
		}
		else
		{
			++bits;
		}

		float res2 = bit_cast<float>(bits);

		double tmp2 = static_cast<double>(res2);
		double diff2 = x - tmp2*tmp2;

		if (fabs(diff2) < fabs(diff))
		{
			res = res2;
		}

		return res;
	}
	
	std::pair<int, float> timeFunction(float(*fun)(float), uint32_t lowerBound, uint32_t upperBound)
	{
		//xoring bits is bad because compiler is too smart for testSqrt1 and testSqrt6, so I did a sum
		float sum = 0;
		
		steady_clock::time_point begin = steady_clock::now();

		for (uint32_t i = lowerBound; i < upperBound; ++i)
		{
			float val = bit_cast<float>(i);
			float res = fun(val);
			sum += res;
		}

		steady_clock::time_point end = steady_clock::now();
		return std::make_pair(sum, duration_cast<microseconds>(end - begin).count()/1000000.0f);
	}
	
}//namespace risuwwv
