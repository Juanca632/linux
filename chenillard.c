#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LED_COUNT 4
const char* leds[LED_COUNT] = {
    "/sys/class/leds/fpga_led1/brightness",
    "/sys/class/leds/fpga_led2/brightness",
    "/sys/class/leds/fpga_led3/brightness",
    "/sys/class/leds/fpga_led4/brightness"
};

void write_led(const char* path, int value) {
    FILE* f = fopen(path, "w");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }
    fprintf(f, "%d", value);
    fclose(f);
}

int main() {
    while (1) {
        for (int i = 0; i < LED_COUNT; i++) {
            // Turn all off
            for (int j = 0; j < LED_COUNT; j++)
                write_led(leds[j], 0);
            // Turn one on
            write_led(leds[i], 1);
            usleep(200000);  // 200ms
        }
    }
    return 0;
}
