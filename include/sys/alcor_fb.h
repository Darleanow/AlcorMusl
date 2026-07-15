/*
 * <sys/alcor_fb.h> — userland access to the Alcor2 linear framebuffer.
 *
 * Part of the Alcor2 libc contract (forked musl). Wraps SYS_ALCOR_FB_INFO /
 * SYS_ALCOR_FB_MMAP behind one verb; the kernel's packed geometry record stays
 * private to the wrapper and never reaches callers.
 */
#ifndef _SYS_ALCOR_FB_H
#define _SYS_ALCOR_FB_H

#include <stdint.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Friendly framebuffer handle filled by alcor_fb_open(). */
typedef struct
{
	void    *pixels; /* first mapped pixel, or 0 on failure */
	uint32_t width;
	uint32_t height;
	uint32_t pitch; /* bytes per row */
	uint32_t bpp;
} alcor_fb_t;

/*
 * Query geometry and map the framebuffer. Returns 0 on success and fills @out,
 * or -1 on failure (with @out->pixels == 0).
 */
static inline int alcor_fb_open(alcor_fb_t *out)
{
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
