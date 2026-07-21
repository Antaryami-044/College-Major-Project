/*
 * Project: IoT Smart Heart Rate Monitor
 * Board: Arduino Uno R4 WiFi
 * Graphing: ThingSpeak Cloud (Every 12s)
 * Output: Clean Serial Monitor Logging
 */
#include "WiFiS3.h"
#include "Arduino_LED_Matrix.h"

// ================= CLOUD & WIFI SETTINGS =================
char ssid[] = "EnterName";   // Must be 2.4GHz!
char pass[] = "lol@0000";       

String apiKey = "****************";  // use your api key
char server[] = "api.thingspeak.com";
WiFiClient client;
// =========================================================

// ================= CALIBRATION =================
const int threshold = 550; 
const int sensorPin = A0;
const int loPlus = 10;
const int loMinus = 11;
// ===============================================

// --- BPM MATH VARIABLES ---
const int RATE_SIZE = 10; 
int rates[RATE_SIZE];     
int rateSpot = 0;         
long lastBeatTime = 0;    
float beatsPerMinute;
int beatAvg = 0;

// --- TIMERS ---
unsigned long lastCloudUpdate = 0;
const unsigned long postingInterval = 12000; // Exactly 12 seconds

// --- ERROR HANDLING TIMER ---
long lastErrorTime = 0;

// --- MATRIX ---
ArduinoLEDMatrix matrix;
const uint32_t heartFrame[] = { 0x3184a444, 0x42081100, 0xa0040000 };

void setup() {
  Serial.begin(9600);
  pinMode(loPlus, INPUT);
  pinMode(loMinus, INPUT);
  matrix.begin();

  // --- BOOT SEQUENCE ---
  Serial.println("===================================");
  Serial.println("  Starting IoT ECG System...");
  Serial.println("===================================");
  Serial.print("Connecting to Wi-Fi ");
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi-Fi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("System Ready. Reading sensor...\n");

  for (int i = 0; i < RATE_SIZE; i++) rates[i] = 0;
}

void loop() {
  int signalValue = analogRead(sensorPin);
  long currentTime = millis();

  // 1. CHECK LEADS OFF
  if ((digitalRead(loPlus) == 1) || (digitalRead(loMinus) == 1)) {
    // Only print the warning once per second so it doesn't flood the screen
    if (currentTime - lastErrorTime > 1000) {
      Serial.println("⚠️ LEADS OFF - Please check electrodes."); 
      lastErrorTime = currentTime;
    }
    return;
  } 

  // 2. DETECT HEARTBEAT
  if (signalValue > threshold && (currentTime - lastBeatTime > 250)) {
    long delta = currentTime - lastBeatTime;
    lastBeatTime = currentTime;
    
    beatsPerMinute = 60000.0 / delta;

    if (beatsPerMinute < 220 && beatsPerMinute > 40) {
      if (rates[0] == 0) {
        for (int i = 0; i < RATE_SIZE; i++) rates[i] = (int)beatsPerMinute;
      }

      rates[rateSpot++] = (int)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      beatAvg = 0;
      for (int x = 0; x < RATE_SIZE; x++) beatAvg += rates[x];
      beatAvg /= RATE_SIZE;

      matrix.loadFrame(heartFrame);
      
      // Print cleanly to Serial Monitor on every valid beat
      Serial.print("💓 Pulse Detected | BPM: ");
      Serial.println(beatAvg);
    }
  }
  else if (currentTime - lastBeatTime > 150) {
    matrix.clear();
  }

  // 3. CLOUD UPLOAD (Every 12 Seconds)
  if (currentTime - lastCloudUpdate > postingInterval) {
    if (beatAvg > 0) { 
      sendToThingSpeak(beatAvg, signalValue, threshold);
    }
    lastCloudUpdate = currentTime;
  }
  
  delay(10); 
}

// --- NETWORK FUNCTION ---
void sendToThingSpeak(int bpmToSend, int signalToSend, int thresholdToSend) {
  
  if (client.connect(server, 80)) {
    String url = "/update?api_key=" + apiKey + 
                 "&field1=" + String(bpmToSend) + 
                 "&field2=" + String(signalToSend) + 
                 "&field3=" + String(thresholdToSend);
    
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Connection: close\r\n\r\n");
                 
    // Clean confirmation box
    Serial.println();
    Serial.println("┌────────────────────────────────────────┐");
    Serial.println("│ ☁️ CLOUD UPLOAD SUCCESS (12s Timer)    │");
    Serial.print("│ ➡️ BPM: "); Serial.print(bpmToSend); Serial.println("                             │");
    Serial.print("│ ➡️ Sig: "); Serial.print(signalToSend); Serial.println("                            │");
    Serial.println("└────────────────────────────────────────┘");
    Serial.println();
    
  } else {
    Serial.println();
    Serial.println("❌ ERROR: Could not connect to ThingSpeak");
    Serial.println();
  }
  
  client.stop(); 
}