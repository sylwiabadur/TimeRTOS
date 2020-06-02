/*
 * wr_czas.h
 *
 *  Created on: Jun 2, 2020
 *      Author: Sylwia_Badur
 */

#ifndef INC_WR_CZAS_H_
#define INC_WR_CZAS_H_

#include "stdint.h"
#include "sys/time.h"

typedef uint64_t wr_czas_us;

wr_czas_us czas_aktualny(void);
wr_czas_us ts_do_wr_czas(const struct timespec *ts);
void wr_czas_do_ts(struct timespec *ts, wr_czas_us tus);
int32_t roznica_czasu(const wr_czas_us *prev);


#endif /* INC_WR_CZAS_H_ */
