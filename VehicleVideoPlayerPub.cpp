
#include "VehicleVideoPlayerPub.h"
//#include "dog_api.h"
#include <stdio.h>

#define TS_SYNC_BYTE 0x47
#define TS_PACKET_SIZE 188

typedef struct 
{
	unsigned pid;
	double clock_begin;
	double clock_end;
} pid_t;

unsigned char g_vendor_code[] = 
				"BdTiLdUC97kjhjv4VIJ0Vh6nsfsDy/ahO/KouVbkdEXdjtvxcgO56deLAx/VN3gsILEA3mT3"
				"UJnU6Xsiz5hM5K6ju4Czz3zMpfWqkfSXQsXZrhZNthirsTxNdXm17nhWroO83QNLlhVJjE4q"
				"Bb386Jn7P1hudcF5QXmjAY/Oild3SyIlL1DUChqA2wn6E7W/GtiNQbbBxOaOObWoTm+I4LMm"
				"EPuVISQ+smWqca+2Z74L22N6cvOdTXNInKHNuz6pQsZIlHQXvBBgBRd38dVwmEbPh8A7Q8fn"
				"Rhwy3UG2pAP4JXVuQHi2xXQiRyBvJtubeCVeJhEYu+JiKMDN7aXWVoa7DgbZsJRgVPfQG5Vw"
				"bUd2P9XpXfj3DOyqVB0PJssQQCH4VWoQWGuckf+ebRMC806m75HMRVGVjb7C45JkPCV5c/E6"
				"LtX7/dtul7JwOLbORHmM136HhBp/7CxscSvC37AG8Q1RcYr9G2jVD/7SwbjNfwAPEPE2rK6E"
				"YNOIlpCBZLslQyKrnFbgHQsIzThgqLYd1Uujpee2jK2YPsKJscybTEN7ipqNEVsPcAqPIHz4"
				"KH38EVycQxkS7VJXFK0KaZvFIwlRfYhRf/b4eCwdwIZhpi8YzpMB3RYl3GARQMREd3x9OmPg"
				"H9LIg8o7c6SVipKT45XlbBrdC+1k7olfoOcSRt3Iv8AFb9n2CvUhYoxjuO+uGgVOBuonhLFj"
				"A8Owb2kqm7yIEYzbOdjYIspnMroIV0zmqI8xd4GaJUp0MORlxYwx8dNFJlxy4IEs/eh+2v93"
				"SOf8sa5sxUjfM4ig9YwsjkbNBzONOc7qjuVvDy1iCJB9zTGFe0oNPrdJ3dE45NpYezuexZid"
				"t/TPx/apZHwtB10lYVBcT8bHWd22QGt9S0DK6eoFf/O2G+D4QgN0Wukeb363s0R7suyMXT2d"
				"wPDIeUyGuE95POWy01CpoETOZmBil+3qGPVGiXVemuqgVg==";

pid_t pid_array[8191]; 
unsigned char buf[TS_PACKET_SIZE];

void get_length(unsigned char* pkt);
void store_pid(unsigned pid, double clock);

int GetDurationFromTs(QString & strFileName)
{
	/*wchar_t* pNewName = (wchar_t*)malloc(3*strFileName.length());
	if (!pNewName)
	{
		return -1;
	}
	wmemset(pNewName,0,3*strFileName.length());
	strFileName.toWCharArray(pNewName);*/
	

	
	FILE *fp = fopen(strFileName.toStdString().c_str(), "rb");//_wfopen(pNewName,L"rb");//
	//free(pNewName);
	if (!fp) 
	{
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);

	while (size > 0) 
	{
		int read_size = fread(buf, 1, sizeof(buf), fp);
		size -= read_size;
		get_length(buf);
	}

	int iSecond = 0;
	for (int i = 0; i < 8191; i++) 
	{
		if (pid_array[i].pid != 0) 
		{
			iSecond = iSecond +	(pid_array[i].clock_end - pid_array[i].clock_begin);
		} 
		else
		{
			break;
		}
	}
	fclose(fp);
	return iSecond;
}

void get_length(unsigned char* pkt) 
{
	// Sanity check: Make sure we start with the sync byte:
	if (pkt[0] != TS_SYNC_BYTE) 
	{
		return;
	}

	// If this packet doesn't contain a PCR, then we're not interested in it:
	long const adaptation_field_control = (pkt[3] & 0x30) >> 4;
	if (adaptation_field_control != 2 && adaptation_field_control != 3) 
	{
		return;
	}

	// there's no adaptation_field
	long const adaptation_field_length = pkt[4];
	if (adaptation_field_length == 0) 
	{
		return;
	}

	// no PCR
	long const pcr_flag = pkt[5] & 0x10;
	if (pcr_flag == 0) 
	{
		return;
	}

	// yes, we get a pcr
	long pcr_base_high = (pkt[6] << 24) | (pkt[7] << 16) | (pkt[8] << 8) | pkt[9];
	// caculate the clock
	double clock = pcr_base_high / 45000.0;
	if ((pkt[10] & 0x80)) 
	{
		clock += 1 / 90000.0; // add in low-bit (if set)
	}
	unsigned short pcr_extra = ((pkt[10] & 0x01) << 8) | pkt[11];
	clock += pcr_extra / 27000000.0;

	unsigned pid = ((pkt[1] & 0x1F) << 8) | pkt[2];
	store_pid(pid, clock);
}

void store_pid(unsigned pid, double clock) 
{
	int i;
	for (i = 0; i < 8191; i++) 
	{
		if (pid == pid_array[i].pid) 
		{
			break;
		}
	}
	if (i == 8191) 
	{
		for (i = 0; i < 8191; i++) 
		{
			if (pid_array[i].pid == 0) 
			{
				break;
			}
		}
		pid_array[i].pid = pid;
		pid_array[i].clock_begin = clock;
	} 
	else 
	{
		pid_array[i].clock_end = clock;
	}
}

BOOL CheckDog()
{
/*	dog_feature_t iDFt = 0;
	dog_handle_t iDht = 0;
	dog_error_codes iDresult = dog_login(iDFt,(dog_vendor_code_t *)g_vendor_code,&iDht);
	dog_logout(iDht);

	if (iDresult == DOG_STATUS_OK)
	{
		return TRUE;
    }*/

	return FALSE;
}
