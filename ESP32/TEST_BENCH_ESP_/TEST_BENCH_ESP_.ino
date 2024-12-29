#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Define constants and settings
const char* ssid = "ESP32_Hotspot";
const char* password = "12345678";

class MotorSpeedometer {
private:
    String motorSpeed;
    AsyncWebServer server;
    int lastSpeed = 0;  // Last valid speed
    unsigned long lastValidTime = 0;  // Track when last valid data was received
    const unsigned long validTimeout = 20000;  // 20 seconds timeout for "stale" data
    const unsigned long fallbackStartTimeout = 30000;  // 30 seconds for fallback reduction

    // Helper function to clean and validate the speed input
    bool isValidSpeed(const String& speed) {
        if (speed.length() == 0) return false;

        // Check if the string is fully numeric
        for (unsigned int i = 0; i < speed.length(); i++) {
            if (!isDigit(speed.charAt(i))) return false;
        }

        // Convert to integer and check the range (assuming 0-4095 for 12-bit ADC)
        int speedValue = speed.toInt();
        if (speedValue < 0 || speedValue > 4095) {
            Serial.println("Out-of-range speed value received: " + speed);
            return false;
        }

        return true;
    }

    // Slowly reduce speed if no data is received for a long time
    void fallbackSpeedReduction() {
        // Gradually reduce speed if no data is received for 30 seconds
        if (millis() - lastValidTime > fallbackStartTimeout && lastSpeed > 0) {
            lastSpeed -= 5;  // Reduce the speed by 5 units every cycle (can be adjusted)
            if (lastSpeed < 0) {
                lastSpeed = 0;  // Ensure it doesn't go negative
            }
            motorSpeed = String(lastSpeed);
            Serial.println("Reducing speed due to long timeout. Current speed: " + motorSpeed);
        }
    }

public:
    // Constructor initializing motor speed and web server
    MotorSpeedometer(int port = 80) : motorSpeed("0"), server(port) {}

    // Set up the Wi-Fi and web server
    void setup() {
        Serial.begin(115200);
        Serial1.begin(112500, SERIAL_8N1, 16, 17);  // UART1 on GPIO16 and GPIO17

        // Start Wi-Fi Access Point
        WiFi.softAP(ssid, password);
        Serial.println("Access point created!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.softAPIP());

        // Set up web server routes
        server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
            request->send_P(200, "text/html", index_html);
        });

        server.on("/getmotorspeed", HTTP_GET, [this](AsyncWebServerRequest *request) {
            request->send(200, "text/plain", String(lastSpeed));  // Always send the last valid speed
        });

        // Start the web server
        server.begin();
    }

    // Update motor speed from UART with validation
    void updateMotorSpeed() {
        if (Serial1.available()) {
            String tempSpeed = Serial1.readStringUntil('\n');  // Read UART input until newline
            tempSpeed.trim();  // Remove any extra spaces or newline characters

            // Debugging: log exactly what data is received
            Serial.println("Received raw speed data: [" + tempSpeed + "]");

            // Validate the received data
            if (isValidSpeed(tempSpeed)) {
                int receivedSpeed = tempSpeed.toInt();
                
                if (receivedSpeed == 0) {
                    // Explicitly handle the case where speed is 0
                    lastSpeed = 0;
                    motorSpeed = "0";
                    Serial.println("Speed is explicitly 0: " + motorSpeed);
                } else {
                    // Only update if the speed is non-zero
                    lastSpeed = receivedSpeed;
                    motorSpeed = String(lastSpeed);
                    lastValidTime = millis();  // Reset the timeout clock
                    Serial.println("Valid speed received: " + motorSpeed);
                }
            } else {
                Serial.println("Invalid or out-of-range speed data received: " + tempSpeed);
            }

            // Clear the serial buffer to avoid reading leftover data
            while (Serial1.available()) {
                Serial1.read();  // Clear out the buffer
            }
        }

        // If no valid data received, gradually reduce the speed
        fallbackSpeedReduction();
    }

    // HTML content served by the ESP32 (stored in flash memory to save RAM)
    static const char index_html[];
};

