#include "esp_camera.h"
#include <WiFi.h>
#include "esp_http_server.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"


#define WIFI_NETWORK "Jhelum.net [Luqman House]"
#define WIFI_PASSWORD "7861234786"


void startCameraServer();
void setupLedFlash(int pin);

void camera_task(void *pvParameters) {
  camera_config_t config;
   config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG; // for streaming
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;
  
  // ... (camera configuration from setup() function)

    if(config.pixel_format == PIXFORMAT_JPEG){
    if(psramFound()){
      config.jpeg_quality = 10;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
      // Limit the frame size when PSRAM is not available
      config.frame_size = FRAMESIZE_SVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
    }
  } else {
    // Best option for face detection/recognition
    config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -2); // lower the saturation
  }
  // drop down frame size for higher initial frame rate
  if(config.pixel_format == PIXFORMAT_JPEG){
    s->set_framesize(s, FRAMESIZE_QVGA);
  }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
  s->set_vflip(s, 1);
#endif

// Setup LED FLash if LED pin is defined in camera_pins.h
#if defined(LED_GPIO_NUM)
  setupLedFlash(LED_GPIO_NUM);
#endif


  // ... (camera sensor adjustments from setup() function)

  while (1) {
    // Do any camera-related tasks here if needed

    vTaskDelay(100 / portTICK_PERIOD_MS); // Adjust the delay time as per your requirement
  }
}

void keepWiFiAlive(void * parameter){

        WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
   vTaskDelay(500 / portTICK_PERIOD_MS);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
  vTaskDelete(NULL); // End the task once Wi-Fi is connected
}



void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  xTaskCreatePinnedToCore(camera_task, "camera_task", 4096, NULL, 1, NULL, 1); // Run camera task on core 1
      xTaskCreatePinnedToCore(
        keepWiFiAlive,         // Function to run
        "keepWiFiAliveTask",   // Name of the task
        4096,                  // Stack size (bytes)
        NULL,                  // Task parameter
        1,                     // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                  // Task handle
        0                      // Run on the first core
    );

  // ... (LED flash setup if LED pin is defined in camera_pins.h)
}

void loop() {
  // Do nothing in the loop. Everything is done in tasks.
  vTaskDelay(10000 / portTICK_PERIOD_MS);
}
