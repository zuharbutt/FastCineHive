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

<img width="1450" height="789" alt="image" src="https://github.com/user-attachments/assets/26fb1ea4-ef8c-4e50-8eb5-18e375c697be" />


### Genre Screen

<img width="1476" height="754" alt="image" src="https://github.com/user-attachments/assets/49f1b33d-98cb-4c44-86b4-6144b75c8595" />


### Films Screens

<img width="1445" height="872" alt="image" src="https://github.com/user-attachments/assets/37bc0a8d-ec3f-40ff-9d74-ada08e393605" />


<img width="1431" height="902" alt="image" src="https://github.com/user-attachments/assets/ec408088-6ff4-4f48-9fd5-95f1a2f0497c" />


<img width="1459" height="880" alt="image" src="https://github.com/user-attachments/assets/f31b92b1-6ee6-4493-80f6-86bbb76898b2" />


### Showtime Screen

<img width="1350" height="771" alt="image" src="https://github.com/user-attachments/assets/5c42d63a-aef4-4b18-af05-2c0735cfff65" />

### Seats Screen (the selected seat becomes white)

<img width="1271" height="868" alt="image" src="https://github.com/user-attachments/assets/d1a92607-5ed5-4622-bcf5-b4a3c7f4ce4c" />

### Snacks Screen

<img width="1462" height="790" alt="image" src="https://github.com/user-attachments/assets/e870f506-e784-4b10-a253-8382343a5e0e" />

### The Reciept Generated Screen

<img width="814" height="818" alt="image" src="https://github.com/user-attachments/assets/ef60929f-f0f8-4a36-9460-76f083ca8846" />






