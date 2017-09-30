/*
 *  tslib/src/ts_read_raw_module.c
 *
 *  Original version:
 *  Copyright (C) 2001 Russell King.
 *
 *  Rewritten for the Linux input device API:
 *  Copyright (C) 2002 Nicolas Pitre
 *
 * This file is placed under the LGPL.  Please see the file
 * COPYING for more details.
 *
 * $Id: input-raw.c,v 1.5 2005/02/26 01:47:23 kergoth Exp $
 *
 * Read raw pressure, x, y, and timestamp from a touchscreen device.
 */
#include "config.h"

#include <errno.h>
#include <stdio.h>

#include <stdlib.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <sys/time.h>
#include <sys/types.h>

#include <linux/input.h>
#ifndef EV_SYN /* 2.4 kernel headers */
# define EV_SYN 0x00
#endif

#include "tslib-private.h"

struct tslib_input {
	struct tslib_module_info module;

	int	current_x;
	int	current_y;
	int	current_p;

	int	sane_fd;
	int	using_syn;
};

static int check_fd(struct tslib_input *i)
{
	struct tsdev *ts = i->module.dev;
	int version;
	u_int32_t bit;
	u_int64_t absbit;
/*
	if (! ((ioctl(ts->fd, EVIOCGVERSION, &version) >= 0) &&
		(version == EV_VERSION) &&
		(ioctl(ts->fd, EVIOCGBIT(0, sizeof(bit) * 8), &bit) >= 0) &&
		(bit & (1 << EV_ABS)) &&
		(ioctl(ts->fd, EVIOCGBIT(EV_ABS, sizeof(absbit) * 8), &absbit) >= 0) &&
		(absbit & (1 << ABS_X)) &&
		(absbit & (1 << ABS_Y)) && (absbit & (1 << ABS_PRESSURE)))) {
		fprintf(stderr, "selected device is not a touchscreen I understand\n");
		return -1;
	}

	if (bit & (1 << EV_SYN))
		i->using_syn = 1;
*/
	return 0;
}

static int ts_input_read(struct tslib_module_info *inf,
             struct ts_sample *samp, int nr)
{
    struct tsdev *ts = inf->dev;
    int total = 0;
    unsigned point;

        while (total < nr) {
           
	    point = ioctl(ts->fd, 9, 0);

            if(point == 0xFFFEFFFE || point == 0xFFFFFFFF)
            {
		usleep(10000);
		continue;
            }
  	
	   if (point == 0xEB90EB90) { 
                samp->x = 0;
                samp->y = 0;
                samp->pressure = 0;

                samp++;
                total++;
			
              } else {
                samp->x = (point & 0xffff);		//x为底位，y为高16位
                samp->y = ((point>>16) & 0xffff);
                samp->pressure = 1;

                samp++;
                total++;
             }
        }

    return total;
}


static int ts_input_fini(struct tslib_module_info *inf)
{
	free(inf);
	return 0;
}

static const struct tslib_ops __ts_input_ops = {
	.read	= ts_input_read,
	.fini	= ts_input_fini,
};

TSAPI struct tslib_module_info *mod_init(struct tsdev *dev, const char *params)
{
	struct tslib_input *i;

	i = malloc(sizeof(struct tslib_input));
	if (i == NULL)
		return NULL;

	i->module.ops = &__ts_input_ops;
	i->current_x = 0;
	i->current_y = 0;
	i->current_p = 0;
	i->sane_fd = 0;
	i->using_syn = 0;
	return &(i->module);
}
