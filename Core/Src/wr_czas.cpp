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
	uint32_t systick = (SysTick->VAL)%(CLK_Frequency_MHZ*1000); //time ms;
	TickType_t currentTime = xTaskGetTickCount();


	// tu coś jeszcze powinno być - jakieś zamiany i dodawanie

	wr_czas_us zmienna = (wr_czas_us)curentTime;
	xTaskResumeAll();
	return zmienna; // w us powinno być
}

wr_czas_us ts_do_wr_czas(struct timespec *ts)
{
	long tsTimeNs = ts->tv_nsec;
	tsTimeNs = tsTimeNs/1000000;
	wr_czas_us zmienna = (wr_czas_us)tsTimeNs;
	return zmienna;
}

void wr_czas_do_ts(struct timespec *ts, wr_czas_us tus)
{
	long timeInMs = (long)tus;
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
	//draft: bo nie wiem o co tu chodzi
	// TODO

	int32_t zmienna = 1;
	return zmienna;
}
