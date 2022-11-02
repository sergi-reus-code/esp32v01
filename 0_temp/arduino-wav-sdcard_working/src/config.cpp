#include "config.h"



// i2s config for reading from I2S
i2s_config_t i2s_mic_Config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0,
    .mclk_multiple = (i2s_mclk_multiple_t) I2S_MCLK_MULTIPLE_DEFAULT,              /*!< The multiple of I2S master clock(MCLK) to sample rate */
    .bits_per_chan = (i2s_bits_per_chan_t) I2S_BITS_PER_CHAN_DEFAULT};

// i2s microphone pins
i2s_pin_config_t i2s_mic_pins = {
    .mck_io_num = -1,     /*!< MCK in out pin. Note that ESP32 supports setting MCK on GPIO0/GPIO1/GPIO3 only*/
    .bck_io_num = I2S_MIC_SERIAL_CLOCK,    /*!< BCK in out pin*/
    .ws_io_num = I2S_MIC_LEFT_RIGHT_CLOCK,      /*!< WS in out pin*/
    .data_out_num = -1,   /*!< DATA out pin*/
    .data_in_num = I2S_MIC_SERIAL_DATA} ;



    

// i2s speaker pins
i2s_pin_config_t i2s_speaker_pins = {
    .mck_io_num = -1,  
    .bck_io_num = I2S_SPEAKER_SERIAL_CLOCK,
    .ws_io_num = I2S_SPEAKER_LEFT_RIGHT_CLOCK,
    .data_out_num = I2S_SPEAKER_SERIAL_DATA,
    .data_in_num = -1};