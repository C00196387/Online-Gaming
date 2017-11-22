#include <iostream>
#include <string>

#include "TcpListener.h"
#include "Qotd.h"

using namespace std;

void Listener_MessageReceived(CTcpListener* listener, int client, string msg, std::string sock);
string PacketMaker();

// This is kinda bad because it's global.
CQotd quotes("wisdom.txt");

int p1x = 0;
int p1y = 0;

int p2x = 400;
int p2y = 400;

int systemID = 0;
int p1 = 0;
int p2 = 0;

bool win = false;

int timeUpdated = 0;

void main()
{
	CTcpListener server("127.0.0.1", 5050, Listener_MessageReceived);
	
	if (server.Init())
	{
		server.Run();
	}
}

void Listener_MessageReceived(CTcpListener* listener, int client, string msg, std::string sock)
{
	if (msg.find("(GIVEID)") != std::string::npos)
	{
		if (systemID == 0)
		{
			systemID = client;
		}
		else if (p1 == 0 && p1 != systemID)
		{
			p1 = client;
		}
		else if (p2 == 0 && p2 != systemID)
		{
			p2 = client;
		}
		listener->Send(client, PacketMaker());
	}
	else
	{
		if (client == p1 && !win)
		{
			if (msg.find("(right)") != std::string::npos)
			{
				p1x += 10;
			}
			if (msg.find("(left)") != std::string::npos)
			{
				p1x -= 10;
			}
			if (msg.find("(up)") != std::string::npos)
			{
				p1y -= 10;
			}
			if (msg.find("(down)") != std::string::npos)
			{
				p1y += 10;
			}
		}
		if (client == p2 && !win)
		{
			if (msg.find("(right)") != std::string::npos)
			{
				p2x += 10;
			}
			if (msg.find("(left)") != std::string::npos)
			{
				p2x -= 10;
			}
			if (msg.find("(up)") != std::string::npos)
			{
				p2y -= 10;
			}
			if (msg.find("(down)") != std::string::npos)
			{
				p2y += 10;
			}
		}
		if (msg.find("(WIN)") != std::string::npos)
		{
			win = true;
		}
		listener->Send(client, PacketMaker());
	}
}


string PacketMaker()
{
	string holder;
	holder = "";
	holder += to_string(p1x);
	holder += " ";
	holder += to_string(p1y);
	holder += " ";
	holder += to_string(p2x);
	holder += " ";
	holder += to_string(p2y);

	return holder;
}