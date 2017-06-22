#include <a_samp>

#define TDW_STRING_JIT_COMPAT
#include "tdw_string\tdw_string.inc"

main()
{
	// Memory functions
	{
		static const
			str1[] = "Test1",
			str2[] = "Test2";
		new buffer[100];
		printf("memcmp %d", memcmp(str1, str2, sizeof str1));
		memmove(buffer, str1, sizeof str1);
		printf("memove %s", buffer);
		memset(buffer, 0, sizeof str1);
		printf("memset %s", buffer);
	}
	// Find functions
	{
		static const
			str_to_find[] = "There is a book";
		printf("find_first %d",        find_first(str_to_find, "is"));
		printf("find_first_char %d",   find_first_char(str_to_find, 'i'));
		printf("find_first_of %d",     find_first_of(str_to_find, "iab"));
		printf("find_first_not_of %d", find_first_not_of(str_to_find, "Ther "));
		printf("find_last %d",         find_last(str_to_find, "is"));
		printf("find_last_char %d",    find_last_char(str_to_find, 'i'));
		printf("find_last_of %d",      find_last_of(str_to_find, "iab"));
		printf("find_last_not_of %d",  find_last_not_of(str_to_find, "Ther "));
	}
	// Erase functions
	{
		new buffer2[] = "Read and and write";
		erase_first(buffer2, "Read");
		printf("erase_first: %s", buffer2);
		erase_last(buffer2, "write");
		printf("erase_last: %s", buffer2);
		erase_nth(buffer2, "and", 1);
		printf("erase_nth: %s", buffer2);
	// Trim functions
		trim_left(buffer2);
		printf("trim_left: %s", buffer2);
		trim_right(buffer2);
		printf("trim_right: %s", buffer2);
		trim(buffer2);
		printf("trim: %s", buffer2);
		new buffer3[] = "-=-= And create something -=-=";
		trim_leftex(buffer3, " -=");
		printf("trim_leftex: %s", buffer3);
		trim_rightex(buffer3, " -=");
		printf("trim_rightex: %s", buffer3);
		new buffer4[] = "-=-= And create something -=-=";
		trim_ex(buffer4, " -=");
		printf("trimex: %s", buffer4);
	}
	// Replace functions
	{
		new buffer5[] = "And create ssssssomething, and and and and";
		replace_first(buffer5, "and", "Or", true);
		printf("replace_first: %s", buffer5);
		replace_last(buffer5, "and", "Or", true);
		printf("replace_last: %s", buffer5);
		replace_nth(buffer5, "and", "--", 1);
		printf("replace_nth: %s", buffer5);
		replace_all(buffer5, "and", "!!");
		printf("replace_all: %s", buffer5);
		replace_symbol(buffer5, 'c', 'C');
		printf("replace_symbol: %s", buffer5);
	}
	// Hashes
	{
		new buffer6[10];
		printf("fnv1_str %d", fnv1_str("Hello world", 123));
		printf("MurmurHash2 %d", MurmurHash2("Hello world", 11));
		strgen(buffer6);
		printf("strgen %s", buffer6);
	}
	// levenshtein
	{
		new bufferstr[60];
		static const str1[] = "Hello there";
		static const str2[] = "Hello tttthere";
		printf("_levenshtein: %d", _levenshtein(bufferstr, str1, str2));
		printf("levenshtein: %d", levenshtein(str1, str2));
	}
}
