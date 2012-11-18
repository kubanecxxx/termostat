/*
 * rfm_port.c
 *
 *  Created on: 5.6.2012
 *      Author: kubanec
 */

#include "rfm_port.h"

typedef struct
{
	GPIO_TypeDef * gpio;
	uint8_t pin;
} gpio_t;

typedef enum
{
	SCK = 0, MISO, MOSI, NSS, FFIT, NIRQ, LAST
} chatra;

static const gpio_t gpio[LAST] =
{
{ GPIOB, 3 },
{ GPIOB, 4 },
{ GPIOB, 5 },
{ GPIOB, 6 },
{ GPIOD, 5 },
{ GPIOD, 6 } };

#define SPI_PIN_LOW(x) (gpio[x].gpio->BSRR.H.clear |= 1<<gpio[x].pin)
#define SPI_PIN_HIGH(x) (gpio[x].gpio->BSRR.H.set  |= 1<<gpio[x].pin)
#define SPI_PIN_READ(x) ((gpio[x].gpio->IDR >> gpio[x].pin) & 1)

#define rfmSetPadMode(co, jak) palSetPadMode(gpio[co].gpio,gpio[co].pin,jak)

void low_level_spi_init(void)
{
	rfmSetPadMode(SCK, PAL_MODE_OUTPUT_PUSHPULL);
	rfmSetPadMode(MISO, PAL_MODE_INPUT);
	rfmSetPadMode(MOSI, PAL_MODE_OUTPUT_PUSHPULL);
	rfmSetPadMode(NSS, PAL_MODE_OUTPUT_PUSHPULL);
	rfmSetPadMode(FFIT, PAL_MODE_INPUT);
	rfmSetPadMode(NIRQ, PAL_MODE_INPUT);

	extChannelEnable(&EXTD1, FFIT);
}

uint16_t low_level_spi_in_out(uint16_t cmd)
{
	unsigned char i;
	unsigned int recv = 0;

	SPI_PIN_LOW(SCK);
	SPI_PIN_LOW(NSS);
	for (i = 0; i < 16; i++)
	{
		if (cmd & 0x8000)
			SPI_PIN_HIGH(MOSI);
		else
			SPI_PIN_LOW(MOSI);
		SPI_PIN_HIGH(SCK);

		recv <<= 1;
		recv += SPI_PIN_READ(MISO);

		SPI_PIN_LOW(SCK);
		cmd <<= 1;
	}
	SPI_PIN_HIGH(NSS);
	return recv;
}

/**
 * @todo časem by se to mohlo zkusit trochu inteligentně přes přerušeni a pak DMA
 * šlo by sem naházet event wait a v externich přerušenich je broadcastit
 */
static Thread * ffit_thd = NULL;

void rf_ffitThreadInit(void)
{
	if (ffit_thd == NULL )
		ffit_thd = chThdSelf();
}

void low_level_wait_ffit_high(void)
{
	chEvtWaitAnyTimeout(1, MS2ST(10) );
	/*
	 while (SPI_PIN_READ(FFIT) == 0)
	 continue;
	 */
}

void low_level_wait_nirq_low(void)
{
	while (SPI_PIN_READ(NIRQ) == 1)
		continue;
}

void ffit_exti(EXTDriver *extp, expchannel_t channel)
{
	(void) channel;
	(void) extp;
	chSysLockFromIsr()
	;
	chEvtSignalFlagsI(ffit_thd, 0b11);
	chSysUnlockFromIsr();
}
