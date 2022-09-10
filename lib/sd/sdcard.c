#include "sdcard.h"

// sdmmc_host_t host = SDSPI_HOST_DEFAULT();
// sdmmc_card_t *card;
void sd_init(sdmmc_card_t *card, sdmmc_host_t *host, char *mount_point)
{
    esp_err_t ret;
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
#ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
#else
        .format_if_mount_failed = false,
#endif // EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .max_files = 5,
        .allocation_unit_size = 16 * 1024};
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ret = spi_bus_initialize(host->slot, &bus_cfg, 1);
    if (ret != ESP_OK)
    {
        return;
    }

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host->slot;
    ret = esp_vfs_fat_sdspi_mount(mount_point, host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK)
    {
        return;
    }

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);
    return card;
}

char *sdcard_read(sdmmc_card_t *card, sdmmc_host_t *host, char *mount_point, char *path, const int read_size)
{
    char *full_path = "";
    sprintf(full_path, "%s%s", mount_point, path);

    FILE *f = fopen(full_path, "r");
    if (f == NULL)
    {
        return;
    }
    // Read text from file
    char text[read_size];
    fgets(text, sizeof(text), f);
    fclose(f);
    // All done, unmount partition and disable SPI peripheral
    esp_vfs_fat_sdcard_unmount(mount_point, card);
    // deinitialize the bus after all devices are removed
    spi_bus_free(host->slot);
    return text;
}