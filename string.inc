/** ======================================================================== **\
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

#if defined _TDW_STRING_INC_
	#endinput
#endif
#define _TDW_STRING_INC_

stock
	strncat(dest[], const src[], n, /* don't use => */ dest_size = sizeof dest)
{
	new src_current_size = strlen(src),
	    dest_current_size = strlen(dest);
	if (n > src_current_size) n = src_current_size;
	if (n > dest_current_size) n = dest_current_size;
	memcpy(dest, src, dest_current_size << 2, n << 2, dest_size);
	return;
}

stock
	memcmp(const s1[], const s2[], n)
{
	// Convert dec to bytes
	#emit load.s.pri n
	#emit shl.c.pri 2
	#emit stor.s.pri n
	// Load addresses of the strings
	#emit load.s.pri s1
	#emit load.s.alt s2
	// Compare blocks in the memory
	#emit cmps n
	// I didn't use the variables, so I use this asm command.
	#emit retn
	// For compiler
	return 0;
}

stock
	strexpl(dest[][], const src[], const delimiter = ' ',
		dest_major_size = sizeof dest, dest_minor_size = sizeof dest[])
{
	new index, pos1, pos2, _char;
	for (;;++pos1)
	{
		if ((_char = src[pos1]) == '\0')
		{
			dest[index][pos2] = '\0';
			break;
		}
		else if (_char == delimiter)
		{
			dest[index][pos2] = '\0';
			pos2 = 0;
			if (dest_major_size > index)
				index++;
			else break;
			continue;
		}
		if (pos2 >= dest_minor_size)
			break;
		dest[index][pos2++] = _char;
	}
}

stock
	strcnt(const src[], const pattern[])
{
	new count, pos1, pos2, pattern_size = strlen(pattern);
	for (;;++pos1)
	{
		if (src[pos1] == '\0')
			break;
		if (src[pos1] == pattern[pos2++])
		{
			if (pos2 == pattern_size)
			{
				if (pattern_size == 1)
					pos2 = 0;
				count++;
			}
		} else {
			if (pos2 > 0)
				pos2 = 0;
		}
	}
	return count;
}

stock
	strerase(dest[], const str[], pos = 0, len = sizeof str,
		/* don't use => */ dest_len = sizeof dest)
{
	if (dest_len < len)
		return;
	new pos1, pos2;
	for (;;++pos1)
	{
		if (str[pos1] == '\0')
			break;
		if (pos <= pos1 <= len + pos - 1)
			continue;
		dest[pos2++] = str[pos1];
	}
	// printf("dest %s", dest);
}