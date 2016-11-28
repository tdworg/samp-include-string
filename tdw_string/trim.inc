/** ======================================================================== **\
	Trim

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
#if defined _inc_trim
	#undef _inc_trim
#endif

#if defined _TDW_STLIB__TRIM
	#endinput
#endif

#define _TDW_STLIB__TRIM


stock
	trim_left(string[], const delimiter = ' ')
{
	new chr, pos;
	if (IsPackedString(string))
	{
		while ((chr = string{pos++}) != '\0')
			if (chr != delimiter)
				break;
	}
	else
	{
		while ((chr = string[pos++]) != '\0')
			if (chr != delimiter)
				break;
	}
	strdel(string, 0, pos - 1);
	return 0;
}


stock
	trim_right(string[], const delimiter = ' ')
{
	new pos = strlen(string), len = strlen(string);
	if (IsPackedString(string))
	{
		while (pos-- != 0)
			if (string{pos} != delimiter)
				break;
	}
	else
	{
		while (pos-- != 0)
			if (string[pos] != delimiter)
				break;
	}
	strdel(string, pos + 1, len);
	return 0;
}


stock
	trim(string[], const delimiter = ' ')
{
	trim_left(string, delimiter);
	trim_right(string, delimiter);
}

// -----------------------------------------------------------------------------
// Extend
// -----------------------------------------------------------------------------

stock
	trim_leftex(string[], const delimiters[] = !" ", start_pos = 0)
{
	new
		len = strlen(string),
		begin_pos = find_first_not_of(string, delimiters, start_pos, len + 1);

	if (begin_pos != -1)
		strmid(string, string, begin_pos, len, len + 1);

	return 0;
}

stock
	trim_rightex(string[], const delimiters[] = !" ")
{
	new
		len = strlen(string),
		end_pos = find_last_not_of(string, delimiters);

	if (end_pos != -1)
		strmid(string, string, len-end_pos, end_pos, len + 1);

	return 0;
}

stock
	trim_ex(string[], const delimiters[] = !" ", start_pos = 0)
{
	new
		len = strlen(string),
		begin_pos = find_first_not_of(string, delimiters, start_pos, len + 1),
		end_pos = find_last_not_of(string, delimiters);

	if (begin_pos != -1)
		strmid(string, string, begin_pos, end_pos + 1, len + 1);

	return 0;
}
