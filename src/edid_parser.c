/*
 ============================================================================
 Name        : edid_parser.c
 Author      : IZel
 Version     :
 Copyright   : Your copyright notice
 Description : EDID Pareser
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "../h/edid_parser.h"

S_DATA data;

/*! Расчеты даты*/
static uint16_t _get_year( uint16_t date)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	uint32_t year = tm.tm_year + 1900;

	date = ( ( year >= (date + YEAR_MIN)) && 3 < date )
			? date + YEAR_MIN
					: 0;

	return date;
}

/*! Расчеты достоверности недели */
static uint8_t _check_week( uint16_t date)
{
	return ( 0 < date && 54 > date);
}

/*! Расчет контрольной суммы массива*/
static uint8_t _cksum_calc ( uint8_t *_p_elem, size_t _s_bufsize)
{
	if ( NULL == _p_elem)
		return 0;

	uint8_t _i_sum1 = 0, _i_sum2 = 0;

	for ( uint8_t _i = 0; _i < _s_bufsize; _i++)
	{
		_i_sum1 += _p_elem[_i];

		if ( ( _s_bufsize - 2) == _i)
			_i_sum2 = _i_sum1;
	}

	return (_i_sum1 - _i_sum2);
}



int main( int argc, char **argv)
{
	printf("EDID parser is running \n");

	FILE *fp;
	uint16_t _i;

	if ( NULL  == ( fp = fopen(argv[ 1], "rb")))
	{
		printf(" FILE ERROR! Enter filename in the command line! Exit now \n");
		return(-1);
	}
	else
	{
		printf("File %s is opened \n", argv[ 1]);
	}

	uint8_t buf[ BUF_SIZE] = { 0};

	uint32_t _read = fread( buf, sizeof( uint8_t), BUF_SIZE, fp);

	fclose(fp);

	if ( BUF_SIZE == _read)
	{
		printf( "All is OK, %d  bvytes from 128 read \n", _read);
	}
	else
	{
		printf(" BYTES COUNT ERROR! Bytes read %d not equal 128 Exit now \n", _read);
		return(-1);
	}

#ifdef PRINTF_DEEP_DEBUG
	for ( _i = 0; _i < BUF_SIZE; _i++)
	{
		printf( " buf[%d] = %x \n", _i, buf[ _i]);
	}
#endif

	memcpy( data._mask, buf, BUF_SIZE * sizeof ( uint8_t));

#ifdef PRINTF_DEEP_DEBUG
	for ( _i = 0; _i < BUF_SIZE; _i++)
	{
		printf("data._mask[%d] = %x \n", _i, data._mask[ _i]);
	}
#endif

#ifdef PRINTF_DEBUG
	printf( "data.bytes.b1  = %x \n", data.bytes.head_p1);
	printf( "data.bytes.b2  = %x \n", data.bytes.head_p2);
#endif
	if (  (data.bytes.head_p1 & 0xFFFFFF00) &&  (data.bytes.head_p2 & 0x00FFFFFF))
	{
		printf("Header %x %x is OK! \n", data.bytes.head_p1,  data.bytes.head_p2);
	}
	else
	{
		printf( "Header %x %x is incoorect! Exit now \n",  data.bytes.head_p1,  data.bytes.head_p2);
		return( -1);
	}

	uint8_t _i_cksum = _cksum_calc( data._mask, BUF_SIZE);

#ifdef PRINTF_DEBUG
	printf("data.bytes.checksum = %x \n", data.bytes.checksum);
	printf("_i_cksum = %x \n", _i_cksum);
#else
	printf("Checksum = %x \n", data.bytes.checksum);
#endif

	if( data.bytes.checksum == _i_cksum)
	{
		"Cecksum is ok! \n";
	}
	else
	{
		printf( "Checksum %x is not equal %x! Exit now \n",data.bytes.checksum, _i_cksum);
		return( -1);
	}

#ifdef PRINTF_DEBUG
	printf("data.bytes.id_manul    = %d \n", data.bytes.id_manul   );
	printf("data.bytes.id_product  = %d \n", data.bytes.id_product );
	printf("data.bytes.id_serial   = %d \n", data.bytes.id_serial  );
	printf("data.bytes.week_manual = %d \n", data.bytes.week_manual);
    printf("data.bytes.year_manual = %d \n", data.bytes.year_manual);
#else
	printf("ID Manufacturer Name = %d \n", data.bytes.id_manul   );
	printf("ID Product Code  = %d \n", data.bytes.id_product );
	printf("ID Serial Number   = %d \n", data.bytes.id_serial  );
	printf("Week of Manufacture = %d, valid = %d \n", data.bytes.week_manual, _check_week( data.bytes.week_manual));
    printf("Year of Manufacture = %d \n", _get_year( data.bytes.year_manual));
#endif

#ifdef PRINTF_DEBUG
    printf("data.bytes.version  = %d \n", data.bytes.version );
    printf("data.bytes.revision = %d \n", data.bytes.revision);
#else
    printf("EDID Structure Version / Revision = %d.%d \n", data.bytes.version, data.bytes.revision);

    if ( 1 != data.bytes.version)
    	printf("EDID version is incorrect! \n");
#endif

#ifdef PRINTF_DEBUG
    printf("data.bytes.input_def   = %d \n", data.bytes.input_def  );
    printf("data.bytes.max_hor_sz  = %d \n", data.bytes.max_hor_sz );
    printf("data.bytes.max_vert_sz = %d \n", data.bytes.max_vert_sz);
    printf("data.bytes.disp_transf = %d \n", data.bytes.disp_transf);
    printf("data.bytes.feature_sup = %d \n", data.bytes.feature_sup);

    printf("data.bytes.rg_l = %d \n", data.bytes.rg_l);
    printf("data.bytes.bw_l = %d \n", data.bytes.bw_l);
    printf("data.bytes.r_x  = %d \n", data.bytes.r_x );
    printf("data.bytes.r_y  = %d \n", data.bytes.r_y );
    printf("data.bytes.g_x  = %d \n", data.bytes.g_x );
    printf("data.bytes.g_y  = %d \n", data.bytes.g_y );
    printf("data.bytes.b_x  = %d \n", data.bytes.b_x );
    printf("data.bytes.b_y  = %d \n", data.bytes.b_y );
    printf("data.bytes.w_x  = %d \n", data.bytes.w_x );
    printf("data.bytes.w_y  = %d \n", data.bytes.w_y );
#else

#endif

    printf("data.bytes.est_timing1 = %x \n", data.bytes.est_timing1);
    printf("data.bytes.est_timing2 = %x \n", data.bytes.est_timing2);
    printf("data.bytes.res_timing  = %x \n", data.bytes.res_timing );


    for ( _i = 0; _i < 8; _i++)
    {
    	printf("data.bytes.std_timing_id 1[%d] = %x \n", _i, data.bytes.std_timing_id1[ _i]);
    }


    for ( _i = 0; _i < 8; _i++)
    {
    	printf("data.bytes.std_timing_id 2[%d] = %x \n", _i, data.bytes.std_timing_id2[ _i]);
    }

#ifdef PRINTF_DEBUG
	printf("data.bytes.std_timing_descr1=");
    for ( _i = 0; _i < 18; _i++)
	{
    	printf( "%c ", data.bytes.std_timing_descr1[_i]);
	}

	printf("\n");

	printf("data.bytes.std_timing_descr2=");
    for ( _i = 0; _i < 18; _i++)
	{
    	printf( "%c ", data.bytes.std_timing_descr2[_i]);
	}

	printf("\n");


	printf("data.bytes.std_timing_descr3=");
    for ( _i = 0; _i < 18; _i++)
	{
    	printf( "%c ", data.bytes.std_timing_descr3[_i]);
	}

	printf("\n");

	printf("data.bytes.std_timing_descr4=");
    for ( _i = 0; _i < 18; _i++)
	{
    	printf( "%c ", data.bytes.std_timing_descr4[_i]);
	}

	printf("\n");
#endif

#ifdef PRINTF_DEBUG
    printf("data.bytes.ext_flag = %d \n", data.bytes.ext_flag);
#endif

	return 0;
}
