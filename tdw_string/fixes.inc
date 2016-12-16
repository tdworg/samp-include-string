/** ======================================================================== **\
	Fixes

| License:
Copyright (c) 2016 Double V

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
\** ======================================================================== **/


// I remove this constant because the compiler automatically generates it.
// github.com/Zeex/pawn/issues/107
#if defined _inc_fixes
	#undef _inc_fixes
#endif

#if defined _TDW_STLIB__FIXES
	#endinput
#endif

#define _TDW_STLIB__FIXES


// Fix the return value.
// Example:
//    strcmp: "" == "1"   =>   returns 0. What?
stock
	TDWSH@strcmp(const string1[], const string2[], bool:ignorecase=false,
		length = cellmax)
{
	static
		is_empty@s1,
		is_empty@s2;
	is_empty@s1 = IsEmptyString(string1);
	is_empty@s2 = IsEmptyString(string2);
	if (is_empty@s1 != 0) {
		return (is_empty@s2 != 0)
			? strcmp(string1, string2, ignorecase, length)
			: 1;
	} else {
		return (is_empty@s2 != 0)
			? -1
			: 0;
	}
}

#if defined _ALS_strcmp
	#undef strcmp
#else
	#define _ALS_strcmp
#endif

#define strcmp TDWSH@strcmp
