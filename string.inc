/** ======================================================================== **\
	String lib

| Version:
	2.0.0

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