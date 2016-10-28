/** ======================================================================== **\
	String

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
#if defined _inc_string
	#undef _inc_string
#endif

#if defined _TDW_STLIB__STRING
	#endinput
#endif

#define _TDW_STLIB__STRING


// Checks if a string is packed.
// Other information: //www.compuphase.com/pawn/String_Manipulation.pdf
// Author: Untonyst.
#if !defined IsPackedString
	#define IsPackedString(%0) ((%0){0} != 0)
#endif


#include <tdw_string/utils/iscasepart>
#include <tdw_string/utils/percent_case>
#include <tdw_string/utils/topartcase>



stock
	strcpy(dest[], const string[], dest_size = sizeof dest)
{
	return
		(IsPackedString(dest) ? (dest{0} = '\0') : (dest[0] = '\0')),
		strcat(dest, string, dest_size);
}


stock
	IsEmptyString(const string[])
{
	return (IsPackedString(string) ? (string{0}) : (string[0])) == '\0';
}


stock
	memcmp(const string1[], const string2[], n = cellmax,
		size_1 = sizeof string1, size_2 = sizeof string2)
{
	if (IsEmptyString(string1))
		return -1;
	if (IsEmptyString(string2))
		return -1;
	if (n == cellmax)
		n = size_1 > size_2 ? size_1 : size_2;
	// Converts the value to bytes.
	#emit load.s.pri n // pri = n
	#emit shl.c.pri 2 // pri <<= 2
	#emit stor.s.pri n // n = pri
	// Addresses..
	#emit load.s.pri string1 // pri = string1
	#emit load.s.alt string2 // alt = string2
	// Compare the memory blocks
	#emit cmps n
	// Returns zero if the blocks are equal.
	#emit retn
	return 0;
}


stock
	strcount(const string[], const find[], bool:ignorecase = false, pos = 0,
		string_size = sizeof string)
{
	if (pos >= string_size)
		return 0;
	new found_pos = pos, count, find_size = strlen(find);
	while ((found_pos = strfind(string, find, ignorecase,
		found_pos)) != -1
	)
	{
		count++;
		found_pos += find_size;
	}
	return count;
}


stock
	strreverse(string[])
{
	new i, len = strlen(string), j = len - 1, chr;
	if (IsPackedString(string))
	{
		do
		{
			chr = string{i};
			string{i++} = string{j};
			string{j--} = chr;
		}
		while (i < j);
	}
	else
	{
		do
		{
			chr = string[i];
			string[i++] = string[j];
			string[j--] = chr;
		}
		while (i < j);
	}
	return 0;
}



/// EMIT FIX
@___();
@___()
{
	new a[1];
	strcat(a, !"");
	return;
}

stock
	strcatex(dest[], size, const ...)
{
	new num_args;

	// Get the number of arguments
	#emit load.s.pri 0x8
	// Subtract one argument.
	#emit const.alt 4 // 1 * 4 = 4
	#emit sub
	#emit stor.s.pri num_args

	if (num_args == 0)
		return 0;

	new darg_start, darg_end, ret;

	// Get the address of start of the dynamic arguments
	#emit const.alt size
	#emit lctrl 5
	#emit add
	#emit stor.s.pri darg_start

	// Get the address of end of the dynamic arguments
	#emit load.s.alt num_args
	#emit add
	#emit stor.s.pri darg_end

	darg_start += 4;

	do
	{
		#emit push.s size

		#emit load.s.pri darg_start
		#emit load.i
		#emit push.pri

		#emit push.s dest
		#emit push.c 12
		#emit sysreq.c strcat

		#emit load.s.alt ret
		#emit add
		#emit stor.s.pri ret

		#emit stack 16

		darg_start += 4;
	}
	while (darg_start < darg_end);
	return ret;
}



stock
	strfill(string[], const pattern[] = " ", fill_length, size = sizeof string)
{
	if (fill_length >= size)
		return 0;

	new pattern_len = strlen(pattern),
		string_len = strlen(string),
		left_part_len = fill_length / 2,
		right_part_len = fill_length - left_part_len,
		string_pos;

	// get a specific length of the parts.
	left_part_len *= pattern_len;
	right_part_len *= pattern_len;

	// strins doesn't support the maxlength.
	if (left_part_len >= size)
		return 0;

	do
	{
		strins(string, pattern, string_pos, size);
		string_pos += pattern_len;
	}
	while (string_pos < left_part_len);

	// Go to the index after the string.
	right_part_len += (string_pos += string_len);

	do
	{
		strcat(string, pattern, size);
		string_pos += pattern_len;
	}
	while (string_pos < right_part_len);

	return 1;
}
