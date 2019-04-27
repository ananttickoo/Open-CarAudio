#pragma once
struct spi_read {
	int x;
	int y;
	int sw;
};

void* readAnalog();
void* read_spi_input();
struct spi_read G_spi;
