#include <a_samp>

#include <string\tdw_string>
#include <string\tdw_istring>
#include <string\tdw_tstring>

public OnFilterScriptInit()
{
	new buffer[10];

	print(!"\n=============== [ IS* FUNCTIONS ] ===============");
	printf("isempty(buffer) %d"  , isempty(buffer));
	printf("isnum(\"123456\") %d", isnum("123456"));

	print(!"\n=============== [ STR* FUNCTIONS ] ===============");
	strcpy(buffer, "Local");
	printf("strcpy(buffer, \"Local\") now buffer stores `%s`;", buffer);
	strrev(buffer);
	printf("strrev(buffer) now buffer stores `%s`;", buffer);
	printf("strcnt(buffer, \"l\", .ignorecase=true) returns %d;", strcnt(buffer, "l", .ignorecase = true));
	printf("strchr(buffer, 'a') returns %d;", strchr(buffer, 'a'));
	printf("strspn(buffer, \"abc\") returns %d", strspn(buffer, "abc"));
	strclr(buffer);
	printf("strclr(buffer) now buffer stores `%s` - nothing;", buffer);

	new String:abc1("This thing is important");
	new String:abc2("This thing is important");
	printf("istring_get_capacity(abc1) returns %d", istring_get_capacity(abc1));
	printf("istring_get_size(abc1) returns %d", istring_get_size(abc1));

	if (abc1 == abc2)
		printf("abc1 == abc2");
}

