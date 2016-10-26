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


//
// Old version
//
// #if !defined IsPackedString
// 	#define IsPackedString(%0) ((%0)[0] > 255)
// #endif


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
			string[part_start] = c;
		}
		while (++part_start != part_end);
	}
	return 1;
}


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


static stock const
	string@rus[] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцч"\
		"шщьыъэюя",
	string@arr_lat[][] = {
		"A",  "B",    "V", "G", "D", "E", "JO", "ZH", "Z", "I", "Y", "K",
		"L",  "M",    "N", "O", "P", "R", "S",  "T", "U", "F", "KH", "C",
		"CH", "SH", "SHH", "JHH", "IH", "JH", "EH", "JU", "JA",
		"a", "b", "v", "g", "d", "e", "e", "zh", "z", "i", "y", "k", "l", "m",
		"n", "o", "p", "r", "s", "t", "u", "f", "kh", "c", "ch", "sh", "shh",
		"jhh", "ih", "jh", "eh", "ju", "ja"
	};


stock
	strtrtrans(string[], string_size = sizeof string)
{
	new chr, i, pos;
	while ((chr = string[i]) != '\0')
	{
		if ((pos = find_char(string@rus, chr)) != -1)
		{
			strdel(string, i, i + 1);
			strins(string, string@arr_lat[pos], i, string_size);
		}
		i++;
	}
	return 0;
}


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

stock
	strcatex(string[], const ...)
{
	new
		args = numargs(),
		arg = 1,
		i,
		j;

	while (arg < args)
	{
		i = 0;
		while ((string[j] = getarg(arg, i)) != '\0')
		{
			j++;
			i++;
		}
		string[j++] = ' ';
		arg++;
	}
}
