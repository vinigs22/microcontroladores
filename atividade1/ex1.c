#include <stdio.h>
#include <stdint.h>

#define SENSOR_TEMP       (1 << 0)
#define SENSOR_UMIDADE    (1 << 1)
#define SENSOR_PRESSAO    (1 << 2)
#define SENSOR_LUZ        (1 << 3)
#define SENSOR_MOVIMENTO  (1 << 4)

uint8_t SENSOR_REG = 0;

inline void ligar_sensor(uint8_t *reg, uint8_t sensor) {
    *reg |= sensor;
}

inline void desligar_sensor(uint8_t *reg, uint8_t sensor) {
    *reg &= ~sensor;
}

inline uint8_t verificar_sensor(uint8_t *reg, uint8_t sensor) {
    return ((*reg & sensor) != 0);
}

int main() {
    ligar_sensor(&SENSOR_REG, SENSOR_TEMP);
    ligar_sensor(&SENSOR_REG, SENSOR_MOVIMENTO);

    printf("Estado apos ligar Temp e Movimento: 0x%02X\n", SENSOR_REG);

    desligar_sensor(&SENSOR_REG, SENSOR_TEMP);

    printf("Estado apos desligar Temp: 0x%02X\n", SENSOR_REG);

    if (verificar_sensor(&SENSOR_REG, SENSOR_PRESSAO)) {
        printf("Sensor de PRESSAO está LIGADO.\n");
    } else {
        printf("Sensor de PRESSAO está DESLIGADO.\n");
    }

    return 0;
}
