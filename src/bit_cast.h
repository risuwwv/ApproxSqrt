//
// Copyright (c) 2016, RISUWWV (https://github.com/risuwwv). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef BIT_CAST_H
#define BIT_CAST_H

#include <cstring>

namespace risuwwv
{
	//Used to provide safe access to bits of floats (using reinterpret_cast or unions is undefined behaviour...)
	//More generally, can be used to get value of type DstType with same bits as a src of type SrcType

	template<typename DstType, typename SrcType>
	DstType bit_cast(SrcType src)
	{
		static_assert(sizeof(DstType) == sizeof(SrcType), "sizeof(DstType) != sizeof(SrcType)");

		DstType dst;
		memcpy(&dst, &src, sizeof(SrcType));
		return dst;
	}

}//namespace risuwwv

#endif//BIT_CAST_H
