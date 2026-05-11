/*
 * Lab5 crackme
 *
 * Password (16 bytes) unlocks the encrypted FLAG embedded in `enc`.
 * Constraints are designed to have a unique satisfying assignment so
 * angr always solves to the same password and prints the same flag.
 *
 * Build:
 *   gcc -O0 -no-pie -fno-stack-protector -o crackme crackme.c
 */
#include <stdio.h>
#include <string.h>

#define PASSWORD_LEN 16
#define FLAG_LEN     31

static const unsigned char enc[FLAG_LEN] = {
    0x27, 0x22, 0x26, 0x35, 0x24, 0x42, 0x4C, 0x32,
    0x56, 0x18, 0x5F, 0x5C, 0x53, 0x32, 0x56, 0x59,
    0x04, 0x0D, 0x12, 0x06, 0x36, 0x5E, 0x5B, 0x00,
    0x59, 0x16, 0x40, 0x41, 0x55, 0x1F, 0x4E,
};

int main(int argc, char **argv) {
    if (argc != 2) {
        puts("Usage: ./crackme <password>");
        return 1;
    }

    const unsigned char *p = (const unsigned char *)argv[1];
    if (strlen((const char *)p) != PASSWORD_LEN) goto wrong;

    for (int i = 0; i < PASSWORD_LEN; i++) {
        if (p[i] < 0x20 || p[i] > 0x7E) goto wrong;
    }

    if ((p[0] ^ 0x42) != 0x23)                       goto wrong;
    if (((p[1] + 7) & 0xFF) != 0x75)                 goto wrong;
    if (p[2] != (unsigned char)(p[0] + 6))           goto wrong;
    if ((p[3] ^ p[2]) != 0x15)                       goto wrong;
    if ((p[4] ^ 0xAA) != 0xF5)                       goto wrong;
    if ((p[5] - 0x10) != 0x21)                       goto wrong;
    if ((p[6] ^ 0x42) != 0x77)                       goto wrong;
    if (p[7] != p[4])                                goto wrong;
    if ((p[8] + 0x10) != 0x44)                       goto wrong;
    if (((unsigned char)(p[9] * 2)) != 0xEE)         goto wrong;
    if ((p[10] ^ p[8]) != 0x07)                      goto wrong;
    if (p[11] != p[6])                               goto wrong;
    if ((p[12] - 5) != 0x2B)                         goto wrong;
    if ((p[13] ^ 0x0F) != 0x62)                      goto wrong;
    if (p[14] != p[10])                              goto wrong;
    if ((p[15] ^ p[13]) != 0x4C)                     goto wrong;

    char flag[FLAG_LEN + 1] = {0};
    for (int i = 0; i < FLAG_LEN; i++) {
        flag[i] = enc[i] ^ p[i % PASSWORD_LEN];
    }
    puts(flag);
    return 0;

wrong:
    puts("Wrong!");
    return 1;
}
