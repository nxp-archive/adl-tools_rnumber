//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

//
// Simple header file for creating a GCC Version 
// macro define.
//

#ifndef _GCC_VERSION_
#define _GCC_VERSION_

#define GCC_VERSION (__GNUC__ * 10000 \
                   + __GNUC_MINOR__ * 100 \
                   + __GNUC_PATCHLEVEL__)

#if GCC_VERSION >= 30200
#  define GCC_3_2 1
#  define STD_CPP
#else
#  define GCC_2_95 1
#endif

#endif
