/* ========================================================================== *\
	Fix

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
			- strins
			- strcmp
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
		- BAD_strins
		- BAD_strcmp
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_strfix
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_strfix
#endif

#if defined _TDW_STR_FIX
	#endinput
#endif

#define _TDW_STR_FIX

#include "tdw_string"

// -----------------------------------------------------------------------------
// Functions

#if !defined BAD_strins
	native BAD_strins(string[], const substr[], pos,
		maxlength = sizeof string) = strins;
#endif

stock tdwSTR@strins(string[], const substr[], pos, maxlength = sizeof string)
{
	if (IsPackedString(string)) {
		new
			str_len = strlen(string),
			substr_len = strlen(substr),
			max_size = maxlength * 4;

		if (str_len + substr_len >= max_size) {
			if (pos + substr_len >= max_size) {
				return
					string{pos} = '\0',
					strcat(string, substr, maxlength);
			} else {
				string{maxlength - substr_len - 1} = '\0';
			}
		}
		return strins(string, substr, pos, maxlength);
	} else if (IsPackedString(substr)) {
		new
			str_len = strlen(string),
			substr_len = strlen(substr);

		if (str_len + substr_len >= maxlength) {
			if (pos + substr_len >= maxlength) {
				return
					string[pos] = '\0',
					strcat(string, substr, maxlength);
			} else {
				string[maxlength - substr_len - 1] = '\0';
			}
		}
		return strins(string, substr, pos, maxlength);
	} else {
		return format(string, maxlength, "%.*s%s%s", pos, string, substr,
			string[pos]);
	}
}

#if defined _ALS_strins
	#undef strins
#else
	#define _ALS_strins
#endif

#define strins tdwSTR@strins


#if !defined BAD_strcmp
	native BAD_strcmp(const string1[], const string2[], bool:ignorecase = false,
		length = cellmax) = strcmp;
#endif

stock tdwSTR@strcmp(const string1[], const string2[], bool:ignorecase = false,
	length = cellmax)
{
	static
		is_empty_s1,
		is_empty_s2;

	is_empty_s1 = IsEmptyString(string1);
	is_empty_s2 = IsEmptyString(string2);

	if (is_empty_s1 != 0)
		return (is_empty_s2 != 0)
			? strcmp(string1, string2, ignorecase, length)
			: 1;

	return (is_empty_s2 != 0) ? -1 : 0;
}

#if defined _ALS_strcmp
	#undef strcmp
#else
	#define _ALS_strcmp
#endif

#define strcmp tdwSTR@strcmp
