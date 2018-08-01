// DataCollect_Sum_dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <direct.h>

#define LIBDLL extern "C" __declspec(dllexport)

#define FILE_NUM 32
#define TRACK_NUM 9999
#define FOLDER_NUM 99

#pragma warning(disable:4996)

#pragma pack(push) 
#pragma pack(1)  
struct collect{
	uint32_t count;
	uint64_t time;
};

struct data_collect{
	struct collect record;
	uint8_t trackNum;
};
#pragma pack(pop)

struct data_collect *init_CollectTable(struct data_collect *table);
struct data_collect *init_CollectTable(struct data_collect *table)
{
	struct data_collect *ptr = table;
	/*unsigned int a;
	for(a=0;a<TRACK_NUM;a++,ptr++)
	{
	ptr->trackNum = 0;
	ptr->record.count=0;
	ptr->record.time=0;
	}*/
	memset(ptr, 0, sizeof(struct data_collect)*(TRACK_NUM + 1));
	ptr = table;
	return ptr;
}

LIBDLL int SumData(char *name, char *Newfolder)
{
	struct data_collect table[TRACK_NUM + 1];
	struct collect field[TRACK_NUM + 1];
	struct data_collect *pclt = table;
	FILE *read_fp, *write_fp;
	char dat[100] = { 0 };
	char path[100];
	unsigned int a, n, m;
	unsigned int empty_flag = 0;


	sprintf(path, "%s\\DataCollect_Sum", Newfolder);
	/*if (_mkdir(path) != 0)
	{
		printf("The Folder is exist!\n");
		system("pause");
		return 0;
	}*/
	_mkdir(path);
	for (n = 1; n<FILE_NUM + 1; n++)/*The language a range of 1~32*/
	{
		if (empty_flag)
			empty_flag = 0;

		pclt = init_CollectTable(pclt);/*initial record table*/

		for (a = 1; a<FOLDER_NUM; a++)/*Search exp folder is exist in disk*/
		{
			memset(dat, 0, 100);
			memset(field, 0, sizeof(field));
			sprintf(dat, "%s\\%02d\\%02d.dat", name, a, n);
			if ((read_fp = fopen(dat, "rb")) == NULL){
				continue;
			}
			else{
				for (m = 0; m <= TRACK_NUM; m++)/*The track a range of 1~9999*/
				{
					fseek(read_fp, m*sizeof(struct collect), SEEK_SET);
					fread(&field[m], sizeof(struct collect), 1, read_fp);

					if (field[m].count != 0){
						printf("%02d.dat\n NO.%d\n%x (%d)\n%#llx (%#lld)\n\n", n, m, field[m].count, field[m].count, field[m].time, field[m].time);						
					}//if
					pclt[m].trackNum = m;
					pclt[m].record.count = pclt[m].record.count + field[m].count;
					pclt[m].record.time = pclt[m].record.time + field[m].time;
				}//for TRACK_NUM
			}//else
			fclose(read_fp);
		}//for USB_NUMBER

		memset(dat, 0, 100);
		sprintf(dat, "%s\\%02d.dat", path, n);

		printf("Creat file:%s\n\n ", dat);
		write_fp = fopen(dat, "wb");
		if (write_fp == NULL){
			continue;
		}/*if (pclt[0].record.count == 0){
			fseek(write_fp, 1 * sizeof(struct collect), SEEK_SET);
			fwrite(&pclt[1].record, sizeof(struct collect), TRACK_NUM, write_fp);
			fseek(write_fp, TRACK_NUM*sizeof(struct collect), SEEK_SET);
			fwrite(&pclt[TRACK_NUM].record, sizeof(struct collect), 6, write_fp);
			continue;
		}*/
		else{
			for (m = 0; m <= TRACK_NUM; m++)/*The track a range of 1~9999*/
			{
				fseek(write_fp, m*sizeof(struct collect), SEEK_SET);
				fwrite(&pclt[m].record, sizeof(struct collect), 1, write_fp);
				printf("The total value:NO.%d\n%x (%d)\n%#llx (%#lld)\n\n", m, pclt[m].record.count, pclt[m].record.count, pclt[m].record.time, pclt[m].record.time);		
			}//for
		}//else
		fflush(write_fp);
		fclose(write_fp);
	}//for FILE_NUM
	return 0;
}