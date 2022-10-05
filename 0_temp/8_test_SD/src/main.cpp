#include <Arduino.h>


#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"




#define PIN_NUM_MISO GPIO_NUM_19
#define PIN_NUM_CLK GPIO_NUM_18
#define PIN_NUM_MOSI GPIO_NUM_23
#define PIN_NUM_CS GPIO_NUM_5



void setup(void)
{

  Serial.begin(115200);

  sdmmc_host_t host = SDSPI_HOST_DEFAULT();
  sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
  slot_config.gpio_miso = PIN_NUM_MISO;
  slot_config.gpio_mosi = PIN_NUM_MOSI;
  slot_config.gpio_sck  = PIN_NUM_CLK;
  slot_config.gpio_cs   = PIN_NUM_CS;

  // Options for mounting the filesystem.
  // If format_if_mount_failed is set to true, SD card will be partitioned and
  // formatted in case when mounting fails.
  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
    .format_if_mount_failed = false,
    .max_files = 5,
    .allocation_unit_size = 16 * 1024
  };


  // Use settings defined above to initialize SD card and mount FAT filesystem.
  // Note: esp_vfs_fat_sdmmc_mount is an all-in-one convenience function.
  // Please check its source code and implement error recovery when developing
  // production applications.
  sdmmc_card_t* card;
  esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

  if (ret != ESP_OK)
  {
    if (ret == ESP_FAIL)
    {
      //LOG(LL_INFO, ("%s", "Failed to mount filesystem.  If you want the card to be formatted, set format_if_mount_failed = true."));
    }
    else
    {
      //LOG(LL_INFO, ("Failed to initialize the card (%s). ", esp_err_to_name(ret)));
    }
    return;
  }

  // Card has been initialized, print its properties
  sdmmc_card_print_info(stdout, card);


  // Use POSIX and C standard library functions to work with files.
  // First create a file.
  //LOG(LL_INFO, ("%s", "Opening file"));
  FILE* f = fopen("/sdcard/hello.txt", "w");
  if (f == NULL)
  {
    //LOG(LL_INFO, ("%s","Failed to open file for writing"));
    return;
  }
  fprintf(f, "Hello %s!\n", card->cid.name);
  fclose(f);
  //LOG(LL_INFO, ("%s","File written"));


  // Check if destination file exists before renaming
  struct stat st;
  if (stat("/sdcard/foo.txt", &st) == 0)
  {
    // Delete it if it exists
    unlink("/sdcard/foo.txt");
  }

  // Rename original file
  //LOG(LL_INFO, ("%s","Renaming file"));
  if (rename("/sdcard/hello.txt", "/sdcard/foo.txt") != 0)
  {
    //LOG(LL_INFO, ("%s","Rename failed"));
    return;
  }

  // Open renamed file for reading
  //LOG(LL_INFO, ("%s","Reading file"));
  f = fopen("/sdcard/foo.txt", "r");
  if (f == NULL)
  {
    //LOG(LL_INFO, ("%s","Failed to open file for reading"));
    return;
  }
  char line[64];
  fgets(line, sizeof(line), f);
  fclose(f);
  // strip newline
  char* pos = strchr(line, '\n');
  if (pos)
  {
    *pos = '\0';
  }
  //LOG(LL_INFO, ("Read from file: %s", line));

  // All done, unmount partition and disable SDMMC or SPI peripheral
  esp_vfs_fat_sdmmc_unmount();
  //LOG(LL_INFO, ("%s", "Card unmounted"));

  //LOG(LL_INFO, ("%s", "**************************************"));
  //LOG(LL_INFO, ("%s", "**************************************"));


  
}

void loop(void){

  
}