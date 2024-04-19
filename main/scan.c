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

//TickType_t xLastWakeTime;
//static const TickType_t xPeriod = 3000 / portTICK_PERIOD_MS;
#define DEFAULT_SCAN_LIST_SIZE CONFIG_EXAMPLE_SCAN_LIST_SIZE

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
    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    printf("Error check = 39\n");
    uint16_t ap_count = 0;
    printf("Error check = 41\n");
    uint8_t center_channel;
    printf("Error check = 43\n");
    uint8_t bw;
    printf("Error check = 45\n");
    esp_wifi_scan_start(NULL, true);
    printf("Error check = 47\n");
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    printf("Error check = 49\n");
    memset(ap_info, 0, sizeof(ap_info));
    printf("Error check = 52\n");
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    
    printf("Total APs scanned = %u\n", ap_count);
    printf("SSID, RSSI, Channel, BW\n");

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
    wifi_scan();
    //xLastWakeTime = xTaskGetTickCount();
    //int logtimer = 0;
    //vTaskDelayUntil(&xLastWakeTime, xPeriod);
    /*for(;;)){
        logtimer++;
        wifi_scan();
        if (logtimer >= 300)
        {
            printf("FTM STOP\n");
            break;
        }
        else
        {
            vTaskDelayUntil(&xLastWakeTime, xPeriod);
            continue;
        }
    }*/
}
