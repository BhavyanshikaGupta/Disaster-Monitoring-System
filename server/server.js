const express = require("express");
const http = require("http");
const { Server } = require("socket.io");

const app = express();
const server = http.createServer(app);
const io = new Server(server);

// Middleware
app.use(express.json());
app.use(express.static("public"));

// Store latest data
let latestData = {
  temp: 0,
  gas: 0,
  status: "SAFE",
  timestamp: new Date()
};

// Default thresholds (Fixed - cannot be changed)
const defaultThresholds = {
  tempWarning: 40,
  tempDanger: 60,
  gasWarning: 1000,
  gasDanger: 3000
};

// Function to determine status based on fixed thresholds
function determineStatus(temp, gas) {
  if (temp > 60 || gas > 3000) {
    return "EMERGENCY";
  }
  if (temp > 50 || gas > 2000) {
    return "DANGER";
  }
  if (temp > 40 || gas > 1000) {
    return "WARNING";
  }
  return "SAFE";
}

// API to receive ESP32 data
app.post("/data", (req, res) => {
  const { temp, gas } = req.body;

  if (temp === undefined || gas === undefined) {
    return res.status(400).json({ error: "Missing temp or gas data" });
  }

  const status = determineStatus(temp, gas);
  latestData = {
    temp: parseFloat(temp),
    gas: parseFloat(gas),
    status: status,
    timestamp: new Date()
  };

  console.log(`[${new Date().toLocaleTimeString()}] Sensor Data - Temp: ${temp}°C, Gas: ${gas} ppm, Status: ${status}`);

  // Send data to all connected clients
  io.emit("sensorData", latestData);

  res.status(200).json({ 
    message: "Data received", 
    status: status,
    timestamp: latestData.timestamp
  });
});

io.on("connection", (socket) => {
  console.log(`[${new Date().toLocaleTimeString()}] ✓ Client connected from ${socket.handshake.address}`);

  // Send last known data immediately
  socket.emit("sensorData", latestData);

  socket.on("disconnect", () => {
    console.log(`[${new Date().toLocaleTimeString()}] ✗ Client disconnected`);
  });

  socket.on("error", (error) => {
    console.error("WebSocket error:", error);
  });
});


process.on("uncaughtException", (error) => {
  console.error("Uncaught Exception:", error);
});

// Start server
const PORT = 3000;
server.listen(PORT, () => {
  console.log(`\n🚀 Disaster Prevention System - Server running at http://localhost:${PORT}`);
  console.log(`📊 Dashboard: http://localhost:${PORT}`);
  console.log(`📡 API: POST http://localhost:${PORT}/data (temp, gas)`);
  console.log(`✓ Server ready to receive sensor data\n`);
});