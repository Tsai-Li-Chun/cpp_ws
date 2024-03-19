/** ******************************************************
	* @file		ADAM5000_DefineTable.hpp
	* @author	Tsai,Li-chun
	******************************************************
**	**/

/* Define to prevent recursive inclusi ----------------------*/
#ifndef __ADAM5000_DefineTable_HPP__
#define __ADAM5000_DefineTable_HPP__


/* System Includes ------------------------------------------*/
/* System Includes Begin */
/* System Includes End */
/* User Includes --------------------------------------------*/
/* User Includes Begin */
/* User Includes End */


/* Define ---------------------------------------------------*/
/* Define Begin */


/* define terminal color */
#define TC_RESET "\033[0m"			// Normal 
#define TC_ERROR "\033[31m[ERROR] " // Red
#define TC_CLOSE "\x1B[2J\x1B[H "	// close

/* define adam5000 modbus net information */
#define adam5000_modbus_IP "192.168.1.122"
#define adam5000_modbus_port 502
#define adam5000_modbus_slave 1

#define digital_module_quantity 3
#define digital_channel 16
#define analogy_module_quantity	1
#define analogy_channel 4
#define slot2_DI_x51 0
// #define slot2_channel 16
#define slot3_DO_x56 1
// #define slot3_channel 16
#define slot4_DO_x56 2
// #define slot4_channel 16
// #define slot1_AO_5024 0

/* Define End */


/* Extern Typedef -------------------------------------------*/
/* Extern Typedef Begin */
/* Extern Typedef End */


/* Extern Class -------------------------------------------*/
/* Extern Class Begin */

/* define adam slot2&3 DI module modbus address */
enum class adam5000_AO:int
{
	AO_1_0 = 0,
	AO_1_1 = 1,
	AO_1_2 = 2,
	AO_1_3 = 3
};
/* define adam slot2&3 DI module modbus address */
enum class adam5000_DI:int
{	
	DI_2_00 = 16,
	DI_2_01 = 17,
	DI_2_02 = 18,
	DI_2_03 = 19,
	DI_2_04 = 20,
	DI_2_05 = 21,
	DI_2_06 = 22,
	DI_2_07 = 23,
	DI_2_08 = 24,
	DI_2_09 = 25,
	DI_2_10 = 26,
	DI_2_11 = 27,
	DI_2_12 = 28,
	DI_2_13 = 29,
	DI_2_14 = 30,
	DI_2_15 = 31
};
/* define adam slot2&3 DO module modbus address */
enum class adam5000_DO:int
{
	DO_3_00 = 32,
	DO_3_01 = 33,
	DO_3_02 = 34,
	DO_3_03 = 35,
	DO_3_04 = 36,
	DO_3_05 = 37,
	DO_3_06 = 38,
	DO_3_07 = 39,
	DO_3_08 = 40,
	DO_3_09 = 41,
	DO_3_10 = 42,
	DO_3_11 = 43,
	DO_3_12 = 44,
	DO_3_13 = 45,
	DO_3_14 = 46,
	DO_3_15 = 47,
	DO_4_00 = 48,
	DO_4_01 = 49,
	DO_4_02 = 50,
	DO_4_03 = 51,
	DO_4_04 = 52,
	DO_4_05 = 53,
	DO_4_06 = 54,
	DO_4_07 = 55,
	DO_4_08 = 56,
	DO_4_09 = 57,
	DO_4_10 = 58,
	DO_4_11 = 59,
	DO_4_12 = 60,
	DO_4_13 = 61,
	DO_4_14 = 62,
	DO_4_15 = 63
};

/* Extern Class End */


/* Extern Variables -----------------------------------------*/
/* Extern Variables Begin */
/* Extern Variables End */


/* Function -------------------------------------------------*/
/* Function Begin */
/* Function End */


#endif /*__ADAM5000_DefineTable_HPP__ */

/* ***** END OF ADAM5000_DefineTable.HPP ***** */
