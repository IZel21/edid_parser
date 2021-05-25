/*
 * draft.c
 *
 *  Created on: May 25, 2021
 *      Author: vxuser
 */

#ifdef draft_code

/*! Получить тайминг видеокарты - разрешение
 *  return - */
static E_FMT _get_fmt( uint8_t byte1)
{
	switch ( byte1)
	{
	case 0x31:
		return E_FMT_640;
		break;

	case 0x45:
		return E_FMT_800;
		break;

	case 0x61:
		return E_FMT_1024;
		break;

	case 0x71:
		return E_FMT_1152;
		break;

	case 0x81:
		return E_FMT_1280;
		break;

	case 0x90:
		return E_FMT_1400;
		break;

	case 0x95:
		return E_FMT_1440;
		break;

	case 0xA9:
		return E_FMT_1600;
		break;

	case 0xB3:
		return E_FMT_1680;
		break;

	case 0xC1:
		return E_FMT_1792;
		break;

	case 0xC9:
		return E_FMT_1856;
		break;

	case 0xD1:
		return E_FMT_1920;
		break;

	case 0xE1:
		return E_FMT_2048;
		break;

	default:
		return E_FMT_ALL;
		break;

	}
}

/*! Получить тайминг видеокарты - частота
 *  return - */
static E_HZ _get_hz( uint8_t byte2)
{
	switch ( byte2)
	{
	case 0x19:
		return E_HZ_85;
		break;

	case 0x40:
		return E_HZ_60;
		break;

	case 0x40:
		return E_HZ_60;
		break;

	case 0x4A:
		return E_HZ_70;
		break;

	case 0x4C:
		return E_HZ_72;
		break;

	case 0x4F:
		return E_HZ_75;
		break;

	case 0x59:
		return E_HZ_85;
		break;

	default:
		return E_HZ_ALL;
		break;
	}

}

/*! Получить тайминг видеокарты - частота
 *  return - */
static E_FMT _get_timing( uint8_t byte1, uint8_t byte2)
{

	E_FMT form = _get_fmt( byte1);
	E_HZ  hz   = _get_hz(  byte2);


	printf( "Form = %d \n", form);
	printf( "hz = %d \n", hz);


	switch ( form)
	{
		case E_FMT_640  :
		if ( E_HZ_85 == hz)
			printf( "640x400 ");
		else
			printf("640x480 ");
			break;

		case E_FMT_720  :
//			printf();
			break;

		case E_FMT_800  :
			printf("800x600 ");
			break;


		case E_FMT_1024 :
			printf("1024x768");
			break;

		case E_FMT_1152:
			printf("1252x864 ");
			break;

		case E_FMT_1280 :
			printf("1280x800 ");
			break;

		case E_FMT_1360 :
//			printf();
			break;

		case E_FMT_1366 :
//			printf();
			break;

		case E_FMT_1400 :
//			printf();
			break;

		case E_FMT_1440 :
//			printf();
			break;

		case E_FMT_1600 :
//			printf();
			break;

		case E_FMT_1680 :
//			printf();
			break;

		case E_FMT_1792 :
//			printf();
			break;

		case E_FMT_1856 :
//			printf();
			break;

		case E_FMT_1920 :
			printf("1920x ");
			break;

		case E_FMT_2048 :
			printf("2048x1152 ");
			break;

		case E_FMT_ALL :
//			printf();
			break;
	}

	switch ( hz)
	{
		case E_HZ_50  :
			printf("50 Hz \n");
			break;

		case E_HZ_56  :
			printf("56 Hz \n");
			break;

		case E_HZ_60  :
			printf("60 Hz \n");
			break;

		case E_HZ_70  :
			printf("70 Hz \n");
			break;

		case E_HZ_72  :
			printf("72 Hz \n");
			break;

		case E_HZ_75  :
			printf("75 Hz \n");
			break;

		case E_HZ_85  :
			printf("85 Hz \n");
			break;

		case E_HZ_120 :
			printf("120 Hz \n");
			break;

		case E_HZ_ALL :
			break;
	}

	return 0;
}
#endif
