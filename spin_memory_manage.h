#ifndef SPINMEMORYMANAGEH
#define SPINMEMORYMANAGEH
#include "spin_common.h" 
#define memory_pool_size	60	  /*�ڴ�ش�С ��λbyte*/
#define memory_pool_table_size	10	 /*�ڴ�ط�����С*/
extern uint memory_head;	   //init֮���ڴ�ص��׵�ַ
bool memory_pool_init();
void* spin_memory_malloc(uchar size);
bool spin_memory_free(void* ptr);

#endif