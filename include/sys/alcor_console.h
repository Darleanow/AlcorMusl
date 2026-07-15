/**
 * @file include/sys/alcor_console.h
 * @brief Userland control of the framebuffer console.
 *
 * Part of the Alcor2 libc contract (forked musl). Lets a graphical app hand
 * the framebuffer back and forth with the kernel console and submit a glyph
 * atlas. The atlas descriptor is a genuine multi-field record, so it is a
 * public (but stable) struct; the ioctl codes stay private.
 */
#ifndef _SYS_ALCOR_CONSOLE_H
#define _SYS_ALCOR_CONSOLE_H

#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Glyph atlas submitted via ::alcor_console_set_atlas.
 *
 * Fixed ABI — must stay byte-identical to the kernel's
 * @c fb_console_atlas_t.
 */
typedef struct
{
	uint64_t pixels_user;   /**< VA of the glyph atlas pixel data. */
	uint32_t pixels_size;   /**< Total atlas bytes. */
	uint32_t cell_w;        /**< Glyph cell width in pixels. */
	uint32_t cell_h;        /**< Glyph cell height in pixels. */
	uint32_t stride_bytes;  /**< Bytes per row of a single cell. */
	uint32_t bpp;           /**< Atlas bpp — must match framebuffer. */
	uint32_t n_glyphs;      /**< Total glyph slots. */
	uint64_t cp_map_user;   /**< VA of u32[n_cp] codepoint→glyph_idx. */
	uint32_t n_cp;          /**< Size of cp_map (codepoints 0..n_cp-1). */
	uint32_t fallback_idx;  /**< Glyph for unmapped codepoints. */
	uint32_t bold_offset;   /**< First bold glyph slot; 0 = none. */
	uint32_t italic_offset; /**< First italic glyph slot; 0 = none. */
} alcor_console_atlas_t;

/* Kernel ioctl ABI — Linux-style _IOC encoding, group 'F' = fb console.
 * Private to these wrappers; keep in sync with the kernel headers. */
#define _ALCOR_IOC_CONSOLE_SET_ATLAS                                           \
	((1U << 30) | ((unsigned)'F' << 8) | 1U |                              \
	 (sizeof(alcor_console_atlas_t) << 16))
#define _ALCOR_IOC_CONSOLE_YIELD   ((unsigned)('F' << 8) | 2U)
#define _ALCOR_IOC_CONSOLE_RECLAIM ((unsigned)('F' << 8) | 3U)

/**
 * @brief Submit a glyph atlas to the kernel console.
 * @param atlas Atlas descriptor; the kernel copies the referenced buffers.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_console_set_atlas(const alcor_console_atlas_t *atlas)
{
	return ioctl(STDOUT_FILENO, _ALCOR_IOC_CONSOLE_SET_ATLAS, atlas);
}

/**
 * @brief Release the framebuffer for raw mmap drawing.
 *
 * The console stops painting (cursor included) until ::alcor_console_reclaim.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_console_yield(void)
{
	return ioctl(STDOUT_FILENO, _ALCOR_IOC_CONSOLE_YIELD, 0);
}

/**
 * @brief Resume kernel console rendering and repaint the grid.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_console_reclaim(void)
{
	return ioctl(STDOUT_FILENO, _ALCOR_IOC_CONSOLE_RECLAIM, 0);
}

#ifdef __cplusplus
}
#endif
#endif /* _SYS_ALCOR_CONSOLE_H */
