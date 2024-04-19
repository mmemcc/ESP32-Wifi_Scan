/* Scan Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/



#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"

TickType_t xLastWakeTime;
static const TickType_t xPeriod = 1000 / portTICK_PERIOD_MS;


void initialise_wifi(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

static void wifi_scan(void)
{

    uint16_t ap_count = 0;
    uint8_t center_channel;
    uint8_t bw;
    esp_wifi_scan_start(NULL, true);

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    wifi_ap_record_t* ap_info = (wifi_ap_record_t*)malloc(ap_count * sizeof(wifi_ap_record_t));

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_info));
    
    printf("%u\n", ap_count);

    for (int i = 0; (i < ap_count); i++) {
        if (ap_info[i].second == WIFI_SECOND_CHAN_ABOVE){
            center_channel = ap_info[i].primary +2;
            bw = 40;
        } 
        else if (ap_info[i].second == WIFI_SECOND_CHAN_BELOW){
            center_channel = ap_info[i].primary -2;
            bw = 40;
        }
        else{
            center_channel = ap_info[i].primary;
            bw = 20;
        }
        printf("%s,\t%d,\t%d,\t%d\n", ap_info[i].ssid, ap_info[i].rssi, center_channel, bw);        
    }
    free(ap_info);
    esp_wifi_scan_stop();
    //vTaskDelayUntil(&xLastWakeTime, xPeriod);
}

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    initialise_wifi();

    xLastWakeTime = xTaskGetTickCount();

    for(;;){
        wifi_scan();
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}
