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
#if defined _inc_topartcase
	#undef _inc_topartcase
#endif

#if defined _TDW_STLIB__TOPARTCASE
	#endinput
#endif

#define _TDW_STLIB__TOPARTCASE


stock
	strparttoupper(string[], part_start, part_end, string_size = sizeof string)
{
	if (part_start < 0)
		return 0;
	if (part_end > string_size)
		return 0;
	const dist = 'A' - 'a';
	new c;
	if (IsPackedString(string))
	{
		do
		{
			if (0xE0 <= (c = string{part_start}) <= 0xFF)
				c += dist;
			else if ('a' <= c <= 'z')
				c += dist;
			else if (c == 0xB8)
				c = 0xA8;
			string{part_start} = c;
		}
		while (++part_start != part_end);
	}
	else
	{
		do
		{
			if (0xE0 <= (c = string[part_start]) <= 0xFF)
				c += dist;
			else if ('a' <= c <= 'z')
				c += dist;
			else if (c == 0xB8)
				c = 0xA8;
			string[part_start] = c;
		}
		while (++part_start != part_end);
	}
	return 1;
}


stock
	strparttolower(string[], part_start, part_end, string_size = sizeof string)
{
	if (part_start < 0)
		return 0;
	if (part_end > string_size)
		return 0;
	const dist = 'A' - 'a';
	new c;
	if (IsPackedString(string))
	{
		do
		{
			if (0xC0 <= (c = string{part_start}) <= 0xDF)
				c -= dist;
			else if ('A' <= c <= 'Z')
				c -= dist;
			else if (c == 0xA8)
				c = 0xB8;
			string{part_start} = c;
		}
		while (++part_start != part_end);
	}
	else
	{
		do
		{
			if (0xC0 <= (c = string[part_start]) <= 0xDF)
				c -= dist;
			else if ('A' <= c <= 'Z')
				c -= dist;
			else if (c == 0xA8)
				c = 0xB8;
			string[part_start] = c;
		}
		while (++part_start != part_end);
	}
	return 1;
}
