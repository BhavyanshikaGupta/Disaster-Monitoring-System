# Disaster Monitoring System

A cross-platform disaster monitoring project combining an ESP32/Arduino sensor implementation with a Node.js web server and real-time dashboard.

## Project Overview

This repository contains:

- `Disaster management System/`
  - ESP32/Arduino PlatformIO project for sensor monitoring
  - `src/` contains the microcontroller firmware
  - `platformio.ini` configures the ESP32 board and libraries
- `server/`
  - Node.js Express + Socket.IO server
  - `public/` contains the web dashboard UI
  - `server.js` serves the dashboard and handles incoming sensor data

## Key Features

- Real-time temperature and gas monitoring
- Web-based dashboard with live updates
- Alert levels for safe, warning, danger, and emergency states
- Sensor data ingestion via HTTP POST
- Activity history and notification alerts

## Getting Started

### Prerequisites

- Git
- PlatformIO (VS Code extension or CLI)
- Node.js and npm
- ESP32 development board

### Install Dependencies

1. Install the PlatformIO dependencies for the embedded project.

```bash
cd "Disaster management System"
# open in PlatformIO or run platformio commands from this folder
```

2. Install server dependencies.

```bash
cd server
npm install
```

### Build & Upload Firmware

Open the `Disaster management System` folder in VS Code with PlatformIO and build/upload the project to your ESP32.

Alternatively, from the command line:

```bash
cd "Disaster management System"
platformio run --environment esp32dev
platformio run --environment esp32dev --target upload
```

### Run the Server

```bash
cd server
npm start
```

The server listens on `http://localhost:3000` by default.

## Usage

- Send sensor readings to the server at `POST /data`
- Open the dashboard in the browser to view live status and alerts

## Repository Structure

```text
Disaster management System/
  .gitignore
  .pio/
  .vscode/
  diagram.json
  include/
  lib/
  platformio.ini
  src/
  test/
  wokwi.toml
  README.md
server/
  package.json
  package-lock.json
  server.js
  public/
  README.md
```

## GitHub Push Ready

This repository is configured for GitHub with the following ignored files:

- `node_modules/`
- `.pio/`
- `.vscode/`
- other local build or editor files

To push to GitHub:

```bash
git init
git add .
git commit -m "Initial commit"
git remote add origin <your-github-repo-url>
git push -u origin main
```

> If your remote branch is `master`, replace `main` with `master`.

## Notes

- The server and dashboard are separated into a `server/` folder.
- The embedded firmware lives in the `Disaster management System/` folder.
- For additional server usage details, see `server/README.md`.
