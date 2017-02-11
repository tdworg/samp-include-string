/* ========================================================================== *\
	Find

| Description:
	Functions to find substrings in a string.

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
			- find_first
			- find_first_char
			- find_first_of
			- find_first_not_of
			- find_last
			- find_last_char
			- find_last_of
			- find_last_not_of
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

#if defined _inc_tdw_strfind
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_strfind
#endif

#if defined _TDW_STR_FIND
	#endinput
#endif

#define _TDW_STR_FIND

#include "tdw_string"

// -----------------------------------------------------------------------------
// Functions

stock find_first(const str[], const substr[], bool:ignorecase = false,
	pos = 0)
{
	return strfind(str, substr, ignorecase, pos);
}

stock find_first_char(const str[], const chr, pos = 0)
{
	if (pos < 0)
		return -1;

	new
		cur_char;

	if (IsPackedString(str)) {
		while ((cur_char = str{pos}) != '\0' && cur_char != chr) pos++;
	} else {
		while ((cur_char = str[pos]) != '\0' && cur_char != chr) pos++;
	}

	return pos;
}

stock find_first_of(const str[], const chrlist[], pos, size = sizeof str)
{
	return find_first_chrlist(str, chrlist, true, pos, size);
}

stock find_first_not_of(const str[], const chrlist[], pos, size = sizeof str)
{
	return find_first_chrlist(str, chrlist, false, pos, size)
}

stock find_last(const str[], const substr[], bool:ignorecase = false,
	end_offset = 0)
{
	new
		str_len = strlen(str),
		substr_len = strlen(substr),
		pos,
		limit_pos = str_len - end_offset;

	for (; str_len >= 0; str_len -= substr_len + 1) {
		pos = strfind(str, substr, ignorecase, str_len);

		if (pos < 0)
			continue;

		if (pos + substr_len <= limit_pos)
			break;

		pos = -1;
	}

	return pos;
}

stock find_last_char(const str[], const chr, end_offset = 0)
{
	new
		pos = strlen(str) - end_offset;

	if (IsPackedString(str)) {
		while (str{pos} != chr && pos > 0) pos--;
	} else {
		while (str[pos] != chr && pos > 0) pos--;
	}

	return pos;
}

stock find_last_of(const str[], const chrlist[], end_offset = 0)
{
	return find_last_chrlist(str, chrlist, true, end_offset);
}

stock find_last_not_of(const str[], const chrlist[], end_offset = 0)
{
	return find_last_chrlist(str, chrlist, false, end_offset);
}

// -----------------------------------------------------------------------------
// Inertnal

static stock find_last_chrlist(const str[], const chrlist[], bool:is_equal,
	end_offset)
{
	new
		chr_pos,
		chrlist_len = strlen(chrlist),
		cur,
		pos = strlen(str) - 1 - end_offset;


	if (IsPackedString(str)) {
		if (IsPackedString(chrlist)) {
			while ((cur = str{pos}) && pos != 0) {
				while (chr_pos <= chrlist_len && cur != chrlist{chr_pos++}) {}

				if (is_equal != (chr_pos > chrlist_len))
					break;

				chr_pos = 0;
				--pos;
			}
		} else {
			while ((cur = str{pos}) && pos != 0) {
				while (chr_pos <= chrlist_len && cur != chrlist[chr_pos++]) {}

				if (is_equal != (chr_pos > chrlist_len))
					break;

				chr_pos = 0;
				--pos;
			}
		}
	} else {
		if (IsPackedString(chrlist)) {
			while (pos > 0 && (cur = str[pos])) {
				while (chr_pos <= chrlist_len && cur != chrlist{chr_pos++}) {}

				if (is_equal != (chr_pos > chrlist_len))
					break;

				chr_pos = 0;
				--pos;
			}
		} else {
			while (pos > 0 && (cur = str[pos])) {
				while (chr_pos <= chrlist_len && cur != chrlist[chr_pos++]) {}

				if (is_equal != (chr_pos > chrlist_len))
					break;

				chr_pos = 0;
				--pos;
			}
		}
	}

	return pos;
}

static stock find_first_chrlist(const str[], const chrlist[], bool:is_equal,
	pos, size)
{
	if (pos > size)
		return -1;

	new
		chr_pos,
		chrlist_len = strlen(chrlist),
		cur;


	if (IsPackedString(string)) {
		if (IsPackedString(chrlist)) {
			while ((cur = str{pos}) != '\0') {
				while (chr_pos <= chrlist_len && cur != chrlist{chr_pos++}) {}

				if (is_equal != (chr_pos > chrlist_len))
					break;

				chr_pos = 0;
				++pos;
			}
		} else {
			while ((cur = str{pos}) != '\0') {
				while (chr_pos <= chrlist_len && cur != chrlist[chr_pos++]) {}

				if (is_equal != (chr_pos > chrlist_len))
					break;

				chr_pos = 0;
				++pos;
			}
		}
	} else {
		if (IsPackedString(chrlist)) {
			while ((cur = str[pos]) != '\0') {
				while (chr_pos <= chrlist_len && cur != chrlist{chr_pos++}) {}

				if (is_equal != (chr_pos > chrlist_len))
					break;

				chr_pos = 0;
				++pos;
			}
		} else {
			while ((cur = str[pos]) != '\0') {
				while (chr_pos <= chrlist_len && cur != chrlist[chr_pos++]) {}

				if (is_equal != _:(chr_pos > chrlist_len))
					break;

				chr_pos = 0;
				++pos;
			}
		}
	}

	return pos;
}