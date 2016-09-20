#ifndef __IR_FUNC_H__
#define __IR_FUNC_H__
#include <AT89X52.h>
#include "com_define.h"
extern IR_DATA ir_value;

void IR_Write(uchar value);
void IR_Init();
#endif