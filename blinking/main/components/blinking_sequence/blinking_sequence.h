/**
 * @file blinking_sequence.h
 * @brief LED pattern sequence controller interface
 * @details Task management for cyclic LED activation patterns
 * 
 * @author Ameed Othman
 * @date 22/01/2025
 */
#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * @brief Create blinking sequence task
 * @return TaskHandle_t Created task handle
 */
TaskHandle_t blinking_sequence_create(void);