/* ========================================================================== *\
	Erase

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
			- erase_first
			- erase_last
			- erase_nth
			- erase
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

#if defined _inc_tdw_strerase
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_strerase
#endif

#if defined _TDW_STR_ERASE
	#endinput
#endif

#define _TDW_STR_ERASE

#include "tdw_string"

// -----------------------------------------------------------------------------
// Functions

stock erase_first(str[], const substr[], bool:ignorecase = false, pos = 0)
{
	new
		substr_len = strlen(substr);

	if ((pos = strfind(str, substr, ignorecase, pos)) < 0)
		return -1;

	strdel(str, pos, pos + substr_len);

	return pos;
}

stock erase_last(str[], const substr[], bool:ignorecase = false, end_offset = 0)
{
	new
		substr_len = strlen(substr),
		pos;

	if ((pos = find_last(str, substr, ignorecase, end_offset)) < 0)
		return -1;

	strdel(str, pos, pos + substr_len);

	return pos;
}

stock erase_nth(str[], const substr[], n, bool:ignorecase = false, pos = 0)
{
	if (n > 0) {
		new
			substr_len = strlen(substr);

		while ((pos = strfind(str, substr, ignorecase, pos)) >= 0) {
			strdel(str, pos, pos + substr_len);

			if (--n == 0)
				break;
		}
	}

	return n;
}

stock erase(str[], start, end = cellmax)
{
	strdel(str, start, end);
	return 0;
}