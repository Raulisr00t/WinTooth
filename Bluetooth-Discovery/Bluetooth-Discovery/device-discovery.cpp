#include <Windows.h>
#include <iostream>
#include <bluetoothapis.h>

using namespace std;

#pragma comment(lib, "Bthprops.lib")

bool IsBlueToothEnabled() {
    BLUETOOTH_FIND_RADIO_PARAMS params = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    HANDLE hRadio = NULL;
    HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&params, &hRadio);

    if (hFind) {
        BluetoothFindRadioClose(hFind);
        CloseHandle(hRadio);
        return true;
    }
    return false;
}

void DiscoverBluetoothDevices() {
    BLUETOOTH_DEVICE_SEARCH_PARAMS params = { 0 };
    BLUETOOTH_DEVICE_INFO info = { 0 };

    HANDLE hRadio = NULL;
    HBLUETOOTH_RADIO_FIND hFind = NULL;
    HBLUETOOTH_DEVICE_FIND device = NULL;

    BLUETOOTH_FIND_RADIO_PARAMS radioParams = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    hFind = BluetoothFindFirstRadio(&radioParams, &hRadio);

    if (hFind == NULL || hRadio == NULL) {
        cerr << "[!] No Bluetooth Radio found." << endl;
        return;
    }
    BluetoothFindRadioClose(hFind);

    params.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    params.fReturnAuthenticated = TRUE;
    params.fReturnConnected = TRUE;
    params.fReturnRemembered = TRUE;
    params.fReturnUnknown = TRUE;
    params.fIssueInquiry = FALSE;
    params.hRadio = hRadio;

    info.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    device = BluetoothFindFirstDevice(&params, &info);

    if (device == NULL) {
        cerr << "[!] No Bluetooth devices found. Error: " << GetLastError() << endl;
        CloseHandle(hRadio);
        return;
    }

    cout << "\n[+] Scanning Bluetooth Devices...\n";

    do {
        wcout << "[+] Found Device: " << info.szName;

        if (info.fConnected) {
            wcout << " (CONNECTED ✅)" << endl;
        }
        else {
            wcout << " (NOT CONNECTED ❌)" << endl;
        }
    } while (BluetoothFindNextDevice(device, &info));

    BluetoothFindDeviceClose(device);
    CloseHandle(hRadio);
}

bool IsDeviceConnected() {
    BLUETOOTH_DEVICE_SEARCH_PARAMS params = { 0 };
    BLUETOOTH_DEVICE_INFO info = { 0 };

    HANDLE hRadio = NULL;
    HBLUETOOTH_RADIO_FIND hFind = NULL;
    HBLUETOOTH_DEVICE_FIND device = NULL;

    BLUETOOTH_FIND_RADIO_PARAMS radioParams = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    hFind = BluetoothFindFirstRadio(&radioParams, &hRadio);

    if (hFind == NULL || hRadio == NULL) {
        return false;
    }
    BluetoothFindRadioClose(hFind);

    params.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    params.fReturnAuthenticated = TRUE;
    params.fReturnConnected = TRUE;
    params.fReturnRemembered = TRUE;
    params.fReturnUnknown = TRUE;
    params.fIssueInquiry = FALSE;
    params.hRadio = hRadio;

    info.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    device = BluetoothFindFirstDevice(&params, &info);

    if (device == NULL) {
        CloseHandle(hRadio);
        return false;
    }

    bool connected = false;

    do {
        if (info.fConnected) {
            connected = true;
            break;
        }
    } while (BluetoothFindNextDevice(device, &info));

    BluetoothFindDeviceClose(device);
    CloseHandle(hRadio);

    return connected;
}

int main() {
    if (IsBlueToothEnabled()) {
        cout << "[+] Bluetooth is Enabled!" << endl;
    }
    else {
        cerr << "[-] Bluetooth is not Enabled, Please Turn ON!" << endl;
        return 1;
    }

    DiscoverBluetoothDevices();

    if (IsDeviceConnected()) {
        cout << "[✅] At least one Bluetooth device is currently connected." << endl;
    }
    else {
        cout << "[❌] No Bluetooth devices are currently connected." << endl;
    }

    return 0;

}