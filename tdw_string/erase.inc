/** ======================================================================== **\
	Erase

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
#if defined _inc_erase
	#undef _inc_erase
#endif

#if defined _TDW_S_ERASE_INC_
	#endinput
#endif

#define _TDW_S_ERASE_INC_


stock
	erase_first(string[], const find[], bool:ignorecase = false, pos = 0)
{
	new find_len = strlen(find);
	if ((pos = strfind(string, find, ignorecase, pos)) == -1)
		return 0;
	strdel(string, pos, pos + find_len);
	return pos;
}


stock
	erase_last(string[], const find[], bool:ignorecase = false)
{
	new find_len = strlen(find), pos;
	if ((pos = find_last(string, find, ignorecase)) == -1)
		return 0;
	strdel(string, pos, pos + find_len);
	return pos;
}


stock
	erase_nth(string[], const find[], n, bool:ignorecase = false, pos = 0)
{
	new find_len = strlen(find);
	if (n == 0)
		return 0;
	while ((pos = strfind(string, find, ignorecase, pos)) != -1)
	{
		strdel(string, pos, pos + find_len);
		if (--n == 0)
			break;
	}
	return 0;
}


stock
	erase(string[], start_pos, length = cellmax)
{
	strdel(string, start_pos, length);
	return 0;
}
