/**
 * @file include/sys/alcor_input.h
 * @brief Userland keyboard-layout and mouse verbs.
 *
 * Verb wrappers over the ABI declared in <bits/alcor_input.h>.
 */
#ifndef _SYS_ALCOR_INPUT_H
#define _SYS_ALCOR_INPUT_H

#include <bits/alcor_input.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the active keyboard layout on the controlling tty.
 * @param layout One of ::alcor_kbd_layout_t.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_kbd_set_layout(alcor_kbd_layout_t layout)
{
	uint32_t id = (uint32_t)layout;
	return ioctl(0, ALCOR_IOC_KBD_SET_LAYOUT, &id);
}

/**
 * @brief Toggle @c \\x00<char> key-release sentinels.
 *
 * Needed to track simultaneously held keys; PS/2 typematic only repeats the
 * last key pressed.
 * @param on Non-zero to enable, 0 to disable.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_kbd_set_release_events(int on)
{
	uint32_t v = on ? 1U : 0U;
	return ioctl(0, ALCOR_IOC_KBD_RELEASE_EVENTS, &v);
}

/**
 * @brief Open @c /dev/mouse in non-blocking mode.
 * @return The file descriptor, or -1 on failure.
 */
static inline int alcor_mouse_open(void)
{
	return open("/dev/mouse", O_RDONLY | O_NONBLOCK);
}

/**
 * @brief Toggle relative mode: cursor pinned, raw deltas pass through.
 * @param fd Descriptor from ::alcor_mouse_open.
 * @param on Non-zero to enable, 0 to disable.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_mouse_set_relative(int fd, int on)
{
	uint32_t v = on ? 1U : 0U;
	return ioctl(fd, ALCOR_IOC_MOUSE_SET_RELATIVE, &v);
}

/**
 * @brief Read one pending mouse event.
 * @param fd      Descriptor from ::alcor_mouse_open.
 * @param dx      Receives the X delta, may be NULL.
 * @param dy      Receives the Y delta, may be NULL.
 * @param dwheel  Receives the wheel delta, may be NULL.
 * @param buttons Receives the ALCOR_MOUSE_BTN_* bitmask, may be NULL.
 * @return 1 when an event was read, 0 when none is queued.
 */
static inline int
alcor_mouse_poll(int fd, int *dx, int *dy, int *dwheel, int *buttons)
{
	alcor_mouse_event_t ev;

	if (read(fd, &ev, sizeof(ev)) != (long)sizeof(ev))
		return 0;
	if (dx)
		*dx = ev.dx;
	if (dy)
		*dy = ev.dy;
	if (dwheel)
		*dwheel = ev.dwheel;
	if (buttons)
		*buttons = ev.buttons;
	return 1;
}

/**
 * @brief Close a mouse descriptor; no-op on negative @p fd.
 * @param fd Descriptor from ::alcor_mouse_open.
 */
static inline void alcor_mouse_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

#ifdef __cplusplus
}
#endif
#endif /* _SYS_ALCOR_INPUT_H */
