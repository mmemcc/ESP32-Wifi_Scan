#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_console.h"

//TickType_t xLastWakeTime;
//static const TickType_t xPeriod = 1000 / portTICK_PERIOD_MS;


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



static int wifi_scan(void)
{
    uint16_t ap_count = 0;
    uint8_t center_channel;
    uint8_t bw;
    esp_wifi_scan_start(NULL, true);

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    printf("%u\n", ap_count);

    wifi_ap_record_t* ap_info = (wifi_ap_record_t*)malloc(ap_count * sizeof(wifi_ap_record_t));

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_info));

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
    
    return 0;
}

void register_scan(void)
{
    const esp_console_cmd_t scan_cmd = {
        .command = "scan",
        .help = "Scan for available WiFi networks",
        .hint = NULL,
        .func = &wifi_scan,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&scan_cmd));
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

    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();

    repl_config.prompt = "scan>";

#if defined(CONFIG_ESP_CONSOLE_UART_DEFAULT) || defined(CONFIG_ESP_CONSOLE_UART_CUSTOM)
    esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_console_new_repl_uart(&uart_config, &repl_config, &repl));

#elif defined(CONFIG_ESP_CONSOLE_USB_CDC)
    esp_console_dev_usb_cdc_config_t hw_config = ESP_CONSOLE_DEV_CDC_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_console_new_repl_usb_cdc(&hw_config, &repl_config, &repl));

#elif defined(CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG)
    esp_console_dev_usb_serial_jtag_config_t hw_config = ESP_CONSOLE_DEV_USB_SERIAL_JTAG_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_console_new_repl_usb_serial_jtag(&hw_config, &repl_config, &repl));
#else
#error Unsupported console type
#endif

    register_scan();

    ESP_ERROR_CHECK(esp_console_start_repl(repl));
}
