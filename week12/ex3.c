#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "stdio.h"
#include "string.h"
#include "linux/input.h"
#include "linux/input-event-codes.h"

#define SIZE 10

int checkCombination(struct input_event pressed[], int combination[], int n) {
    int flag = 1;
    for (int i = 0; i < n; i++) {
        int simFlag = 0;
        for (int j = 0; j < SIZE; j++) {
            if (pressed[j].code == combination[i]) {
                simFlag = 1;
            }
        }
        if (!simFlag) {
            flag = 0;
        }
    }
    if (n == 0) return 0;
    return flag;
}

int main() {
    char *devicePath = "/dev/input/by-path/pci-0000:00:14.0-usb-0:8.2:1.2-event-kbd";
    struct input_event ev;
    ssize_t n;
    int fd = open(devicePath, O_RDONLY);

    struct input_event pressed[SIZE];
    struct input_event emp;
    emp.code = 0;
    emp.value = 0;
    emp.type = 0;
    emp.time.tv_sec = 0;
    emp.time.tv_usec = 0;
    for (int i = 0; i < SIZE; i++) {
        pressed[i] = emp;
    }
    printf("LIST OF SHORTCUTS:\nP + E\nC + A + P\nO + M + G\n");

    for(;;) {
        n = read(fd, &ev, sizeof(ev));
        if (ev.type == EV_KEY) {
            if (ev.value == 0){
                for (int i = 0; i < SIZE; i++) {
                    if (pressed[i].code == ev.code) {
                        pressed[i] = emp;
                        break;
                    }
                }
            }
            if (ev.value == 1){
                for (int i = 0; i < SIZE; i++) {
                    if (pressed[i].code == emp.code && pressed[i].type == emp.type && pressed[i].value == emp.value) {
                        pressed[i] = ev;
                        break;
                    }
                }
            }
        }

        int combination1[] = {KEY_P, KEY_E};
        int combination3[] = {KEY_O, KEY_M, KEY_G};
        int combination2[] = {KEY_C, KEY_A, KEY_P};

        if (checkCombination(pressed, combination1, 2)) {
            printf("I passed the Exam!\n");
        }

        if (checkCombination(pressed, combination2, 3)) {
            printf("Get some cappuccino!\n");
        }

        if (checkCombination(pressed, combination3, 3)) {
            printf("OMG\n");
        }

    }
    return 0;
}