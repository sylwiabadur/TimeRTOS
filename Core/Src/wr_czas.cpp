/*
 * wr_czas.c
 *
 *  Created on: May 19, 2020
 *      Author: Sylwia_Badur
 */
#include "wr_czas.h"
#include "task.h"
#include <cmath>

wr_czas_us czas_aktualny(void)
{
	vTaskSuspendAll();

	uint32_t systickTime = (SysTick->VAL)%(CLK_Frequency_MHZ*1000);//time ms
	wr_czas_us systickUS = wr_czas_us(systickTime)*1000;
	TickType_t currentTime = xTaskGetTickCount(); // z dokladnoscia do ms
	wr_czas_us tickCountUS = wr_czas_us(currentTime)*1000;

	xTaskResumeAll();

	return systickUS; // w us powinno być
}

wr_czas_us ts_do_wr_czas(struct timespec *ts)
{
	long tsTimeNs = ts->tv_nsec;
	tsTimeNs = tsTimeNs/1000; // TO MICROSECOND
	wr_czas_us timeInus = (wr_czas_us)tsTimeNs;
	return timeInus;
}

void wr_czas_do_ts(struct timespec *ts, wr_czas_us tus)
{
	long timeInNs = tus*1000;
	time_t sStruct = 0;
	long nsStruct = timeInNs % 999999999;

	if(timeInNs>999999999)
	{
		sStruct = std::floor(timeInNs / 999999999);
	}
	else
	{
		sStruct = 0;
	}

	ts->tv_sec = sStruct;
	ts->tv_nsec = nsStruct;

	return;
}

int32_t roznica_czasu(const wr_czas_us *poprzedni)
{
	wr_czas_us current = czas_aktualny();
	wr_czas_us diff = abs(poprzedni - current);
	int32_t returnedDiff = (int32_t)diff;
	return returnedDiff;
}
