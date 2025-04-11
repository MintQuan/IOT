#include "dht11.h"
#include "system.h"
#include "io.h"

// DHT11 PIO base address
#define DHT11_BASE DHT11_0_BASE

// Các macro thao tác PIO
#define DHT11_SET_OUTPUT() IOWR_ALTERA_AVALON_PIO_DIRECTION(DHT11_BASE, 1)
#define DHT11_SET_INPUT()  IOWR_ALTERA_AVALON_PIO_DIRECTION(DHT11_BASE, 0)
#define DHT11_WRITE(val)   IOWR(DHT11_BASE, 0, (val))
#define DHT11_READ()       IORD(DHT11_BASE, 0)

void delay_us(unsigned int us) {
    volatile unsigned int i;
    for (i = 0; i < (us * 50); i++) {
        __asm__ volatile ("nop");
    }
}

void DHT11_init(void) {
    DHT11_SET_INPUT();
}

static bool DHT11_wait_for_level(int level, unsigned int timeout_us) {
    while (timeout_us--) {
        if (DHT11_READ() == level) return true;
        delay_us(1);
    }
    return false;
}

bool DHT11_read(uint8_t *temperature, uint8_t *humidity) {
    uint8_t data[5] = {0};

    // Gửi tín hiệu Start
    DHT11_SET_OUTPUT();
    DHT11_WRITE(0);
    delay_us(18000); // giữ thấp ít nhất 18ms
    DHT11_WRITE(1);
    delay_us(20);
    DHT11_SET_INPUT();

    // Đợi DHT11 phản hồi
    if (!DHT11_wait_for_level(0, 80)) return false;
    if (!DHT11_wait_for_level(1, 80)) return false;

    // Bắt đầu đọc 40 bit
    for (int i = 0; i < 40; i++) {
        if (!DHT11_wait_for_level(0, 60)) return false;
        if (!DHT11_wait_for_level(1, 60)) return false;

        delay_us(30); // chờ giữa bit để xác định 0 hay 1

        uint8_t bit = DHT11_READ();
        data[i / 8] <<= 1;
        data[i / 8] |= bit;

        // đợi hết mức cao
        while (DHT11_READ() == 1);
    }

    uint8_t checksum = data[0] + data[1] + data[2] + data[3];
    if (checksum != data[4]) return false;

    *humidity = data[0];
    *temperature = data[2];

    return true;
}
