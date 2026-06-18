/*
 * <alcor2/input.h> — userland keyboard-layout and mouse verbs.
 *
 * Part of the Alcor2 libc contract (forked musl). The ioctl request codes are
 * an implementation detail of these wrappers; callers deal only in verbs,
 * scalars, and the layout enum.
 */
#ifndef _ALCOR2_INPUT_H
#define _ALCOR2_INPUT_H

#include <fcntl.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Keyboard layouts (argument to alcor_kbd_set_layout). */
typedef enum
{
	ALCOR_KBD_US = 0, /* US QWERTY */
	ALCOR_KBD_FR = 1  /* AZERTY lettering on a US scan map */
} alcor_kbd_layout_t;

/* _IOW encoding, group 'K' = keyboard, 'T' = timer-adjacent; private here. */
#define _ALCOR_IOC_KBD_SET_LAYOUT                                              \
	((1U << 30) | (0x4BU << 8) | 1U | (sizeof(uint32_t) << 16))
#define _ALCOR_IOC_KBD_RELEASE_EVENTS                                          \
	((1U << 30) | (0x4BU << 8) | 2U | (sizeof(uint32_t) << 16))
/* _IOW, group 'M' = mouse. */
#define _ALCOR_IOC_MOUSE_SET_RELATIVE                                          \
	((1U << 30) | ((unsigned)'M' << 8) | 1U | (4U << 16))

/* Set the active keyboard layout on the controlling tty. 0 on success. */
static inline int alcor_kbd_set_layout(alcor_kbd_layout_t layout)
{
	uint32_t id = (uint32_t)layout;
	return ioctl(0, _ALCOR_IOC_KBD_SET_LAYOUT, &id);
}

/*
 * Toggle \x00<char> key-release sentinels (needed to track simultaneously
 * held keys, e.g. diagonal movement). 0 on success.
 */
static inline int alcor_kbd_set_release_events(int on)
{
	uint32_t v = on ? 1U : 0U;
	return ioctl(0, _ALCOR_IOC_KBD_RELEASE_EVENTS, &v);
}

/* Open /dev/mouse non-blocking. Returns the fd, or -1. */
static inline int alcor_mouse_open(void)
{
	return open("/dev/mouse", O_RDONLY | O_NONBLOCK);
}

/* Pin the cursor and pass raw deltas (relative mode) when @on. 0 on success. */
static inline int alcor_mouse_set_relative(int fd, int on)
{
	uint32_t v = on ? 1U : 0U;
	return ioctl(fd, _ALCOR_IOC_MOUSE_SET_RELATIVE, &v);
}

/*
 * Read one pending mouse event. Returns 1 and fills the non-null out-params on
 * an event, 0 when none is queued, or -1 on error. The on-wire event record is
 * private to this wrapper.
 */
static inline int
alcor_mouse_poll(int fd, int *dx, int *dy, int *dwheel, int *buttons)
{
	struct
	{
		int32_t dx, dy;
		int16_t dwheel;
		uint8_t buttons, flags;
	} ev;

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

static inline void alcor_mouse_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

#ifdef __cplusplus
}
#endif
#endif /* _ALCOR2_INPUT_H */
