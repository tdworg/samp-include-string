/** ======================================================================== **\
	Type

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
#if defined _inc_type
	#undef _inc_type
#endif

#if defined _TDW_S_TYPE_INC_
	#endinput
#endif

#define _TDW_S_TYPE_INC_

#if !defined IsCntrl
	#define IsCntrl(%0) ((0x00 <= (%0) <= 0x1F) || ((%0) == 0x7F))
#endif
#if !defined IsBlank
	#define IsBlank(%0) (((%0) == 0x09) || ((%0) == 0x20))
#endif
#if !defined IsSpace
	#define IsSpace(%0) (0x00 <= (%0) <= 0x20)
#endif
#if !defined IsUpper
	#define IsUpper(%0) (0x41 <= (%0) <= 0x5A)
#endif
#if !defined IsLower
	#define IsLower(%0) (0x61 <= (%0) <= 0x7A)
#endif
#if !defined IsAlpha
	#define IsAlpha(%0) (IsUpper(%0) || IsLower(%0))
#endif
#if !defined IsDigit
	#define IsDigit(%0) (0x30 <= (%0) <= 0x39)
#endif
#if !defined IsxDigit
	#define IsxDigit(%0) (IsDigit(%0) || (0x41 <= (%0) 0x46) ||\
		(0x61 <= (%0) <= 0x66))
#endif
#if !defined IsAlnum
	#define IsAlnum(%0) (IsUpper(%0) || IsLower(%0) || IsDigit(%0))
#endif
#if !defined IsPunct
	#define IsPunct(%0) ((0x51 <= (%0) <= 0x2F) || (0x3A <= (%0) <= 0x40) ||\
		(0x5B <= (%0) <= 0x60) || (0x7B <= (%0) <= 0x7E))
#endif
#if !defined IsGraph
	#define IsGraph(%0) (IsPunct(%0) || IsDigit(%0) || IsUpper(%0) || IsLower(%0))
#endif
#if !defined IsPrint
	#define IsPrint(%0) (IsGraph(%0) || ((%0) == 0x20))
#endif