// HTML content stored in flash memory
const char MotorSpeedometer::index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Car Speedometer</title>
    <style>
        body { font-family: 'Arial', sans-serif; background-color: #e8f4f8; margin: 0; padding: 0; display: flex; flex-direction: column; justify-content: center; align-items: center; }
        h1 { color: #007bff; text-align: center; margin-top: 20px; }
        .team-container { margin-top: 10px; text-align: center; }
        .team-container p { font-size: 18px; color: #333; margin: 5px 0; }
        .gauge-container { display: flex; justify-content: center; align-items: center; height: 70vh; background-color: #f0f0f0; padding: 20px; border-radius: 15px; box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.1); }
        .gauge { width: 300px; height: 300px; }
        .textbox { margin-top: 20px; font-size: 24px; padding: 10px; width: 100px; text-align: center; border: 2px solid #007bff; border-radius: 5px; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2); transition: border-color 0.3s ease; }
        .textbox:focus { border-color: #007bff; outline: none; }
        text { font-family: Arial, sans-serif; fill: #333; }
    </style>
</head>
<body>
<h1>TEST BENCH</h1>
<div class="team-container"><p>Ayoub ABBES, Saber Abisse,Tom Bollard</p></div>
<div class="gauge-container">
    <svg class="gauge" viewBox="0 0 100 100">
        <circle cx="50" cy="50" r="45" fill="none" stroke="#007bff" stroke-width="3"/>
        <g id="ticks"><line x1="50" y1="5" x2="50" y2="10" stroke="#007bff" stroke-width="2"/>
        <line x1="72.5" y1="12.5" x2="70.5" y2="17.5" stroke="#007bff" stroke-width="2"/><line x1="87.5" y1="27.5" x2="83.5" y2="31.5" stroke="#007bff" stroke-width="2"/><line x1="95" y1="50" x2="90" y2="50" stroke="#007bff" stroke-width="2"/>
        <line x1="87.5" y1="72.5" x2="83.5" y2="68.5" stroke="#007bff" stroke-width="2"/><line x1="72.5" y1="87.5" x2="70.5" y2="82.5" stroke="#007bff" stroke-width="2"/><line x1="50" y1="95" x2="50" y2="90" stroke="#007bff" stroke-width="2"/>
        <line x1="27.5" y1="87.5" x2="29.5" y2="82.5" stroke="#007bff" stroke-width="2"/><line x1="12.5" y1="72.5" x2="16.5" y2="68.5" stroke="#007bff" stroke-width="2"/><line x1="5" y1="50" x2="10" y2="50" stroke="#007bff" stroke-width="2"/><line x1="12.5" y1="27.5" x2="16.5" y2="31.5" stroke="#007bff" stroke-width="2"/><line x1="27.5" y1="12.5" x2="29.5" y2="17.5" stroke="#007bff" stroke-width="2"/></g>
        <line id="needle" x1="50" y1="50" x2="50" y2="15" stroke="red" stroke-width="2" transform="rotate(0 50 50)"/>
        <circle cx="50" cy="50" r="2" fill="#007bff"/>
    </svg>
    <input type="text" id="speedValue" class="textbox" value="0" readonly>
</div>
<script>
    function updateGauge(speed) {
        let speedAngle = (speed / 4095) * 360;
        let needle = document.getElementById('needle');
        needle.setAttribute('transform', `rotate(${speedAngle - 90} 50 50)`);
        document.getElementById('speedValue').value = speed;
    }
    function fetchMotorSpeed() {
        fetch("/getmotorspeed").then(response => response.text()).then(data => {let speedValue = parseInt(data, 10) || 0; updateGauge(speedValue);}).catch(error => console.error('Error fetching speed:', error));
    }
    setInterval(fetchMotorSpeed, 500);  // Update every 500ms for smoother display
</script>
</body>
</html>
)rawliteral";

// Instantiate the MotorSpeedometer object
MotorSpeedometer speedometer;

void setup() {
    speedometer.setup();  // Set up Wi-Fi and web server
}

void loop() {
    speedometer.updateMotorSpeed();  // Update motor speed data
}
