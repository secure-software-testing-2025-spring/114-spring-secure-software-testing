#!/bin/bash
# TA build script for Lab5 crackme binary.
# Cross-compiles scripts/lab5_crackme.c to Lab5/crackme as a Linux x86_64 ELF.
# Requires zig (https://ziglang.org) for cross-compilation from macOS / non-Linux.
#
# Usage (from repo root): ./scripts/build_lab5.sh
set -e

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
src="$repo_root/scripts/lab5_crackme.c"
out="$repo_root/Lab5/crackme"

if [[ "$(uname -s)" == "Linux" ]] && command -v gcc >/dev/null 2>&1; then
    gcc -O0 -no-pie -fno-stack-protector -o "$out" "$src"
elif command -v zig >/dev/null 2>&1; then
    zig cc -target x86_64-linux-gnu \
        -O0 -no-pie -fno-stack-protector -fno-sanitize=all \
        -o "$out" "$src"
else
    echo "[!] Need either Linux gcc or zig for cross-compilation." >&2
    exit 1
fi

file "$out"
