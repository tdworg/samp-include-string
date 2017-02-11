/* ========================================================================== *\
	Hash functions

| Description:

| License:
	Copyright (c) 2016-2017 Double V

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgement in the product documentation would be
		appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.

| Metadata:
	[Functions]:
		Stock:
			- fnv1_str
			- MurmurHash2
		Static:
			-
		Public:
			-
		Hooks:
			-
	[Callbacks]:
		-
	[Definitions]:
		-
	[Enumerations]:
		-
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			-
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_strhash
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_strhash
#endif

#if defined _TDW_STR_HASH
	#endinput
#endif

#define _TDW_STR_HASH

#include "tdw_string"

// -----------------------------------------------------------------------------
// FNV-1

stock fnv1_str(const string[], hash_val)
{
	new
		len = strlen(string);

	while (len-- != 0) {
		hash_val += (hash_val << 1) + (hash_val << 4) + (hash_val << 7) +
			(hash_val << 8) + (hash_val << 24);

		hash_val ^= string[len];
	}

	return hash_val;
}

// -----------------------------------------------------------------------------
// MurmurHash2

stock MurmurHash2(key[], len)
{
	const
		m = 0x5bd1e995,
		seed = 0,
		r = 24;

	new
		h = seed ^ len,
		k;

	while (len >= 4) {
		k  = key[0];
		k |= key[1] << 8;
		k |= key[2] << 16;
		k |= key[3] << 24;

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		// key += key (not value in the first cell)
		#emit load.s.pri key
		#emit add.c 4
		#emit stor.s.pri key

		len -= 4;
	}

	switch (len) {
		case 3:
			h ^= key[2] << 16;
		case 2:
			h ^= key[1] << 8;
		case 1:
			h ^= key[0],
			h *= m;
	}

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}
