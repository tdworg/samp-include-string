/** ======================================================================== **\
	Depend Encoding

| Charset
	Cyrillic (Windows 1251)

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
#if defined _inc_depend_encoding
	#undef _inc_depend_encoding
#endif

#if defined _TDW_STLIB__DEPEND_ENCODING
	#endinput
#endif

#define _TDW_STLIB__DEPEND_ENCODING


static stock const
	string@rus[] = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäå¸æçèéêëìíîïğñòóôõö÷"\
		"øùüûúışÿ",
	string@arr_lat[][] = {
		"A",  "B",    "V", "G", "D", "E", "JO", "ZH", "Z", "I", "Y", "K",
		"L",  "M",    "N", "O", "P", "R", "S",  "T", "U", "F", "KH", "C",
		"CH", "SH", "SHH", "JHH", "IH", "JH", "EH", "JU", "JA",
		"a", "b", "v", "g", "d", "e", "e", "zh", "z", "i", "y", "k", "l", "m",
		"n", "o", "p", "r", "s", "t", "u", "f", "kh", "c", "ch", "sh", "shh",
		"jhh", "ih", "jh", "eh", "ju", "ja"
	};

stock
	strtrtrans(string[], string_size = sizeof string)
{
	new chr, i, pos;
	while ((chr = string[i]) != '\0')
	{
		if ((pos = find_char(string@rus, chr)) != -1)
		{
			strdel(string, i, i + 1);
			strins(string, string@arr_lat[pos], i, string_size);
		}
		i++;
	}
	return 0;
}
