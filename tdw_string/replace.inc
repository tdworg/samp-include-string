/** ======================================================================== **\
	Replace

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
#if defined _inc_replace
	#undef _inc_replace
#endif

#if defined _TDW_STLIB__REPLACE
	#endinput
#endif

#define _TDW_STLIB__REPLACE

static const
	TDW_g_sFormat[] = "%.*s%s%s";

stock
	replace_first(string[], const find[], const replace[],
		bool:ignorecase = false, pos = 0, string_size = sizeof string)
{
	if ((pos = erase_first(string, find, ignorecase, pos)) == -1)
		return 0;
	format(string, string_size, TDW_g_sFormat, pos, string, replace,
		string[pos]
	);
	return 1;
}


stock
	replace_last(string[], const find[], const replace[],
		bool:ignorecase = false, pos = 0, string_size = sizeof string)
{
	if ((pos = erase_last(string, find, ignorecase)) == -1)
		return 0;
	format(string, string_size, TDW_g_sFormat, pos, string, replace,
		string[pos]
	);
	return 1;
}


stock
	replace_nth(string[], const find[], const replace[], n,
		bool:ignorecase = false, pos = 0, string_size = sizeof string)
{
	new find_len = strlen(find), replace_len = strlen(replace),
		string_len = strlen(string);
	while ((pos = strfind(string, find, ignorecase, pos)) != -1)
	{
		if ((string_len -= find_len) + replace_len >= string_size)
			return 0;
		strdel(string, pos, pos + find_len);
		strins(string, replace, pos, string_size);
		pos += replace_len;
		string_len += replace_len;
		if (--n == 0)
			break;
	}
	return 1;
}


stock
	replace_all(string[], const find[], const replace[],
		bool:ignorecase = false, pos = 0, string_size = sizeof string)
{
	new string_len = strlen(string), find_len = strlen(find),
		replace_len = strlen(replace);
	while ((pos = strfind(string, find, ignorecase, pos)) != -1)
	{
		if ((string_len -= find_len) + replace_len >= string_size)
			return 0;
		strdel(string, pos, pos + find_len);
		strins(string, replace, pos, string_size);
		pos += replace_len;
		string_len += replace_len;
	}
	return 1;
}

stock
	replace_symbol(string[], find[2], replace, pos = 0)
{
	if(string{0} != 0)
	{
		while ((pos = strfind(string, find, false, pos)) != -1)
			string{pos} = replace;
	}
	else
	{
		while ((pos = strfind(string, find, false, pos)) != -1)
			string[pos] = replace;
	}
}
