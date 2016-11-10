//
// Copyright (c) 2016, RISUWWV (https://github.com/risuwwv). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

#include "approxSqrt.h"
#include "bit_cast.h"

using namespace risuwwv;

#include <vector>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

//tests that all the algorithms verify the maximal error on the specified ranges
//and that the next values out of the ranges break the maximal error constraint
int main()
{
	struct Elem
	{
		float(*fun)(float);
		string name;
		uint32_t mini;
		uint32_t maxi;
		float error;
	};

	//testcases for v1-v10
	vector<Elem> tests = {
		{ testSqrt1, "testSqrt1",5999996, 2139095040, 0.206136f },
		{ testSqrt2, "testSqrt2",6300003, 2139095040, 0.00623746f },
		{ testSqrt3, "testSqrt3",6497369, 2139095040, 6e-06f },
		{ testSqrt4, "testSqrt4",3962353, 2139095040, 2.63158e-07f },
		{ testSqrt5, "testSqrt5",1238799, 2139095040, 2.68155e-07f },
		{ testSqrt6, "testSqrt6", 6872893, 2139095040, 0.0695972f },
		{ testSqrt7, "testSqrt7", 6813933, 2139095040, 0.00130169f },
		{ testSqrt8, "testSqrt8", 6778363, 2139095040, 5.95071e-07f },
		{ testSqrt9, "testSqrt9", 4023293, 2139095040, 1.78727e-07f },
		{ testSqrt10, "testSqrt10", 2100551, 2139095040, 1.78727e-07f }
	};

	//special constraint on this one: overestimating
	for (uint32_t i = tests[0].mini; i != tests[0].maxi; ++i)
	{
		float val = bit_cast<float>(i);

		if (sqrtf(val) > tests[0].fun(val))
		{
			cerr << "error: " << tests[0].name << " did not overestimate compared with sqrtf" << endl;
			break;
		}
	}
	
	for (const auto& elem : tests)
	{
		//higher error out of the range
		float val = bit_cast<float>(elem.mini - 1);

		double res = elem.fun(val);

		double diff = fabs(val - res*res) / fabs(val);

		if (diff <= elem.error)
		{
			cerr << "error: " << elem.name << " has valid range bigger than expected" << endl;
		}

		for (uint32_t i = elem.mini; i != elem.maxi; ++i)
		{
			val = bit_cast<float>(i);

			res = elem.fun(val);

			diff = fabs(val - res*res) / fabs(val);

			if (diff > elem.error)
			{
				cerr << "error: " << elem.name << " has error superior than expected" << endl;
				break;
			}
		}

		//higher error out of the range
		val = bit_cast<float>(elem.maxi);

		res = elem.fun(val);

		diff = fabs(val - res*res) / fabs(val);

		if (diff <= elem.error)
		{
			cerr << "error: testSqrt10 has valid range bigger than expected" << endl;
		}
		
		cout << "Done: " << elem.name << endl;
	}

	return 0;
}
