#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: ./recover card.raw\n"); return 1; }
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL) return 1;
    uint8_t buffer[512];
    FILE *outptr = NULL;
    char filename[8];
    int count = 0;
    while (fread(buffer, 512, 1, inptr)) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            if (outptr != NULL) fclose(outptr);
            sprintf(filename, "%03i.jpg", count++);
            outptr = fopen(filename, "w");
        }
        if (outptr != NULL) fwrite(buffer, 512, 1, outptr);
    }
    if (outptr != NULL) fclose(outptr);
    fclose(inptr);
}
