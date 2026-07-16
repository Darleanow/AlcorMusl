/**
 * @file arch/generic/bits/alcor_fb.h
 * @brief Framebuffer geometry record returned by the ALCOR_FB_INFO syscall.
 */
#ifndef _BITS_ALCOR_FB_H
#define _BITS_ALCOR_FB_H

#include <stdint.h>

/** @brief Geometry of the linear framebuffer. */
typedef struct __attribute__((packed))
{
	uint32_t width;    /**< Width in pixels. */
	uint32_t height;   /**< Height in pixels. */
	uint32_t pitch;    /**< Bytes per row. */
	uint16_t bpp;      /**< Bits per pixel. */
	uint16_t _pad;     /**< Reserved padding, zero. */
	uint64_t byte_len; /**< Active bytes: pitch times height. */
	uint64_t map_size; /**< Mappable span in bytes, page aligned. */
} alcor_fb_info_t;

#endif /* _BITS_ALCOR_FB_H */
