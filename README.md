# FastCineHive 🎬

An interactive, graphical desktop Cinema Reservation System built in **C++** using the **Simple and Fast Multimedia Library (SFML)**. This application provides a complete cinema ticketing experience, featuring a dynamic UI for movie discovery, seat selection, concessions, and invoicing (screenshots attached at end) .

---

## 🚀 Key Features

*   **Immersive Welcome Screen:** An aesthetic graphical landing page to begin the booking process.
*   **Multi-Genre Catalog:** Browse movie listings categorized by Lollywood, Bollywood, and Hollywood.
*   **Interactive Showtime Selection:** Choose show times dynamically.
*   **Visual Seating Arrangement:** Interactive grid allowing users to click and select available seats (green) while showing booked seats (red).
*   **Snack Selection Counter:** Order refreshments (Popcorn, Nachos, Soda) with live quantity counters.
*   **Real-time Billing & Invoicing:** Instantly calculates total bill and generates a printable payment slip (`paymentslip.txt`).

---

## 🛠️ Tools & Technologies Used

*   **Programming Language:** C++ (C++14 / C++17 standard)
*   **Graphics & Windowing:** SFML 2.6.2 (Simple and Fast Multimedia Library) for UI rendering and window management
*   **Audio Engine:** OpenAL (integrated via SFML Audio module)
*   **Integrated Development Environment (IDE):** Visual Studio 2022 / Visual Studio Code
*   **Build System:** MSBuild (Microsoft Visual C++ compiler toolchain)
*   **Version Control:** Git & GitHub

---

## 📁 Project Directory Structure

```text
FastCineHive/
├── FASTCINEHIVE.sln        # Visual Studio 2022 Solution
├── .gitignore               # Configured git ignore patterns
├── README.md                # Project documentation
│
├── EXTERNAL/                # Pre-packaged external dependencies
│   └── SFML/
│       ├── include/         # SFML C++ header files
│       └── lib/             # SFML pre-compiled static libraries
│
├── FASTCINEHIVE/            # Main Project Directory
│   ├── FASTCINEHIVE.vcxproj         # MSBuild project file
│   ├── FASTCINEHIVE.vcxproj.filters # MSBuild filters file
│   ├── src/                 # Code files
│   │   └── FAST_CINE_HIVE_CODE.cpp  # Main program code
│   └── assets/              # Static assets
│       ├── audio/           # Soundtracks and sound effects
│       ├── fonts/           # TrueType (.ttf) font files
│       └── images/          # UI textures and movie poster graphics
│
└── x64/                     # Build output folder
    └── Debug/               # Target directory for executable & DLLs
```

---

## ⚙️ Installation & Running the Project

### Prerequisites
1. **Windows OS** (64-bit).
2. **Visual Studio 2022** with the **Desktop development with C++** workload installed.

### Setup Instructions
1. **Clone the repository:**
   ```bash
   git clone https://github.com/zuharbutt/FastCineHive.git
   cd FastCineHive
   ```

2. **Open & Build in Visual Studio:**
   - Double-click `FASTCINEHIVE.sln` to open the solution in Visual Studio 2022.
   - Set the build configuration to **Debug** or **Release** and platform to **x64**.
   - Press **F5** or click **Local Windows Debugger** to compile and run.

> [!NOTE]
> All required SFML DLL dependencies (`sfml-window-d-2.dll`, `sfml-graphics-d-2.dll`, etc.) and game asset directories have been pre-packaged and configured to reside in the run directory (`x64/Debug`), making the project plug-and-play.


### Welcome Screen

<img width="1440" height="846" alt="image" src="https://github.com/user-attachments/assets/44e24b15-d0e8-480b-a233-6203e7205c2f" />

### Genre Screen

<img width="1496" height="752" alt="image" src="https://github.com/user-attachments/assets/4c12c21e-c4d2-4e5a-a24a-854ed86b7922" />

### Films Screens

<img width="1456" height="918" alt="image" src="https://github.com/user-attachments/assets/969da72a-1b3f-4f19-8a31-f8fad18eb990" />

<img width="1885" height="932" alt="image" src="https://github.com/user-attachments/assets/b871cd3c-fef0-41d1-b14f-08e5982f9abe" />

<img width="1459" height="886" alt="image" src="https://github.com/user-attachments/assets/0da0c695-450c-4821-9df6-e7b676a0df3b" />

### Showtime Screen

<img width="1472" height="758" alt="image" src="https://github.com/user-attachments/assets/3476c0b4-6638-40bf-ad63-54754ebeff6c" />

### Seats Screen (the selected seat becomes white)

<img width="1086" height="784" alt="image" src="https://github.com/user-attachments/assets/974d19d0-faa6-40b9-bb30-192ff988661c" />

### Snacks Screen

<img width="1466" height="849" alt="image" src="https://github.com/user-attachments/assets/ebedfdc7-e532-4d57-b093-af47ea67c2ce" />

### The Reciept Generated Screen

<img width="795" height="840" alt="image" src="https://github.com/user-attachments/assets/fe1cfdaa-968f-425a-bc54-71ca5c6d1047" />





