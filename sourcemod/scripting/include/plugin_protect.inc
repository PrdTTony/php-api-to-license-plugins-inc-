#if defined _Plugin_Protect_included
 #endinput
#endif
#define _Plugin_Protect_included

#define REQUIRE_EXTENSIONS
#define REQUIRE_PLUGIN
#include <SteamWorks>
#include <sourcemod>
#include <json>

#pragma tabsize 0;
#pragma semicolon 1;


stock void PluginProtect_SelfDestroy(const char[] sMessage)
{
	LogError(sMessage);

	char cFileName[64];
	GetPluginFilename(INVALID_HANDLE, cFileName, sizeof(cFileName));
	ServerCommand("sm plugins unload_all");
	ServerCommand("sm plugins unload_all");
}

public void OnPluginStart()
{
	PluginProtect_IsValidServer();
	_REAL_OnPluginStart();
}


stock void PluginProtect_IsValidServer() {

	if (!SteamWorks_IsLoaded() || !SteamWorks_IsConnected())
	{
		PluginProtect_SelfDestroy("SteamWorks is required to run to use this plugin.");
		return;
	}

	static char cIP[32];

	if (cIP[0] == '\0')
	{
		int iIP[4];
		if (!SteamWorks_GetPublicIP(iIP))
		{
			PluginProtect_SelfDestroy("Failed to get the public IP address through SteamWorks.");
			return;
		}

		FormatEx(cIP, sizeof(cIP), "%d.%d.%d.%d:%d", iIP[0], iIP[1], iIP[2], iIP[3], GetConVarInt(FindConVar("hostport")));
	}

    char[] sURL = " ";          // PUT YOUR API URL HERE !!!! FORMAT MUST BE RESPECTED https://yourwebsiteurl/api.php/records/Db_Table_Name

    Handle HTTPRequest = SteamWorks_CreateHTTPRequest(k_EHTTPMethodGET, sURL);

    bool setnetwork = SteamWorks_SetHTTPRequestNetworkActivityTimeout(HTTPRequest, 10);
    char IpPort[64];
    Format(IpPort, 64, "IpPort,eq,%s", cIP);
    bool setparam = SteamWorks_SetHTTPRequestGetOrPostParameter(HTTPRequest, "filter", IpPort);
    bool setcontext = SteamWorks_SetHTTPRequestContextValue(HTTPRequest, 5);
    bool setcallback = SteamWorks_SetHTTPCallbacks(HTTPRequest, getCallback);

    if(!setnetwork || !setcallback) {
        PrintToServer("[Plugin_Protect] Error in setting request properties, cannot send request \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
        CloseHandle(HTTPRequest);
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        return;
    }

    bool sentrequest = SteamWorks_SendHTTPRequest(HTTPRequest);
    if(!sentrequest) {
        PrintToServer("[Plugin_Protect] Error in sending request, cannot send request \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
        CloseHandle(HTTPRequest);
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        return;
    }

    SteamWorks_PrioritizeHTTPRequest(HTTPRequest);
    return;
}

public getCallback(Handle:hRequest, bool:bFailure, bool:bRequestSuccessful, EHTTPStatusCode:eStatusCode, any:data1) {

	if (!SteamWorks_IsLoaded() || !SteamWorks_IsConnected())
	{
		PluginProtect_SelfDestroy("[Plugin_Protect] SteamWorks is required to run to use this plugin. \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
		return;
	}

	static char cIP[32];

	if (cIP[0] == '\0')
	{
		int iIP[4];
		if (!SteamWorks_GetPublicIP(iIP))
		{
			PluginProtect_SelfDestroy("[Plugin_Protect] Failed to get the public IP address through SteamWorks.");
			ServerCommand("sm plugins unload_all");
			ServerCommand("sm plugins unload_all");
			return;
		}

		FormatEx(cIP, sizeof(cIP), "%d.%d.%d.%d:%d", iIP[0], iIP[1], iIP[2], iIP[3], GetConVarInt(FindConVar("hostport")));
	}


    if(!bRequestSuccessful) {
        PrintToServer("[Plugin_Protect] There was an error in the request \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        CloseHandle(hRequest);
        return;
    }

    if(eStatusCode == k_EHTTPStatusCode200OK) {
        PrintToServer("[Plugin_Protect] The request has been succesfully made, http code 200");

    } else if(eStatusCode == k_EHTTPStatusCode304NotModified) {
        PrintToServer("[Plugin_Protect] The request did not return new data, but did not error, http code 304 \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
        CloseHandle(hRequest);
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        return;
    } else if(eStatusCode == k_EHTTPStatusCode404NotFound) {
        PrintToServer("[Plugin_Protect] The requested URL could not be found, http code 404 \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
        CloseHandle(hRequest);
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        return;
    } else if(eStatusCode == k_EHTTPStatusCode500InternalServerError) {
        PrintToServer("[Plugin_Protect] The requested URL had an internal error, http code 500 \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
        CloseHandle(hRequest);
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        return;
    } else {
        char errmessage[128];
        Format(errmessage, 128, "[Plugin_Protect] The requested returned with an unexpected HTTP Code %d \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD", eStatusCode);
        PrintToServer(errmessage);
        CloseHandle(hRequest);
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        return;
    }

    int bodysize;
    bool bodyexists = SteamWorks_GetHTTPResponseBodySize(hRequest, bodysize);
    if(bodyexists == false) {
        PrintToServer("[Plugin_Protect] Could not get body response size \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
        CloseHandle(hRequest);
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        return;
    }

    char bodybuffer[10000];
    if(bodysize > 10000) {
        PrintToServer("[Plugin_Protect] The requested URL returned with more data than expected \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
        CloseHandle(hRequest);
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        return;
    }

    bool gotdata = SteamWorks_GetHTTPResponseBodyData(hRequest, bodybuffer, bodysize);
    if(gotdata == false) {
        PrintToServer("[Plugin_Protect] Could not get body data or body data is blank \n[Plugin_Protect] ACCESS DENIED. PLEASE CONTACT ON DISCORD");
        CloseHandle(hRequest);
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
        return;
    }

	JSON_Object obj = json_decode(bodybuffer);
    JSON_Array arr = view_as<JSON_Array>(obj.GetObject("records"));
    JSON_Object read = arr.GetObject(0);

	if(!read){

        PrintToServer("[Plugin_Protect] Someone tried to sell you a private plugin. This server does not have a license and cannot run this plugin");
		PrintToServer("[Plugin_Protect] Someone tried to sell you a private plugin. This server does not have a license and cannot run this plugin");
		CloseHandle(hRequest);	
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");
		return;
    }

    char IpPort[32]; 
    read.GetString("IpPort", IpPort, sizeof(IpPort));
    char name[64];
    read.GetString("server_name", name, sizeof(name));
    char discord_owner[64];
    read.GetString("discord_owner", discord_owner, sizeof(discord_owner));
    char expires_date[64];
    read.GetString("Expires", expires_date, sizeof(expires_date));
    char sTime[32];
    FormatTime(sTime, sizeof(sTime), "%Y-%m-%d", GetTime()); 
    
	if(StrEqual(IpPort, cIP)){

        if(StrEqual(expires_date, "forever")){

            PrintToServer("[Plugin_Protect] Access Allowed. \n[Plugin_Protect] License Ip_Port: %s \n[Plugin_Protect] Name: %s \n[Plugin_Protect] Discord Owner: %s \n[Plugin_Protect] Expires at: Never \n[Plugin_Protect] Enjoy using the this plugin", IpPort, name, discord_owner);			    

        } else if(CompareDates(sTime, expires_date)){

            PrintToServer("[Plugin_Protect] Access Allowed. \n[Plugin_Protect] License Ip_Port: %s \n[Plugin_Protect] Name: %s \n[Plugin_Protect] Discord Owner: %s \n[Plugin_Protect] Expires at: %s \n[Plugin_Protect] Enjoy using the this plugin", IpPort, name, discord_owner, expires_date);
		    
        } else {

            PrintToServer("[Plugin_Protect] Access Denied. \n[Plugin_Protect] License Ip_Port: %s \n[Plugin_Protect] Name: %s \n[Plugin_Protect] Discord Owner: %s \n[Plugin_Protect] Expires at: %s \n[Plugin_Protect] Your LICENSE has EXPIRED. Contact on discord if you want to renew it", IpPort, name, discord_owner, expires_date);
			ServerCommand("sm plugins unload_all");
			ServerCommand("sm plugins unload_all");
        }

	} else {

		PrintToServer("[Plugin_Protect] Someone tried to sell you a private plugin. This server does not have a license and cannot run this plugin");			
		ServerCommand("sm plugins unload_all");
		ServerCommand("sm plugins unload_all");	
	}

    json_cleanup_and_delete(obj);

    CloseHandle(hRequest);
} 

bool CompareDates(char[] Date1, char[] Date2)
{   
    char sData1[3][32], sData2[4][32];
    ExplodeString(Date1, "-", sData1, sizeof(sData1), sizeof(sData1[]));
    ExplodeString(Date2, "-", sData2, sizeof(sData2), sizeof(sData2[]));

    int year1 = StringToInt(sData1[0]);
    int year2 = StringToInt(sData2[0]);

    int month1 = StringToInt(sData1[1]);
    int month2 = StringToInt(sData2[1]);

    int day1 = StringToInt(sData1[2]);
    int day2 = StringToInt(sData2[2]);

    if(year1 > year2){
        return false;
    } else if(month1 > month2){
        return false;
    } else if(year1 == year2 && month1 == month2 && day1 > day2){
        return false;
    } else {
        return true;
    }
}

#define OnPluginStart _REAL_OnPluginStart
