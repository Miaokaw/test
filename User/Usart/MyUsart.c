#include "MyUsart.h"

FormData OpennMv_Data;

union floatType{
	uint8_t c[4];
	float f;
}globaFdata;

void FormData_Init(FormData *Data)
{
	for(uint8_t i=0; i<20; i++){
		Data->RxBuffer[i] = 0x00;
	}
	Data->frame_head[0] = 0x55;
	Data->frame_head[1] = 0x12;
	Data->frame_tail = 0x55;
	Data->color = 0x00;
	Data->shape = 0x00;
	Data->cx = 0;
	Data->cy = 0;
	Data->distanse = 0;
	Data->area = 0;
}

float getFloat (uint8_t *point){
	for(uint8_t i=0;i<4;i++){
		globaFdata.c[i] = point[i];
	}
	return globaFdata.f;
}

void OpenMvData_Process(FormData *Data){
	//检查帧头帧尾
	if(Data->RxBuffer[0] != OpennMv_Data.frame_head[0]) return;
	if(Data->RxBuffer[1] != OpennMv_Data.frame_head[1]) return;
	if(Data->RxBuffer[20] != OpennMv_Data.frame_tail) return;
	Data->color = Data->RxBuffer[2];
	Data->shape = Data->RxBuffer[3];
	Data->cx = getFloat(&Data->RxBuffer[4]);
	Data->cy = getFloat(&Data->RxBuffer[8]);
	Data->distanse = getFloat(&Data->RxBuffer[12]);
	Data->area = getFloat(&Data->RxBuffer[16]);
	
	
	
//	int color, shape;
//	float cx, cy, distanse, area;

}

