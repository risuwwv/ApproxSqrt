//
// Copyright (c) 2016, RISUWWV (https://github.com/risuwwv). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

#include "approxSqrt.h"

using namespace risuwwv;

#include "bit_cast.h"

using std::vector;
using std::string;

using std::cout;
using std::endl;

//This is the performance test: it computes the sum of the square roots of all the normalized floats
int main()
{
	struct Elem
	{
		float(*fun)(float);
		string name;
	};

	vector<Elem> functions = {
		{testSqrt10,  "warm-up   "},
		{ sqrtf,      "sqrtf     "},
		{ testSqrt1,  "testSqrt1 "},
		{ testSqrt2,  "testSqrt2 "},
		{ testSqrt3,  "testSqrt3 "},
		{ testSqrt4,  "testSqrt4 "},
		{ testSqrt5,  "testSqrt5 "},
		{ testSqrt6,  "testSqrt6 "},
		{ testSqrt7,  "testSqrt7 "},
		{ testSqrt8,  "testSqrt8 "},
		{ testSqrt9,  "testSqrt9 "},
		{ testSqrt10, "testSqrt10"}
	};	
		
	const uint32_t smallestNormalizedBits = 8388608;
	const uint32_t infinityBits = 2139095040;
		
	float sum = 0.0;

	for(auto elem : functions)
	{
		auto p = timeFunction(elem.fun, smallestNormalizedBits, infinityBits);
		cout << elem.name << " took : " << p.second << " seconds" << endl;

		sum += p.first;
	}	
	
	cout << "sum : " << sum << endl;//side effect to make sure the the loop is not dead code inside timeFunction	
	
#ifdef __AVX2__
	struct Elem2
	{
		__m256(*fun)(__m256);
		string name;
	};

	vector<Elem2> functions2 = {
		{testSqrt10,      "warm-up       "},
		{ _mm256_sqrt_ps, "_mm256_sqrt_ps"},
		{ testSqrt6,      "testSqrt6     "},
		{ testSqrt7,      "testSqrt7     "},
		{ testSqrt8,      "testSqrt8     "},
		{ testSqrt9,      "testSqrt9     "},
		{ testSqrt10,     "testSqrt10    "}
	};	
	
	__m256 sum2 = _mm256_set1_ps(0.0f); 
	for(auto elem : functions2)
	{
		auto p = timeFunction(elem.fun, smallestNormalizedBits, infinityBits);
		cout << elem.name << " took : " << p.second << " seconds" << endl;

		sum2 = _mm256_add_ps(sum2, p.first);
	}

	float var[8];
	_mm256_storeu_ps(var, sum2);
	
	sum = 0;
	for(int i=0; i<8; ++i)
	{
		sum += var[i];
	}
	cout << "sum : " << sum << endl;
	
#endif//__AVX2__	
	
	return 0;
}
