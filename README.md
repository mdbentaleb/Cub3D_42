# 🕹️ CUB3D



## 📌 Overview

**CUB3D** is a core project in the 42 curriculum that aims to build a simple 3D graphics engine using **C** and **MLX**. The project focuses on learning the basics of **raycasting**, window management, image handling, and converting 2D maps into a 3D first-person perspective similar to games like Wolfenstein 3D.

## ✨ Features

* 🧠 3D rendering engine using **raycasting**
* 🌍 Load and display 2D maps (`.cub` files)
* 🪄 Render walls, floor, and ceiling with colors and textures
* 🔄 Smooth player movement and rotation
* 📜 File parsing and map validation
* 🧱 Image management using **MLX**
* ⚡ Wall collision detection to prevent walking through walls
* 🖼️ Texture loading and rendering
* 🧪 Proper memory management to avoid leaks
* 🎨 Basic graphics with dynamic coloring
* ⏱️ Real-time updates of player movement

## 🧭 What CUB3D Supports

### 🧵 Execution Engine

* Parse `.cub` map files to generate the environment
* Use **raycasting** to calculate distances and render walls
* Draw walls and floors in real time

### 🧹 Parsing & Map Loading

* Read map files and validate their structure
* Check player position and other map elements
* Support fully enclosed maps to avoid errors

### ⚖️ Movement & Physics

* Move forward, backward, left, and right
* Rotate smoothly left/right
* Wall collision detection to prevent walking through walls

### 📂 Graphics

* Render walls column by column (raycasting)
* Apply textures to walls and floors
* Render elements dynamically on the screen
* Continuously update the screen with player movement

### 💬 Input & Interaction

* Keyboard input for movement and rotation
* Safe exit by closing the window or pressing ESC
* Smooth screen updates for a better experience

### ⚠️ Error Handling

* Validate files and inputs
* Handle loading and rendering errors
* Avoid memory leaks and ensure proper file handling

## 🛠️ Technical Constraints

* ❌ No external graphics libraries except **MLX**

* ✅ Must comply with **Norminette** rules:

  * Max 25 lines per function
  * Max 4 variables per function
  * Max 4 arguments per function

* 📁 Proper memory management to prevent leaks

* 🔀 Smooth frame updates without freezing

## ▶️ How to Use

### 🛠️ First-Time Setup

Before using the project for the first time, you need to run the `setup.sh` script to install all required dependencies (like MLX and any required libraries).

If your system requires administrative privileges to install libraries, run the script with sudo:

```bash
./setup.sh
```

This will check your system, install any missing libraries, and prepare the environment for CUB3D.

### 🚀 Running CUB3D

Run the game with:

```bash
./cub3d path/to/map.cub
```

A window will open displaying the 3D world where you can navigate using the keyboard.

### 💡 Tips

* Use **W/A/S/D** to move
* Use **Arrow keys** to rotate
* Close the window or press **ESC** to exit
* Make sure your map files are valid before running

### 🧪 Example Usage

```shell
./cub3d maps/map1.cub
```

* A window opens with a 3D map
* You can move within the map
* Walls and floors are rendered in 3D
* Wall collision prevents walking through walls

---