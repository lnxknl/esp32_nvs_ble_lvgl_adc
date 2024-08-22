#include <stdio.h>
#include "hid_touch_gestures.h"
#include "hidd_le_prf_int.h"
#include "paj7620.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define Delay(t) vTaskDelay(t / portTICK_PERIOD_MS)

int gesture_available(gesture_state gs)
{
    return gs.available;
}

int get_gesture(gesture_state *gs)
{
    gs->available = 0;
    return gs->gesture;
}

void set_gesture(gesture_state *gs, int gesture)
{
    gs->available = 1;
    gs->gesture = gesture;
}

void send_touch_gesture(uint16_t hid_conn_id, int gesture)
{
    switch (gesture)
    {
        case GES_UP_FLAG:
            send_slide_up(hid_conn_id);
            break;
        case GES_DOWN_FLAG:
            send_slide_down(hid_conn_id);
            break;
        case GES_LEFT_FLAG:
            send_slide_left(hid_conn_id);
            break;
        case GES_RIGHT_FLAG:
            send_slide_right(hid_conn_id);
            break;
        case GES_CLOCKWISE_FLAG:
            send_double_tap(hid_conn_id);
            break;  
        case GES_COUNT_CLOCKWISE_FLAG:
            send_back(hid_conn_id);
            break;
        case GES_FORWARD_FLAG:
            send_tap(hid_conn_id);
            break;            
        default:
            break;
    }
}

// need to modify the actions below for different mobile phone if neccessary
void send_slide_up(uint16_t hid_conn_id)
{
    esp_hidd_send_touch_value(hid_conn_id, 1, 1, 1, 0, 2000, 3000, 1, 1);
    Delay(TOUCH_DELAY);

    for (int j = 1; j <= 10; j++)
    {
        esp_hidd_send_touch_value(hid_conn_id, 1, 1, 1, 0, 2000, 3000 - 200 * j, 1, 1);
        Delay(TOUCH_INTERVAL);
    }

    esp_hidd_send_touch_value(hid_conn_id, 0, 0, 1, 0, 2000, 1000, 0, 0);
    Delay(TOUCH_DELAY);
}

void send_slide_down(uint16_t hid_conn_id)
{
    esp_hidd_send_touch_value(hid_conn_id, 1, 1, 2, 0, 2000, 1000, 1, 1);
    Delay(TOUCH_DELAY);

    for (int j = 1; j <= 10; j++)
    {
        esp_hidd_send_touch_value(hid_conn_id, 1, 1, 2, 0, 2000, 1000 + 200 * j, 1, 1);
        Delay(TOUCH_INTERVAL);
    }

    esp_hidd_send_touch_value(hid_conn_id, 0, 0, 2, 0, 2000, 3000, 0, 0);
    Delay(TOUCH_DELAY);
}

void send_slide_left(uint16_t hid_conn_id)
{
    esp_hidd_send_touch_value(hid_conn_id, 1, 1, 3, 0, 3000, 1600, 1, 1);
    Delay(TOUCH_DELAY);

    for (int j = 1; j <= 16; j++)
    {
        esp_hidd_send_touch_value(hid_conn_id, 1, 1, 3, 0, 3000 - 125 * j, 1600, 1, 1);
        Delay(TOUCH_INTERVAL);
    }

    esp_hidd_send_touch_value(hid_conn_id, 0, 1, 3, 0, 1000, 1600, 0, 0);
    Delay(TOUCH_DELAY);
}

void send_slide_right(uint16_t hid_conn_id)
{
    esp_hidd_send_touch_value(hid_conn_id, 1, 1, 4, 0, 1000, 1600, 1, 1);
    Delay(TOUCH_DELAY);

    for (int j = 1; j <= 16; j++)
    {
        esp_hidd_send_touch_value(hid_conn_id, 1, 1, 4, 0, 1000 + 125 * j, 1600, 1, 1);
        Delay(TOUCH_INTERVAL);
    }

    esp_hidd_send_touch_value(hid_conn_id, 0, 1, 4, 0, 3000, 1600, 0, 0);
    Delay(TOUCH_DELAY);
}

// send back gesture 
void send_back(uint16_t hid_conn_id)
{
    esp_hidd_send_touch_value(hid_conn_id, 1, 1, 5, 0, 4000, 3000, 1, 1);
    Delay(TOUCH_DELAY);

    for (int j = 1; j <= 10; j++)
    {
        esp_hidd_send_touch_value(hid_conn_id, 1, 1, 5, 0, 4000 - 100 * j, 3000, 1, 1);
        Delay(TOUCH_INTERVAL);
    }

    esp_hidd_send_touch_value(hid_conn_id, 0, 1, 5, 0, 3000, 3000, 0, 0);
    Delay(TOUCH_DELAY);
}

void send_tap(uint16_t hid_conn_id)
{
    esp_hidd_send_touch_value(hid_conn_id, 1, 1, 6, 0, 2000, 2000, 1, 1);
    Delay(TAP_DELAY);
    esp_hidd_send_touch_value(hid_conn_id, 0, 0, 6, 0, 2000, 2000, 0, 0);
    Delay(TAP_DELAY);
}

void send_press_down(uint16_t hid_conn_id)
{
    esp_hidd_send_touch_value(hid_conn_id, 1, 1, 1, 0, 2000, 2000, 1, 1);
    Delay(TAP_DELAY);
}

void send_press_up(uint16_t hid_conn_id)
{
    esp_hidd_send_touch_value(hid_conn_id, 0, 0, 1, 0, 2000, 2000, 0, 0);
    Delay(TAP_DELAY);
}

void send_double_tap(uint16_t hid_conn_id)
{
    esp_hidd_send_touch_value(hid_conn_id, 1, 1, 7, 0, 2000, 1600, 1, 1);
    Delay(TOUCH_INTERVAL);

    esp_hidd_send_touch_value(hid_conn_id, 0, 1, 7, 0, 2000, 1600, 0, 0);
    Delay(TAP_DELAY);

    esp_hidd_send_touch_value(hid_conn_id, 1, 1, 8, 0, 2000, 1600, 1, 1);
    Delay(TOUCH_INTERVAL);

    esp_hidd_send_touch_value(hid_conn_id, 0, 1, 8, 0, 2000, 1600, 0, 0);
    Delay(TAP_DELAY);
}