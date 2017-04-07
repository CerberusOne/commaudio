#define STRICT
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _UNICODE

#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <streambuf>
#include "MenuSettings.h"
#include <tchar.h>
#include <strsafe.h>
#include <vector>
#include "Microphone.h"

#define DEFAULT_PORT	5555	
#define WM_SOCKET		104
#define PACKET_SIZE		1024
#define MAX_THREADS		3
#define DEFAULT_IP		"127.0.0.1"
#define TEST_FILE		"06 - Little Wing.flac"

#define SONG_LIST		1
#define CLIENT_LIST		2
#define SONG_REQUEST	3




typedef struct {
	int header;
	union {
		int numOfSongs;
		int numOfClients;
		int SID;		
	};
} ControlMessage;

typedef struct {
	char* username;;
	char* ip;
} ClientData;

typedef struct {
	int SID;
	char* title;
	char* artist;
} SongData;


LRESULT CALLBACK Idle(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI command(LPVOID lpParam);
DWORD WINAPI recvCommand(LPVOID lpParam);
DWORD WINAPI connect(LPVOID lpParam);
bool uploadFile();
bool downloadFile();
bool recvServerMessage();

static TCHAR Name[] = TEXT("COMM Audio Client");
HWND hwnd;
HINSTANCE mainInst;
SOCKET Socket = NULL;
HANDLE  hThreadArray[MAX_THREADS];
DWORD dwThreadIdArray[MAX_THREADS];
std::vector<SongData> songs;
std::vector<ClientData> clients;




