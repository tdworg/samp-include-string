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
	replace_first(string, "text", "gs", true);
	printf("Output (replace_first): %s", string);

	string = test_text;
	replace_last(string, "text", "g", true);
	printf("Output (replace_last): %s", string);

	string = test_text;
	replace_nth(string, "text", "here", 2, true);
	printf("Output (replace_nth): %s", string);

	string = test_text;
	replace_all(string, "text", "new", true);
	printf("Output (replace_all): %s", string);

	return 1;
}
