/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>

#include <metal/spi.h>

#ifdef metal_spi_1
/* Get SPI 1 */
#define spi metal_spi_1
#else
#ifdef metal_spi_0
/* Fallback to SPI 0 */
#define spi metal_spi_0
#endif
#endif

int main() {
	printf("METAL SPI Driver Demo\n");

#ifdef spi
	/* Initialize the SPI device to 100_000 baud */
	metal_spi_init(spi, 100000);

	/* CPOL = 0, CPHA = 0, MSB-first, CS active low */
	struct metal_spi_config config = {
		.protocol = METAL_SPI_SINGLE,
		.polarity = 0,
		.phase = 0,
		.little_endian = 0,
		.cs_active_high = 0,
		.csid = 0,
	};

	/* Transfer three bytes */
	char tx_buf[3] = {0x55, 0xAA, 0xA5};
	char rx_buf[3] = {0};

	metal_spi_transfer(spi, &config, 3, tx_buf, rx_buf);
#endif

	return 0;
}
