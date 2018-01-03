/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include "Player.h"
#include "UserInput.h"

#pragma comment(lib, "ws2_32.lib")

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gDotTexture;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!gDotTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//std::string ipAddress = "51.37.108.114";
	std::string ipAddress = "127.0.0.1";
	int port = 1234;

	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "CAN'T START WINSOCK" << std::endl;
		WSACleanup();
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket" << std::endl;
		WSACleanup();
		return 0;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));

	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't create socket" << std::endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	char buf[4096];
	std::string userInput;

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			//Player player1(SCREEN_WIDTH, SCREEN_HEIGHT, "red");
			//Player player2(SCREEN_WIDTH, SCREEN_HEIGHT, "blue");

			std::vector<Player> redTeam;
			redTeam.push_back(Player{ SCREEN_WIDTH, SCREEN_HEIGHT, "red" });

			std::vector<Player> blueTeam;
			blueTeam.push_back(Player{ SCREEN_WIDTH, SCREEN_HEIGHT, "blue" });

			UserInput input;

			bool win = false;

			std::string id = "(NULL)";

			userInput = "(GIVEID)";

			int sendResult = send(sock, userInput.c_str(), userInput.size(), 0);
			if (sendResult != SOCKET_ERROR)
			{
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					std::stringstream ss(std::string(buf, 0, bytesReceived));
				}
			}

			//While application is running
			while (1 != 0)
			{

				userInput = id;
				if (win)
				{
					userInput += "(WIN)";
				}

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					input.handleInput(e);
				}

				if (input.up)
				{
					userInput += "(up)";
				}
				if (input.down)
				{
					userInput += "(down)";
				}
				if (input.left)
				{
					userInput += "(left)";
				}
				if (input.right)
				{
					userInput += "(right)";
				}

				int sendResult = send(sock, userInput.c_str(), userInput.size(), 0);
				if (sendResult != SOCKET_ERROR)
				{
					ZeroMemory(buf, 4096);
					int bytesReceived = recv(sock, buf, 4096, 0);
					if (bytesReceived > 0)
					{
						std::stringstream ss(std::string(buf, 0, bytesReceived));
						//ss >> id >> player1.mRect.x >> player1.mRect.y >> player2.mRect.x >> player2.mRect.y;
						ss >> id >> redTeam.at(0).mRect.x >> redTeam.at(0).mRect.y >> blueTeam.at(0).mRect.x >> blueTeam.at(0).mRect.y;
					}
				}

				//if (SDL_IntersectRect(new SDL_Rect{ player1.mPosX, player1.mPosY, player1.mWidth, player1.mHeight }, new SDL_Rect{ player2.mPosX, player2.mPosY, player2.mWidth, player2.mHeight}, new SDL_Rect{ 0,0,0,0 }))
				//{
				//	//win = true;
				//}

				for (int i = 0; i < redTeam.size(); i++)
				{
					for (int j = 0; j < blueTeam.size(); j++) 
					{
						blueTeam.at(j).checkIntersection(redTeam.at(i).mRect);
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render objects
				//if (!win)
				//{
				for (int i = 0; i < redTeam.size(); i++)
				{
					redTeam.at(i).render(gDotTexture, gRenderer);
				}
				for (int i = 0; i < blueTeam.size(); i++)
				{
					blueTeam.at(i).render(gDotTexture, gRenderer);
				}
				//}
				//else
				//{
				//	player1.render(gDotTexture, gRenderer);
				//	player2.render(gDotTexture, gRenderer);
				//}

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	closesocket(sock);
	//Free resources and close SDL
	close();

	return 0;
}