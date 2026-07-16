/**
 * @file arch/generic/bits/alcor_console.h
 * @brief Framebuffer console ABI: glyph atlas record and console ioctls.
 */
#ifndef _BITS_ALCOR_CONSOLE_H
#define _BITS_ALCOR_CONSOLE_H

#include <stdint.h>

/** @brief Glyph atlas descriptor submitted via ::ALCOR_IOC_CONSOLE_SET_ATLAS. */
typedef struct
{
	uint64_t pixels_user;   /**< VA of the glyph atlas pixel data. */
	uint32_t pixels_size;   /**< Total atlas bytes. */
	uint32_t cell_w;        /**< Glyph cell width in pixels. */
	uint32_t cell_h;        /**< Glyph cell height in pixels. */
	uint32_t stride_bytes;  /**< Bytes per row of a single cell. */
	uint32_t bpp;           /**< Atlas bpp, must match the framebuffer. */
	uint32_t n_glyphs;      /**< Total glyph slots. */
	uint64_t cp_map_user;   /**< VA of uint32_t[n_cp] codepoint to glyph index map. */
	uint32_t n_cp;          /**< Size of cp_map, covers codepoints 0 to n_cp-1. */
	uint32_t fallback_idx;  /**< Glyph for unmapped codepoints. */
	uint32_t bold_offset;   /**< First bold glyph slot, 0 when absent. */
	uint32_t italic_offset; /**< First italic glyph slot, 0 when absent. */
} alcor_console_atlas_t;

/** @brief ioctl, group 'F': submit an ::alcor_console_atlas_t descriptor. */
#define ALCOR_IOC_CONSOLE_SET_ATLAS                                            \
	((1U << 30) | ((uint32_t)'F' << 8) | 1U |                              \
	 (sizeof(alcor_console_atlas_t) << 16))

/** @brief ioctl, group 'F': release the framebuffer to the application. */
#define ALCOR_IOC_CONSOLE_YIELD ((uint32_t)('F' << 8) | 2U)

/** @brief ioctl, group 'F': return the framebuffer to the kernel console. */
#define ALCOR_IOC_CONSOLE_RECLAIM ((uint32_t)('F' << 8) | 3U)

#endif /* _BITS_ALCOR_CONSOLE_H */
