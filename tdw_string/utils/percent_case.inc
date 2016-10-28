/** ======================================================================== **\
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
#if defined _inc_percent_case
	#undef _inc_percent_case
#endif

#if defined _TDW_STLIB__PERCENT_CASE
	#endinput
#endif

#define _TDW_STLIB__PERCENT_CASE


stock
	countofuppercase(const string[])
{
	new string_len = strlen(string);
	return floatround(
		floatmul(
			floatdiv(
				float(countof@loop(string, 'A', 'Z', string_len)),
				float(string_len)
			), 100.0)
	);
}


stock
	countoflowpercase(const string[])
{
	new string_len = strlen(string);
	return floatround(
		floatmul(
			floatdiv(
				float(countof@loop(string, 'a', 'z', string_len)),
				float(string_len)
			), 100.0)
	);
}


static stock
	countof@loop(const string[], start_sym, end_sym, string_len)
{
	assert(end_sym > start_sym);
	new index, count;
	if (IsPackedString(string))
	{
		while(index < string_len)
		{
			if (start_sym <= string{index++} <= end_sym)
				++count;
		}
	}
	else
	{
		while(index < string_len)
		{
			if (start_sym <= string[index++] <= end_sym)
				++count;
		}
	}
	return count;
}
