/*
 * TDW String
 *
 * Copyright (c) 2017 Double V
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#if defined _TDW_STRING_INC_
	#endinput
#endif
#define _TDW_STRING_INC_

#if !defined TDW_STRING_IS_PACKED
	#define TDW_STRING_IS_PACKED(%0) ((%0){0} != 0)
#endif

#if !defined TDW_STRING_BYTES_PER_CELL
	#define TDW_STRING_BYTES_PER_CELL (cellbits / charbits)
#endif

enum e_TDW_FILL_TYPE (<<= 1)
{
	ei_TDW_FILL_TYPE_LEFT = 1,
	ei_TDW_FILL_TYPE_RIGHT,
	ei_TDW_FILL_TYPE_BOTH = ei_TDW_FILL_TYPE_LEFT | ei_TDW_FILL_TYPE_RIGHT
};

// Returns true if a passed string is empty, otherwise returns false.
stock isempty(const str[])
{
	return str[0] == EOS;
}

// Returns true if a passed string contains only a number, otherwise return
// false.
stock isnum(const str[])
{
	new
		i,
		temp;

	while ((temp = str[i++]) != EOS) {
		switch (temp) {
			case '0'..'9':
				continue;
			case '+', '-', '.':
				continue;
			default:
				return 0;
		}
	}
	return 1;
}

// Moves the indicator string end to the beginning.
stock strclr(str[])
{
	return str[0] = EOS;
}

// Copies a source string to a destination string. Returns the number of
// copied characters.
stock strcpy(dest[], const src[], maxlength=sizeof dest)
{
	strclr(dest);
	return strcat(dest, src, maxlength);
}

// Reverses a string. Returns the number of replaced characters.
stock strrev(str[])
{
	new
		length = strlen(str),
		i,
		j = length - 1,
		temp;

	if (TDW_STRING_IS_PACKED(str)) {
		length *= TDW_STRING_BYTES_PER_CELL;

		do {
			temp = str{i};
			str{i++} = str{j};
			str{j--} = temp;
		} while (i < j);
	} else {
		do {
			temp = str[i];
			str[i++] = str[j];
			str[j--] = temp;
		} while (i < j);
	}
	return i;
}

// Counts the number of matches. Returns the number of matches.
stock strcnt(const src[], const sub[], bool:ignorecase=false)
{
	new
		last_pos,
		cnt,
		sub_length = strlen(sub);

	if (TDW_STRING_IS_PACKED(sub))
		sub_length *= TDW_STRING_BYTES_PER_CELL;

	while ((last_pos = strfind(src, sub, ignorecase, last_pos)) >= 0)
	{
		last_pos += sub_length;
		cnt++;
	}

	return cnt;
}

// Returns an index of the first  occurrence of character in the str.
stock strchr(const str[], chr)
{
	new
		cur_chr,
		pos;

	if (TDW_STRING_IS_PACKED(str)) {
		while ((cur_chr = str{pos}) && cur_chr != chr)
			pos++;
	} else {
		while ((cur_chr = str[pos]) && cur_chr != chr)
			pos++;
	}

	return pos;
}

stock strspn(const str1[], const str2[])
{
	new
		str1_chr,
		str1_pos,
		str2_chr,
		str2_pos;

	if (TDW_STRING_IS_PACKED(str1)) {
		if (TDW_STRING_IS_PACKED(str2)) {
			while ((str1_chr = str1{str1_pos})) {
				while ((str2_chr = str2{str2_pos}) && str1_chr != str2_chr)
					str2_pos++;

				if (str2_chr != EOS)
					break;

				str2_pos = 0;
				str1_pos++;
			}
		} else {
			while ((str1_chr = str1{str1_pos})) {
				while ((str2_chr = str2[str2_pos]) && str1_chr != str2_chr)
					str2_pos++;

				if (str2_chr != EOS)
					break;

				str2_pos = 0;
				str1_pos++;
			}
		}
	} else {
		if (TDW_STRING_IS_PACKED(str2)) {
			while ((str1_chr = str1[str1_pos])) {
				while ((str2_chr = str2{str2_pos}) && str1_chr != str2_chr)
					str2_pos++;

				if (str2_chr != EOS)
					break;

				str2_pos = 0;
				str1_pos++;
			}
		} else {
			while ((str1_chr = str1[str1_pos])) {
				while ((str2_chr = str2[str2_pos]) && str1_chr != str2_chr)
					str2_pos++;

				if (str2_chr != EOS)
					break;

				str2_pos = 0;
				str1_pos++;
			}
		}
	}

	return str1_pos;
}
