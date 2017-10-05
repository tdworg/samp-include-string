/*
 * TDW Type
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

#if defined _TDW_TSTRING_INC_
	#endinput
#endif
#define _TDW_TSTRING_INC_

#define iscntrl(%0) ((0x00 <= (%0) < 0x20) || ((%0) == 0x7f))
#define isblank(%0) (((%0) == 0x09) || ((%0) == 0x20))
#define isspace(%0) (0x09 <= (%0) <= 0x20)
#define isupper(%0) (0x41 <= (%0) <= 0x5a)
#define islower(%0) (0x61 <= (%0) <= 0x7a)
#define isalpha(%0) (isupper(%0) || islower(%0))
#define isdigit(%0) (0x30 <= (%0) <= 0x39)
#define isxdigit(%0) (isdigit(%0) || (0x41 <= (%0) <= 0x46) || (0x61 <= (%0) <= 0x66))
#define isalnum(%0) (isdigit(%0) || isalpha(%0))
#define ispunct(%0) ((0x21 <= (%0) <= 0x2f) || (0x3a <= (%0) <= 0x40) || (0x5b <= (%0) <= 0x60) || (0x7b <= (%0) <= 0x7e))
#define isgraph(%0) (0x21 <= (%0) <= 0x7e)
#define isprint(%0) (0x20 <= (%0) <= 0x7e)
