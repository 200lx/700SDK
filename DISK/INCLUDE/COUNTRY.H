/* COUNTRY.H         NOTE: This is a MASTER copy - DO NOT CHANGE THIS FILE */
/* File updates must be implemented by using the REDITOR Compile option on */
/* C:\TSR\TASK0\COUNTRY.RS                                                 */



/* country abbreviate for menu */
#define COUNTRY_ID 0

/* long version of name. */
#define COUNTRY_NAME 1

/* \0 for sun; \001 for monday */
#define CTRY_WEEKSTART 2

/* Set A */
#define CTRY_PUNCT 3

#define CTRY_DATEFORM 4

#define CTRY_TIMEFORM 5

/* Numbers First */
#define CTRY_SORT 6

/* 15 characters max. */
#define CTRY_CURRENCY 7

/* \0 = prefix; \001 = suffix */
#define CTRY_CURR_PRESUF 8

/* US Keyboard (0x8000) - bytes are swapped */
#define CTRY_KEYBOARD 9

/* for file date display only */
#define CTRY_DATESEP 10

/* for file time display only */
#define CTRY_TIMESEP 11

/* using 24 clock?, for file times only */
#define CTRY_TIME24 12

/* day,month,year; for file dates only */
#define CTRY_DATEORDER 13
