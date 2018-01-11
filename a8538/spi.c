#include "spi.h"
#include <util/delay.h>

void SPI_Init(void)
{
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1);
    SPCR &= ~_BV(SPR0);

    SPSR = 0x00;
}
