/*
 * =============================================================================
 * Project    : ESP32 OLED Independence Day Tribute
 * Version    : 1.0.0
 * Author     : LifeTronix
 * License    : MIT License
 * =============================================================================
 *
 * An animated Independence Day tribute for a 128×64 SSD1306 OLED using ESP32.
 * Features a cinematic intro, typewriter-style text animations, transitions,
 * and a pulsing heart with the message "I ♥ INDIA".
 *
 * Hardware:
 * • ESP32 Development Board
 * • SSD1306 128×64 OLED Display (I2C)
 *
 * Wiring:
 * VCC → 3.3V
 * GND → GND
 * SDA → GPIO 21
 * SCL → GPIO 22
 *
 * Libraries:
 * • Adafruit GFX
 * • Adafruit SSD1306
 *
 * =============================================================================
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C
#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ============================================================
// SETTINGS
// ============================================================

// ALL BLUE TEXT USES THIS SAME SIZE
#define BLUE_SIZE_X 1
#define BLUE_SIZE_Y 2

// Yellow header
#define HEADER_TEXT_Y 4
#define LETTER_GAP 1

// Animation timing
#define LETTER_DELAY 38
#define SPACE_DELAY 18
#define LINE_DELAY 60
#define HOLD_DELAY 220
#define TRANSITION_SPEED 10

// OLED zones
#define YELLOW_HEIGHT 16
#define BLUE_TOP 16

// ============================================================
// TEXT FUNCTIONS
// ============================================================

int getTextWidth(const char *text, int sx, int sy) {
  int16_t x1, y1;
  uint16_t w, h;
  display.setTextSize(sx, sy);
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  return w;
}

int centerX(const char *text, int sx, int sy) {
  return (SCREEN_WIDTH - getTextWidth(text, sx, sy)) / 2;
}

// ============================================================
// HEART
// ============================================================

void drawHeart(int cx, int cy, int size) {
  display.fillCircle(cx - size, cy - size / 2, size, SSD1306_WHITE);
  display.fillCircle(cx + size, cy - size / 2, size, SSD1306_WHITE);
  display.fillTriangle(
    cx - size * 2,
    cy,
    cx + size * 2,
    cy,
    cx,
    cy + size * 2,
    SSD1306_WHITE
  );
}

// ============================================================
// SPACED TEXT
// ============================================================

void drawSpacedText(const char *text, int x, int y, int gap) {
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  for (int i = 0; text[i] != '\0'; i++) {
    display.setCursor(x, y);
    display.write(text[i]);
    x += 6 + gap;
  }
}

// ============================================================
// FIXED HEADER
//
//               I ♥ I N D I A
//
// Only heart pulses.
// ============================================================

void drawHeader(bool pulse = false) {
  const int iX = 30;
  const int heartX = 47;
  const int indiaX = 56;

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  // Fixed I
  display.setCursor(iX, HEADER_TEXT_Y);
  display.print("I");

  // Only heart changes size
  drawHeart(heartX, 7, pulse ? 3 : 2);

  // INDIA with small letter spacing
  drawSpacedText("INDIA", indiaX, HEADER_TEXT_Y, LETTER_GAP);
}

// ============================================================
// DRAW BLUE TEXT
// ============================================================

void drawBlueText(const char *text, int x, int y, int visible) {
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(BLUE_SIZE_X, BLUE_SIZE_Y);
  display.setCursor(x, y);

  int len = strlen(text);
  if (visible > len) visible = len;

  for (int i = 0; i < visible; i++) {
    display.write(text[i]);
  }
}

// ============================================================
// TYPEWRITER CURSOR
// ============================================================

void drawCursor(int x, int y, int visible) {
  int cursorX = x + visible * 6 * BLUE_SIZE_X;

  display.fillRect(cursorX, y + 1, 1, 13, SSD1306_WHITE);
}

// ============================================================
// HEART PULSE HOLD
// ============================================================

void pulseHeart(
  const char *line1,
  const char *line2,
  int x1, int y1,
  int x2, int y2,
  int pulses = 1
) {
  for (int p = 0; p < pulses; p++) {
    display.clearDisplay();
    drawHeader(true);

    if (line1) drawBlueText(line1, x1, y1, strlen(line1));
    if (line2) drawBlueText(line2, x2, y2, strlen(line2));

    display.display();
    delay(65);

    display.clearDisplay();
    drawHeader(false);

    if (line1) drawBlueText(line1, x1, y1, strlen(line1));
    if (line2) drawBlueText(line2, x2, y2, strlen(line2));

    display.display();
    delay(65);
  }
}

// ============================================================
// BLUE EXIT TRANSITION
// ============================================================

void clearBlueTransition() {
  for (int x = SCREEN_WIDTH; x >= 0; x -= 8) {
    display.fillRect(
      x,
      BLUE_TOP,
      8,
      SCREEN_HEIGHT - BLUE_TOP,
      SSD1306_BLACK
    );

    display.display();
    delay(TRANSITION_SPEED);
  }
}

// ============================================================
// TWO LINE TYPEWRITER
// ============================================================

void animateTwoLines(
  const char *line1,
  const char *line2,
  int hold
) {
  // Final positions calculated once.
  // They never move during typing.
  int x1 = centerX(line1, BLUE_SIZE_X, BLUE_SIZE_Y);
  int x2 = centerX(line2, BLUE_SIZE_X, BLUE_SIZE_Y);

  // Improved breathing space
  int y1 = 23;
  int y2 = 43;

  int len1 = strlen(line1);
  int len2 = strlen(line2);

  // TYPE LINE 1
  for (int i = 0; i <= len1; i++) {
    display.clearDisplay();
    drawHeader(false);

    drawBlueText(line1, x1, y1, i);

    if (i < len1) drawCursor(x1, y1, i);

    display.display();

    if (i < len1) {
      delay(line1[i] == ' ' ? SPACE_DELAY : LETTER_DELAY);
    }
  }

  delay(LINE_DELAY);

  // TYPE LINE 2
  for (int i = 0; i <= len2; i++) {
    display.clearDisplay();
    drawHeader(false);

    drawBlueText(line1, x1, y1, len1);
    drawBlueText(line2, x2, y2, i);

    if (i < len2) drawCursor(x2, y2, i);

    display.display();

    if (i < len2) {
      delay(line2[i] == ' ' ? SPACE_DELAY : LETTER_DELAY);
    }
  }

  // Subtle heart pulse only
  pulseHeart(line1, line2, x1, y1, x2, y2, 1);

  delay(hold);
}

// ============================================================
// SINGLE LINE TYPEWRITER
// ============================================================

void animateSingleLine(const char *text, int hold) {
  int x = centerX(text, BLUE_SIZE_X, BLUE_SIZE_Y);
  int y = 34;
  int len = strlen(text);

  for (int i = 0; i <= len; i++) {
    display.clearDisplay();
    drawHeader(false);

    drawBlueText(text, x, y, i);

    if (i < len) drawCursor(x, y, i);

    display.display();

    if (i < len) {
      delay(text[i] == ' ' ? SPACE_DELAY : LETTER_DELAY);
    }
  }

  pulseHeart(text, NULL, x, y, 0, 0, 1);

  delay(hold);
}

// ============================================================
// INTRO
//
//              15 AUGUST
//
//               INDIA'S
//            INDEPENDENCE
// ============================================================

void intro() {
  const char *date = "15 AUGUST";
  const char *india = "INDIA'S";
  const char *independence = "INDEPENDENCE";

  int dateX = centerX(date, 1, 1);
  int dateY = 3;
  int dateLen = strlen(date);

  // 15 AUGUST — letter by letter
  for (int i = 0; i <= dateLen; i++) {
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(dateX, dateY);

    for (int j = 0; j < i; j++) {
      display.write(date[j]);
    }

    if (i < dateLen) {
      display.fillRect(dateX + i * 6, dateY, 1, 8, SSD1306_WHITE);
    }

    display.display();

    if (i < dateLen) {
      delay(date[i] == ' ' ? SPACE_DELAY : LETTER_DELAY);
    }
  }

  delay(100);

  // INDIA'S slides smoothly upward
  int indiaX = centerX(india, BLUE_SIZE_X, BLUE_SIZE_Y);

  for (int y = 42; y >= 25; y -= 3) {
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(dateX, dateY);
    display.print(date);

    drawBlueText(india, indiaX, y, strlen(india));

    display.display();
    delay(18);
  }

  delay(70);

  // INDEPENDENCE slides upward
  int independenceX = centerX(
    independence,
    BLUE_SIZE_X,
    BLUE_SIZE_Y
  );

  for (int y = 63; y >= 47; y -= 2) {
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(dateX, dateY);
    display.print(date);

    drawBlueText(india, indiaX, 25, strlen(india));
    drawBlueText(
      independence,
      independenceX,
      y,
      strlen(independence)
    );

    display.display();
    delay(16);
  }

  delay(350);

  // Cinematic wipe away
  for (int y = 0; y < SCREEN_HEIGHT; y += 8) {
    display.fillRect(0, y, SCREEN_WIDTH, 8, SSD1306_BLACK);
    display.display();
    delay(8);
  }

  // Header enters from left
  for (int x = -100; x <= 0; x += 10) {
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(30 + x, HEADER_TEXT_Y);
    display.print("I");

    drawHeart(47 + x, 7, 2);

    drawSpacedText(
      "INDIA",
      56 + x,
      HEADER_TEXT_Y,
      LETTER_GAP
    );

    display.display();
    delay(12);
  }

  delay(80);
}

// ============================================================
// OUTRO
// Same blue text size as every lyric.
// ============================================================

void outro() {
  animateTwoLines(
    "HAPPY",
    "INDEPENDENCE DAY",
    900
  );
}

// ============================================================
// FULL VIDEO
// ============================================================

void playVideo() {
  intro();

  animateTwoLines("KHATRO SE", "HASKE", HOLD_DELAY);
  clearBlueTransition();

  animateTwoLines("KHELNA", "ITNI TOH", HOLD_DELAY);
  clearBlueTransition();

  animateTwoLines("HAMME", "HIMMAT HAI", HOLD_DELAY);
  clearBlueTransition();

  animateTwoLines("MORE KALAI", "MAUT TAK", HOLD_DELAY);
  clearBlueTransition();

  animateTwoLines("ITNI TOH", "HAMME", HOLD_DELAY);
  clearBlueTransition();

  animateSingleLine("TAAQAT HAI", 350);
  clearBlueTransition();

  outro();

  display.clearDisplay();
  display.display();
  delay(250);
}

// ============================================================
// SETUP
// ============================================================

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true);
  }

  display.clearDisplay();
  display.display();
}

// ============================================================
// LOOP
// ============================================================

void loop() {
  playVideo();
}
