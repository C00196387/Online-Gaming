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
	//if (msg.find("$QUOTE") != std::string::npos)
	//{
	//	listener->Send(client, quotes.GetRandomQuote());
	//}
	//else if (msg.find("say:") != std::string::npos)
	//{
	//	std::string holder = "say:";
	//
	//	std::string::size_type i = msg.find(holder);
	//
	//	msg.erase(i, holder.length());
	//
	//	std::string holder_ = sock + " : " + msg;
	//
	//	listener->Send(client, holder_);
	//}
	//else
	//{
	//	listener->Send(client, "");
	//}
	if (msg.find("(p1)") != std::string::npos)
	{
		if (msg.find("(right)") != std::string::npos)
		{
			p1x += 1;
		}
		if (msg.find("(left)") != std::string::npos)
		{
			p1x -= 1;
		}
		if (msg.find("(up)") != std::string::npos)
		{
			p1y -= 1;
		}
		if (msg.find("(down)") != std::string::npos)
		{
			p1y += 1;
		}
	}
	listener->Send(client, PacketMaker());
	timeUpdated++;
	std::cout << timeUpdated << std::endl;
}

string PacketMaker()
{
	string holder;
	holder = "";
	holder += to_string(p1x);
	holder += " ";
	holder += to_string(p1y);
	//holder = " ";
	//holder += to_string(p2x);
	//holder = " ";
	//holder += to_string(p2y);

	return holder;
}