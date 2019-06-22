// IPTool.cpp : main project file.

#include <iostream>
#include <string>
#include "IpChanger.h"
#include <algorithm>

using namespace System;
using namespace std;

void Usage()
{
	color("YELLOW");
	cout << "Usage: IpTool ";
	color();
	cout << " [ -l ] ";
	cout << "[ -a -n <index - id> -i <ip - address> -m <subnet mask>]\n";
	cout << "\t[ -d -c <context-id>]\n\n";
}
void Help()
{
	color("LIGHTGREEN");
	cout << "\nIpTool is a program that helps you with ip addresses." << endl;
	color();
	cout << "Syntaxis:\n" << endl;
	cout << "IpTool ";
	color();
	cout << " [ -l ] ";
	cout << "[ -a -n <index - id> -i <ip - address> -m <subnet mask>]\n";
	cout << "\t[ -d -c <context-id>]\n";
	cout << "Options:\n" << endl;
	color("YELLOW");
	cout << "-h, --help \t\t\t Show this help-list." << endl;
	cout << "-a, --add \t\t\t Add an IP Address." << endl;
	cout << "-d, --delete \t\t\t Delete an IP Adress." << endl;
	cout << "-i, --IP \t\t\t Ip Address to specify with -a option." << endl;
	cout << "-m, --mask \t\t\t Subnet Mask to specify with -a option." << endl;
	cout << "-n, --number \t\t\t Index ID of an existing network adapter." << endl;
	cout << "-c, --context \t\t\t Adapters context ID." << endl;
	cout << "-l, --list \t\t\t List adapter index IDs and IP Address context ID information." << endl;
	color("GREEN");
	cout << "\nCopyrights (C) ramb0 2017." << endl;
	color();
}
void VERSION()
{
	color("WHITE");
	cout << "\nName: \t\t";
	color("LIGHTGREEN");
	cout << "IpTool.exe" << endl;
	color("WHITE");
	cout << "Version: \t";
	color("GREEN");
	cout << "25-6-2017 # 1.4.5" << endl;
	color("WHITE");
	cout << "Author: \t";
	color("CYAN");
	cout << "Ramb0" << endl;
	color("LIGHTRED");
	cout << "\t\tCopyrights (C) ramb0 2017" << endl;
	color("WHITE");
	cout << "Description: \n\n";
	color("YELLOW");
	cout << "\t\tTool to do things with ip addresses." << endl;
	color();
}
BOOL WINAPI ConsoleHandler(DWORD Event)
{
	switch (Event)
	{
	case CTRL_C_EVENT:
		color();
		cout << "CTRL+C event triggered..." << endl;
		exit(0);
	case CTRL_BREAK_EVENT:
		color();
		cout << "BREAK event triggered..." << endl;
		exit(0);
	case CTRL_CLOSE_EVENT:
		color();
		cout << "PROGRAMCLOSE event triggered..." << endl;
		exit(0);
	case CTRL_LOGOFF_EVENT:
		color();
		cout << "USERLOGOFF event triggered..." << endl;
		exit(0);
	case CTRL_SHUTDOWN_EVENT:
		color();
		cout << "COMPUTERSHUTDOWN event trigggered..." << endl;
		exit(0);
	}
	return TRUE;
}
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		Usage();
		exit(1);
	}
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
	{
		cout << "Unable to install console handlers!" << endl;
		return -1;
	}
	color();
	BOOL OptList = FALSE;
	BOOL OptAdd = FALSE;
	BOOL OptDel = FALSE;
	BOOL DNS = FALSE;
	CHAR NewIPStr[64];
	CHAR NewMaskStr[64];
	NewIPStr[0] = '\0';
	NewMaskStr[0] = '\0';
	DWORD Index = 0;
	DWORD Context = 0;
	//	Argument/Option parser.
	for (int i = 1; i < argc; i++)
	{
		if ((argv[i][0] == '-') || (argv[i][0] == '/'))
		{
			string arg = argv[i];
			transform(arg.begin(), arg.end(), arg.begin(), tolower);
			switch (tolower(argv[i][1]))
			{
			case 'l':
				OptList = TRUE;
				break;
			case 'h':
				Help();
				exit(0);
			case 'a':
				OptAdd = TRUE;
				break;
			case 'd':
				OptDel = TRUE;
				break;
			case 'g':
				DNS = TRUE;
				break;
			case 'i':
				if (strlen(argv[i + 1]) > 6)
				{
					strcpy_s(NewIPStr, sizeof(NewIPStr), argv[i+1]);
					i++;
					break;
				}
				else
				{
					if (argc == i)
					{
						color("LIGHTRED");
						cout << "\nNo value given for -i!" << endl;
						color();
						exit(1);
					}
					color("LIGHTRED");
					cout << "\n '";
					color("YELLOW");
					cout << argv[i + 1];
					color("LIGHTRED");
					cout << "' is an invalid ip address." << endl;
					color();
					exit(1);
				}
				break;
			case 'm':
				if (strlen(argv[i + 1]) > 9)
				{
					strcpy_s(NewMaskStr, sizeof(NewMaskStr), argv[i+1]);
					i++;
					break;
				}
				else
				{
					if (argc == i)
					{
						color("LIGHTRED");
						cout << "\nNo value given for -m!" << endl;
						color();
						exit(1);
					}
					color("LIGHTRED");
					cout << "\n '";
					color("YELLOW");
					cout << argv[i + 1];
					color("LIGHTRED");
					cout << "' is an invalid Network mask." << endl;
					color();
					exit(1);
				}
				break;
			case 'n':
				if (strlen(argv[i + 1]) != NULL)
				{
					Index = atoi(argv[i+ 1]);
					i++;
					break;
				}
				else
				{
					if (argc == i + 1)
					{
						color("LIGHTRED");
						cout << "\nNo value given for -n!" << endl;
						color();
						exit(1);
					}
					color("LIGHTRED");
					cout << "\n '";
					color("YELLOW");
					cout << argv[i + 1];
					color("LIGHTRED");
					cout << "' is an invalid Index Number." << endl;
					color();
					exit(1);
				}
				break;
			case 'c':
				if (strlen(argv[i + 1]) != NULL)
				{
					Context = atoi(argv[i + 1]);
					i++;
					break;
				}
				else
				{
					if (argc == i + 1)
					{
						color("LIGHTRED");
						cout << "\nNo value given for -c!" << endl;
						color();
						exit(1);
					}
					color("LIGHTRED");
					cout << "\n '";
					color("YELLOW");
					cout << argv[i + 1];
					color("LIGHTRED");
					cout << "' is an invalid Context Number." << endl;
					color();
					exit(1);
				}
			case '-':
				if (arg == "--help")
				{
					Help();
					exit(0);
				}
				if (arg == "--version")
				{
					VERSION();
					exit(0);
				}
				if (arg == "--add" || arg == "-add")
				{
					OptAdd = TRUE;
				}
				if (arg == "--mask" || arg == "-mask")
				{
					if (strlen(argv[i + 1]) > 9)
					{
						strcpy_s(NewMaskStr, sizeof(NewMaskStr), argv[i + 1]);
						i++;
						break;
					}
					else
					{
						if (argc == i + 1)
						{
							color("LIGHTRED");
							cout << "\nNo value given for --mask!" << endl;
							color();
							exit(1);
						}
						color("LIGHTRED");
						cout << "\n '";
						color("YELLOW");
						cout << argv[i + 1];
						color("LIGHTRED");
						cout << "' is an invalid Network mask." << endl;
						color();
						exit(1);
					}
					break;
				}
				if (arg == "--ip" || arg == "-ip")
				{
					if (strlen(argv[i + 1]) > 6)
					{
						strcpy_s(NewIPStr, sizeof(NewIPStr), argv[i + 1]);
						i++;
						break;
					}
					else
					{
						if (argc == i + 1)
						{
							color("LIGHTRED");
							cout << "\nNo value given for --ip!" << endl;
							color();
							exit(1);
						}
						color("LIGHTRED");
						cout << "\n '";
						color("YELLOW");
						cout << argv[i + 1];
						color("LIGHTRED");
						cout << "' is an invalid ip address." << endl;
						color();
						exit(1);
					}
					break;
				}
				if (arg == "--number" || arg == "-number")
				{
					if (strlen(argv[i + 1]) > 2)
					{
						Index = atoi(&argv[i][2]);
						i++;
						break;
					}
					else
					{
						if (argc == i + 1)
						{
							color("LIGHTRED");
							cout << "\nNo value given for --number!" << endl;
							color();
							exit(1);
						}
						color("LIGHTRED");
						cout << "\n '";
						color("YELLOW");
						cout << argv[i + 1];
						color("LIGHTRED");
						cout << "' is an invalid Index Number." << endl;
						color();
						exit(1);
					}
				}
				if (arg == "--context" || arg == "-context")
				{
					if (strlen(argv[i + 1]) != NULL)
					{
						Context = atoi(argv[i + 1]);
						i++;
						break;
					}
					else
					{
						if (argc == i + 1)
						{
							color("LIGHTRED");
							cout << "\nNo value given for -c!" << endl;
							color();
							exit(1);
						}
						color("LIGHTRED");
						cout << "\n '";
						color("YELLOW");
						cout << argv[i + 1];
						color("LIGHTRED");
						cout << "' is an invalid Context Number." << endl;
						color();
						exit(1);
					}
				}
				if (arg == "--delete" || arg == "-delete")
				{
					OptDel = TRUE;
					break;
				}
				if (arg == "--list" || arg == "-list")
				{
					OptList = TRUE;
					break;
				}
				if (arg == "--dns" || arg == "-dns" || arg == "--getdns" || arg == "-getdns")
				{
					DNS = TRUE;
					break;
				}

				else
				{

					color("LIGHTRED");
					cout << "Unknown option: ";
					color("YELLOW");
					cout << argv[i];
					color();
					exit(1);
				}
			default:
				color("LIGHTRED");
				cout << "\nUnknown option: ";
				color("YELLOW");
				cout << argv[i][1] << endl;
				color();
				exit(1);
				break;
			}
		}
		else
		{
			color("LIGHTRED");
			cout << "\nUnknown argument: ";
			color("YELLOW");
			cout << argv[i] << endl;
			color();
			exit(1);
		}
	}
	//	Check Options.
	if (OptList == TRUE)
	{
		IpChanger changer;
		changer.LIST_ADAPTERS();
		exit(0);
	}
	if (OptAdd == TRUE )
	{
		if (Index == NULL || NewIPStr[0] == '\0' || NewMaskStr[0] == '\0')
		{
			color("LIGHTRED");
			cout << "\nCould not run OptAdd: One parameter or more parameters is missing." << endl;
			color("YELLOW");
			cout << "Usage: ";
			color();
			cout << "IpTool [ -a -n <index-id> -i <ip_address> -m <subnet mask> ]" << endl;
			exit(1);
		}
		else
		{
			//	Add Ip Address.
			IpChanger(Index, NewIPStr, NewMaskStr);
			exit(0);
		}
	}
	if (OptDel == TRUE)
	{
		if (Context == NULL)
		{
			color("LIGHTRED");
			cout << "\nCould not run OptDel: -c is missing." << endl;
			color("YELLOW");
			cout << "Usage: ";
			color();
			cout << "IpTool [ -d -c <context> ]" << endl;
			exit(1);
		}
		else
		{
			//	Delete Ip Address.
			IpChanger(Context, TRUE);
			exit(0);
		}
		
	}
	if (DNS == TRUE)
	{
		IpChanger changer;
		changer.GET_DNS_PARS();
		exit(0);
	}
	color("LIGHTRED");
	cout << "\nInvalid syntaxis!" << endl;
	color();
	return 1;
}
