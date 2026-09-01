# 🚨 Disaster Prevention & Monitoring System

A professional real-time environmental monitoring and alert system for temperature and gas sensors.

## 🎯 Features

### Dashboard Interface
- **Real-time Monitoring**: Live sensor data updates via WebSocket
- **Visual Status Indicators**: Color-coded cards (Green=Safe, Yellow=Warning, Orange=Danger, Red=Emergency)
- **Progress Bars**: Visual representation of sensor readings relative to limits
- **Professional UI**: Modern, responsive design optimized for desktop and mobile

### Alert System
- **Customizable Thresholds**: Set your own warning and danger limits for both sensors
- **Multi-Level Alerts**: 
  - ✓ **SAFE**: All parameters normal
  - ⚡ **WARNING**: One or more parameters elevated
  - ⚠️ **DANGER**: Critical levels approaching
  - 🚨 **EMERGENCY**: Critical thresholds exceeded
- **Alert Notifications**: Sliding notifications with alert details
- **Audio Alarms**: Sound alerts for emergency situations
- **Alert History**: Track recent events and alerts

### Sensor Cards
- Temperature monitoring with °C display
- Gas concentration monitoring with ppm (parts per million) display
- Status indicators for each sensor
- Progress bars showing relative intensity

### Configuration
- **Fixed Thresholds**: Thresholds cannot be changed by users - they are locked for safety
- All operations follow the established safety limits

### API Endpoints
- `POST /data` - Send sensor data (requires `temp` and `gas` parameters)
- `GET /current` - Get latest sensor readings
- `GET /thresholds` - Get current thresholds
- `GET /health` - Check server health

## 📊 Fixed Safety Thresholds (Cannot be Changed)

| Status | Temperature | Gas Concentration |
|--------|-------------|-------------------|
| SAFE | ≤ 40°C | ≤ 1000 ppm |
| WARNING | 40°C < Temp ≤ 50°C | 1000 ppm < Gas ≤ 2000 ppm |
| DANGER | 50°C < Temp ≤ 60°C | 2000 ppm < Gas ≤ 3000 ppm |
| EMERGENCY | > 60°C | > 3000 ppm |

## 🚀 Getting Started

### Installation
```bash
cd c:\Users\Hp\Documents\PlatformIO\Projects\server
npm install
```

### Running the Server
```bash
npm start
```

The server will start on `http://localhost:3000`

### Sending Sensor Data

#### Using cURL (Testing)
```bash
# Send data to the server
curl -X POST http://localhost:3000/data \
  -H "Content-Type: application/json" \
  -d '{"temp": 25.5, "gas": 300}'
```

#### From ESP32/Arduino
```cpp
#include <WiFi.h>
#include <HTTPClient.h>

void sendSensorData(float temperature, float gasLevel) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://YOUR_SERVER_IP:3000/data");
    http.addHeader("Content-Type", "application/json");
    
    String payload = "{\"temp\":" + String(temperature) + ",\"gas\":" + String(gasLevel) + "}";
    http.POST(payload);
    http.end();
  }
}
```

## 🎨 UI Components

### Threshold Configuration Section
- Input fields for all four thresholds
- Save button to persist settings
- Reset button to restore defaults

### Main Dashboard
- Three main sensor cards (Temperature, Gas, Overall Status)
- Real-time value updates
- Color-coded status indicators
- Progress bars for visual feedback

### Alert Notification
- Fixed position in top-right corner
- Auto-hides after 8 seconds (except emergencies)
- Color-coded by severity
- Displays specific alert reasons

### Activity History
- Scrollable list of recent events
- Timestamped entries
- Shows all system activities and alerts

## 🔧 System Configuration

### Fixed Thresholds
The safety thresholds are **hardcoded and locked** for security and consistency:

- **Temperature Warning**: > 40°C
- **Temperature Danger**: > 50°C  
- **Temperature Emergency**: > 60°C
- **Gas Warning**: > 1000 ppm
- **Gas Danger**: > 2000 ppm
- **Gas Emergency**: > 3000 ppm

These values cannot be modified through the user interface. To change thresholds, you must modify the source code in `server.js`.

### Styling
The application uses CSS variables and can be easily customized. All colors and styling are defined in the `<style>` section of `index.html`.

## 📱 Responsive Design
- Desktop optimized layout
- Mobile-friendly interface
- Adapts to screen size
- Touch-friendly controls

## 🔐 Security Considerations

For production deployment:
- Add authentication to the API
- Validate all incoming sensor data
- Implement rate limiting
- Use HTTPS for secure communication
- Add CORS configuration if accessed from different domains

## 📊 Data Flow

```
ESP32/Sensor → POST /data → Server → WebSocket → Dashboard
                   ↓
            Status Calculation
                   ↓
            Alert Generation
                   ↓
            Browser Notification
```

## 🛠 Troubleshooting

### Connection Issues
- Ensure server is running on port 3000
- Check firewall settings
- Verify ESP32 has correct server IP address

### Alerts Not Showing
- Check browser console for JavaScript errors
- Verify WebSocket connection in DevTools
- Ensure data is being received (check Network tab)

### Thresholds Not Saving
- Check browser's localStorage is enabled
- Clear cache if needed
- Verify browser developer tools shows no errors

## 📝 Log Output

The server logs important information:
```
[HH:MM:SS] ✓ Client connected from 127.0.0.1
[HH:MM:SS] Sensor Data - Temp: 28.5°C, Gas: 350 ppm, Status: SAFE
[HH:MM:SS] ✗ Client disconnected
```

## 🆘 Emergency Response

When EMERGENCY status is triggered:
1. Alert notification appears immediately
2. Browser plays audio alarm (synthesized beep)
3. Status badge pulses with red animation
4. Alert remains visible until manually closed
5. Logged in activity history

## 📄 License

ISC

---

**System Status**: Ready to Monitor | **Version**: 1.0.0 | **Last Updated**: 2024
