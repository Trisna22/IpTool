#include "IpChanger.h"

IpChanger::IpChanger()
{
	if (WSAStartup(VERSION, &wsaData) != NULL)
	{
		color("LIGHTRED");
		cout << "\nWsa Startup failed!" << endl;
		color();
		exit(1);
	}
}
IpChanger::IpChanger(DWORD Context, BOOL FCK)
{
	if (WSAStartup(VERSION, &wsaData) != NULL)
	{
		color("LIGHTRED");
		cout << "\nWsa Startup failed!" << endl;
		color();
		exit(1);
	}
	//	Variable where handle to the deleted IP will be returned.
	if ((dwRetVal = DeleteIPAddress(Context)) == NO_ERROR)
	{
		color("LIGHTGREEN");
		cout << "\nIPv4 Address succesfully deleted!" << endl;
		color();
	}
	else
	{
		color("LIGHTRED");
		cout << "\nDeleteIpAddress failed with error: " << dwRetVal << endl;	
		color();
	}

}
IpChanger::IpChanger(DWORD Index, CHAR NewIPStr[64], CHAR NewMaskStr[64])
{
	if (WSAStartup(VERSION, &wsaData) != NULL)
	{
		color("LIGHTRED");
		cout << "\nWsa Startup failed!" << endl;
		color();
		exit(1);
	}
	//	TESTING
	//cout << "\nNewIpStr: " << NewIPStr << endl;
	//cout << "NewMaskStr: " << NewMaskStr << endl;
	//cout << "Index: " << Index << endl;

	//	IPv4 address and subnet mask.
	ULONG iaIPAddress = inet_addr(NewIPStr);
	ULONG iaIPMask = inet_addr(NewMaskStr);
	//	Variables where handles to the added IP are returned.
	ULONG NTEContext = 0;
	ULONG NTEInstance = 0;
	if ((dwRetVal = AddIPAddress(iaIPAddress, iaIPMask, Index, &NTEContext, &NTEInstance)) == NO_ERROR)
	{
		color("LIGHTGREEN");
		cout << "\nIPv4 address ";
		color("WHITE");
		cout << NewIPStr;
		color("LIGHTGREEN");
		cout << " was succesfully added." << endl;
		color();
	}
	else
	{
		color("LIGHTRED");
		cout << "\nAddIPAddress failed with error: ";
		color("YELLOW");
		cout << dwRetVal << endl;
		color();
		if (dwRetVal == 5 && dwRetVal == ERROR_ACCESS_DENIED)
		{
			color("YELLOW");
			cout << "You need to have admin priveleges!" << endl;
			color();
		}
		else if (dwRetVal == 5010 && dwRetVal == ERROR_OBJECT_ALREADY_EXISTS)
		{
			color("LIGHTRED");
			cout << "Ip address already exists!" << endl;
			color();
		}
		else if (dwRetVal == 1168 && dwRetVal == ERROR_NOT_FOUND)
		{
			color("LIGHTRED");
			cout << "Element not found!" << endl;
			color();
		}
		else if (dwRetVal == 87 && dwRetVal == ERROR_INVALID_PARAMETER)
		{
			color("LIGHTRED");
			cout << "Invalid parameter given!" << endl;
			color();
		}
		exit(1);
	}
	 
}

