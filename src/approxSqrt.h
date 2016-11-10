//
// Copyright (c) 2016, RISUWWV (https://github.com/risuwwv). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef APPROX_SQRT_H
#define APPROX_SQRT_H

#include <cstdint>
#include <utility>

#ifdef __AVX2__
#include <immintrin.h>
#endif

namespace risuwwv
{
#ifdef __AVX2__
	__m256 testSqrt6(__m256 x) noexcept;
	__m256 testSqrt7(__m256 x) noexcept;
	__m256 testSqrt8(__m256 x) noexcept;
	__m256 testSqrt9(__m256 x) noexcept;
	__m256 testSqrt10(__m256 x) noexcept;
#endif//__AVX2__

	//all intervals below are bigger than normalized
	float testSqrt1(float x) noexcept;//does behave correctly in [bit_cast<float>(5999996), bit_cast<float>(2139095040)[ : max_diff is 0.206136f
	float testSqrt2(float x) noexcept;//does behave correctly in [bit_cast<float>(6300003), bit_cast<float>(2139095040)[ : max_diff is 0.00623746f 
	float testSqrt3(float x) noexcept;//does behave correctly in [bit_cast<float>(6497369), bit_cast<float>(2139095040)[ : max_diff is 6e-06f
	float testSqrt4(float x) noexcept;//does behave correctly in [bit_cast<float>(3962353), bit_cast<float>(2139095040)[ : max_diff is 2.63158e-07f
	float testSqrt5(float x) noexcept;//does behave correctly in [bit_cast<float>(1238799), bit_cast<float>(2139095040)[ : max_diff is 2.68155e-07f

	float testSqrt6(float x) noexcept; //does behave correctly in [bit_cast<float>(6872893), bit_cast<float>(2139095040)[ : max_diff is 0.0695972f
	float testSqrt7(float x) noexcept; //does behave correctly in [bit_cast<float>(6813933), bit_cast<float>(2139095040)[ : max_diff is 0.00130169f 
	float testSqrt8(float x) noexcept; //does behave correctly in [bit_cast<float>(6778363), bit_cast<float>(2139095040)[ : max_diff is 5.95071e-07f
	float testSqrt9(float x) noexcept; //does behave correctly in [bit_cast<float>(4023293), bit_cast<float>(2139095040)[ : max_diff is 1.78727e-07f
	float testSqrt10(float x) noexcept;//does behave correctly in [bit_cast<float>(2100551), bit_cast<float>(2139095040)[ : max_diff is 1.78727e-07f

	//assuming we search the square root of x
	//and bits is the binary form of an approximate of sqrt(x)
	//this function returns the best approximation in [bits-1, bits+1]
	float localSearch(float x, uint32_t bits) noexcept;
	
	//times the function on [bit_cast<float>(lowerBound), bit_cast<float>(upperBound)[ 
	//and returns the cumulative sum to ensure that the loop is not optimized away
	std::pair<float, float> timeFunction(float(*fun)(float), uint32_t lowerBound, uint32_t upperBound);

#ifdef __AVX2__
	std::pair<__m256, float> timeFunction(__m256(*fun)(__m256), uint32_t lowerBound, uint32_t upperBound);
#endif//__AVX2__
	
}//namespace risuwwv

#endif//APPROX_SQRT_H
