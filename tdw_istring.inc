/*
 * TDW Improved Strings
 *
 * Copyright (c) 2017 Double V
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#if defined _TDW_ISTRING_INC_
	#endinput
#endif
#define _TDW_ISTRING_INC_

#if !defined TDW_STRING_BYTES_PER_CELL
	#define TDW_STRING_BYTES_PER_CELL (cellbits / charbits)
#endif

#define TDW_STRING_T {Str_, StrB}

#define String:%0(%1) Str_:%0=Str_:istring_ref(%1)
#define Str_:%0=Str_:istring_ref(%1,%2) TDWS@%0[(%2) + 1] = " " %1,\
	StrB:%0=StrB:(istring_ref(((TDWS@%0[0]=(%2)),TDWS@%0)) +\
		TDW_STRING_BYTES_PER_CELL)

// Returns an address of a passed argument.
stock istring_ref(...)
{
	#emit load.s.pri 12
	#emit retn

	return 0;
}

// Returns the capacity of a string.
stock istring_get_capacity(TDW_STRING_T:str, tag = tagof str)
{
	// Different algorithms to obtain the capacity of the string.
	switch (tag) {
		case (tagof(StrB:)): {
			// Reads the previous cell.
			#emit load.s.pri str
			#emit add.c 0xfffffffc  // -4
			#emit load.i
			#emit retn
		}
		case (tagof(Str_:)): {
			return istring_get_size(str);
		}
	}

	return 0;
}

// Returns the current size of a string.
stock istring_get_size(TDW_STRING_T:str)
{
	#emit push.s str
	#emit push.c 4

	#emit sysreq.c strlen

	#emit stack 8
	#emit retn

	return 0;
}

// ----------------------------------------------------------------------------
// Overloaded operators

stock bool:operator==(Str_:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit eq
	#emit retn

	return bool:0;
}
stock bool:operator==(Str_:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit eq
	#emit retn

	return bool:0;
}
stock bool:operator==(StrB:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit eq
	#emit retn

	return bool:0;
}
stock bool:operator==(StrB:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit eq
	#emit retn

	return bool:0;
}
stock bool:operator!=(Str_:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit neq
	#emit retn

	return bool:0;
}
stock bool:operator!=(Str_:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit neq
	#emit retn

	return bool:0;
}
stock bool:operator!=(StrB:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit neq
	#emit retn

	return bool:0;
}
stock bool:operator!=(StrB:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit neq
	#emit retn

	return bool:0;
}
stock bool:operator>(Str_:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit grtr
	#emit retn

	return bool:0;
}
stock bool:operator>(Str_:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit grtr
	#emit retn

	return bool:0;
}
stock bool:operator>(StrB:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit grtr
	#emit retn

	return bool:0;
}
stock bool:operator>(StrB:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit grtr
	#emit retn

	return bool:0;
}
stock bool:operator<(Str_:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit less
	#emit retn

	return bool:0;
}
stock bool:operator<(Str_:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit less
	#emit retn

	return bool:0;
}
stock bool:operator<(StrB:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit less
	#emit retn

	return bool:0;
}
stock bool:operator<(StrB:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit less
	#emit retn

	return bool:0;
}
stock bool:operator>=(Str_:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit geq
	#emit retn

	return bool:0;
}
stock bool:operator>=(Str_:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit geq
	#emit retn

	return bool:0;
}
stock bool:operator>=(StrB:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit geq
	#emit retn

	return bool:0;
}
stock bool:operator>=(StrB:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit geq
	#emit retn

	return bool:0;
}
stock bool:operator<=(Str_:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit leq
	#emit retn

	return bool:0;
}
stock bool:operator<=(Str_:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit leq
	#emit retn

	return bool:0;
}
stock bool:operator<=(StrB:str1, Str_:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit leq
	#emit retn

	return bool:0;
}
stock bool:operator<=(StrB:str1, StrB:str2)
{
	#emit push.c cellmax
	#emit push.c 0
	#emit push.s str2
	#emit push.s str1
	#emit push.c 16

	#emit sysreq.c strcmp

	#emit stack 20
	#emit zero.alt
	#emit leq
	#emit retn

	return bool:0;
}
