/** ======================================================================== **\
	String lib

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

// file guard
#if defined _inc_string
	#undef _inc_string
#endif
#if defined _TDW_STRING_INC_
	#endinput
#endif
#define _TDW_STRING_INC_

stock
	strncat(dest[], const src[], n,
		/* not recommended to use => */ dest_size = sizeof dest)
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
	#emit shl.c.pri  2
	#emit stor.s.pri n
	// Load addresses of the strings
	#emit load.s.pri s1
	#emit load.s.alt s2
	// Compare blocks in the memory
	#emit cmps       n
	// I didn't use the variables, so I use this asm command.
	#emit retn
	// For compiler
	return 0;
}

stock
	strexplode(dest[][], const src[], const delimiter = ' ',
		/* not recommended to use => */ dest_major_size = sizeof dest,
		dest_minor_size = sizeof dest[])
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
			break;
			// continue;
		}
		if (pos2 >= dest_minor_size)
			break;
		dest[index][pos2++] = _char;
	}
	return;
}

stock
	strcount(const src[], const pattern[])
{
	new _char, count, pos1, pos2, pattern_size = strlen(pattern);
	for (;;++pos1)
	{
		if ((_char = src[pos1]) == '\0')
			break;
		if (_char == pattern[pos2++])
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
	strerase(dest[], const src[], pos = 0, len = sizeof src,
		/* don't use => */ dest_len = sizeof dest)
{
	if (dest_len < len)
		return;
	new _char, pos1, pos2;
	for (;;++pos1)
	{
		if ((_char = src[pos1]) == '\0')
			break;
		if (pos <= pos1 <= len + pos - 1)
			continue;
		dest[pos2++] = _char;
	}
	// printf("dest %s", dest);
	return;
}

stock
	strltrim_c(dest[], const src[], const s = ' ',
		/* not recommended to use => */ dest_size = sizeof dest)
{
	if (strlen(src) > dest_size)
		return;
	new pos, pos2, _f_char = s, _char;
	for (;;++pos)
	{
		if ((_char = src[pos]) == '\0')
		{
			dest[pos2++] == '\0';
			break;
		}
		if (_char == _f_char)
			continue;
		else _f_char = '\0';
		dest[pos2++] = _char;
	}
	return;
}

stock
	strltrim_s(dest[], const src[], const s[] = " ",
		/* not recommended to use => */ dest_size = sizeof dest)
{
	if (strlen(src) > dest_size)
		return;
	new pos, pos2, _char, _f_char, pos3;
	for (;;++pos)
	{
		if ((_char = src[pos]) == '\0')
		{
			dest[pos2++] == '\0';
			break;
		}
		while ((_f_char = s[pos3++]))
			if (_char == _f_char)
				continue;
			else _f_char = '\0';
		dest[pos2++] = _char;
	}
	return;
}

stock
	strrtrim_c(dest[], const src[], const s = ' ',
		/* not recommended to use => */ dest_size = sizeof dest)
{
	new pos = strlen(src) - 1;
	if (pos > dest_size)
		return;
	for (;;--pos)
	{
		if (pos == -1)
			break;
		if (src[pos] == s)
			continue;
		dest[pos++] = '\0';
		while (pos--) dest[pos] = src[pos];
		break;
	}
	return;
}

stock
	strrtrim_s(dest[], const src[], const s[] = " ",
		/* not recommended to use => */ dest_size = sizeof dest)
{
	new pos = strlen(src) - 1, pos2, _char;
	if (pos > dest_size)
		return;
	for (;;--pos)
	{
		if (pos == -1)
			break;
		while ((_char = s[pos2++]))
			if (src[pos] == _char)
				continue;
		dest[pos++] = '\0';
		while (pos--) dest[pos] = src[pos];
		break;
	}
	return;
}

enum e_TDW_STRING_TRIM_Alg
{
	LEFT  = 0b01,
	RIGHT = 0b10,
	BOTH  = 0b11
};

stock
	strtrim_c(dest[], const src[], const s = ' ', e_TDW_STRING_TRIM_Alg:al=BOTH,
		/* not recommended to use => */ dest_size = sizeof dest)
{
	if (al & LEFT ) strltrm_c(dest, src, s, dest_size);
	if (al & RIGHT) strrtrm_c(dest, src, s, dest_size);
	return;
}

stock
	strtrim_s(dest[], const src[], const s[] = " ",
		e_TDW_STRING_TRIM_Alg:al=BOTH,
		/* not recommended to use => */ dest_size = sizeof dest)
{
	if (al & LEFT ) strltrm_s(dest, src, s, dest_size);
	if (al & RIGHT) strrtrm_s(dest, src, s, dest_size);
	return;
}

stock
	find_first_c(const src[], const _char)
{
	new pos, _ctmp;
	for(;;++pos)
	{
		if ((_ctmp = src[pos]) == '\0')
			break;
		if (_ctmp == _char)
			return pos;
	}
	return -1;
}

stock
	find_first_s(const src[], const _chars[])
{
	new pos, _ctmp, pos2, _ctmp2;
	for(;;++pos)
	{
		if ((_ctmp = src[pos]) == '\0')
			break;
		while (_chars[pos2++])
			if (_ctmp != _ctmp2)
				continue;
			else
				return pos;
	}
	return -1;
}

stock
	find_last_c(const src[], const _char,
		/* not recommended to use => */ const size = sizeof src)
{
	new i = size - 1;
	while (src[--i])
	{
		if (src[i] == _char)
			return i;
	}
	return -1;
}

stock
	find_last_s(const src[], const _chars[],
		/* not recommended to use => */ const size = sizeof src)
{
	new i = size - 1, _char, _char2, pos;
	while ((_char = src[--i]))
	{
		while ((_char2 = _chars[pos++]))
			if (_char2 != _char)
				continue;
			else
				return i;
	}
	return -1;
}

stock
	strreplace(dest[], const src[], const replace[], const replacment[],
		start = 0, len = 0xFFFFFFFF,
		/* not recommended to use => */ dest_size = sizeof dest,
		src_size = sizeof src)
{
	new pos, pos2, pos3, replace_length = strlen(replace),
		replacment_length = strlen(replacment), _char, pos4;
	if (start >= src_size)
		return 0;
	if (len + start >= src_size)
		return 0;
	for (;len;++pos2)
	{
		if ((_char = src[pos2]) == '\0')
		{
			dest[pos++] = '\0';
			break;
		}
		else if (_char == replace[pos3])
		{
			pos3++;
			if (replace_length == pos3)
			{
				if (dest_size - pos < replacment_length)
				{
					dest[pos++] = '\0';
					break;
				}
				while ((_char = replacment[pos4++]))
				{
					dest[pos++] = _char;
				}
				pos4 = 0;
			}
			continue;
		}
		if (pos3 != 0)
			pos3 = 0;
		dest[pos++] = _char;
	}
	return 1;
}

stock
	strtok_c(dest[], const src[], &index, const delim = ' ')
{
	static _char, pos;
	for (pos = 0;;index++)
	{
		if ((_char = src[index]) == '\0' || _char == delim)
		{
			dest[pos++] = '\0';
			break;
		}
		dest[pos++] = _char;
	}
}

stock
	strtok_s(dest[], const src[], &index, const delim[] = " ")
{
	static _char, pos, pos2, _char2;
	for (pos = 0;;index++)
	{
		if ((_char = src[index]) == '\0')
		{
			dest[pos++] = '\0';
			break;
		}
		while ((_char2 = delim[pos2++]))
			if (_char2 != _char)
				continue;
			else
			{
				dest[pos++] = '\0';
				break;
			}
		dest[pos++] = _char;
	}
}

stock
	stoi(const src[])
{
	new sign, _char, pos, result;

	if (src[0] == '-')
		sign = -1;
	for (pos = _:(sign == -1); (_char = src[pos++]);)
		if (0 <= _char <= 9)
			result = result * 10 + _char - '0';
	if (sign == -1)
		result = -result;

	return result;
}

stock
	Float:stof(const src[])
{
	new Float:result, Float:fact = 1.000000, pos, _char, point;

	if (src[0] == '-')
	{
		pos++;
		fact = -1.000000;
	}
	for (; (_char = src[pos++]);)
	{
		if (_char == '.')
		{
			point = 1;
			continue;
		}
		_char -= '0';
		if (0 <= _char <= 9)
		{
			if (point)
				fact = floatdiv(fact, 10.000000);
			result = floatadd(floatmul(result, 10.000000), float(_char));
		}
	}
	return floatmul(result, fact);
}