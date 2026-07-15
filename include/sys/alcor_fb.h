/**
 * @file include/sys/alcor_fb.h
 * @brief Userland access to the Alcor2 linear framebuffer.
 *
 * Part of the Alcor2 libc contract (forked musl). Wraps @c SYS_ALCOR_FB_INFO
 * and @c SYS_ALCOR_FB_MMAP behind one verb; the kernel's packed geometry
 * record stays private to the wrapper and never reaches callers.
 */
#ifndef _SYS_ALCOR_FB_H
#define _SYS_ALCOR_FB_H

#include <stdint.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Framebuffer handle filled by ::alcor_fb_open. */
typedef struct
{
	void    *pixels; /**< First mapped pixel, or 0 on failure. */
	uint32_t width;  /**< Width in pixels. */
	uint32_t height; /**< Height in pixels. */
	uint32_t pitch;  /**< Bytes per row. */
	uint32_t bpp;    /**< Bits per pixel. */
} alcor_fb_t;

/**
 * @brief Query geometry and map the framebuffer into the process.
 * @param out Handle to fill; @c out->pixels is 0 on failure.
 * @return 0 on success, -1 on failure.
 */
static inline int alcor_fb_open(alcor_fb_t *out)
{
	/* Mirrors the kernel's alcor_fb_info_t byte for byte — keep in sync. */
	struct
	{
		uint32_t width, height, pitch;
		uint16_t bpp, _pad;
		uint64_t byte_len, map_size;
	} __attribute__((packed)) info;

	if (!out)
		return -1;
	if (syscall(SYS_ALCOR_FB_INFO, &info) < 0)
		return (out->pixels = 0), -1;

	long p = syscall(SYS_ALCOR_FB_MMAP, 0UL, 0UL);
	if (p < 0)
		return (out->pixels = 0), -1;

	out->pixels = (void *)p;
	out->width  = info.width;
	out->height = info.height;
	out->pitch  = info.pitch;
	out->bpp    = info.bpp;
	return 0;
}

#ifdef __cplusplus
}
#endif
#endif /* _SYS_ALCOR_FB_H */
