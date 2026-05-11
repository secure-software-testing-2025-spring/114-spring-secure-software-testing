# Lab5

## Introduction

In this lab, you will use **symbolic execution** to defeat a small crackme. The binary `./crackme` accepts a 16-byte password as `argv[1]`; if the password satisfies every constraint inside `main`, the binary decrypts and prints a FLAG of the form `FLAG{...}`. Your job is to recover that FLAG.

References worth skimming before you start:

- angr documentation — [Toplevel interface](https://docs.angr.io/core-concepts/toplevel) and [Symbolic execution](https://docs.angr.io/core-concepts/pathgroups)
- [angr_ctf](https://github.com/jakespringer/angr_ctf) walkthroughs (challenges `00`–`02` cover the basics you need here)

## Requirement

Recover the FLAG hidden inside `./crackme` and write it to `answer.txt` on a single line, e.g.:

```
FLAG{...}
```

`validate.sh` reads `answer.txt`, extracts the first `FLAG{...}` token, and compares it to the expected value.

### Grading

| Weight | Criterion |
|---|---|
| 40% | `./validate.sh` passes (the FLAG in `answer.txt` is correct). |
| 30% | You use **angr** to derive the FLAG. The crackme is small enough that pure manual reverse engineering can also recover the FLAG, but this lab is about symbolic execution — your `solve.py` must drive angr to produce the answer. |
| 30% | You submit a report (see *Submission* below) that explains your work. |

### Setup

```sh
python3 -m pip install -r requirements.txt
```

angr supports Python 3.10–3.13. If you're on a newer interpreter, create a virtual environment with a supported version first.

Please note that you must not alter `crackme`, `validate.sh`, or `README.md`. You will get 0 points if

1. You modify any file other than `solve.py`, `answer.txt`, `requirements.txt`, or your `report.md`.
2. You can't pass all CI on your PR.

## Submission

Commit and push the following to your repository:

1. `answer.txt` containing the recovered FLAG.
2. `solve.py` filled in with your angr script.
3. A short **report** in Markdown format. The file must be named exactly `report.md` (no `.pdf`, `.docx`, or other extensions) and committed under `Lab5/`. The report should cover:
   - How you located the **win address** and the **avoid address** (which tool you used, screenshots or snippets of the relevant disassembly, and how you decided which block is which).
   - How you wrote `solve.py` with angr to recover the FLAG — at minimum: how you built the symbolic argv, which state options or constraints you added, how you drove the simulation manager, and how you read the FLAG out of the found state.
   - If you used AI tools (Claude Code, Codex, ChatGPT, Copilot, etc.), describe **how** you used them — what you asked, what you accepted or rejected, and how you verified the output. Using AI tools is allowed; not disclosing how you used them is not.
