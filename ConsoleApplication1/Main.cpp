#include <ctime>
#include <iostream>
#include "LazyImporter.h"
#include "XOR.hpp"
#include <random>
#include <cstdio>
#include <windows.h>
#include <tchar.h>
#include <tlhelp32.h>

FILE* pFile = nullptr;
char title[100];




bool Get(const TCHAR* const executableName) {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	const auto snapshot = LI_FN(CreateToolhelp32Snapshot)(TH32CS_SNAPPROCESS, NULL);

	if (!Process32First(snapshot, &entry)) {
		CloseHandle(snapshot);
		return false;
	}

	do {
		if (!_tcsicmp(entry.szExeFile, executableName)) {
			CloseHandle(snapshot);
			return true;
		}
	} while (Process32Next(snapshot, &entry));

	CloseHandle(snapshot);
	return false;
}





auto Find()-> VOID
{
	DWORD PID = Get(xorthis("FortniteClient-Win64-Shipping.exe"));
	if (PID != NULL)
	{
		printf(xorthis("[+] Press F2 In The Lobby To Inject The Cheat.\n"));
	}
	else if (PID == NULL)
	{
		printf(xorthis("[+] Wating For FortniteClient-Win64-Shipping.exe\n"));
		while (true)
		{
			PID = Get(xorthis("FortniteClient-Win64-Shipping.exe"));
			if (PID != NULL)
			{
				printf(xorthis("[+] Press F2 In The Lobby To Inject The Cheat.\n"));
				break;
				continue;

			}
		}

	}
}

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}


void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

std::string random_string(std::size_t length)
{

	const std::string CHARACTERS = ("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

	std::string random_string;

	for (std::size_t i = 0; i < length; ++i)
	{
		random_string += CHARACTERS[distribution(generator)];
	}

	return random_string;
}

void strGetRandomAlphaNum(char* sStr, unsigned int iLen)
{
	char Syms[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned int Ind = 0;
	srand(time(NULL) + rand());
	while (Ind < iLen)
	{
		sStr[Ind++] = Syms[rand() % 62];
	}
	sStr[iLen] = '\0';
}



DWORD MainThread(LPVOID lp)
{
	AllocConsole();
	freopen_s(&pFile, xorthis("CONOUT$"), xorthis("w"), stdout);

	strGetRandomAlphaNum(title, 8);
	SetConsoleTitleA(random_string(50).c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	Sleep(1000);
	std::cout << xorthis("[+] GhostFN Free Version Fortnite Cheat! Status: "); // Name of your cheat
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	std::cout << xorthis("Semi Detected\n");
	Sleep(1000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	std::cout << xorthis("[+] Loading The Free Driver...\n");
	HideConsole();
	system(xorthis("start C:/Windows/System32/kdmappernew.exe C:/Windows/System32/1909Inj.sys ")); //First Path of kdmapper //Path of driver
	ShowConsole();
	std::cout << xorthis("[+] Driver Loaded Successfully.\n");
	Sleep(3000);
	system(xorthis("cls"));
	Find();

	while (true)
	{
		if (GetAsyncKeyState(VK_F2))
		{
			HideConsole();
			system(xorthis("start C:\\Windows\\System32\\sexmap.exe FortniteClient-Win64-Shipping.exe dxgi.dll C:\\Windows\\System32\\updated1.dll"));// Put the path of your dll
			Sleep(1500);
			std::cout << xorthis("[+] Successfully Injected \n");
			break;
			continue;
		}
	}
	return false;
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}