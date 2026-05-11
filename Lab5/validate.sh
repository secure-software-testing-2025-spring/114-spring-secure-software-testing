#!/bin/bash

if [[ ! -f answer.txt ]]; then
  echo "[!] answer.txt not found."
  exit 1
fi

answer="FLAG{symbolic_execution_master}"
actual=$(grep -oE 'FLAG\{[^}]+\}' answer.txt | head -1)

if [[ "$actual" == "$answer" ]]; then
  echo "[V] Pass"
  exit 0
else
  echo "[!] Expected: $answer"
  echo "[!] Actual:   $actual"
  exit 1
fi

# vim: set fenc=utf8 ff=unix et sw=2 ts=2 sts=2:
