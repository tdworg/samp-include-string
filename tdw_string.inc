/** ======================================================================== **\
	String library

| Description:
This library exports several useful string functions that are not included in
the PAWN string library. Besides, it adds a new syntax.

| Version:
1.1.15

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
#if defined _inc_tdw_string
	#undef _inc_tdw_string
#endif

#if defined _TDW_STCOL__H
	#endinput
#endif

#define _TDW_STCOL__H

#include "tdw_string\string"
#include "tdw_string\find"
#include "tdw_string\replace"
#include "tdw_string\type"
#include "tdw_string\erase"
#include "tdw_string\trim"
