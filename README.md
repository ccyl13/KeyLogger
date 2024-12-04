
# KeyLogger Personalizable

This project is a keylogger developed in C++ by **Thomas O'Neil Álvarez**, with support for customizing its icon and compiling it for Windows systems.

## How It Works

The keylogger records all keypresses on a Windows machine and logs them into a file named `registro_teclas.txt`. It runs in the background as a hidden process.

### Features
- Records all keypresses, including special characters and combinations.
- Supports customizable icons for the executable.
- Developed in C++ for educational purposes.

## How to Use

### Compilation Steps (on Kali Linux)
1. Ensure you have `mingw-w64` installed on your Kali Linux machine. Install it if necessary with:
   ```bash
   sudo apt update
   sudo apt install mingw-w64
   ```
2. Navigate to the directory containing the project files:
   ```bash
   cd /path/to/project
   ```
3. Compile the keylogger into a `.exe` file:
   - Without a custom icon:
     ```bash
     x86_64-w64-mingw32-g++ keylogger.cpp -o keylogger.exe -lws2_32 -static -mwindows
     ```
   - With a custom icon (requires `recursos.rc`):
     1. Compile the resource file:
        ```bash
        x86_64-w64-mingw32-windres recursos.rc -o recursos.o
        ```
     2. Compile the executable:
        ```bash
        x86_64-w64-mingw32-g++ keylogger.cpp recursos.o -o keylogger.exe -lws2_32 -static -mwindows
        ```

### Adding a Custom Icon
1. Replace `Photoshop.ico` with your desired `.ico` file in the project folder.
2. Update `recursos.rc` to point to the new icon file:
   ```plaintext
   ICONO ICON "new_icon_name.ico"
   ```
3. Recompile the project following the steps above.

### Transferring to Windows
- **Using a USB Drive**:
  1. Copy the `keylogger.exe` file onto a USB drive.
  2. Plug the USB into a Windows machine and transfer the file.

- **Dragging from Kali to Windows** (in a virtual machine setup):
  1. Ensure shared folders are enabled between your Kali and Windows VM environments.
  2. Drag and drop the file from Kali to the Windows desktop.

## Stopping the Keylogger
To stop the keylogger running in the background:
1. Open Task Manager on Windows (`Ctrl + Shift + Esc`).
2. Locate the `keylogger.exe` process.
3. Right-click and select **End Task**.

## Notes
- This project is intended for educational purposes only. Use it responsibly and ensure compliance with all local laws and regulations.

## License
Use this project at your own risk. It is designed exclusively for educational purposes.
