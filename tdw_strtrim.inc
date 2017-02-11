/* ========================================================================== *\
	Trim

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
			- trim_left
			- trim_right
			- trim
			- trim_leftex
			- trim_rightex
			- trim_ex
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

#if defined _inc_tdw_strtrim
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_strtrim
#endif

#if defined _TDW_STR_TRIM
	#endinput
#endif

#define _TDW_STR_TRIM

#include "tdw_string"

// -----------------------------------------------------------------------------
// Functions

stock trim_left(str[], const delim = ' ', pos = 0)
{
	if (pos < 0)
		return 0;

	new
		chr_cur;

	if (IsPackedString(str)) {
		while ((chr_cur = str{pos++}) != '\0' && chr_cur == delim) {}
	} else {
		while ((chr_cur = str[pos++]) != '\0' && chr_cur == delim) {}
	}

	return strdel(str, 0, --pos);
}

stock trim_right(str[], const delim = ' ', end_offset = 0)
{
	new
		len = strlen(str) - end_offset,
		cur_pos = len;

	if (IsPackedString(string)) {
		while (cur_pos-- != 0 && str{cur_pos} == delimiter) {}
	} else {
		while (cur_pos-- != 0 && str[cur_pos] == delimiter) {}
	}

	return strdel(string, cur_pos + 1, len);
}

stock trim(str[], const delim = ' ')
{
	return
		trim_left(str, delim),
		trim_right(str, delim);
}

stock trim_leftex(str[], const delims[] = !" ", pos = 0)
{
	new
		str_len = strlen(str),
		delim_pos = find_first_not_of(str, delims, pos, len + 1);

	if (delim_pos >= 0)
		strmid(str, str, delim_pos, len, len + 1);

	return 0;
}

stock trim_rightex(str[], const delims[] = !" ", end_offset = 0)
{
	new
		str_len = strlen(str),
		end_pos = find_last_not_of(str, delims, end_offset);

	if (end_pos >= 0)
		strmid(str, str, len - end_pos, end_pos, len + 1);

	return 0;
}

stock trim_ex(str[], const delims[] = !" ", pos = 0, end_offset = 0)
{
	return
		trim_leftex(str, delims, pos),
		trim_rightex(str, delims, end_offset);
}
