# AlcorMusl

Fork of musl libc carrying the Alcor2OS userland ABI. Upstream musl is left
untouched; every Alcor2 addition is a new file, plus one `#include` line at the
end of `arch/x86_64/bits/syscall.h.in`.

## The ABI contract

These files are the single source of truth for the Alcor2 kernel/userland ABI.
The kernel consumes them through a staged copy (`build/abi/` in Alcor2OS); the
verb headers below wrap them for applications.

| File | Contents |
| --- | --- |
| `arch/x86_64/bits/alcor_syscall.h` | Custom syscall numbers (bit-31 namespace) |
| `arch/generic/bits/alcor_fb.h` | Framebuffer geometry struct |
| `arch/generic/bits/alcor_input.h` | Keyboard layouts, mouse event, input ioctls |
| `arch/generic/bits/alcor_console.h` | Console atlas struct and ioctls |
| `arch/generic/bits/alcor_timer.h` | Timer ioctl |

Contract rules:

- `bits/alcor_*.h` stay self-contained: `stdint.h` types only, no libc
  dependencies, so any future consumer (or libc) can vendor them verbatim.
- Custom syscall numbers carry `ALCOR_SYSCALL_BIT` (bit 31). Upstream numbers
  are positive C ints with bit 30 reserved for the x32 marker, so no upstream
  number can ever enter this space: collision is impossible by construction.
- Changes are additive whenever possible: new numbers, new fields at the end
  of structs. A breaking change bumps `ALCOR_ABI_VERSION`.
- One declaration per doc comment, no em-dashes, doxygen style, following the
  Alcor2OS conventions.

Application-facing verb wrappers: `include/sys/alcor_{fb,input,console,timer,tty}.h`.

## Branch policy

- `alcor2` is the integration branch and is append-only: no rebase, no
  force-push. Alcor2OS pins it as a submodule; rewriting history would orphan
  every recorded pin.
- Upstream musl updates come in as merge commits, never rebases.
- Every contract change gets a lightweight tag (`abi-v1`, `abi-v2`, ...).
