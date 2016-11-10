//
// Copyright (c) 2016, RISUWWV (https://github.com/risuwwv). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

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
		
	auto p = timeFunction(testSqrt10, smallestNormalizedBits, infinityBits);
	cout << "warm-up : " << p.first << '\n' << endl; 
	
	float sum = 0.0;

	for(auto elem : functions)
	{
		p = timeFunction(elem.fun, smallestNormalizedBits, infinityBits);
		cout << elem.name << " took : " << p.second << " seconds" << endl;

		sum += p.first;
	}	
	
	cout << "sum : " << p.first << endl;//side effect to make sure the the loop is not dead code inside timeFunction	
	
	return 0;
}
