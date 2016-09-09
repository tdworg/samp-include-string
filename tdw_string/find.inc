/** ======================================================================== **\
	Find

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
#if defined _inc_find
	#undef _inc_find
#endif

#if defined _TDW_S_FIND_INC_
	#endinput
#endif

#define _TDW_S_FIND_INC_


stock
	find_first(const string[], const find[], bool:ignorecase = false, pos = 0)
{
	return strfind(string, find, ignorecase, pos);
}


stock
	find_last(const string[], const find[], bool:ignorecase = false)
{
	new string_len = strlen(string), find_len = strlen(find), pos;
	while (string_len > 0)
	{
		if ((pos = strfind(string, find, ignorecase,
			string_len -= find_len)) == -1)
			continue;
		return pos;
	}
	return 0;
}


stock
	find_first_of(const string[], const charlist[])
{
	new pos_string, pos_charlist, chr, charlist_len = strlen(charlist);
	if (IsPackedString(string))
	{
		if (IsPackedString(charlist))
		{
			while ((chr = string{pos_string}) != '\0')
			{
				do
				{
					if (chr != charlist{pos_charlist})
						continue;
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				pos_charlist = 0;
				pos_string++;
			}
		}
		else
		{
			while ((chr = string{pos_string}) != '\0')
			{
				do
				{
					if (chr != charlist[pos_charlist])
						continue;
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				pos_charlist = 0;
				pos_string++;
			}
		}
	}
	else
	{
		if (IsPackedString(charlist))
		{
			while ((chr = string[pos_string]) != '\0')
			{
				do
				{
					if (chr != charlist{pos_charlist})
						continue;
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				pos_charlist = 0;
				pos_string++;
			}
		}
		else
		{
			while ((chr = string[pos_string]) != '\0')
			{
				do
				{
					if (chr != charlist[pos_charlist])
						continue;
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				pos_charlist = 0;
				pos_string++;
			}
		}
	}
	return -1;
}


stock
	find_last_of(const string[], const charlist[])
{
	new pos_string = strlen(string), pos_charlist,
		charlist_len = strlen(charlist);
	if (IsPackedString(string))
	{
		if (IsPackedString(charlist))
		{
			while (pos_string-- != 0)
			{
				do
				{
					if (string{pos_string} != charlist{pos_charlist})
						continue;
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				pos_charlist = 0;
			}
		}
		else
		{
			while (pos_string-- != 0)
			{
				do
				{
					if (string{pos_string} != charlist[pos_charlist])
						continue;
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				pos_charlist = 0;
			}
		}
	}
	else
	{
		if (IsPackedString(charlist))
		{
			while (pos_string-- != 0)
			{
				do
				{
					if (string[pos_string] != charlist{pos_charlist})
						continue;
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				pos_charlist = 0;
			}
		}
		else
		{
			while (pos_string-- != 0)
			{
				do
				{
					if (string[pos_string] != charlist[pos_charlist])
						continue;
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				pos_charlist = 0;
			}
		}
	}
	return -1;
}


stock
	find_first_not_of(const string[], const charlist[])
{
	new pos_string, pos_charlist, chr, charlist_len = strlen(charlist);
	if (IsPackedString(string))
	{
		if (IsPackedString(charlist))
		{
			while ((chr = string{pos_string++}) != '\0')
			{
				do
				{
					if (chr == charlist{pos_charlist})
					{
						pos_charlist = 0;
						break;
					}
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				if (pos_charlist != 0)
					return pos_string - 1;
			}
		}
		else
		{
			while ((chr = string{pos_string++}) != '\0')
			{
				do
				{
					if (chr == charlist[pos_charlist])
					{
						pos_charlist = 0;
						break;
					}
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				if (pos_charlist != 0)
					return pos_string - 1;
			}
		}
	}
	else
	{
		if (IsPackedString(charlist))
		{
			while ((chr = string[pos_string++]) != '\0')
			{
				do
				{
					if (chr == charlist{pos_charlist})
					{
						pos_charlist = 0;
						break;
					}
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				if (pos_charlist != 0)
					return pos_string - 1;
			}
		}
		else
		{
			while ((chr = string[pos_string++]) != '\0')
			{
				do
				{
					if (chr == charlist[pos_charlist])
					{
						pos_charlist = 0;
						break;
					}
					return pos_string - 1;
				}
				while (++pos_charlist <= charlist_len);
				if (pos_charlist != 0)
					return pos_string - 1;
			}
		}
	}
	return -1;
}


stock
	find_last_not_of(const string[], const charlist[])
{
	new pos_string = strlen(string), pos_charlist, chr,
		charlist_len = strlen(charlist);
	if (IsPackedString(string))
	{
		if (IsPackedString(charlist))
		{
			while (pos_string-- != 0)
			{
				chr = string{pos_string};
				do
				{
					if (chr == charlist{pos_charlist})
					{
						pos_charlist = 0;
						break;
					}
				}
				while (++pos_charlist <= charlist_len);
				if (pos_charlist != 0)
					return pos_string;
			}
		}
		else
		{
			while (pos_string-- != 0)
			{
				chr = string{pos_string};
				do
				{
					if (chr == charlist[pos_charlist])
					{
						pos_charlist = 0;
						break;
					}
				}
				while (++pos_charlist <= charlist_len);
				if (pos_charlist != 0)
					return pos_string;
			}
		}
	}
	else
	{
		if (IsPackedString(charlist))
		{
			while (pos_string-- != 0)
			{
				chr = string[pos_string];
				do
				{
					if (chr == charlist{pos_charlist})
					{
						pos_charlist = 0;
						break;
					}
				}
				while (++pos_charlist <= charlist_len);
				if (pos_charlist != 0)
					return pos_string;
			}
		}
		else
		{
			while (pos_string-- != 0)
			{
				chr = string[pos_string];
				do
				{
					if (chr == charlist[pos_charlist])
					{
						pos_charlist = 0;
						break;
					}
				}
				while (++pos_charlist <= charlist_len);
				if (pos_charlist != 0)
					return pos_string;
			}
		}
	}
	return -1;
}
