/** ======================================================================== **\
	String

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
#if defined _inc_string
	#undef _inc_string
#endif

#if defined _TDW_STLIB__STRING
	#endinput
#endif

#define _TDW_STLIB__STRING


// Checks if a string is packed.
// Other information: //www.compuphase.com/pawn/String_Manipulation.pdf
// Author: Untonyst.
#if !defined IsPackedString
	#define IsPackedString%0(%1) ((%1){0} != 0)
#endif


#include <tdw_string/utils/pawn_emit_fix>
#include <tdw_string/utils/iscasepart>
#include <tdw_string/utils/percent_case>
#include <tdw_string/utils/topartcase>


// Note: This function does not delete all characters. If you want to remove
// all characters you need to use the memset function.
stock
	strclear(string[])
{
	return (IsPackedString(string) ? (string{0} = '\0') : (string[0] = '\0'));
}


stock
	strcpy(dest[], const string[], dest_size = sizeof dest)
{
	return
		strclear(dest), strcat(dest, string, dest_size);
}


stock
	IsEmptyString(const string[])
{
	return (IsPackedString(string) ? (string{0}) : (string[0])) == '\0';
}


stock
	memcmp(const string1[], const string2[], n = cellmax,
		size_1 = sizeof string1, size_2 = sizeof string2)
{
	if (IsEmptyString(string1))
		return -1;
	if (IsEmptyString(string2))
		return -1;
	if (n == cellmax)
		n = size_1 > size_2 ? size_1 : size_2;
	// Converts the value to bytes.
	#emit load.s.pri n // pri = n
	#emit shl.c.pri 2 // pri <<= 2
	#emit stor.s.pri n // n = pri
	// Addresses..
	#emit load.s.pri string1 // pri = string1
	#emit load.s.alt string2 // alt = string2
	// Compare the memory blocks
	#emit cmps n
	// Returns zero if the blocks are equal.
	#emit retn
	return 0;
}


stock
	strcount(const string[], const find[], bool:ignorecase = false, pos = 0,
		string_size = sizeof string)
{
	if (pos >= string_size)
		return 0;
	new found_pos = pos, count, find_size = strlen(find);
	while ((found_pos = strfind(string, find, ignorecase,
		found_pos)) != -1
	)
	{
		count++;
		found_pos += find_size;
	}
	return count;
}


stock
	strreverse(string[])
{
	new i, len = strlen(string), j = len - 1, chr;
	if (IsPackedString(string))
	{
		do
		{
			chr = string{i};
			string{i++} = string{j};
			string{j--} = chr;
		}
		while (i < j);
	}
	else
	{
		do
		{
			chr = string[i];
			string[i++] = string[j];
			string[j--] = chr;
		}
		while (i < j);
	}
	return 0;
}


stock
	strcatex(dest[], size, const ...)
{
	new num_args;

	const BYTES_PER_CELL = cellbits / charbits;

	// Get the number of arguments
	#emit load.s.pri 0x8
	// Subtract one argument.
	#emit const.alt BYTES_PER_CELL // 1 * 4 = 4
	#emit sub
	#emit stor.s.pri num_args

	if (num_args == 0)
		return 0;

	new darg_start, darg_end, ret, push_items_bytes;

	// Get the address of start of the dynamic arguments
	#emit const.alt size
	#emit lctrl 5
	#emit add
	#emit stor.s.pri darg_start

	// Get the address of end of the dynamic arguments
	#emit load.s.alt num_args
	#emit add
	#emit stor.s.pri darg_end

	darg_start += BYTES_PER_CELL;

	do
	{
		#emit push.s size

		#emit load.s.pri darg_start
		#emit load.i
		#emit push.pri

		#emit push.s dest
		#emit push.c 12
		#emit sysreq.c strcat

		#emit load.s.alt ret
		#emit add
		#emit stor.s.pri ret

		darg_start += BYTES_PER_CELL;
		push_items_bytes += 16;
	}
	while (darg_start < darg_end);

	// Restore the stack
	#emit lctrl 4
	#emit load.s.alt push_items_bytes
	#emit add
	#emit sctrl 4

	return ret;
}


enum
	E_TDW_FILL_TYPE (<<= 1)
{
	FILL_TYPE_LEFT = 1,
	FILL_TYPE_RIGHT,
	FILL_TYPE_BOTH = FILL_TYPE_LEFT | FILL_TYPE_RIGHT
};

stock
	strfill(string[], const pattern[] = " ", fill_length,
		E_TDW_FILL_TYPE:type = FILL_TYPE_BOTH, size = sizeof string)
{
	if (fill_length >= size)
		return 0;

	new pattern_len = strlen(pattern),
		string_len = strlen(string),
		left_part_len,
		right_part_len,
		string_pos;

	if (type & FILL_TYPE_BOTH)
	{
		left_part_len = right_part_len = fill_length;
	}
	else
	{
		left_part_len = fill_length / 2;
		right_part_len = fill_length - left_part_len;
	}

	if (type & FILL_TYPE_LEFT)
	{
		// get a specific length of the parts.
		left_part_len *= pattern_len;

		// strins doesn't support the maxlength.
		if (left_part_len > size)
			return 0;

		do
		{
			strins(string, pattern, string_pos, size);
			string_pos += pattern_len;
		}
		while (string_pos < left_part_len);
	}

	if (type & FILL_TYPE_RIGHT)
	{
		// get a specific length of the parts.
		right_part_len *= pattern_len;

		// Go to the index after the string.
		right_part_len += (string_pos += string_len);

		do
		{
			strcat(string, pattern, size);
			string_pos += pattern_len;
		}
		while (string_pos < right_part_len);
	}

	return 1;
}


stock
	strimplode(dest[], const arrays[][], const delimiter[] = !" ",
		array_items = sizeof arrays, dest_size = sizeof dest)
{
	new current_index_item;

	dset[0] = '\0';

	while (current_index_item < array_items)
	{
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


stock
	strexplode(arrays[][], const string[], const delimiter[] = !" ",
		array_items = sizeof arrays, array_item_size = sizeof arrays[])
{
	new start_pos, end_pos, current_index_item;

	while (current_index_item < array_items)
	{
		end_pos = strfind(string, delimiter, false, start_pos);

		if (end_pos == -1)
			end_pos = array_item_size;

		strmid(arrays[current_index_item], string, start_pos, end_pos,
			array_item_size
		);

		if (end_pos == -1)
			break;

		start_pos = end_pos + 1;
		current_index_item++;
	}
	return current_index_item;
}


stock
	strimplodeex(dest[], const delimiter[] = !" ",
		dest_size = sizeof dest, const ...)
{
	new num_args;

	const BYTES_PER_CELL = cellbits / charbits;

	#emit load.s.pri 0x8
	#emit const.alt 12 // 3 * 4 = 12
	#emit sub
	#emit stor.s.pri num_args

	if (num_args == 0)
		return 0;

	dest[0] = '\0';

	new darg_start, darg_end, push_items_bytes, ret;

	// Get the address of start of the dynamic arguments
	#emit const.alt dest_size
	#emit lctrl 5
	#emit add
	#emit stor.s.pri darg_start

	// Get the address of end of the dynamic arguments
	#emit load.s.alt num_args
	#emit add
	#emit stor.s.pri darg_end

	darg_start += BYTES_PER_CELL;

	do
	{
		#emit push.s dest_size

		#emit load.s.pri darg_start
		#emit load.i
		#emit push.pri

		#emit push.s dest
		#emit push.c 12
		#emit sysreq.c strcat

		#emit load.s.alt ret
		#emit add
		#emit stor.s.pri ret

		// Don't insert a delimiter.
		if (darg_start == darg_end)
			break;

		strcat(dest, delimiter, dest_size);

		darg_start += BYTES_PER_CELL;
		push_items_bytes += 16;
	}
	while (darg_start < darg_end);

	// Restore the stack
	#emit lctrl 4
	#emit load.s.alt push_items_bytes
	#emit add
	#emit sctrl 4

	return ret;
}


stock
	IsEqual(const string1[], const string2[], bool:ignorecase = false)
{
	return
		string1[0] == '\0' || string2[0] == '\0' ?
		false : (strcmp(string1, string2, ignorecase) == 0);
}



#define TDW_STRING_DEFAULT_CHARLIST\
	"AaBb0CcDd1EeFf2GgHh3IiJj4KkLl5MmNn6OoPp7QqRr8SsTt9UuVvWwXxYyZz"


stock
	GenerateString(dest[], const charlist[] = TDW_STRING_DEFAULT_CHARLIST,
		charlist_size = sizeof charlist, dest_size = sizeof dest)
{
	new i;
	--charlist_size;
	do {
		dest[i] = charlist[random(charlist_size) % dest_size];
	} while (++i < dest_size);
	return;
}


stock
	strsplit(dest[], const string[], &index, const seperator = ' ')
{
	new chr, i;
	if (IsPackedString(string))
	{
		if (index)
		{
			if (string{index} != '\0')
				++index;
		}
		while ((chr = string{index}) != '\0' && chr != seperator)
		{
			switch (chr)
			{
				case '\0', '\n', '\r':
					break;
				default:
				{
					dest{i++} = chr;
					++index;
				}
			}
		}
	}
	else
	{
		if (index)
		{
			if (string[index] != '\0')
				++index;
		}
		while ((chr = string[index]) != '\0' && chr != seperator)
		{
			switch (chr)
			{
				case '\0', '\n', '\r':
					break;
				default:
				{
					dest[i++] = chr;
					++index;
				}
			}
		}
	}
	return dest[i] = '\0';
}


// Author of the first implementation is VVWVV.
// Author: ziggi.
stock
	ucfirst(string[])
{
	const
		FIRST_UPPER_SYMBOL = 224,
		LAST_UPPER_SYMBOL = 225,
		EXTRA_UPPER_SYMBOL = 184,

		FIRST_LOWER_SYMBOL = 192,
		LAST_LOWER_SYMBOL = 223,
		EXTRA_LOWER_SYMBOL = 168,

		DIFF_SYMBOL = FIRST_UPPER_SYMBOL - FIRST_LOWER_SYMBOL,
		DIFF_EXTRA = EXTRA_UPPER_SYMBOL - EXTRA_LOWER_SYMBOL;

	new i = strlen(string);
	if (string{0} != 0)
	{
		switch (string{0})
		{
			case 'a'..'z', FIRST_LOWER_SYMBOL..LAST_LOWER_SYMBOL:
			{
				string{0} -= DIFF_SYMBOL;
			}
			case EXTRA_LOWER_SYMBOL:
			{
				string{0} -= DIFF_EXTRA;
			}
		}
		do
		{
			switch (string{i})
			{
				case 'A'..'Z', FIRST_UPPER_SYMBOL..LAST_UPPER_SYMBOL:
				{
					string{i} += DIFF_SYMBOL;
				}
				case EXTRA_UPPER_SYMBOL:
				{
					string{i} += DIFF_EXTRA;
				}
			}
		}
		while (--i != 0);
	}
	else
	{
		switch (string[0])
		{
			case 'a'..'z', FIRST_LOWER_SYMBOL..LAST_LOWER_SYMBOL:
			{
				string[0] -= DIFF_SYMBOL;
			}
			case 168:
			{
				string[0] -= DIFF_EXTRA;
			}
		}
		do
		{
			switch (string[i])
			{
				case 'A'..'Z', FIRST_UPPER_SYMBOL..LAST_UPPER_SYMBOL:
				{
					string[i] += DIFF_SYMBOL;
				}
				case EXTRA_UPPER_SYMBOL:
				{
					string[i] += DIFF_EXTRA;
				}
			}
		}
		while (--i != 0);
	}
}


stock
	isNumeric(const string[])
{
	new i, c;
	if (IsPackedString(string))
	{
		while ((c = string{i++}) != '\0')
		{
			switch (c)
			{
				case '0'..'9':
					continue;
				case '.', '+', '-':
					continue;
				default:
					return 0;
			}
		}
	}
	else
	{
		while ((c = string[i++]) != '\0')
		{
			switch (c)
			{
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


stock
	strswh(const source[], bool:ignorecase = false, length = cellmax, const ...)
{
	new
		n_args,
		darg_start,
		darg_end, tmp;
	// Get the number of arguments.
	#emit load.s.pri 0x8
	#emit const.alt 12 // 3 * 4 = 12
	#emit sub
	#emit stor.s.pri n_args
	// Get the address of first parameter.
	#emit lctrl 5
	#emit const.alt length
	#emit add
	#emit stor.s.pri darg_start
	// Get the adress of the last parameter.
	#emit load.s.alt n_args
	#emit add
	#emit stor.s.pri darg_end

	goto _init;
_strcmp_return_true:
	// return the argument.
	#emit load.s.alt darg_end
	#emit load.s.pri darg_start
	#emit sub.alt
	#emit shr.c.pri 2
	#emit stack 16
	#emit retn
_init:
	// At each iteration we are compare two strings.
	do
	{
		// Push the other arguments into 'strcmp'.
		#emit push.s length
		#emit push.s ignorecase
		// Load the parameter address
		#emit load.s.pri darg_end
		#emit load.i
		// Push it onto stack
		#emit push.pri
		// Save the value.
		#emit load.i
		#emit move.alt
		#emit const.pri 0xff
		#emit and
		#emit stor.s.pri tmp
		// Workaround strcmp bug with empty strings.
		if (tmp == '\0')
		{
			// Restore the stack.
			#emit stack 12
			// Go to the next iteration.
			goto _next;
		}
		{} // Zero...
		#emit push.s source
		// Push the number of arguments (in bytes).
		#emit push.c 16
		// Call the function.
		#emit sysreq.c strcmp
		// Restore the stack.
		#emit stack 20
		// If the value in PRI is equal to zero.
		#emit jzer _strcmp_return_true
	_next:
		darg_end -= 4;
	}
	while (darg_end > darg_start);
	// If the argument was not found, return -1.
	return -1;
}


stock
	strAfter(string[], const pattern[] = !" = ", bool:ignorecase = false,
		pos = 0, size_string = sizeof string)
{
	new
		string_len = strlen(string),
		pattern_len = strlen(pattern);
	return
		strmid(string, string,
			strfind(string, pattern, ignorecase, pos) + pattern_len, string_len,
			size_string
		);
}


stock
	strBefore(string[],  const pattern[] = !" = ", bool:ignorecase = false,
		pos = 0, size_string = sizeof string)
{
	return
		strmid(string, string,
			0, strfind(string, pattern, ignorecase, pos) - 1,
			size_string
		);
}
