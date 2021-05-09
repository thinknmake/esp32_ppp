/*
 * ESP32 PPP MQTT Example Code
 * By Nilesh Mundphan
 * */

#include <string.h>
#include "wifi.h"
#include "mqtt.h"
#include "ppp.h"

void mainTask(void *pvParameters){
  char str[32];
  int index=0;
  while (1) {
    
    if(mqtt_connected){
        sprintf(str, "Hello Nilesh %d",index++);
        mqtt_publish(str);
    }

    vTaskDelay(10*1000 / portTICK_PERIOD_MS);
  }
}
void app_main(void)
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    
    //wifi_init_sta();
    ppp_setup();
    mqtt_app_start();
    xTaskCreatePinnedToCore(&mainTask, "mainTask", 2048, NULL, 5, NULL, 0);
}
