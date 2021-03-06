/*
	logoview - Logoviewer for Coolstream

	Copyright (C) 2011-2016 Michael Liebmann

	License: GPL

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	General Public License for more details.

	You should have received a copy of the GNU General Public
	License along with this program; if not, write to the
	Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
	Boston, MA  02110-1301, USA.
*/

#ifndef __logoview_h__
#define __logoview_h__

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <string.h>
#include <string>

//#define LV_DEBUG

class CLogoView
{
	public:
		static CLogoView* getInstance();
		CLogoView();
		~CLogoView();
		int run(int argc, char *argv[]);
		void ClearThis(bool ClearDisplay=true);
		void PrintHelp();
		enum
			{
				EMPTY      = 0,
				SIGHANDLER = 1,
				TIMEOUT    = 2,
				FLAGFILE   = 3
			};
		int doneMode;

	private:
		unsigned char *lfb, *PicBuf, *TmpBuf, *ScBuf;
		struct fb_fix_screeninfo fix_screeninfo;
		struct fb_var_screeninfo var_screeninfo;
		int stride;
		std::string nomem, start_logo;
		unsigned int screen_StartX, screen_StartY, screen_EndX, screen_EndY;
		int screen_preset, fb;
		time_t timeout;
		bool clearScreen, onlyClearScreen, background;

		bool CheckFile(std::string datei);
		bool ReadConfig();
		unsigned char * Resize(unsigned char *orgin, int ox, int oy, int dx, int dy, bool alpha);
		void SetScreenBuf(unsigned char *buf, int r, int g, int b, int t);
		void blitPicture(void *fbbuff, uint32_t width, uint32_t height, uint32_t xoff, uint32_t yoff, uint32_t xp, uint32_t yp);
		void * int_convertRGB2FB(unsigned char *rgbbuff, unsigned long x, unsigned long y, bool alpha);
		void * convertRGB2FB(unsigned char *rgbbuff, unsigned long x, unsigned long y);
		void * convertRGBA2FB(unsigned char *rgbbuff, unsigned long x, unsigned long y);
};

#ifdef LV_DEBUG
static struct timeval timer_tv, timer_tv2;
static unsigned int timer_msec;

#define TIMER_START() gettimeofday(&timer_tv, NULL)

#define TIMER_STOP(label)												\
	gettimeofday(&timer_tv2, NULL);											\
	timer_msec = ((timer_tv2.tv_sec - timer_tv.tv_sec) * 1000) + ((timer_tv2.tv_usec - timer_tv.tv_usec) / 1000);	\
	printf("%s: %u msec\n", label, timer_msec)
#else
#define TIMER_START()
#define TIMER_STOP(label)
#endif


#endif // __logoview_h__
