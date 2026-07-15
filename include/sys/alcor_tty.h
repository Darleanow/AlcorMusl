/*
 * <sys/alcor_tty.h> — userland TTY job-control helper.
 *
 * Part of the Alcor2 libc contract (forked musl). Wraps SYS_ALCOR_SET_FG_PID,
 * which has no standard POSIX equivalent.
 */
#ifndef _SYS_ALCOR_TTY_H
#define _SYS_ALCOR_TTY_H

#include <sys/syscall.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Register the current TTY foreground PID so canonical-mode VINTR (Ctrl+C)
 * delivers SIGINT to that job. Pass 0 to clear. 0 on success, -errno on
 * failure.
 */
static inline long alcor_set_fg_pid(long pid)
{
	return syscall(SYS_ALCOR_SET_FG_PID, pid);
}

#ifdef __cplusplus
}
#endif
#endif /* _SYS_ALCOR_TTY_H */
