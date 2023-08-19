/*
 * Handlers for board audio hooks, splitted from bttv-cards
 *
<<<<<<< HEAD
 * Copyright (c) 2006 Mauro Carvalho Chehab <mchehab@kernel.org>
=======
 * Copyright (c) 2006 Mauro Carvalho Chehab (mchehab@infradead.org)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * This code is placed under the terms of the GNU General Public License
 */

#include "bttvp.h"

void winview_volume (struct bttv *btv, __u16 volume);

void lt9415_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);
void avermedia_tvphone_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);
void avermedia_tv_stereo_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);
void terratv_audio(struct bttv *btv,  struct v4l2_tuner *tuner, int set);
void gvbctv3pci_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);
void gvbctv5pci_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);
void winfast2000_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);
void pvbt878p9b_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);
void fv2000s_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);
void windvr_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);
void adtvk503_audio(struct bttv *btv, struct v4l2_tuner *tuner, int set);

