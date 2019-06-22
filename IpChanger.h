#pragma once
//	Link to libary files.
#pragma comment(lib, "IPhlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
//	Link to header files.
#include <WinSock2.h>
#include <iphlpapi.h>
#include <WS2tcpip.h>
#include <string>
#include <stdio.h>
#include <COLORS.h>
//	Function to use.
#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
using namespace std;
#ifndef IpChanger_H
#define IpChanger_H
class IpChanger
{
public:
	IpChanger();
	//	Initializes IpChanger and deletes an ip.
	IpChanger(DWORD Context, BOOL FCK);
	//	Initializes IpChanger and adds an ip.
	IpChanger(DWORD Index, CHAR NewIPstr[64], CHAR NewMaskStr[64]);
	void LIST_ADAPTERS();
	void GET_DNS_PARS();
private:
	WSADATA wsaData;
	DWORD VERSION = MAKEWORD(2, 2);
	ULONG NTEContext = 0;
	ULONG NTEInstance;
	IPAddr NewIP;
	IPAddr NewMask;
	PMIB_IPADDRTABLE pIPAddrTable;
	DWORD dwRetVal = 0;
	DWORD dwSize = 0;
	IN_ADDR IPAddr;
	DWORD ifIndex;
	DWORD AdapterInfoSize;
	DWORD Err;
	PIP_ADAPTER_INFO pAdapterInfo, pAdapt;
	PIP_ADDR_STRING pAddrStr;

};
#endif // !IpChanger_H