#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 8192

int main(int argc, char *argv[])
{
    FILE *src, *dest;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    clock_t start, end;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    src = fopen(argv[1], "rb");

    if (src == NULL)
    {
        perror("Error opening source");
        return 1;
    }

    dest = fopen(argv[2], "wb");

    if (dest == NULL)
    {
        perror("Error opening destination");
        fclose(src);
        return 1;
    }

    start = clock();

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0)
    {
        if (fwrite(buffer, 1, bytes_read, dest) != bytes_read)
        {
            perror("Error writing file");
            fclose(src);
            fclose(dest);
            return 1;
        }
    }

    if (ferror(src))
    {
        perror("Error reading file");
        fclose(src);
        fclose(dest);
        return 1;
    }

    end = clock();

    printf("File copied successfully using standard library I/O.\n");
    printf("Execution time: %.6f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    fclose(src);
    fclose(dest);

    return 0;
}
