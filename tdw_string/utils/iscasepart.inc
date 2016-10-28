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
#if defined _inc_iscasepart
	#undef _inc_iscasepart
#endif

#if defined _TDW_STLIB__ISCASEPART
	#endinput
#endif

#define _TDW_STLIB__ISCASEPART


stock
	islowerpart(const string[], start_part_pos, end_part_pos)
{
	new size = strlen(string);
	if (_:(start_part_pos < end_part_pos < size) == 0)
		return 0;
	new c;
	if (IsPackedString(string))
	{
		do
		{
			if ('a' <= (c = string{start_part_pos}) <= 'z')
				continue;
			else if (0xE0 <= c <= 0xFF)
				continue;
			else if (c == ' ')
				continue;
			return 0;
		}
		while(++start_part_pos < end_part_pos);
	}
	else
	{
		do
		{
			if ('a' <= (c = string[start_part_pos]) <= 'z')
				continue;
			else if (0xE0 <= c <= 0xFF)
				continue;
			else if (c == ' ')
				continue;
			return 0;
		}
		while(++start_part_pos < end_part_pos);
	}
	return 1;
}


stock
	isupperpart(const string[], start_part_pos, end_part_pos)
{
	new size = strlen(string);
	if (_:(start_part_pos < end_part_pos < size) == 0)
		return 0;
	new c;
	if (IsPackedString(string))
	{
		do
		{
			if ('A' <= (c = string{start_part_pos}) <= 'Z')
				continue;
			else if (0xC0 <= c <= 0xDF)
				continue;
			else if (c == ' ')
				continue;
			return 0;
		}
		while(++start_part_pos < end_part_pos);
	}
	else
	{
		do
		{
			if ('A' <= (c = string[start_part_pos]) <= 'Z')
				continue;
			else if (0xC0 <= c <= 0xDF)
				continue;
			else if (c == ' ')
				continue;
			return 0;
		}
		while(++start_part_pos < end_part_pos);
	}
	return 1;
}
