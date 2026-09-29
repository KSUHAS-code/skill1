#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "server_fifo"

int main() {
    char message[100];

    int fd = open(FIFO_NAME, O_WRONLY);

    if (fd == -1) {
        perror("Error opening FIFO");
        return 1;
    }

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    write(fd, message, sizeof(message));

    close(fd);

    printf("Message sent successfully.\n");

    return 0;
}
