#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "stdio.h"
#include "string.h"
#include "linux/input.h"
#include "linux/input-event-codes.h"

static const char *const evval[2] = {
        "RELEASED",
        "PRESSED ",
};

int main() {
    char *path = "/dev/input/by-path/pci-0000:00:14.0-usb-0:8.2:1.2-event-kbd";
    struct input_event ev;
    ssize_t n;
    int fd = open(path, O_RDONLY);


    for(;;) {
        n = read(fd, &ev, sizeof(ev));

        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 1) {
            printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
        }

    }
    return 0;
}