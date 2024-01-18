/*
 * This is very useful!
*/


#include <windows.h>


namespace Functions {
	
	int createAndSetRegKey(HKEY key, LPCSTR subKey, LPCSTR valueName, DWORD type, const BYTE* data, DWORD size){
		HKEY hKey = nullptr;
		if (RegCreateKeyExA(key, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS){
			RegSetValueExA(hKey, valueName, 0, type, data, size);
			RegCloseKey(hKey);
			return 0;
		}
		return 1;
	}
	
	int setRegKey(HKEY key, LPCSTR subKey, LPCSTR valueName, DWORD type, const BYTE* data, DWORD size){
		HKEY hKey = nullptr;
		if (RegOpenKeyExA(key, subKey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS){
			RegSetValueExA(hKey, valueName, 0, type, data, size);
			RegCloseKey(hKey);
			return 0;
		}
		return 1;
	}
	
	int createFile(LPCSTR fName, DWORD fAttributes, LPCVOID pBuff, DWORD buffSize){
		HANDLE file = CreateFileA(fName, GENERIC_READ | GENERIC_WRITE, 0, NULL,	CREATE_ALWAYS, fAttributes,	NULL);
		if (file != INVALID_HANDLE_VALUE){
			WriteFile(file, pBuff, buffSize, NULL,	NULL);
			CloseHandle(file);
			return 0;
		}
		CloseHandle(file);
		return 1;
	}
}