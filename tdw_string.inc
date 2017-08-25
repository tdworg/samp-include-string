/** ======================================================================== **\
	String

| Description:

| Version:
	4.1.1

| Dependencies:
	- n\a

| Compatible with the JIT plugin:
	- Yes (use TDW_STRING_JIT_COMPAT)

| License:
	Copyright (c) 2017 Double V

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

#if defined _inc_tdw_string
	#undef _inc_tdw_string
#endif

#if defined _TDW_string
	#endinput
#endif

#define _TDW_string

#define TDW_SECURE

// ----------------------------------------------------------------------------

#if !defined IS_PACKED_STRING
	// Author: Untonyst
	#define IS_PACKED_STRING(%1) (%1{0} != 0)
#endif

#if !defined _inc_string && !defined _string_included
	#include <string>
#endif

#if defined TDW_SECURE
	#define TDW_STATIC static
#else
	#define TDW_STATIC
#endif

// ----------------------------------------------------------------------------
// Fixes functions

#if !defined _INC_SAMP_Community_fixes
	#if !defined BAD_strins
		native BAD_strins(string[], const substr[], pos,
			maxlength = sizeof string) = strins;
	#endif

	stock tdwSTR@strins(string[], const substr[], pos, maxlength = sizeof string)
	{
		if (IS_PACKED_STRING(string)) {
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
		} else if (IS_PACKED_STRING(substr)) {
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
		is_empty_s1 = isempty(string1);
		is_empty_s2 = isempty(string2);
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
#endif

// ----------------------------------------------------------------------------
// Utils functions

stock strclear(string[])
{
	return (IS_PACKED_STRING(string) ? (string{0} = '\0') : (string[0] = '\0'));
}

stock strcpy(dest[], const string[], dest_size = sizeof dest)
{
	return strclear(dest), strcat(dest, string, dest_size);
}

stock isempty(const string[])
{
	return (IS_PACKED_STRING(string) ? (string{0}) : (string[0])) == '\0';
}

stock strreverse(string[])
{
	new
		i,
		len = strlen(string),
		j = len - 1,
		chr;
	if (IS_PACKED_STRING(string)) {
		do {
			chr = string{i};
			string{i++} = string{j};
			string{j--} = chr;
		} while (i < j);
	} else {
		do {
			chr = string[i];
			string[i++] = string[j];
			string[j--] = chr;
		} while (i < j);
	}
	return 0;
}

stock strcount(const string[], const find[], bool:ignorecase = false, pos = 0,
	string_size = sizeof string)
{
	if (pos >= string_size)
		return 0;
	new
		found_pos = pos,
		count,
		find_size = strlen(find);
	while ((found_pos = strfind(string, find, ignorecase,
		found_pos)) >= 0)
	{
		count++;
		found_pos += find_size;
	}
	return count;
}

enum E_TDW_FILL_TYPE (<<= 1)
{
	FILL_TYPE_LEFT = 1,
	FILL_TYPE_RIGHT,
	FILL_TYPE_BOTH = FILL_TYPE_LEFT | FILL_TYPE_RIGHT
};

stock strfill(string[], const pattern[] = " ", fill_length,
	E_TDW_FILL_TYPE:type = FILL_TYPE_BOTH, size = sizeof string)
{
	if (fill_length >= size)
		return 0;
	new
		pattern_len = strlen(pattern),
		string_len = strlen(string),
		left_part_len,
		right_part_len,
		string_pos;
	if (type & FILL_TYPE_BOTH) {
		left_part_len = right_part_len = fill_length;
	} else {
		left_part_len = fill_length / 2;
		right_part_len = fill_length - left_part_len;
	}
	if (type & FILL_TYPE_LEFT) {
		// get a specific length of the parts.
		left_part_len *= pattern_len;
		// strins doesn't support the maxlength.
		if (left_part_len > size)
			return 0;
		do {
			strins(string, pattern, string_pos, size);
			string_pos += pattern_len;
		} while (string_pos < left_part_len);
	}
	if (type & FILL_TYPE_RIGHT) {
		// get a specific length of the parts.
		right_part_len *= pattern_len;
		// Go to the index after the string.
		right_part_len += (string_pos += string_len);
		do {
			strcat(string, pattern, size);
			string_pos += pattern_len;
		} while (string_pos < right_part_len);
	}
	return 1;
}


stock strimplode(dest[], const arrays[][], const delimiter[] = !" ",
	array_items = sizeof arrays, dest_size = sizeof dest)
{
	new
		current_index_item;
	dset[0] = '\0';
	while (current_index_item < array_items) {
		// chars are not inserted.
		if (strcat(dest, arrays[current_index_item], dest_size) == 0)
			break;
		// Don't insert a delimiter.
		if (current_index_item == array_items)
			break;
		strcat(dest, delimiter, dest_size);
		current_index_item++;
	}
	return current_index_item;
}


stock strexplode(arrays[][], const string[], const delimiter[] = !" ",
	array_items = sizeof arrays, array_item_size = sizeof arrays[])
{
	new
		start_pos,
		end_pos,
		current_index_item;
	while (current_index_item < array_items) {
		end_pos = strfind(string, delimiter, false, start_pos);
		if (end_pos == -1)
			end_pos = array_item_size;
		strmid(arrays[current_index_item], string, start_pos, end_pos,
			array_item_size);
		if (end_pos == -1)
			break;
		start_pos = end_pos + 1;
		current_index_item++;
	}
	return current_index_item;
}

stock isequal(const string1[], const string2[], bool:ignorecase = false)
{
	return string1[0] == '\0' || string2[0] == '\0'
		? false
		: (strcmp(string1, string2, ignorecase) == 0);
}

stock strafter(string[], const pattern[] = !" = ", bool:ignorecase = false,
	pos = 0, size_string = sizeof string)
{
	new
		string_len = strlen(string),
		pattern_len = strlen(pattern);
	return strmid(string, string,
		strfind(string, pattern, ignorecase, pos) + pattern_len, string_len,
			size_string);
}

stock strbefore(string[],  const pattern[] = !" = ", bool:ignorecase = false,
	pos = 0, size_string = sizeof string)
{
	return strmid(string, string, 0,
		strfind(string, pattern, ignorecase, pos) - 1, size_string);
}

// Author of the first implementation is VVWVV.
// Author: ziggi.
stock ucfirst(string[])
{
	const
		FIRST_UPPER_SYMBOL = 'А',
		LAST_UPPER_SYMBOL = 'Я',
		EXTRA_UPPER_SYMBOL = 'Ё',
		FIRST_LOWER_SYMBOL = 'а',
		LAST_LOWER_SYMBOL = 'я',
		EXTRA_LOWER_SYMBOL = 'ё',
		DIFF_SYMBOL = FIRST_LOWER_SYMBOL - FIRST_UPPER_SYMBOL,
		DIFF_EXTRA = EXTRA_LOWER_SYMBOL - EXTRA_UPPER_SYMBOL;
	new
		i = strlen(string);
	if (IS_PACKED_STRING(string)) {
		switch (string{0}) {
			case 'a'..'z', FIRST_LOWER_SYMBOL..LAST_LOWER_SYMBOL:
				string{0} -= DIFF_SYMBOL;
			case EXTRA_LOWER_SYMBOL:
				string{0} -= DIFF_EXTRA;
		}
		do {
			switch (string{i}) {
				case 'A'..'Z', FIRST_UPPER_SYMBOL..LAST_UPPER_SYMBOL:
					string{i} += DIFF_SYMBOL;
				case EXTRA_UPPER_SYMBOL:
					string{i} += DIFF_EXTRA;
			}
		} while (--i != 0);
	} else {
		switch (string[0]) {
			case 'a'..'z', FIRST_LOWER_SYMBOL..LAST_LOWER_SYMBOL:
				string[0] -= DIFF_SYMBOL;
			case EXTRA_LOWER_SYMBOL:
				string[0] -= DIFF_EXTRA;
		}
		do {
			switch (string[i]) {
				case 'A'..'Z', FIRST_UPPER_SYMBOL..LAST_UPPER_SYMBOL:
					string[i] += DIFF_SYMBOL;
				case EXTRA_UPPER_SYMBOL:
					string[i] += DIFF_EXTRA;
			}
		} while (--i != 0);
	}
	return 0;
}

stock isnum(const string[])
{
	new
		i,
		c;
	if (IS_PACKED_STRING(string)) {
		while ((c = string{i++}) != '\0') {
			switch (c) {
				case '0'..'9':
					continue;
				case '.', '+', '-':
					continue;
				default:
					return 0;
			}
		}
	} else {
		while ((c = string[i++]) != '\0') {
			switch (c) {
				case '0'..'9':
					continue;
				case '.', '+', '-':
					continue;
				default:
					return 0;
			}
		}
	}
	return 1;
}

#define MIN3(%0,%1,%2) ((%0) < (%1) ? ((%0) < (%2) ? (%0) : (%2)) : ((%1) < (%2) ? (%1) : (%2)))
stock _levenshtein(buffer[], const str1[], const str2[])
{
	new
		str1Len = strlen(str1),
		str2Len = strlen(str2),
		x, y, lastdiag, olddiag;
	for (y = 1; y <= str1Len; ++y) {
		buffer[y] = y;
	}
	for (x = 1; x <= str2Len; ++x) {
		buffer[0] = x;
		for (y = 1, lastdiag = x - 1; y <= str1Len; ++y) {
			olddiag = buffer[y];
			buffer[y] = MIN3(buffer[y] + 1, buffer[y - 1] + 1, lastdiag + (str1[y - 1] == str2[x - 1] ? 0 : 1));
			lastdiag = olddiag;
		}
	}
	return buffer[str1Len];
}

stock levenshtein(const str1[], const str2[])
{
	new
		str1Len,
		bytes,
		ret;
	str1Len = strlen(str1);
	bytes = str1Len << 2;

	// allocate memory in the stack
	#emit lctrl      4
	#emit load.s.alt bytes
	#emit sub
	#emit sctrl      4

	// call _levenshtein
	#emit push.s     str2
	#emit push.s     str1
	#emit push.pri   // push address
	#emit push.c     12
	#emit call       _levenshtein
	#emit stor.s.pri ret

	// restore the stack
	#emit lctrl      4
	#emit load.s.alt bytes
	#emit add
	#emit sctrl      4

	return ret;
}

// ----------------------------------------------------------------------------
// Memory functions

#if !defined TDW_STRING_JIT_COMPAT
	stock memcmp(const str1[], const str2[], num)
	{
		#pragma unused str1, str2, num
		static
			cmps_inst_offset;
		if (cmps_inst_offset == 0) {
			#emit lctrl    6                // Offsets:
			#emit move.alt                  // 4
			#emit lctrl    0                // 8
			#emit add                       // 4
			#emit move.alt                  // 4
			#emit lctrl    1                // 8
			#emit sub.alt                   // 4
			#emit add.c    92               // 8
			#emit stor.pri cmps_inst_offset // 8
		} {}                                // | crash fix
		#emit load.s.pri   20               // 8
		#emit shl.c.pri    2                // 8
		#emit sref.pri     cmps_inst_offset // 8
		#emit load.s.alt   12               // 8
		#emit load.s.pri   16               // 8
		#emit cmps         1                // 4
		#emit retn
		return 0;
	}

	stock memset(src[], chr, size)
	{
		#pragma unused src, chr, size
		static
			fill_inst_offset;
		if (fill_inst_offset == 0) {
			#emit lctrl    6                // Offsets:
			#emit move.alt                  // 4
			#emit lctrl    0                // 8
			#emit add                       // 4
			#emit move.alt                  // 4
			#emit lctrl    1                // 8
			#emit sub.alt                   // 4
			#emit add.c    92               // 8
			#emit stor.pri fill_inst_offset // 8
		} {}                                // | crash fix
		#emit load.s.pri   20               // 8
		#emit shl.c.pri    2                // 8
		#emit sref.pri     fill_inst_offset // 8
		#emit load.s.alt   12               // 8
		#emit load.s.pri   16               // 8
		#emit fill         1                // 4
		#emit zero.pri
		#emit retn
		return 0;
	}

	stock memmove(dest[], const src[], num)
	{
		#pragma unused dest, src, num
		static
			movs_inst_offset;
		if (movs_inst_offset == 0) {
			#emit lctrl    6                // Offsets:
			#emit move.alt                  // 4
			#emit lctrl    0                // 8
			#emit add                       // 4
			#emit move.alt                  // 4
			#emit lctrl    1                // 8
			#emit sub.alt                   // 4
			#emit add.c    92               // 8
			#emit stor.pri movs_inst_offset // 8
		} {}                                // | crash fix
		#emit load.s.pri   20               // 8
		#emit shl.c.pri    2                // 8
		#emit sref.pri     movs_inst_offset // 8
		#emit load.s.alt   12               // 8
		#emit load.s.pri   16               // 8
		#emit movs         1                // 4
		#emit retn
		return 0;
	}
#else
	const
		_TDW_STRING_MEM_BLOCK_4    = 4,
		_TDW_STRING_MEM_BLOCK_16   = 16,
		_TDW_STRING_MEM_BLOCK_64   = 64,
		_TDW_STRING_MEM_BLOCK_256  = 256,
		_TDW_STRING_MEM_BLOCK_1024 = 1024,
		_TDW_STRING_MEM_BLOCK_4096 = 4096;

	stock memcmp(const str1[], const str2[], num)
	{
		#pragma unused str1, str2
		new
			str1Addr,
			str2Addr,
			ret;
		#emit load.s.pri 12
		#emit stor.s.pri str1Addr
		#emit load.s.pri 16
		#emit stor.s.pri str2Addr
		#emit load.s.pri num
		#emit shl.c.pri 2
		#emit stor.s.pri num
		while (num > 0) {
			if (num >= _TDW_STRING_MEM_BLOCK_4096) {
				#emit load.s.alt str1Addr
				#emit load.s.pri str2Addr
				#emit cmps _TDW_STRING_MEM_BLOCK_4096
				#emit stor.s.pri ret
				num -= _TDW_STRING_MEM_BLOCK_4096;
				str1Addr += _TDW_STRING_MEM_BLOCK_4096;
				str2Addr += _TDW_STRING_MEM_BLOCK_4096;
			} else if (num >= _TDW_STRING_MEM_BLOCK_1024) {
				#emit load.s.alt str1Addr
				#emit load.s.pri str2Addr
				#emit cmps _TDW_STRING_MEM_BLOCK_1024
				#emit stor.s.pri ret
				num -= _TDW_STRING_MEM_BLOCK_1024;
				str1Addr += _TDW_STRING_MEM_BLOCK_1024;
				str2Addr += _TDW_STRING_MEM_BLOCK_1024;
			} else if (num >= _TDW_STRING_MEM_BLOCK_256) {
				#emit load.s.alt str1Addr
				#emit load.s.pri str2Addr
				#emit cmps _TDW_STRING_MEM_BLOCK_256
				#emit stor.s.pri ret
				num -= _TDW_STRING_MEM_BLOCK_256;
				str1Addr += _TDW_STRING_MEM_BLOCK_256;
				str2Addr += _TDW_STRING_MEM_BLOCK_256;
			} else if (num >= _TDW_STRING_MEM_BLOCK_64) {
				#emit load.s.alt str1Addr
				#emit load.s.pri str2Addr
				#emit cmps _TDW_STRING_MEM_BLOCK_64
				#emit stor.s.pri ret
				num -= _TDW_STRING_MEM_BLOCK_64;
				str1Addr += _TDW_STRING_MEM_BLOCK_64;
				str2Addr += _TDW_STRING_MEM_BLOCK_64;
			} else if (num >= _TDW_STRING_MEM_BLOCK_16) {
				#emit load.s.alt str1Addr
				#emit load.s.pri str2Addr
				#emit cmps _TDW_STRING_MEM_BLOCK_16
				#emit stor.s.pri ret
				num -= _TDW_STRING_MEM_BLOCK_16;
				str1Addr += _TDW_STRING_MEM_BLOCK_16;
				str2Addr += _TDW_STRING_MEM_BLOCK_16;
			} else if (num >= _TDW_STRING_MEM_BLOCK_4) {
				#emit load.s.alt str1Addr
				#emit load.s.pri str2Addr
				#emit cmps _TDW_STRING_MEM_BLOCK_4
				#emit stor.s.pri ret
				num -= _TDW_STRING_MEM_BLOCK_4;
				str1Addr += _TDW_STRING_MEM_BLOCK_4;
				str2Addr += _TDW_STRING_MEM_BLOCK_4;
			}
			if (ret != 0)
				break;
		}
		return ret;
	}

	stock memset(src[], chr, size)
	{
		#pragma unused src, chr
		new
			srcAddr;
		#emit load.s.pri 12
		#emit stor.s.pri srcAddr
		#emit load.s.pri size
		#emit shl.c.pri 2
		#emit stor.s.pri size
		while (size > 0) {
			if (size >= _TDW_STRING_MEM_BLOCK_4096) {
				#emit load.s.alt srcAddr
				#emit load.s.pri chr
				#emit fill _TDW_STRING_MEM_BLOCK_4096
				size -= _TDW_STRING_MEM_BLOCK_4096;
				srcAddr += _TDW_STRING_MEM_BLOCK_4096;
			} else if (size >= _TDW_STRING_MEM_BLOCK_1024) {
				#emit load.s.alt srcAddr
				#emit load.s.pri chr
				#emit fill _TDW_STRING_MEM_BLOCK_1024
				size -= _TDW_STRING_MEM_BLOCK_1024;
				srcAddr += _TDW_STRING_MEM_BLOCK_1024;
			} else if (size >= _TDW_STRING_MEM_BLOCK_256) {
				#emit load.s.alt srcAddr
				#emit load.s.pri chr
				#emit fill _TDW_STRING_MEM_BLOCK_256
				size -= _TDW_STRING_MEM_BLOCK_256;
				srcAddr += _TDW_STRING_MEM_BLOCK_256;
			} else if (size >= _TDW_STRING_MEM_BLOCK_64) {
				#emit load.s.alt srcAddr
				#emit load.s.pri chr
				#emit fill _TDW_STRING_MEM_BLOCK_64
				size -= _TDW_STRING_MEM_BLOCK_64;
				srcAddr += _TDW_STRING_MEM_BLOCK_64;
			} else if (size >= _TDW_STRING_MEM_BLOCK_16) {
				#emit load.s.alt srcAddr
				#emit load.s.pri chr
				#emit fill _TDW_STRING_MEM_BLOCK_16
				size -= _TDW_STRING_MEM_BLOCK_16;
				srcAddr += _TDW_STRING_MEM_BLOCK_16;
			} else if (size >= _TDW_STRING_MEM_BLOCK_4) {
				#emit load.s.alt srcAddr
				#emit load.s.pri chr
				#emit fill _TDW_STRING_MEM_BLOCK_4
				size -= _TDW_STRING_MEM_BLOCK_4;
				srcAddr += _TDW_STRING_MEM_BLOCK_4;
			}
		}
		return 0;
	}

	stock memmove(dest[], const src[], num)
	{
		#pragma unused dest, src
		new
			destAddr,
			srcAddr;
		#emit load.s.pri 12
		#emit stor.s.pri destAddr
		#emit load.s.pri 16
		#emit stor.s.pri srcAddr
		#emit load.s.pri num
		#emit shl.c.pri 2
		#emit stor.s.pri num
		while (num > 0) {
			if (num >= _TDW_STRING_MEM_BLOCK_4096) {
				#emit load.s.alt destAddr
				#emit load.s.pri srcAddr
				#emit movs _TDW_STRING_MEM_BLOCK_4096
				num -= _TDW_STRING_MEM_BLOCK_4096;
				destAddr += _TDW_STRING_MEM_BLOCK_4096;
				srcAddr += _TDW_STRING_MEM_BLOCK_4096;
			} else if (num >= _TDW_STRING_MEM_BLOCK_1024) {
				#emit load.s.alt destAddr
				#emit load.s.pri srcAddr
				#emit movs _TDW_STRING_MEM_BLOCK_1024
				num -= _TDW_STRING_MEM_BLOCK_1024;
				destAddr += _TDW_STRING_MEM_BLOCK_1024;
				srcAddr += _TDW_STRING_MEM_BLOCK_1024;
			} else if (num >= _TDW_STRING_MEM_BLOCK_256) {
				#emit load.s.alt destAddr
				#emit load.s.pri srcAddr
				#emit movs _TDW_STRING_MEM_BLOCK_256
				num -= _TDW_STRING_MEM_BLOCK_256;
				destAddr += _TDW_STRING_MEM_BLOCK_256;
				srcAddr += _TDW_STRING_MEM_BLOCK_256;
			} else if (num >= _TDW_STRING_MEM_BLOCK_64) {
				#emit load.s.alt destAddr
				#emit load.s.pri srcAddr
				#emit movs _TDW_STRING_MEM_BLOCK_64
				num -= _TDW_STRING_MEM_BLOCK_64;
				destAddr += _TDW_STRING_MEM_BLOCK_64;
				srcAddr += _TDW_STRING_MEM_BLOCK_64;
			} else if (num >= _TDW_STRING_MEM_BLOCK_16) {
				#emit load.s.alt destAddr
				#emit load.s.pri srcAddr
				#emit movs _TDW_STRING_MEM_BLOCK_16
				num -= _TDW_STRING_MEM_BLOCK_16;
				destAddr += _TDW_STRING_MEM_BLOCK_16;
				srcAddr += _TDW_STRING_MEM_BLOCK_16;
			} else if (num >= _TDW_STRING_MEM_BLOCK_4) {
				#emit load.s.alt destAddr
				#emit load.s.pri srcAddr
				#emit movs _TDW_STRING_MEM_BLOCK_4
				num -= _TDW_STRING_MEM_BLOCK_4;
				destAddr += _TDW_STRING_MEM_BLOCK_4;
				srcAddr += _TDW_STRING_MEM_BLOCK_4;
			}
		}
		return 0;
	}

	// TDW_STRING_JIT_COMPAT
#endif

// ----------------------------------------------------------------------------
// Find functions

stock find_first(const str[], const substr[], bool:ignorecase = false,
	pos = 0)
{
	return strfind(str, substr, ignorecase, pos);
}

stock find_first_char(const str[], const chr, pos = 0)
{
	if (pos < 0)
		return -1;
	new
		cur_char;
	if (IS_PACKED_STRING(str)) {
		while ((cur_char = str{pos}) != '\0' && cur_char != chr) pos++;
	} else {
		while ((cur_char = str[pos]) != '\0' && cur_char != chr) pos++;
	}
	return pos;
}

stock find_first_of(const str[], const chrlist[], pos = 0, size = sizeof str)
{
	return find_first_chrlist(str, chrlist, true, pos, size);
}

stock find_first_not_of(const str[], const chrlist[], pos = 0,
	size = sizeof str)
{
	return find_first_chrlist(str, chrlist, false, pos, size);
}

stock find_last(const str[], const substr[], bool:ignorecase = false,
	end_offset = 0)
{
	new
		str_len = strlen(str),
		substr_len = strlen(substr),
		_pos,
		limit_pos = str_len - end_offset;
	for (; str_len >= 0; str_len -= substr_len + 1) {
		_pos = strfind(str, substr, ignorecase, str_len);
		if (_pos < 0)
			continue;
		if (_pos + substr_len <= limit_pos)
			break;
		_pos = -1;
	}

	return _pos;
}

stock find_last_char(const str[], const chr, end_offset = 0)
{
	new
		_pos = strlen(str) - end_offset;
	if (IS_PACKED_STRING(str)) {
		while (str{_pos} != chr && _pos > 0) _pos--;
	} else {
		while (str[_pos] != chr && _pos > 0) _pos--;
	}
	return _pos;
}

stock find_last_of(const str[], const chrlist[], end_offset = 0)
{
	return find_last_chrlist(str, chrlist, true, end_offset);
}

stock find_last_not_of(const str[], const chrlist[], end_offset = 0)
{
	return find_last_chrlist(str, chrlist, false, end_offset);
}

TDW_STATIC stock find_last_chrlist(const str[], const chrlist[], bool:is_equal,
	end_offset)
{
	new
		chr_pos,
		chrlist_len = strlen(chrlist),
		cur,
		_pos = strlen(str) - 1 - end_offset;
	if (IS_PACKED_STRING(str)) {
		if (IS_PACKED_STRING(chrlist)) {
			while ((cur = str{_pos}) && _pos != 0) {
				while (chr_pos <= chrlist_len && cur != chrlist{chr_pos++}) {}
				if (is_equal != (chr_pos > chrlist_len))
					break;
				chr_pos = 0;
				--_pos;
			}
		} else {
			while ((cur = str{_pos}) && _pos != 0) {
				while (chr_pos <= chrlist_len && cur != chrlist[chr_pos++]) {}
				if (is_equal != (chr_pos > chrlist_len))
					break;
				chr_pos = 0;
				--_pos;
			}
		}
	} else {
		if (IS_PACKED_STRING(chrlist)) {
			while (_pos > 0 && (cur = str[_pos])) {
				while (chr_pos <= chrlist_len && cur != chrlist{chr_pos++}) {}
				if (is_equal != (chr_pos > chrlist_len))
					break;
				chr_pos = 0;
				--_pos;
			}
		} else {
			while (_pos > 0 && (cur = str[_pos])) {
				while (chr_pos <= chrlist_len && cur != chrlist[chr_pos++]) {}
				if (is_equal != (chr_pos > chrlist_len))
					break;
				chr_pos = 0;
				--_pos;
			}
		}
	}
	return _pos;
}

TDW_STATIC stock find_first_chrlist(const str[], const chrlist[], bool:is_equal,
	pos, size)
{
	if (pos > size)
		return -1;
	new
		chr_pos,
		chrlist_len = strlen(chrlist),
		cur;
	if (IS_PACKED_STRING(str)) {
		if (IS_PACKED_STRING(chrlist)) {
			while ((cur = str{pos}) != '\0') {
				while (chr_pos <= chrlist_len && cur != chrlist{chr_pos++}) {}
				if (is_equal != (chr_pos > chrlist_len))
					break;
				chr_pos = 0;
				++pos;
			}
		} else {
			while ((cur = str{pos}) != '\0') {
				while (chr_pos <= chrlist_len && cur != chrlist[chr_pos++]) {}
				if (is_equal != (chr_pos > chrlist_len))
					break;
				chr_pos = 0;
				++pos;
			}
		}
	} else {
		if (IS_PACKED_STRING(chrlist)) {
			while ((cur = str[pos]) != '\0') {
				while (chr_pos <= chrlist_len && cur != chrlist{chr_pos++}) {}
				if (is_equal != (chr_pos > chrlist_len))
					break;
				chr_pos = 0;
				++pos;
			}
		} else {
			while ((cur = str[pos]) != '\0') {
				while (chr_pos <= chrlist_len && cur != chrlist[chr_pos++]) {}
				if (is_equal != (chr_pos > chrlist_len))
					break;
				chr_pos = 0;
				++pos;
			}
		}
	}
	return pos;
}

// ----------------------------------------------------------------------------
// Erase functions

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
		_pos;
	if ((_pos = find_last(str, substr, ignorecase, end_offset)) < 0)
		return -1;
	strdel(str, _pos, _pos + substr_len);
	return _pos;
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

// ----------------------------------------------------------------------------
// Trim functions

stock trim_left(str[], const delim = ' ', pos = 0)
{
	if (pos < 0)
		return 0;
	new
		chr_cur;
	if (IS_PACKED_STRING(str)) {
		while ((chr_cur = str{pos++}) != '\0' && chr_cur == delim) {}
	} else {
		while ((chr_cur = str[pos++]) != '\0' && chr_cur == delim) {}
	}

	return strdel(str, 0, --pos);
}

stock trim_right(str[], const delim = ' ', end_offset = 0)
{
	new
		len = strlen(str) - end_offset,
		cur_pos = len;
	if (IS_PACKED_STRING(str)) {
		while (cur_pos-- != 0 && str{cur_pos} == delim) {}
	} else {
		while (cur_pos-- != 0 && str[cur_pos] == delim) {}
	}

	return strdel(str, cur_pos + 1, len);
}

stock trim(str[], const delim = ' ')
{
	return
		trim_left(str, delim),
		trim_right(str, delim);
}

stock trim_leftex(str[], const delims[] = !" ", pos = 0)
{
	new
		str_len = strlen(str),
		delim_pos = find_first_not_of(str, delims, pos, str_len + 1);
	if (delim_pos >= 0)
		strmid(str, str, delim_pos, str_len, str_len + 1);
	return 0;
}

stock trim_rightex(str[], const delims[] = !" ", end_offset = 0)
{
	new
		str_len = strlen(str),
		end_pos = find_last_not_of(str, delims, end_offset);
	if (end_pos >= 0)
		strmid(str, str, end_pos - str_len, end_pos + 1, str_len + 1);
	return 0;
}

stock trim_ex(str[], const delims[] = !" ", pos = 0, end_offset = 0)
{
	return
		trim_leftex(str, delims, pos),
		trim_rightex(str, delims, end_offset);
}

// ----------------------------------------------------------------------------
// Replace functions

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
	bool:ignorecase = false, end_offset = 0, str_size = sizeof str)
{
	new pos;
	if ((pos = erase_last(str, substr, ignorecase, end_offset)) < 0)
		return 0;

	// We use a fixed strins because the original function doesn't work
	// correctly.
	strins(str, replace, pos, str_size);

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
			if ((str_len -= substr_len) + replace_len >= str_size)
				return 0;
			strdel(str, pos, pos + substr_len);
			// To optimize the function, we use a bad version of strins, because
			// we've already checked the str size.
			BAD_strins(str, replace, pos, str_size);
			// pos += replace_len;
			// str_len += replace_len;
			#emit load.s.alt replace_len

			#emit load.s.pri pos
			#emit add
			#emit stor.s.pri pos

			#emit load.s.pri str_len
			#emit add
			#emit stor.s.pri str_len
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
		if (IS_PACKED_STRING(str)) {
			str{pos} = replace;
		} else {
			str[pos] = replace;
		}
	}
	return pos;
}

stock replace_symbols(str[], const chr, const replace, pos = 0)
{
	if (IS_PACKED_STRING(str)) {
		while ((pos = find_first_char(str, chr, pos)) >= 0)
			str{pos} = replace;
	} else {
		while ((pos = find_first_char(str, chr, pos)) >= 0)
			str[pos] = replace;
	}
	return 1;
}

// ----------------------------------------------------------------------------
// Hashes

// FNV-1
stock fnv1_str(const string[], hash_val)
{
	new
		len = strlen(string);

	while (len-- != 0) {
		hash_val += (hash_val << 1) + (hash_val << 4) + (hash_val << 7) +
			(hash_val << 8) + (hash_val << 24);

		hash_val ^= string[len];
	}

	return hash_val;
}

// MurmurHash2
stock MurmurHash2(key[], len)
{
	const
		m = 0x5bd1e995,
		seed = 0,
		r = 24;

	new
		h = seed ^ len,
		k;

	while (len >= 4) {
		k  = key[0];
		k |= key[1] << 8;
		k |= key[2] << 16;
		k |= key[3] << 24;

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		// key += key (not value in the first cell)
		#emit load.s.pri key
		#emit add.c 4
		#emit stor.s.pri key

		len -= 4;
	}

	switch (len) {
		case 3:
			h ^= key[2] << 16;
		case 2:
			h ^= key[1] << 8;
		case 1:
			h ^= key[0],
			h *= m;
	}

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

#define TDW_STRING_DEFAULT_CHARLIST\
	"AaBb0CcDd1EeFf2GgHh3IiJj4KkLl5MmNn6OoPp7QqRr8SsTt9UuVvWwXxYyZz"

stock strgen(dest[], const charlist[] = TDW_STRING_DEFAULT_CHARLIST,
	bool:is_packed = false, charlist_size = sizeof charlist,
	dest_size = sizeof dest)
{
	new
		i;
	--charlist_size;
	if (is_packed) {
		dest_size *= 4;
		if (IS_PACKED_STRING(charlist)) {
			charlist_size *= 4;
			do {
				dest{i} = charlist{random(charlist_size) % dest_size};
			} while (++i < dest_size);
		} else {
			do {
				dest{i} = charlist[random(charlist_size) % dest_size];
			} while (++i < dest_size);
		}
	} else {
		if (IS_PACKED_STRING(charlist)) {
			charlist_size *= 4;
			do {
				dest[i] = charlist{random(charlist_size) % dest_size};
			} while (++i < dest_size);
		} else {
			do {
				dest[i] = charlist[random(charlist_size) % dest_size];
			} while (++i < dest_size);
		}
	}
	return 0;
}
