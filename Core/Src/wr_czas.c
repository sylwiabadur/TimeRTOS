/*
 * wr_czas.c
 *
 *  Created on: Jun 2, 2020
 *      Author: Sylwia_Badur
 */

#include "wr_czas.h"
#include "cmsis_os.h"
#include "stm32f4xx.h"
#include "task.h"
#include "math.h"
#include "stdlib.h"

wr_czas_us czas_aktualny(void)
{
	vTaskSuspendAll();

	uint32_t clk = SystemCoreClock;
	uint32_t systickNs = SysTick->VAL % clk * (1000 * 1000 * 1000 / clk);
	uint32_t taskGetTickMs = xTaskGetTickCount();
	uint32_t currentTime = taskGetTickMs* 1000 + systickNs / 1000;

	xTaskResumeAll();
	return currentTime;
}

wr_czas_us ts_do_wr_czas(const struct timespec *ts)
{
	wr_czas_us tsTimeNs = ts->tv_nsec / 1000;  // do micro
	wr_czas_us tsTimeS = ts->tv_sec * 1000 * 1000; // do micro
	return tsTimeNs + tsTimeS;
}

void wr_czas_do_ts(struct timespec *ts, wr_czas_us tus)
{
	long timeInNs = tus * 1000; // do nano
	time_t sStruct = 0;
	long nsStruct = timeInNs % 999999999;

	if (timeInNs > 999999999)
	{
		sStruct = floor(timeInNs / 999999999);
	}
	else
	{
		sStruct = 0;
	}

	ts->tv_sec = sStruct;
	ts->tv_nsec = nsStruct;
}

int32_t roznica_czasu(const wr_czas_us *prev)
{
	wr_czas_us current = czas_aktualny();
	wr_czas_us diff = abs(*prev - current);
	int32_t returnedDiff = (int32_t)diff;
	return returnedDiff;
}
