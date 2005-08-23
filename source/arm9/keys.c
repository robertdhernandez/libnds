/*---------------------------------------------------------------------------------
	$Id: keys.c,v 1.6 2005-08-23 17:06:10 wntrmute Exp $

	key input code -- provides slightly higher level input forming

	Copyright (C) 2005
			Christian Auby (DesktopMan)
			Dave Murphy (WinterMute)

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any
	damages arising from the use of this software.

	Permission is granted to anyone to use this software for any
	purpose, including commercial applications, and to alter it and
	redistribute it freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you
		must not claim that you wrote the original software. If you use
		this software in a product, an acknowledgment in the product
		documentation would be appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and
		must not be misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source
		distribution.

	$Log: not supported by cvs2svn $
	Revision 1.5  2005/08/03 18:07:55  wntrmute
	don't use nds.h
	
	Revision 1.4  2005/07/25 02:31:07  wntrmute
	made local variables static
	added proper header to keys.h
	
	Revision 1.3  2005/07/25 02:19:01  desktopman
	Added support for KEY_LID in keys.c.
	Moved KEYS_CUR from header to source file.
	Changed from the custom abs() to stdlib.h's abs().
	
	Revision 1.2  2005/07/14 08:00:57  wntrmute
	resynchronise with ndslib
	

---------------------------------------------------------------------------------*/

#include <stdlib.h>

#include <nds/ipc.h>
#include <nds/system.h>
#include <nds/arm9/input.h>

#define KEYS_CUR (( ((~KEYS)&0x3ff) | (((~IPC->buttons)&3)<<10) | (((~IPC->buttons)<<6) & (KEY_TOUCH|KEY_LID) ))^KEY_LID)

static u16 keys=0;
static u16 keysold=0;

static u16 oldx=0;
static u16 oldy=0;

//---------------------------------------------------------------------------------
void keysInit() {
//---------------------------------------------------------------------------------
	keys=0;
	keysold=0;
}

//---------------------------------------------------------------------------------
void scanKeys() {
//---------------------------------------------------------------------------------
	keysold=keys;
	keys=KEYS_CUR;

	if(abs(IPC->touchXpx - oldx)>20 || abs(IPC->touchYpx - oldy)>20)
		keys&=~KEY_TOUCH;

	oldx=IPC->touchXpx;
	oldy=IPC->touchYpx;
	
}

//---------------------------------------------------------------------------------
u32 keysHeld() {
//---------------------------------------------------------------------------------
	return keys;
}

//---------------------------------------------------------------------------------
u32 keysDown() {
//---------------------------------------------------------------------------------
	return (keys^keysold)&keys;
}

//---------------------------------------------------------------------------------
u32 keysUp() {
//---------------------------------------------------------------------------------
	return (keys^keysold)&(~keys);
}
