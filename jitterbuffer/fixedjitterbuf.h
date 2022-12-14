/*
 * Copyright (C) 2005, Attractel OOD
 *
 * Contributors:
 * Slav Klenov <slav@securax.org>
 *
 * Copyright on this file is disclaimed to Digium for inclusion in Asterisk
 *
 * See http://www.asterisk.org for more information about
 * the Asterisk project. Please do not directly contact
 * any of the maintainers of this project for assistance;
 * the project provides a web site, mailing lists and IRC
 * channels for your use.
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */

/*! \file 
 * 
 * \brief Jitterbuffering algorithm.
 * 
 */

#ifndef _FIXEDJITTERBUF_H_
#define _FIXEDJITTERBUF_H_

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


/* return codes */
enum {
	FIXED_JB_OK,
	FIXED_JB_DROP,
	FIXED_JB_INTERP,
	FIXED_JB_NOFRAME,
	FIXED_JB_ERROR
};


/* defaults */
#define FIXED_JB_SIZE_DEFAULT 200
#define FIXED_JB_RESYNCH_THRESHOLD_DEFAULT 500


/* jb configuration properties */
struct fixed_jb_conf
{
	long jbsize;
 	long resync_threshold;
};


struct fixed_jb_frame
{
	void *data;
	long ts;
	long ms;
	long delivery;
	struct fixed_jb_frame *next;
	struct fixed_jb_frame *prev;
};


struct fixed_jb;


/* jb interface */

struct fixed_jb * fixed_jb_new(struct fixed_jb_conf *conf, struct ast_channel *chan);

void fixed_jb_destroy(struct fixed_jb *jb);

int fixed_jb_put_first(struct fixed_jb *jb, void *data, long ms, long ts, long now, char marker);

int fixed_jb_put(struct fixed_jb *jb, void *data, long ms, long ts, long now, char marker);

int fixed_jb_get(struct fixed_jb *jb, struct fixed_jb_frame *frame, long now, long interpl);

long fixed_jb_next(struct fixed_jb *jb);

int fixed_jb_remove(struct fixed_jb *jb, struct fixed_jb_frame *frameout);

void fixed_jb_set_force_resynch(struct fixed_jb *jb);

int fixed_jb_flush(struct fixed_jb *jb, struct fixed_jb_frame *frame);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _FIXEDJITTERBUF_H_ */
