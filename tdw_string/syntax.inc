/** ======================================================================== **\
	New Syntax

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
#if defined _inc_syntax
	#undef _inc_syntax
#endif

#if defined _TDW_S_SYNTAX_INC_
	#endinput
#endif

#define _TDW_S_SYNTAX_INC_


#define O@tC: O@tCt:O@tCf:
#define O@T: O@tA:O@tF:O@tD:O@tC:O@tM:O@E:

#define O@tA:O@tF:O@tD:O@tC:O@tM:O@E:%1+%2$ strcat(%1,_:A@sM:A@sN:%2,)
#define A@sM:A@sN:%2[%3], %2,%3
#define A@sN:%2, %2

#define O@tF:O@tD:O@tC:O@tM:O@E:%1??%2$ strfind(_:F@pM:F@pN:%1,_:F@I:%2,)
#define F@pM:F@pN:%1[%3],%2, %1,%2,%3
#define F@pN:%1,%2, %1,%2,0
#define F@I: F@iV:F@iT:F@iF:
#define F@iV:F@iT:F@iF:%2!!%4, %2,%4,
#define F@iT:F@iF:%2!, %2,true,
#define F@iF:%2, %2,false,

#define O@tD:O@tC:O@tM:O@E:--%1$ strdel(_:D@pT0:D@pT1:D@pT2:D@pT3:D@pT4:%1,)
#define D@pT0:D@pT1:D@pT2:D@pT3:D@pT4:%1[%2,%3], %1,%2,%3
#define D@pT1:D@pT2:D@pT3:D@pT4:%1[,%3], %1,0,%3
#define D@pT2:D@pT3:D@pT4:%1[,], %1,0,sizeof %1
#define D@pT3:D@pT4:%1[%2,], %1,%2,sizeof %1
#define D@pT4:%1, %1,0,sizeof %1

#define O@tCt:O@tCf:O@tM:O@E:%1==%2$ (P@C:%1,%2$==0)
#define O@tCf:O@tM:O@E:%1!=%2$ (P@C:%1,%2$!=0)
#define P@C:%1,%2$ strcmp(%1,_:C@IP0:C@IP1:%2,)
#define C@IP0:C@IP1:%2!, C@I0:C@I1:%2,true,
#define C@IP1:%2, C@I0:C@I1:%2,false,
#define C@I0:C@I1:%2[%4],%3, %2,%3,%4
#define C@I1:%2,%3, %2,%3

#define O@E:%1=%2$ strcpy(%1,E@S0:E@S1:%2,)
#define E@S0:E@S1:%2[%3], %2,%3
#define E@S1:%2, %2

#define s<%1> (_:O@T:%1$)
