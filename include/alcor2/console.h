/*
 * <alcor2/console.h> — userland control of the framebuffer console.
 *
 * Part of the Alcor2 libc contract (forked musl). Lets a graphical app hand
 * the framebuffer back and forth with the kernel console and submit a glyph
 * atlas. The atlas descriptor is a genuine multi-field record, so it is a
 * public (but stable) struct; the ioctl codes stay private.
 */
#ifndef _ALCOR2_CONSOLE_H
#define _ALCOR2_CONSOLE_H

#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Glyph atlas submitted via alcor_console_set_atlas(). Layout is fixed ABI and
 * must stay byte-identical to the kernel's fb_console_atlas_t.
 */
typedef struct
{
	uint64_t pixels_user;   /* VA of the glyph atlas pixel data */
	uint32_t pixels_size;   /* total atlas bytes */
	uint32_t cell_w;        /* glyph cell width in pixels */
	uint32_t cell_h;        /* glyph cell height in pixels */
	uint32_t stride_bytes;  /* bytes per row of a single cell */
	uint32_t bpp;           /* atlas bpp — must match framebuffer */
	uint32_t n_glyphs;      /* total glyph slots */
	uint64_t cp_map_user;   /* VA of u32[n_cp] codepoint→glyph_idx */
	uint32_t n_cp;          /* size of cp_map (codepoints 0..n_cp-1) */
	uint32_t fallback_idx;  /* glyph for unmapped codepoints */
	uint32_t bold_offset;   /* first bold glyph slot; 0 = none */
	uint32_t italic_offset; /* first italic glyph slot; 0 = none */
} alcor_console_atlas_t;

/* Linux-style _IOC encoding, group 'F' = fb console; private here. */
#define _ALCOR_IOC_CONSOLE_SET_ATLAS                                           \
	((1U << 30) | ((unsigned)'F' << 8) | 1U |                              \
	 (sizeof(alcor_console_atlas_t) << 16))
#define _ALCOR_IOC_CONSOLE_YIELD   ((unsigned)('F' << 8) | 2U)
#define _ALCOR_IOC_CONSOLE_RECLAIM ((unsigned)('F' << 8) | 3U)

/* Submit a glyph atlas to the kernel console. 0 on success. */
static inline int alcor_console_set_atlas(const alcor_console_atlas_t *atlas)
{
	return ioctl(STDOUT_FILENO, _ALCOR_IOC_CONSOLE_SET_ATLAS, atlas);
}

/* Release the framebuffer for raw mmap drawing (console stops painting). */
static inline int alcor_console_yield(void)
{
	return ioctl(STDOUT_FILENO, _ALCOR_IOC_CONSOLE_YIELD, 0);
}

/* Resume kernel console rendering and repaint the grid. */
static inline int alcor_console_reclaim(void)
{
	return ioctl(STDOUT_FILENO, _ALCOR_IOC_CONSOLE_RECLAIM, 0);
}

#ifdef __cplusplus
}
#endif
#endif /* _ALCOR2_CONSOLE_H */
