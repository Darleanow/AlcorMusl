# AlcorMusl

Fork of musl carrying the Alcor2OS ABI: the `alcor_*` files under
`arch/generic/bits/` and `include/sys/`, plus one `#include` line in
`include/sys/syscall.h`. Upstream files are otherwise untouched.

## Branch policy

- `alcor2` is append-only: no rebase, no force-push. Alcor2OS pins it as a
  submodule; rewriting history would orphan every recorded pin.
- Upstream musl comes in as merge commits, never rebases.
- ABI changes are additive when possible; a breaking change bumps
  `ALCOR_ABI_VERSION` and gets a lightweight tag (`abi-v1`, `abi-v2`, ...).
