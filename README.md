# WinTooth

WinTooth is a simple C++ program for discovering Bluetooth devices and checking their connection status on Windows.

## Features
- Detects if Bluetooth is enabled.
- Lists all nearby and paired Bluetooth devices.
- Checks which devices are currently connected.

## Requirements
- Windows OS
- Microsoft Visual Studio (or any C++ compiler with Windows SDK)
- Bluetooth hardware enabled

## Installation
1. Clone the repository:
```powershell
git clone https://github.com/Raulisr00t/WinTooth.git
```
2.Open the project in Visual Studio or compile it manually:
```powershell
cl WinTooth.cpp /link /LIBPATH:"C:\Path\To\Windows\SDK\Lib" Bthprops.lib
```
## Usage
Run the executable to scan for Bluetooth devices:
```powershell
> Bluetooth-Discovery.exe
```

### Example Output:
```powershell
[+] Bluetooth is Enabled!
[+] Found Device: Wireless Mouse (CONNECTED ✅)
[+] Found Device: John's Phone (NOT CONNECTED ❌)
[✅] At least one Bluetooth device is currently connected.
```

## License
This project is licensed under the MIT License.
