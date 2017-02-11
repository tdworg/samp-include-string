/* ========================================================================== *\
	Utils

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
			-
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

#if defined _inc_tdw_strutils
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_strutils
#endif

#if defined _TDW_STR_UTILS
	#endinput
#endif

#define _TDW_STR_UTILS

#include "tdw_string"


stock strclear(string[])
{
	return (IsPackedString(string) ? (string{0} = '\0') : (string[0] = '\0'));
}


stock strcpy(dest[], const string[], dest_size = sizeof dest)
{
	return strclear(dest), strcat(dest, string, dest_size);
}


stock IsEmptyString(const string[])
{
	return (IsPackedString(string) ? (string{0}) : (string[0])) == '\0';
}

stock strreverse(string[])
{
	new
		i,
		len = strlen(string),
		j = len - 1,
		chr;

	if (IsPackedString(string)) {
		do {
			chr = string{i};
			string{i++} = string{j};
			string{j--} = chr;
		} while (i < j);
	} else {
		do {
			chr = string[i];
			string[i++] = string[j];
			string[j--] = chr;
		} while (i < j);
	}
	return 0;
}

stock strcount(const string[], const find[], bool:ignorecase = false, pos = 0,
	string_size = sizeof string)
{
	if (pos >= string_size)
		return 0;

	new
		found_pos = pos,
		count,
		find_size = strlen(find);

	while ((found_pos = strfind(string, find, ignorecase,
		found_pos)) >= 0)
	{
		count++;
		found_pos += find_size;
	}

	return count;
}

enum E_TDW_FILL_TYPE (<<= 1)
{
	FILL_TYPE_LEFT = 1,
	FILL_TYPE_RIGHT,
	FILL_TYPE_BOTH = FILL_TYPE_LEFT | FILL_TYPE_RIGHT
};

stock strfill(string[], const pattern[] = " ", fill_length,
	E_TDW_FILL_TYPE:type = FILL_TYPE_BOTH, size = sizeof string)
{
	if (fill_length >= size)
		return 0;

	new
		pattern_len = strlen(pattern),
		string_len = strlen(string),
		left_part_len,
		right_part_len,
		string_pos;

	if (type & FILL_TYPE_BOTH) {
		left_part_len = right_part_len = fill_length;
	} else {
		left_part_len = fill_length / 2;
		right_part_len = fill_length - left_part_len;
	}

	if (type & FILL_TYPE_LEFT) {
		// get a specific length of the parts.
		left_part_len *= pattern_len;

		// strins doesn't support the maxlength.
		if (left_part_len > size)
			return 0;

		do {
			strins(string, pattern, string_pos, size);
			string_pos += pattern_len;
		} while (string_pos < left_part_len);
	}

	if (type & FILL_TYPE_RIGHT) {
		// get a specific length of the parts.
		right_part_len *= pattern_len;

		// Go to the index after the string.
		right_part_len += (string_pos += string_len);

		do {
			strcat(string, pattern, size);
			string_pos += pattern_len;
		} while (string_pos < right_part_len);
	}

	return 1;
}


stock strimplode(dest[], const arrays[][], const delimiter[] = !" ",
	array_items = sizeof arrays, dest_size = sizeof dest)
{
	new
		current_index_item;

	dset[0] = '\0';

	while (current_index_item < array_items) {
		// chars are not inserted.
		if (strcat(dest, arrays[current_index_item], dest_size) == 0)
			break;

		// Don't insert a delimiter.
		if (current_index_item == array_items)
			break;

		strcat(dest, delimiter, dest_size);
		current_index_item++;
	}

	return current_index_item;
}


stock strexplode(arrays[][], const string[], const delimiter[] = !" ",
	array_items = sizeof arrays, array_item_size = sizeof arrays[])
{
	new
		start_pos,
		end_pos,
		current_index_item;

	while (current_index_item < array_items) {
		end_pos = strfind(string, delimiter, false, start_pos);

		if (end_pos == -1)
			end_pos = array_item_size;

		strmid(arrays[current_index_item], string, start_pos, end_pos,
			array_item_size);

		if (end_pos == -1)
			break;

		start_pos = end_pos + 1;
		current_index_item++;
	}

	return current_index_item;
}

stock IsEqual(const string1[], const string2[], bool:ignorecase = false)
{
	return string1[0] == '\0' || string2[0] == '\0'
		? false
		: (strcmp(string1, string2, ignorecase) == 0);
}

stock strAfter(string[], const pattern[] = !" = ", bool:ignorecase = false,
	pos = 0, size_string = sizeof string)
{
	new
		string_len = strlen(string),
		pattern_len = strlen(pattern);

	return strmid(string, string,
		strfind(string, pattern, ignorecase, pos) + pattern_len, string_len,
			size_string);
}

stock strBefore(string[],  const pattern[] = !" = ", bool:ignorecase = false,
	pos = 0, size_string = sizeof string)
{
	return strmid(string, string, 0,
		strfind(string, pattern, ignorecase, pos) - 1, size_string);
}

// Author of the first implementation is VVWVV.
// Author: ziggi.
stock ucfirst(string[])
{
	const
		FIRST_UPPER_SYMBOL = 224,
		LAST_UPPER_SYMBOL = 225,
		EXTRA_UPPER_SYMBOL = 184,

		FIRST_LOWER_SYMBOL = 192,
		LAST_LOWER_SYMBOL = 223,
		EXTRA_LOWER_SYMBOL = 168,

		DIFF_SYMBOL = FIRST_UPPER_SYMBOL - FIRST_LOWER_SYMBOL,
		DIFF_EXTRA = EXTRA_UPPER_SYMBOL - EXTRA_LOWER_SYMBOL;

	new
		i = strlen(string);

	if (IsPackedString(string)) {
		switch (string{0}) {
			case 'a'..'z', FIRST_LOWER_SYMBOL..LAST_LOWER_SYMBOL:
				string{0} -= DIFF_SYMBOL;
			case EXTRA_LOWER_SYMBOL:
				string{0} -= DIFF_EXTRA;
		}

		do {
			switch (string{i}) {
				case 'A'..'Z', FIRST_UPPER_SYMBOL..LAST_UPPER_SYMBOL:
					string{i} += DIFF_SYMBOL;
				case EXTRA_UPPER_SYMBOL:
					string{i} += DIFF_EXTRA;
			}
		} while (--i != 0);
	} else {
		switch (string[0]) {
			case 'a'..'z', FIRST_LOWER_SYMBOL..LAST_LOWER_SYMBOL:
				string[0] -= DIFF_SYMBOL;
			case 168:
				string[0] -= DIFF_EXTRA;
		}

		do {
			switch (string[i]) {
				case 'A'..'Z', FIRST_UPPER_SYMBOL..LAST_UPPER_SYMBOL:
					string[i] += DIFF_SYMBOL;
				case EXTRA_UPPER_SYMBOL:
					string[i] += DIFF_EXTRA;
			}
		} while (--i != 0);
	}

	return 0;
}


stock isNumeric(const string[])
{
	new
		i,
		c;

	if (IsPackedString(string)) {
		while ((c = string{i++}) != '\0') {
			switch (c) {
				case '0'..'9':
					continue;
				case '.', '+', '-':
					continue;
				default:
					return 0;
			}
		}
	} else {
		while ((c = string[i++]) != '\0') {
			switch (c) {
				case '0'..'9':
					continue;
				case '.', '+', '-':
					continue;
				default:
					return 0;
			}
		}
	}

	return 1;
}
