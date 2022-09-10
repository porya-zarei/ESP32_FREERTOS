#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "sdspi_host.h"

#define PIN_NUM_MISO 12
#define PIN_NUM_MOSI 13
#define PIN_NUM_CLK 14
#define PIN_NUM_CS 15
#define MOUNT_POINT "/sd"

void sd_init(sdmmc_card_t *card, sdmmc_host_t *host, char *mount_point);
char *sdcard_read(sdmmc_card_t *card, sdmmc_host_t *host, char *mount_point, char *path, const int read_size);