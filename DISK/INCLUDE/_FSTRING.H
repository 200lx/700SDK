/* SCCS info:   Module _fstring.h  Version 1.1  Date 11/09/93  Time 15:14:10 */

/* $Header:   T:/HH/INCLUDE/VCS/_FSTRING.H_V   1.0   05 Jan 1993 19:29:14   ROGER  $ */
/**************************************************************************
 *
 * Name:        _FSTRING.H
 *
 * Date:        Tuesday January 5, 1993
 *
 * Abstract:    Function prototypes for the string library functions.
 *
 * ------------------------------------------------------------------------
 *                   Copyright 1993 Lotus Development Corp.
 *                           All rights reserved.
 **************************************************************************
 *
 * $Log:   T:/HH/INCLUDE/VCS/_FSTRING.H_V  $
 * 
 *    Rev 1.0   05 Jan 1993 19:29:14   ROGER
 * Initial revision.
 *
 **************************************************************************/

void  _far * _far _cdecl _fbmemcpy(
    void _far *dest,
    void _far *src,
    unsigned short count);

int _far _cdecl _fmemcmp(
    const void _far *m1,
    const void _far *m2,
    unsigned int len);

void  _far * _far _cdecl _fmemcpy(
    void _far *dest,
    void _far *src,
    unsigned short count);

void _far * _far _cdecl _fmemset(
    void _far *buffer,
    int fillchar,
    unsigned short count);

void  _far * _far _cdecl _frmemcpy(
    void _far *dest,
    void _far *src,
    unsigned short count);

char _far * _far _cdecl _fstrcat(
    char _far *str1,
    char _far *str2);

char _far * _far _cdecl _fstrchr(
    char _far *str,
    int srch_char);

char _far * _far _cdecl _fstrcpy(
    char _far *dest,
    char _far *src);

/*
 * Note, the comparison is case insensitive and diacritically sensitive.
 */
int _far _cdecl _fstricmp(
    char _far *str1,
    char _far *str2);

unsigned short _far _cdecl _fstrlen(char _far *str);

char _far * _far _cdecl _fstrncpy(
    char _far *dest,
    char _far *src, 
    unsigned short count);

/*
 * Note, the comparison is case insensitive and diacritically sensitive.
 */
int _far _cdecl _fstrnicmp(
    char _far *str1,
    char _far *str2,
    unsigned short len);

/*
 * Note, the comparison is case insensitive and diacritically sensitive.,
 */
char _far * _far _cdecl _fstristr(
    char _far *str1,
    char _far *str2);

