# ESP32 OLED Independence Day Tribute

Celebrate **India's Independence Day** with an animated patriotic tribute on a **128×64 SSD1306 OLED** using an ESP32. The project combines cinematic transitions, typewriter-style text animations, patriotic messages, and a special **“I ♥ INDIA”** ending.

---

## ✨ Features

- 🇮🇳 Animated Independence Day tribute
- ✍️ Typewriter-style text animations
- 🎬 Smooth cinematic transitions
- ❤️ Pulsing heart animation
- 🇮🇳 Patriotic messages and visuals
- 📺 Optimized for 128×64 OLED displays
- ⚡ Lightweight and optimized for ESP32
- 📚 Beginner-friendly and easy to customize

---

## 🛠️ Hardware Required

| Component | Quantity |
|-----------|:--------:|
| ESP32 Development Board | 1 |
| SSD1306 OLED Display (128×64) | 1 |
| Breadboard | 1 |
| Jumper Wires | As Required |
| USB Cable | 1 |

---

## 🔌 Wiring

| OLED Pin | ESP32 Pin |
|---------|-----------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

> ⚠️ This project is designed for a **128×64 SSD1306 I²C OLED**.

---

## 💻 Software Requirements

Install the following libraries using the **Arduino IDE Library Manager**:

- Adafruit GFX
- Adafruit SSD1306

---

## 🚀 Getting Started

1. Download or clone this repository.
2. Open the `.ino` file in Arduino IDE.
3. Install the required libraries.
4. Connect the OLED according to the wiring table.
5. Select your ESP32 board and COM Port.
6. Upload the sketch.
7. Watch the Independence Day tribute come alive on the OLED. 🇮🇳

---

## 🎬 Animation

The tribute includes a sequence of animated patriotic messages with:

- ✍️ Typewriter text effects
- 🎞️ Smooth screen transitions
- ❤️ Pulsing heart animation
- 🇮🇳 A special **I ♥ INDIA** ending

The animation runs automatically after powering the ESP32.

---

## ⚙️ Customization

You can customize:

- Patriotic messages
- Text animation speed
- Display timing
- Transition effects
- Text size
- Animation sequence

---

## ⚠️ Troubleshooting

| Problem | Solution |
|---------|----------|
| OLED remains blank | Check VCC, GND, SDA, and SCL connections |
| Display not detected | Check the I²C address and OLED compatibility |
| Text not visible | Confirm the required libraries are installed |
| Upload failed | Verify the ESP32 board and COM Port |
| Animation looks incorrect | Make sure you are using a 128×64 SSD1306 OLED |

---

## 📚 Technologies Used

- ESP32
- Arduino IDE
- C++
- SSD1306 OLED Display
- I²C Communication
- Adafruit GFX
- Adafruit SSD1306

---

## ⭐ Support

If you found this project helpful, consider giving this repository a **⭐ Star**.

Your support helps **LifeTronix** create more open-source Arduino, ESP32, IoT, and Robotics projects.

---

## 📄 License

This project is licensed under the **MIT License**.

---

<p align="center">
Made with ❤️ by <strong>LifeTronix</strong>
</p>
