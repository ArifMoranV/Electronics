#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>  //we are using the ESP82

//To provide the ESP32 / ESP8266 with the connection and the sensor type
//DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "iPhone de Alberto"//"Totalplay-D6AA"//
#define WIFI_PASSWORD "bibliopiso4"//"D6AAA8DFrJyw3yyv"// 

// Insert Firebase project API Key
#define API_KEY "AIzaSyAsyvcBUhNivDoPiDP55YVx-R2NEE9QBeQ"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://c-citicinemas-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;  //since we are doing an anonymous sign in

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;  //"c-citicinemas-default-rtdb.firebaseio.com/"

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {

  if (Serial.available()) {
    String gg = Serial.readStringUntil('\n');
    float time = round(micros() / 1e3) / 1000;

    // Convert String to char array
    char receivedCharArray[gg.length() + 1];
    gg.toCharArray(receivedCharArray, sizeof(receivedCharArray));

    // Initialize an array to store individual values
    float values[10];

    // Tokenize the string using strtok
    char *token = strtok(receivedCharArray, ",");
    int i = 0;
    while (token != NULL && i < 10) {
      // Convert the token to a floating-point number and store in the array
      values[i] = atof(token);

      // Move to the next token
      token = strtok(NULL, ",");
      i++;
    }

    // Assign values to individual variables
    float t1 = values[0];
    float t2 = values[1];
    float t3 = values[2];
    float t4 = values[3];
    float t5 = values[4];
    float t6 = values[5];
    float t7 = values[6];
    float t8 = values[7];
    float p1 = values[8];
    float p2 = values[9];




    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
      //since we want the data to be updated every second
      sendDataPrevMillis = millis();
      // Enter Temperature in to the DHT_11 Table
      if (Firebase.RTDB.setFloat(&fbdo, "Sensor/Temperature", t1)) {
        // This command will be executed even if you dont serial print but we will make sure its working
        //Serial.print("Temperature:");
        //Serial.println(t1);
      } else {
        Serial.println("Failed to Read from the Sensor");
        Serial.println("REASON: " + fbdo.errorReason());
      }
      if (Firebase.RTDB.setDouble(&fbdo, "Sensor/Temperature2", t2)) {
      }
      ///else {
      //  Serial.println("Failed to Read from the Sensor");
      //  Serial.println("REASON: " + fbdo.errorReason());
      //}
      if (Firebase.RTDB.setFloat(&fbdo, "Sensor/Temperature3", t3)) {
        // This command will be executed even if you dont serial print but we will make sure its working
      }

      if (Firebase.RTDB.setDouble(&fbdo, "Sensor/Temperature4", t4)) {
        // This command will be executed even if you dont serial print but we will make sure its working
      }

      if (Firebase.RTDB.setDouble(&fbdo, "Sensor/Temperature5", t5)) {
        // This command will be executed even if you dont serial print but we will make sure its working
      }

      if (Firebase.RTDB.setDouble(&fbdo, "Sensor/Temperature6", t6)) {
        // This command will be executed even if you dont serial print but we will make sure its working
      }

      if (Firebase.RTDB.setDouble(&fbdo, "Sensor/Temperature7", t7)) {
        // This command will be executed even if you dont serial print but we will make sure its working
      }

      if (Firebase.RTDB.setDouble(&fbdo, "Sensor/Temperature8", t8)) {
        // This command will be executed even if you dont serial print but we will make sure its working
      }

      if (Firebase.RTDB.setDouble(&fbdo, "Sensor/Pressure1", p1)) {
        // This command will be executed even if you dont serial print but we will make sure its working
      }

      if (Firebase.RTDB.setDouble(&fbdo, "Sensor/Pressure2", p2)) {
        // This command will be executed even if you dont serial print but we will make sure its working
      }

      if (Firebase.RTDB.setDouble(&fbdo, "Sensor/Time", time)) {
        // This command will be executed even if you dont serial print but we will make sure its working
        //Serial.print("Elapsed Time : ");
        //Serial.println(time);
      }
    }
  }
}