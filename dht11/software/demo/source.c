#include <stdio.h>
#include "dht11.h"
#include "system.h"

int main() {
    DHT11_Data data;

    while (1) {
        int ret = dht11_read((uint32_t *)DHT11_0_BASE, &data);
        if (ret == 0) {
            printf("Nhiet do: %d*C | Do am: %d%%\n", data.temperature, data.humidity);
        } else {
            printf("Doc DHT11 that bai. Loi: %d\n", ret);
        }
        usleep(2000000);
    }

    return 0;
}
