#include "main.h"

#include "NanoEdgeAI.h"
#include "knowledge.h"
#include <stdio.h>

#define AUDIO_BUF 2048  // Total samples
#define AXIS_NUMBER 1
#define DATA_INPUT_USER 1
#define CLASS_NUMBER 3

int32_t RecBuff[AUDIO_BUF];       // Raw 24-bit DFSDM data
int16_t PlayBuff[AUDIO_BUF];      // Converted 16-bit data

float input_user_buffer[DATA_INPUT_USER * AXIS_NUMBER];
float output_class_buffer[CLASS_NUMBER];

const char *id2class[CLASS_NUMBER + 1] = {
    "unknown", "S1", "S2", "S3"
};

uint8_t DmaRecHalfBuffCplt = 0;
uint8_t DmaRecBuffCplt = 0;

extern DFSDM_Filter_HandleTypeDef hdfsdm1_filter0;
extern UART_HandleTypeDef huart2;

// printf redirection
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

// DMA Callbacks
void HAL_DFSDM_FilterRegConvHalfCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter) {
    DmaRecHalfBuffCplt = 1;
}

void HAL_DFSDM_FilterRegConvCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter) {
    DmaRecBuffCplt = 1;
}

void SystemClock_Config(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_DFSDM1_Init();
    MX_USART2_UART_Init();

    // Start DFSDM + DMA
    HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter0, RecBuff, AUDIO_BUF);

    // Initialize NanoEdge AI library
    enum neai_state error_code = neai_classification_init(knowledge);
    if (error_code != NEAI_OK) {
        printf("NEAI init failed: %d\r\n", error_code);
        while (1);
    }

    uint16_t id_class = 0;

    while (1) {
        // First half of buffer
        if (DmaRecHalfBuffCplt) {
            for (int i = 0; i < AUDIO_BUF / 2; i++) {
                PlayBuff[i] = RecBuff[i] >> 8; // Convert 24-bit to 16-bit
            }

            // Use first sample for classification
            input_user_buffer[0] = (float)PlayBuff[0];
            neai_classification(input_user_buffer, output_class_buffer, &id_class);

            printf("Class: %s\tProbabilities: [%.2f, %.2f, %.2f]\r\n",
                   id2class[id_class], output_class_buffer[0], output_class_buffer[1], output_class_buffer[2]);

            // Also print raw waveform value for plotting (optional)
            printf("%ld\r\n", PlayBuff[0]);

            DmaRecHalfBuffCplt = 0;
        }

        // Second half of buffer
        if (DmaRecBuffCplt) {
            for (int i = AUDIO_BUF / 2; i < AUDIO_BUF; i++) {
                PlayBuff[i] = RecBuff[i] >> 8;
            }

            input_user_buffer[0] = (float)PlayBuff[AUDIO_BUF / 2];
            neai_classification(input_user_buffer, output_class_buffer, &id_class);

            printf("Class: %s\tProbabilities: [%.2f, %.2f, %.2f]\r\n",
                   id2class[id_class], output_class_buffer[0], output_class_buffer[1], output_class_buffer[2]);

            // Optional: plot this value in Python
            printf("%ld\r\n", PlayBuff[AUDIO_BUF / 2]);

            DmaRecBuffCplt = 0;
        }
    }
}