void IpChanger::LIST_ADAPTERS()
{
	/*
	//////////////////////////////////////////////////////////////////////////////
		FIRST TABLE
	//////////////////////////////////////////////////////////////////////////////
	*/
	pIPAddrTable = (MIB_IPADDRTABLE*)MALLOC(sizeof(MIB_IPADDRTABLE));
	if (pIPAddrTable == NULL)
	{
		color("LIGHTRED");
		cout << "Error allocating memory needed to call GetIpAddrTable." << endl;
		color();
		exit(1);
	}
	else
	{
		dwSize = 0;
		// Make an initial call to GetIpAddrTable to get the
		// necessary size into the dwSize variable.
		if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER)
		{
			FREE(pIPAddrTable);
			pIPAddrTable = (MIB_IPADDRTABLE*)MALLOC(dwSize);
		}
		if (pIPAddrTable == NULL)
		{
			color("LIGHTRED");
			cout << "Memory allocation failed for GetIpAddrTable." << endl;
			color();
			exit(1);
		}
	}
	// Make a second call to GetIpAddrTable to get the
	// actual data we want.
	if ((dwRetVal = GetIpAddrTable(pIPAddrTable, &dwSize, 0)) == NO_ERROR) {
		color("WHITE");
		cout << "Information about connected adapter." << endl;
		color("YELLOW");
		// Save the interface index to use for adding an IP address
		ifIndex = pIPAddrTable->table[0].dwIndex;
		printf("\nInterface Index:\t%ld\n", ifIndex);
		IPAddr.S_un.S_addr = (u_long)pIPAddrTable->table[0].dwAddr;
		printf("IP Address:       \t%s (%lu%)\n", inet_ntoa(IPAddr),
			pIPAddrTable->table[0].dwAddr);
		IPAddr.S_un.S_addr = (u_long)pIPAddrTable->table[0].dwMask;
		printf("Subnet Mask:      \t%s (%lu%)\n", inet_ntoa(IPAddr),
			pIPAddrTable->table[0].dwMask);
		IPAddr.S_un.S_addr = (u_long)pIPAddrTable->table[0].dwBCastAddr;
		printf("BroadCast Address:\t%s (%lu%)\n", inet_ntoa(IPAddr),
			pIPAddrTable->table[0].dwBCastAddr);
		printf("Reassembly size:  \t%lu\n\n",
			pIPAddrTable->table[0].dwReasmSize);
		color();
	}
	else {
		printf("Call to GetIpAddrTable failed with error %d.\n", dwRetVal);
		if (pIPAddrTable)
			FREE(pIPAddrTable);
		exit(1);
	}
	/*
	//////////////////////////////////////////////////////////////////////////////
		SECOND TABLE
	//////////////////////////////////////////////////////////////////////////////
	*/
	AdapterInfoSize = 0;
	//	Get sizing information about all adapters.
	if ((Err = GetAdaptersInfo(NULL, &AdapterInfoSize)) != NULL)
	{
		if (Err != ERROR_BUFFER_OVERFLOW)
		{
			color("LIGHTRED");
			cout << "GetAdaptersInfo sizing failed with error: ";
			color("YELLOW");
			cout << Err << endl;
			color();
			exit(1);
		}
	}
	//	Allocating memory from sizing information.
	if ((pAdapterInfo = (PIP_ADAPTER_INFO)GlobalAlloc(GPTR, AdapterInfoSize)) == NULL)
	{
		color("LIGHTRED");
		cout << "Memory allocating error." << endl;
		color();
		exit(1);
	}
	//	Get actual adapter information.
	if ((Err = GetAdaptersInfo(pAdapterInfo, &AdapterInfoSize)) != NULL)
	{
		color("LIGHTRED");
		cout << "GetAdaptersInfo failed with error: ";
		color("YELLOW");
		cout << Err << endl;
		color();
		exit(1);
	}
	color("WHITE");
	cout << "Other Adapters.\n" << endl;
	color();
	cout << "MAC Address - Adapter" << endl;
	cout << "Index \t Context \t Ip Address \t Subnet Mask" << endl;
	cout << "---------------------------------------------------------" << endl;
	pAdapt = pAdapterInfo;
	while (pAdapt)
	{
		//	Showing MAC Address.
		color("WHITE");
		for (int j = 0; j < pAdapt->AddressLength; j++)
		{
			if (j == (pAdapt->AddressLength - 1))
				printf("%.2X - ", (int)pAdapt->Address[j]);
			else
				printf("%.2X-", (int)pAdapt->Address[j]);
		}
		color("LIGHTGREEN");
		printf("%s\n", pAdapt->Description);
		color();
		pAddrStr = &(pAdapt->IpAddressList);
		while (pAddrStr)
		{
			color("CYAN");
			printf("%-10.d", pAdapt->Index);
			color("LIGHTRED");
			printf("%-10.d", pAddrStr->Context);
			color();
			printf("\t%-20.20s", pAddrStr->IpAddress.String);
			printf("%s\n", pAddrStr->IpMask.String);

			pAddrStr = pAddrStr->Next;
		}
		pAdapt = pAdapt->Next;
		cout << endl;
	}
	color();
}
void IpChanger::GET_DNS_PARS()
{
	FIXED_INFO *pFixedInfo;
	ULONG ulOutBufLen;
	DWORD dwRetVal;
	IP_ADDR_STRING *pIPAddr;

	pFixedInfo = (FIXED_INFO *)MALLOC(sizeof(FIXED_INFO));
	if (pFixedInfo == NULL) {
		color("LIGHTRED");
		printf("Error allocating memory needed to call GetNetworkParams\n");
		color();
		exit(1);
	}
	ulOutBufLen = sizeof(FIXED_INFO);

	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into the ulOutBufLen variable
	if (GetNetworkParams(pFixedInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
		FREE(pFixedInfo);
		pFixedInfo = (FIXED_INFO *)MALLOC(ulOutBufLen);
		if (pFixedInfo == NULL) {
			color("LIGHTRED");
			printf("Error allocating memory needed to call GetNetworkParams\n");
			color();
			exit(1);
		}
	}
	if (dwRetVal = GetNetworkParams(pFixedInfo, &ulOutBufLen) == NO_ERROR) {

		printf("\nHost Name: ");
		color("LIGHTGREEN");
		printf("\t\t%s\n", pFixedInfo->HostName);
		color();
		printf("Domain Name: \t\t%s\n", pFixedInfo->DomainName);

		printf("DNS Servers:\n");
		color("YELLOW");
		printf("\t%s\n", pFixedInfo->DnsServerList.IpAddress.String);

		pIPAddr = pFixedInfo->DnsServerList.Next;
		while (pIPAddr) {
			printf("\t%s\n", pIPAddr->IpAddress.String);
			pIPAddr = pIPAddr->Next;
		}
		color();
		printf("Node Type: ");
		switch (pFixedInfo->NodeType) {
		case BROADCAST_NODETYPE:
			printf("\t\tBroadcast node\n");
			break;
		case PEER_TO_PEER_NODETYPE:
			printf("\t\tPeer to Peer node\n");
			break;
		case MIXED_NODETYPE:
			printf("\t\tMixed node\n");
			break;
		case HYBRID_NODETYPE:
			printf("\t\tHybrid node\n");
			break;
		default:
			printf("\t\tUnknown node type %0lx\n", pFixedInfo->NodeType);
			break;
		}

		printf("DHCP scope name: \t\t%s\n", pFixedInfo->ScopeId);
		
		if (pFixedInfo->EnableRouting)
		{
			cout << "Routing: ";
			color("LIGHTGREEN");
			printf("\t\ttenabled\n");
			color();
		}
		else
		{
			cout << "Routing: ";
			color("LIGHTRED");
			printf("\t\tdisabled\n");
			color();
		}
		if (pFixedInfo->EnableProxy)
		{
			cout << "ARP proxy: ";
			color("LIGHTGREEN");
			printf("\t\tenabled\n");
			color();
		}
		else
		{
			cout << "ARP proxy: ";
			color("LIGHTRED");
			printf("\t\tdisabled\n");
			color();
		}
		if (pFixedInfo->EnableDns)
		{
			cout << "DNS: ";
			color("LIGHTGREEN");
			printf("\t\t\tenabled\n");
			color();
		}
		else
		{
			cout << "DNS: ";
			color("LIGHTRED");
			printf("\t\t\tdisabled\n");
			color();
		}
	}
	else 
	{
		color("LIGHTRED");
		printf("GetNetworkParams failed with error: %d\n", dwRetVal);
		color();
		exit(1);
	}
	if (pFixedInfo)
		FREE(pFixedInfo);
}
