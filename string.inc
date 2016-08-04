/** ======================================================================== **\
	String lib

| Version:
	2.0.8

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


#if defined _inc_string
	#undef _inc_string
#endif

#if defined _TDW_STRING_INC_
	#endinput
#endif

#define _TDW_STRING_INC_


enum e_TDW_STRING
{
	LEFT  = 0b01,
	RIGHT = 0b10,
	BOTH  = 0b11
};


stock
	strcount(const string[], const find[], bool:ignorecase = false, pos = 0,
		const string_size = sizeof string)
{
	if (pos >= string_size)
		return 0;
	new found_pos = pos, count, find_size = strlen(find);
	while ((found_pos = strfind(string, find, ignorecase,
		found_pos + find_size)) != -1
	)
		count++;
	return count;
}


stock
	find_last(const string[], const find[], bool:ignorecase = false)
{
	new find_size = strlen(find), string_size = strlen(string),
		found_pos = string_size - find_size - 1;
	while ((found_pos = strfind(string, find, ignorecase,
		found_pos - find_size)) != -1
	)
		return found_pos;
	return -1;
}


stock
	find_first(const string[], const find[], bool:ignorecase = false, pos = 0)
{
	if (pos >= string_size)
		return 0;
	new found_pos = pos, find_size = strlen(find);
	while ((found_pos = strfind(string, find, ignorecase,
		found_pos++)) != -1
	)
		return found_pos;
	return -1;
}


stock
	strreplace(string[], const find[], const replacement[],
		bool:ignorecase = false, bool:replace_all = false, const pos = 0,
		string_size = sizeof string)
{
	new found_pos = pos, current_string_len = strlen(string),
		find_size = strlen(find), replacement_len = strlen(replacement);
	while ((found_pos = strfind(string, find, ignorecase, found_pos)) != -1)
	{
		if ((current_string_len -= find_size) + replacement_len >= string_size)
			return 0;
		strdel(string, found_pos, found_pos + find_size);
		strins(string, replacement, found_pos, string_size);
		found_pos += replacement_len;
		current_string_len += replacement_len;
		if (_:replace_all == 0)
			break;
	}
	return 1;
}


// Note: This function doesn't support packed strings.
stock
	strtrim(string[], const delimiter = ' ', e_TDW_STRING:algo = BOTH)
{
	new pos;
	if (algo & LEFT)
	{
		new chr;
		while ((chr = string[pos++]) != '\0') if (chr != delimiter) break;
		strdel(string, 0, pos - 1);
	}
	if (algo & RIGHT)
	{
		new len = strlen(string);
		pos = len;
		while (pos-- != 0) if (string[pos] != delimiter) break;
		strdel(string, pos + 1, len);
	}
	return 1;
}


stock
	memcmp(const string1[], const string2[], n)
{
	#emit load.s.pri n
	#emit shl.c.pri 2
	#emit stor.s.pri n
	#emit load.s.pri string1
	#emit load.s.alt string2
	#emit cmps n
	#emit retn
	return 0;
}


stock
	strexplode(dest[][], const string[], const delimiter[] = " ",
		bool:ignorecase = false, const pos = 0,
		const dest_size_major = sizeof dest
		const dest_size_minor = sizeof dest[],
		const string_size = sizeof string)
{
	if (pos >= string_size)
		return -1;
	new current_index_major, found_pos = pos, last_pos,
		delimiter_len = strlen(delimiter);
	while (current_index_major != dest_size_major)
	{
		if ((found_pos = strfind(string, delimiter, ignorecase, found_pos)
			) == -1)
		{
			strmid(dest[current_index_major], string, last_pos, string_size,
				dest_size_minor);
			break;
		}
		strmid(dest[current_index_major], string, last_pos, found_pos,
			dest_size_minor);
		last_pos = (found_pos += delimiter_len);
		current_index_major++;
	}
	return last_pos;
}


// Note: This function doesn't support packed strings.
stock
	strerase(string[], const start_pos, n, string_size = sizeof string)
{
	if (_:(0 <= start_pos && start_pos < string_size) == 0)
		return 0;
	if (_:(0 < n && n <= string_size - start_pos) == 0)
		return 0;
	new i = start_pos, iterations = string_size - n;
	while (i < iterations)
		string[i] = string[i++ + n];
	while (i < string_size)
		string[i++] = '\0';
	string_size -= n;
	return string_size;
}