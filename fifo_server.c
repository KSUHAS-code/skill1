#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME "server_fifo"

int main() {
    char buffer[100];

    mkfifo(FIFO_NAME, 0666);

    printf("FIFO Server started...\n");
    printf("Waiting for client messages...\n");

    int fd = open(FIFO_NAME, O_RDONLY);

    while (1) {
        int n = read(fd, buffer, sizeof(buffer) - 1);

        if (n > 0) {
            buffer[n] = '\0';

            printf("Server received: %s\n", buffer);

            if (strcmp(buffer, "exit\n") == 0 ||
                strcmp(buffer, "exit") == 0) {
                break;
            }
        }
    }

    close(fd);
    unlink(FIFO_NAME);

    printf("Server terminated.\n");

    return 0;
}
