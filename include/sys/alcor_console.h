/**
 * @file include/sys/alcor_console.h
 * @brief Userland control of the framebuffer console.
 *
 * Verb wrappers over the ABI declared in <bits/alcor_console.h>.
 */
#ifndef _SYS_ALCOR_CONSOLE_H
#define _SYS_ALCOR_CONSOLE_H

#include <bits/alcor_console.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Submit a glyph atlas to the kernel console.
 * @param atlas Atlas descriptor; the kernel copies the referenced buffers.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_console_set_atlas(const alcor_console_atlas_t *atlas)
{
	return ioctl(STDOUT_FILENO, ALCOR_IOC_CONSOLE_SET_ATLAS, atlas);
}

/**
 * @brief Release the framebuffer for raw mmap drawing.
 *
 * The console stops painting until ::alcor_console_reclaim.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_console_yield(void)
{
	return ioctl(STDOUT_FILENO, ALCOR_IOC_CONSOLE_YIELD, 0);
}

/**
 * @brief Resume kernel console rendering and repaint the grid.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_console_reclaim(void)
{
	return ioctl(STDOUT_FILENO, ALCOR_IOC_CONSOLE_RECLAIM, 0);
}

#ifdef __cplusplus
}
#endif
#endif /* _SYS_ALCOR_CONSOLE_H */
