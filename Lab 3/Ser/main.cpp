#include <iostream>
#include <string>

#include "TcpListener.h"
#include "Qotd.h"
#include <vector>

using namespace std;

void Listener_MessageReceived(CTcpListener* listener, int client, string msg, std::string sock);
string PacketMaker(std::string id);

// This is kinda bad because it's global.
CQotd quotes("wisdom.txt");

int p1x = 0;
int p1y = 0;

int p2x = 400;
int p2y = 400;

int systemID = 0;
int p1 = 0;
int p2 = 0;

bool p1Arrived = false;
bool p2Arrived = false;

bool win = false;

int timeUpdated = 0;

std::vector<int> smolder;

void main()
{
	CTcpListener server("149.153.106.156", 1234, Listener_MessageReceived);
	
	if (server.Init())
	{
		server.Run();
	}
}

void Listener_MessageReceived(CTcpListener* listener, int client, string msg, std::string sock)
{
	std::string holder = "(NULL)";
	if (msg.find("(GIVEID)") != std::string::npos)
	{
		if (systemID == 0)
		{
			systemID = client;
		}
		else if (p1 == 0 && client != systemID)
		{
			p1 = client;
		}
		else if (p2 == 0 && client != systemID && client != p1)
		{
			p2 = client;
		}
		smolder.push_back(client);
	}
	else
	{

		if (client != systemID)
		{
			holder = std::to_string(client);
		}

		if (msg.find(std::to_string(p1)) != std::string::npos && !win)
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
		else if (msg.find(std::to_string(p2)) != std::string::npos && !win)
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
	}
	listener->Send(client, PacketMaker(holder));
}


string PacketMaker(std::string id)
{
	string holder;
	holder = id;
	holder += " ";
	holder += to_string(p1x);
	holder += " ";
	holder += to_string(p1y);
	holder += " ";
	holder += to_string(p2x);
	holder += " ";
	holder += to_string(p2y);

	return holder;
}