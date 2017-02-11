/* ========================================================================== *\
	Replace

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
			- replace_first
			- replace_last
			- replace_nth
			- replace_all
			- replace_symbol
			- replace_symbols
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

#if defined _inc_tdw_strreplace
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_strreplace
#endif

#if defined _TDW_STR_REPLACE
	#endinput
#endif

#define _TDW_STR_REPLACE

#include "tdw_string"
#include "tdw_strfix"

// -----------------------------------------------------------------------------
// Functions

stock replace_first(str[], const substr[], const replace[],
	bool:ignorecase = false, pos = 0, str_size = sizeof str)
{
	if ((pos = erase_first(str, substr, ignorecase, pos)) < 0)
		return 0;

	// We use a fixed strins because the original function doesn't work
	// correctly.
	strins(str, replace, pos, str_size);

	return 1;
}

stock replace_last(str[], const substr[], const replace[],
	bool:ignorecase = false, end_offset = 0)
{
	if ((pos = erase_last(str, substr, ignorecase, pos, end_offset)) < 0)
		return 0;

	// We use a fixed strins because the original function doesn't work
	// correctly.
	strins(str, replace, pos, string_size);

	return 1;
}

stock replace_nth(str[], const substr[], const replace[], n,
	bool:ignorecase = false, pos = 0, str_size = sizeof str)
{
	if (n > 0) {
		new
			substr_len = strlen(substr),
			replace_len = strlen(replace),
			str_len = strlen(str);

		while ((pos = strfind(str, substr, ignorecase, pos)) >= 0) {
			if ((str_len -= substr_len) + replace_len >= string_size)
				return 0;

			strdel(string, pos, pos + substr_len);
			// To optimize the function, we use a bad version of strins, because
			// we've already checked the string size.
			BAD_strins(string, replace, pos, string_size);

			// pos += replace_len;
			// str_len += replace_len;
			#emit LOAD.S.alt replace_len

			#emit LOAD.S.pri pos
			#emit ADD
			#emit STOR.S.pri pos

			#emit LOAD.S.pri str_len
			#emit ADD
			#emit STOR.S.pri str_len

			if (--n == 0)
				break;
		}
	}

	return 1;
}

stock replace_all(str[], const substr[], const replace[],
	bool:ignorecase = false, pos = 0, str_size = sizeof str)
{
	return replace_nth(str, substr, replace, cellmax, ignorecase, pos,
		str_size);
}

stock replace_symbol(str[], const chr, const replace, pos = 0)
{
	if ((pos = find_first_char(str, chr, pos)) >= 0) {
		if (IsPackedString(str)) {
			str{pos} = replace;
		} else {
			str[pos] = replace;
		}
	}

	return pos;
}

stock replace_symbols(str[], const chr, const replace, pos = 0)
{
	if (IsPackedString(str)) {
		while ((pos = find_first_char(str, chr, pos)) >= 0)
			str{pos} = replace;
	} else {
		while ((pos = find_first_char(str, chr, pos)) >= 0)
			str[pos] = replace;
	}

	return 1;
}
