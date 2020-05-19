/*
 * wr_czas.h
 *
 *  Created on: May 19, 2020
 *      Author: Sylwia_Badur
 */

#ifndef INC_WR_CZAS_H_
#define INC_WR_CZAS_H_

#include "main.h"

typedef uint64_t wr_czas_us;

struct wr_czas {
	wr_czas_us time_us;
	wr_czas_us czas_aktualny(void);
	wr_czas_us ts_do_wr_czas(struct timespec *ts);
	void wr_czas_do_ts(struct timespec *ts, wr_czas_us tus);
	int32_t roznica_czasu(const wr_czas_us *poprzedni);
};

#endif /* INC_WR_CZAS_H_ */
