#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[]) {
    if (argc != 2) { printf("Usage: ./substitution key\n"); return 1; }
    if (strlen(argv[1]) != 26) { printf("Key must contain 26 characters.\n"); return 1; }
    for (int i = 0; i < 26; i++) {
        if (!isalpha(argv[1][i])) return 1;
        for (int j = i + 1; j < 26; j++) {
            if (toupper(argv[1][i]) == toupper(argv[1][j])) return 1;
        }
    }
    string p = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(p); i++) {
        if (isupper(p[i])) printf("%c", toupper(argv[1][p[i] - 'A']));
        else if (islower(p[i])) printf("%c", tolower(argv[1][p[i] - 'a']));
        else printf("%c", p[i]);
    }
    printf("\n");
}
