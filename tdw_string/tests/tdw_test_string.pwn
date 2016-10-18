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
	//
	// Function: IsPackedString
	//
	new test_packed_string[] = "Name";
	printf("Output (IsPackedString): %d", IsPackedString(test_packed_string));

	//
	// Function: strcpy
	//
	static const
		test_string@1[] = "First",
		test_string@2[] = "Second";
	printf("| Output (String1): %s and (String2): %s", test_string@1,
		test_string@2
	);
	// Calculate the size of the string.
	const
		size_1 = sizeof test_string@1,
		size_2 = sizeof test_string@2;
	#if size_1 > size_2
		const size = size_1;
	#else
		const size = size_2;
	#endif
	// Create a buffer for the string.
	new buffer[size];
	buffer = test_string@1;
	strcpy(buffer, test_string@2);
	printf("| 2. Output (String1): %s -> (String1): %s", test_string@1, buffer);

	//
	// Function: IsEmptyString
	//
	new empty_string[2];
	printf("Output (IsEmptyString): %d", IsEmptyString(empty_string));

	//
	// Function: memcmp
	//
	static const
		test_string@3[] = "First";
	printf("Output (memcmp): %d",
		memcmp(test_string@1, test_string@2, 2)
	);
	printf("Output (memcmp): %d",
		memcmp(test_string@1, test_string@3, 2)
	);

	//
	// Function: strcount
	//
	static const test[] = "text-text-text-text-TEXXT, lol";
	printf("Output (strcount): %d",
		strcount(test, "text", true)
	);

	//
	// Function: strreverse
	//
	new buffer@0[] = "text-text-text-text-TEXXT, lol";
	strreverse(buffer@0);
	printf("Output (strreverse): %s", buffer@0);

	//
	// Function: strparttoupper
	//
	new buffer_t[] = "this is text";

	strparttoupper(buffer_t, 5, 7);
	printf("Output (strparttoupper): %s", buffer_t);
	printf("Output (countofuppercase): %d", countofuppercase(buffer_t));


	// Function: strparttolower
	strparttolower(buffer_t, 5, 7);
	printf("Output (strparttolower): %s", buffer_t);
	printf("Output (countoflowpercase): %d", countoflowpercase(buffer_t));


	return 1;
}
