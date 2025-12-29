# Connect Four - Modular C & Web Implementation 🔴🟡

A high-performance implementation of the classic Connect Four game, featuring robust backend logic in C and a modern, interactive web frontend. Developed as a final project for the C Programming course at HIT.

## 🚀 Key Features

### 💻 C Logic (Core Engine)
- **Modular Architecture:** Clean separation between game mechanics (`logic.c`) and the system interface.
- **3 AI Difficulty Levels:**
  - **Easy:** Computer makes random moves.
  - **Medium (Smart):** Features a look-ahead algorithm to identify winning moves or block the player.
  - **Hard (Strategic):** Advanced logic focusing on center-column dominance and planning.
- **Game Statistics:** Integrated tracking system for Player 1, Player 2, and Computer wins, including draws.
- **Robust Input Handling:** Advanced validation to prevent crashes from invalid inputs.

### 🌐 Web Frontend (GUI Version)
- **Visual Interface:** A polished, modern UI built with HTML5 and CSS3.
- **Interactive Gameplay:** Smooth "click-to-play" interface with real-time updates.
- **GitHub Pages Ready:** Fully functional web version accessible directly through the browser.

## 📁 Project Structure

- `logic.c`: The core game engine containing win detection and AI algorithms.
- `logic.h`: Header file containing constants, definitions, and function prototypes.
- `main.c`: Handles the game loops and terminal-based interaction.
- `index.html`, `style.css`, `script.js`: Files comprising the visual web implementation.

## 🛠️ How to Play

### Web Version (Live GUI)
Simply visit the live link on this repository (via GitHub Pages) or open the `index.html` file in any modern web browser to play the visual version.

### C Version (Source Code)
The C source files are provided for logic review. To run the terminal version, compile `main.c` and `logic.c` using any standard C compiler (GCC, Clang, or MSVC).

## 📝 AI Usage & Documentation
This project utilized AI tools (Google Gemini) for architectural planning, logic optimization, and debugging assistance. A full `AI_Usage.txt` document is included in the project files in accordance with academic requirements.

---
**Academic Project - Computer Science**
