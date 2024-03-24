#ifndef __MALLOC_H__
#define __MALLOC_H__

#include "main.h"
#include "stdint.h"

/* 内部SRAM */
#define SRAMIN_BLOCK_SIZE 32                                 /* 内存块大小，必须为2的幂次方 */
#define SRAMIN_MAX_SIZE 40 * 1024                            /* 最大内存 */
#define SRAMIN_BLOCK_NUM SRAMIN_MAX_SIZE / SRAMIN_BLOCK_SIZE /* 内存块个数 */

/* 外部SRAM */
#define SRAMOUT_BLOCK_SIZE 32
#define SRAMOUT_MAX_SIZE 235 * 1024
#define SRAMOUT_BLOCK_NUM SRAMOUT_MAX_SIZE / SRAMOUT_BLOCK_SIZE

typedef enum
{
    IN = 0,
    OUT = 1,
} typeSRAM;

typedef struct _SRAM
{
    uint8_t *pool[2];
    uint16_t *map[2];
} SRAM;

extern SRAM sram;

void mallocInit(void);
void FSMC_SRAM_ReadBuffer(uint8_t *pBuffer,uint32_t ReadAddr,uint32_t n);
void *mymalloc(typeSRAM type, uint32_t size);
void myfree(typeSRAM type, void *ptr);
uint16_t getMemoryUsage(typeSRAM type);

#endif /*__MALLOC_H__*/
