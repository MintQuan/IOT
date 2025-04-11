#include "dht11.h"
#include <stdio.h>

int main() {
    uint8_t temp, hum;

    printf("Initializing DHT11...\n");
    DHT11_init();

    while (1) {
        if (DHT11_read(&temp, &hum)) {
            printf("Temperature: %d°C, Humidity: %d%%\n", temp, hum);
        } else {
            printf("Failed to read from DHT11\n");
        }

        // Đợi 2s để đọc lại
        for (volatile long i = 0; i < 5000000; i++); // delay approx 2s
    }

    return 0;
}
