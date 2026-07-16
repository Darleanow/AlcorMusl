/**
 * @file arch/generic/bits/alcor_fb.h
 * @brief Alcor2 framebuffer ABI, single source of the contract.
 *
 * Consumed by the Alcor2 kernel and by <sys/alcor_fb.h>. Must stay
 * self-contained: fixed-width integer types only, no libc dependencies.
 */
#ifndef _BITS_ALCOR_FB_H
#define _BITS_ALCOR_FB_H

#include <stdint.h>

/** @brief Framebuffer geometry filled by the ALCOR_FB_INFO syscall. */
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
