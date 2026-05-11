#!/usr/bin/env python3
"""TA reference solver — finds password and prints the decrypted FLAG."""

import sys

import angr
import claripy

BINARY = "./crackme"
PASSWORD_LEN = 16

FIND_ADDR = 0x4013EE
AVOID_ADDR = 0x401429


def main():
    proj = angr.Project(BINARY, auto_load_libs=False)

    sym_arg = claripy.BVS("argv1", PASSWORD_LEN * 8)
    state = proj.factory.entry_state(args=[BINARY, sym_arg])

    for i in range(PASSWORD_LEN):
        b = sym_arg.get_byte(i)
        state.solver.add(b >= 0x20)
        state.solver.add(b <= 0x7E)

    simgr = proj.factory.simulation_manager(state)
    simgr.explore(find=FIND_ADDR, avoid=AVOID_ADDR)

    if not simgr.found:
        print("[!] No password found", file=sys.stderr)
        sys.exit(1)

    found = simgr.found[0]
    password = found.solver.eval(sym_arg, cast_to=bytes)
    print(f"[*] password = {password!r}", file=sys.stderr)

    stdout = found.posix.dumps(1).decode(errors="replace")
    for line in stdout.splitlines():
        if line.startswith("FLAG{"):
            print(line)
            return

    print(stdout)


if __name__ == "__main__":
    main()
