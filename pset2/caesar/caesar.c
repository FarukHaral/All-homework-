#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[]) {
    if (argc != 2) { printf("Usage: ./caesar key\n"); return 1; }
    for (int i = 0; i < strlen(argv[1]); i++) {
        if (!isdigit(argv[1][i])) { printf("Usage: ./caesar key\n"); return 1; }
    }
    int k = atoi(argv[1]);
    string p = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(p); i++) {
        if (isupper(p[i])) printf("%c", (p[i] - 'A' + k) % 26 + 'A');
        else if (islower(p[i])) printf("%c", (p[i] - 'a' + k) % 26 + 'a');
        else printf("%c", p[i]);
    }
    printf("\n");
}
