/*
 * edid_parser.h
 *
 *  Created on: May 18, 2021
 *      Author: vxuser
 */

#ifndef EDID_PARSER_H_
#define EDID_PARSER_H_

#define BUF_SIZE 128
#define YEAR_MIN 1990

#undef PRINTF_DEBUG
#undef PRINTF_DEEP_DEBUG


/*! Структура считываемых данных*/
typedef struct s_data
{
	union
	{
		uint8_t _mask [ BUF_SIZE];

		struct
		{
			/*! Header (8)*/
			uint32_t head_p1    ; /*!< Header part 1 FFFFFF00*/
			uint32_t head_p2    ; /*!< Header part 2 00FFFFFF*/

			/*! Vendor / Product Identification (10)*/
			uint16_t id_manul   ; /*!< ID Manufacturer Name*/
			uint16_t id_product ; /*!< ID Product Code     */
			uint32_t id_serial  ; /*!< ID Serial Number    */
			uint8_t  week_manual; /*!< Week of Manufacture */
			uint8_t  year_manual; /*!< Year of Manufacture */

			/*! EDID Structure Version / Revision (2)*/
			uint8_t  version    ; /*!< version */
			uint8_t  revision   ; /*!< revision*/

			/*! Basic Display Parameters / Features (5)*/
			uint8_t  input_def  ; /*!< Video Input Definition*/
			uint8_t  max_hor_sz ; /*!< Max. Horizontal Image Size*/
			uint8_t  max_vert_sz; /*!< Max. Vertical Image Size*/
			uint8_t  disp_transf; /*!< Display Transfer Characteristic (Gamma)*/
			uint8_t  feature_sup; /*!< Feature Support*/

			/*! Color Characteristics (10)*/
			uint8_t  rg_l     	; /*!< Red/Green Low Bits  */
			uint8_t  bw_l     	; /*!< Blue/White Low Bit  */
			uint8_t  r_x     	; /*!< Red-x   		   	   */
			uint8_t  r_y     	; /*!< Red-y   		       */
			uint8_t  g_x     	; /*!< Green-x 		       */
			uint8_t  g_y     	; /*!< Green-y			   */
			uint8_t  b_x     	; /*!< Blue-x			   */
			uint8_t  b_y     	; /*!< Blue-y			   */
			uint8_t  w_x     	; /*!< White-x			   */
			uint8_t  w_y     	; /*!< White-y			   */

			/*! Established Timings (3)*/
			uint8_t  est_timing1 ; /*!< Established Timings 1*/
			uint8_t  est_timing2 ; /*!< Established Timings 2*/
			uint8_t  res_timing  ; /*!< Manufacturer's Reserved Timings */

			/*! Standard Timing Identification (16)*/
			uint8_t std_timing_id1    [ 8]; /*!< Standard Timing Identification*/
			uint8_t std_timing_id2    [ 8]; /*!< Standard Timing Identification*/


			/*! Detailed Timing Descriptions (72)*/
			uint8_t  std_timing_descr1[ 18]; /*!< Detailed Timing Description 1*/
			uint8_t  std_timing_descr2[ 18]; /*!< Detailed Timing Description 2*/
			uint8_t  std_timing_descr3[ 18]; /*!< Detailed Timing Description 3*/
			uint8_t  std_timing_descr4[ 18]; /*!< Detailed Timing Description 4*/

			/*! Extension Flag (1)*/
			uint8_t  ext_flag   ; /*!< Extension Flag */

			/*! Checksum (1)*/
			uint8_t  checksum   ; /*!< Checksum */
		} bytes;
	};
} S_DATA;


typedef enum E_HZ
{
	E_HZ_50 = 0,
	E_HZ_56,
	E_HZ_60_1,
	E_HZ_60,
	E_HZ_70,
	E_HZ_72,
	E_HZ_75,
	E_HZ_85,
	E_HZ_120,
	E_HZ_ALL
} E_HZ;

typedef enum E_FMT
{
	E_FMT_640,
	E_FMT_720,
	E_FMT_800,
	E_FMT_848,
	E_FMT_1024,
	E_FMT_1152,
	E_FMT_1280,
	E_FMT_1360,
	E_FMT_1366,
	E_FMT_1400,
	E_FMT_1440,
	E_FMT_1600,
	E_FMT_1680,
	E_FMT_1792,
	E_FMT_1856,
	E_FMT_1920,
	E_FMT_2048,
	E_FMT_ALL
} E_FMT;

#endif /* EDID_PARSER_H_ */
