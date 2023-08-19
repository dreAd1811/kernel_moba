/*
 * Copyright (C) 2010 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#include "priv.h"
#include "ram.h"

void
nv40_fb_tile_comp(struct nvkm_fb *fb, int i, u32 size, u32 flags,
		  struct nvkm_fb_tile *tile)
{
	u32 tiles = DIV_ROUND_UP(size, 0x80);
	u32 tags  = round_up(tiles / fb->ram->parts, 0x100);
	if ( (flags & 2) &&
<<<<<<< HEAD
	    !nvkm_mm_head(&fb->tags, 0, 1, tags, tags, 1, &tile->tag)) {
=======
	    !nvkm_mm_head(&fb->ram->tags, 0, 1, tags, tags, 1, &tile->tag)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		tile->zcomp  = 0x28000000; /* Z24S8_SPLIT_GRAD */
		tile->zcomp |= ((tile->tag->offset           ) >> 8);
		tile->zcomp |= ((tile->tag->offset + tags - 1) >> 8) << 13;
#ifdef __BIG_ENDIAN
		tile->zcomp |= 0x40000000;
#endif
	}
}

static void
nv40_fb_init(struct nvkm_fb *fb)
{
	nvkm_mask(fb->subdev.device, 0x10033c, 0x00008000, 0x00000000);
}

static const struct nvkm_fb_func
nv40_fb = {
<<<<<<< HEAD
	.tags = nv20_fb_tags,
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.init = nv40_fb_init,
	.tile.regions = 8,
	.tile.init = nv30_fb_tile_init,
	.tile.comp = nv40_fb_tile_comp,
	.tile.fini = nv20_fb_tile_fini,
	.tile.prog = nv20_fb_tile_prog,
	.ram_new = nv40_ram_new,
<<<<<<< HEAD
=======
	.memtype_valid = nv04_fb_memtype_valid,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

int
nv40_fb_new(struct nvkm_device *device, int index, struct nvkm_fb **pfb)
{
	return nvkm_fb_new_(&nv40_fb, device, index, pfb);
}
