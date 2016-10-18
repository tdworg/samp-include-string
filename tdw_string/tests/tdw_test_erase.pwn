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

#include <a_samp>
#include <tdw_string>

public OnFilterScriptInit()
{
	static const test_text[] = "Text, text, and text";
	new string[sizeof test_text];

	string = test_text;
	erase_first(string, "text", true);
	printf("Output (erase_first): %s", string);

	string = test_text;
	erase_last(string, "text", true);
	printf("Output (erase_last): %s", string);

	string = test_text;
	erase_nth(string, "text", 2, true);
	printf("Output (erase_nth): %s", string);

	string = test_text;
	erase(string, 2, 9);
	printf("Output (erase): %s", string);

	return 1;
}
