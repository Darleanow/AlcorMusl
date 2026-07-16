/**
 * @file include/sys/alcor_tty.h
 * @brief Userland TTY job-control helper.
 *
 * Wraps @c SYS_ALCOR_SET_FG_PID, which has no standard POSIX equivalent.
 */
#ifndef _SYS_ALCOR_TTY_H
#define _SYS_ALCOR_TTY_H

#include <sys/syscall.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Register the current TTY foreground PID.
 *
 * Canonical-mode VINTR (Ctrl+C) delivers @c SIGINT to that job instead of the
 * shell.
 * @param pid PID to register, or 0 to clear.
 * @return 0 on success, negative errno on failure.
 */
static inline long alcor_set_fg_pid(long pid)
{
	return syscall(SYS_ALCOR_SET_FG_PID, pid);
}

#ifdef __cplusplus
}
#endif
#endif /* _SYS_ALCOR_TTY_H */
