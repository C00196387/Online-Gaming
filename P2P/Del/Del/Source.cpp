/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <sstream>
#include <time.h>

#include <vector>

#include "TcpListener.h"
#include "PlayerObject.h"

#pragma comment(lib, "ws2_32.lib")

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};
//The dot that will move around on the screen
class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;

	//Initializes the variables
	Dot();

	//Takes key presses and adjusts the dot's velocity
	std::string handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void render();

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;
};

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

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


Dot::Dot()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

std::string Dot::handleEvent(SDL_Event& e)
{

	return "NO";
}

void Dot::move()
{
	//Move the dot left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
	{
		//Move back
		mPosY -= mVelY;
	}
}

void Dot::render()
{
	//Show the dot
	gDotTexture.render(mPosX, mPosY);
}

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
	if (!gDotTexture.loadFromFile("dot.bmp"))
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


void Listener_MessageReceived(CTcpListener* listener, int client, std::string msg, std::string sock);
std::string PacketMaker(std::string id);
int host(std::string ipAddress, int port);
int client(std::string ipAddress, int port);

std::vector<PlayerObject*> player;

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

int main(int argc, char* args[])
{
	std::string ipAddress = "149.153.106.155";
	int port = 1234;

	std::cout << "Host? Y/N" << std::endl;
	std::string result;
	std::cin >> result;
	std::cout << std::endl;

	if (result == "Y" || result == "y")
	{
		host(ipAddress, port);
	}
	else
	{
		client(ipAddress, port);
	}
	close();

	return 0;
}


int host(std::string ipAddress, int port)
{
	srand(time(NULL));
	player.push_back(new PlayerObject(250, 250, "0", rand() % 255, rand() % 255, rand() % 255));
	CTcpListener server(ipAddress, port, Listener_MessageReceived);
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

			bool up = false;
			bool down = false;
			bool left = false;
			bool right = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;
			Dot dot2;

			bool win = false;

			//While application is running
			while (1 != 0)
			{
				server.Run();
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if (e.type == SDL_KEYDOWN)
					{
						//Adjust the velocity
						switch (e.key.keysym.sym)
						{
						case SDLK_UP: up = true; break;
						case SDLK_DOWN: down = true; break;
						case SDLK_LEFT: left = true; break;
						case SDLK_RIGHT: right = true; break;
						default: break;
						}
					}
					if (e.type == SDL_KEYUP)
					{
						//Adjust the velocity
						switch (e.key.keysym.sym)
						{
						case SDLK_UP: up = false; break;
						case SDLK_DOWN: down = false; break;
						case SDLK_LEFT: left = false; break;
						case SDLK_RIGHT: right = false; break;
						default: break;
						}
					}
				}

				if (up)
				{
					player.at(0)->y -= 10;
				}
				if (down)
				{
					player.at(0)->y += 10;
				}
				if (left)
				{
					player.at(0)->x -= 10;
				}
				if (right)
				{
					player.at(0)->x += 10;
				}

				//if (SDL_IntersectRect(new SDL_Rect{ dot.mPosX, dot.mPosY, 20, 20 }, new SDL_Rect{ dot2.mPosX, dot2.mPosY, 20, 20 }, new SDL_Rect{ 0,0,0,0 }))
				//{
				//	win = true;
				//}

				for (int i = 0; i < player.size(); i++)
				{
					if (player.at(i)->x < 0)
					{
						player.at(i)->x = 640;
					}
					if (player.at(i)->x > 640)
					{
						player.at(i)->x = 0;
					}
					if (player.at(i)->y < 0)
					{
						player.at(i)->y = 480;
					}
					if (player.at(i)->y > 480)
					{
						player.at(i)->y = 0;
					}

					for (int j = 0; j < player.size(); j++)
					{
						if (i != j)
						{
							SDL_Rect tempUs = SDL_Rect{ player.at(i)->x, player.at(i)->y, 20, 20 };
							SDL_Rect tempThem = SDL_Rect{ player.at(j)->x, player.at(j)->y, 20, 20 };
							SDL_Rect temp = SDL_Rect{0,0,0,0};
							if (SDL_IntersectRect(&tempUs, &tempThem, &temp))
							{
								if (player.at(i)->chaser)
								{
									if (player.at(j)->alive)
									{
										player.at(j)->alive = false;
									}
								}
								else if (player.at(j)->chaser)
								{
									if (player.at(i)->alive)
									{
										player.at(i)->alive = false;
									}
								}
							}

						}
					}

				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render objects
				for (int i = 0; i < player.size(); i++)
				{

					dot.mPosX = player.at(i)->x;
					dot.mPosY = player.at(i)->y;

					gDotTexture.setColor(player.at(i)->r, player.at(i)->g, player.at(i)->b);
					if (player.at(i)->alive)
					{
						dot.render();
					}
				}

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	return 0;
}

int client(std::string ipAddress, int port)
{
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

			bool up = false;
			bool down = false;
			bool left = false;
			bool right = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;
			Dot dot2;

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
					if (e.type == SDL_KEYDOWN)
					{
						//Adjust the velocity
						switch (e.key.keysym.sym)
						{
						case SDLK_UP: up = true; break;
						case SDLK_DOWN: down = true; break;
						case SDLK_LEFT: left = true; break;
						case SDLK_RIGHT: right = true; break;
						default: break;
						}
					}
					if (e.type == SDL_KEYUP)
					{
						//Adjust the velocity
						switch (e.key.keysym.sym)
						{
						case SDLK_UP: up = false; break;
						case SDLK_DOWN: down = false; break;
						case SDLK_LEFT: left = false; break;
						case SDLK_RIGHT: right = false; break;
						default: break;
						}
					}
				}

				if (up)
				{
					userInput += "(up)";
				}
				if (down)
				{
					userInput += "(down)";
				}
				if (left)
				{
					userInput += "(left)";
				}
				if (right)
				{
					userInput += "(right)";
				}

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				int sendResult = send(sock, userInput.c_str(), userInput.size(), 0);
				if (sendResult != SOCKET_ERROR)
				{
					ZeroMemory(buf, 4096);
					int bytesReceived = recv(sock, buf, 4096, 0);
					if (bytesReceived > 0)
					{
						int size, x, y;
						int r, g, b;

						std::stringstream ss(std::string(buf, 0, bytesReceived));
						ss >> size;
						for (int i = 0; i < size; i++)
						{
							ss >> x >> y >> r >> g >> b;
							dot.mPosX = x;
							dot.mPosY = y;
							gDotTexture.setColor(r, g, b);
							dot.render();
						}
					}
				}

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	closesocket(sock);

	return 0;
}

void Listener_MessageReceived(CTcpListener* listener, int client, std::string msg, std::string sock)
{
	std::string holder = "(NULL)";


	bool proceed = false;
	for (int i = 0; i < player.size(); i++)
	{
		proceed = true;
		if (player.at(i)->id == sock)
		{
			proceed = false;
			break;
		}
	}

	//COLORREF myColorRef = RGB(
	//	(BYTE)(rand() % 255), // red component of color
	//	(BYTE)(rand() % 255), // green component of color
	//	(BYTE)(rand() % 255) // blue component of color
	//);

	if (proceed)
	{
		player.push_back(new PlayerObject(0, 0, sock, rand() % 255, rand() % 255, rand() % 255));
	}

	if (client != systemID)
	{
		holder = sock;
	}
	for (int i = 0; i < player.size(); i++)
	{
		if (player.at(i)->id == sock && sock == std::to_string(client))
		{
			if (msg.find("(right)") != std::string::npos)
			{
				player.at(i)->x += 10;
			}
			if (msg.find("(left)") != std::string::npos)
			{
				player.at(i)->x -= 10;
			}
			if (msg.find("(up)") != std::string::npos)
			{
				player.at(i)->y -= 10;
			}
			if (msg.find("(down)") != std::string::npos)
			{
				player.at(i)->y += 10;
			}
		}
	}

	listener->Send(client, PacketMaker(holder));
}


std::string PacketMaker(std::string id)
{
	std::string holder;

	holder = std::to_string(player.size()) + " ";

	for (int i = 0; i < player.size(); i++)
	{
		holder += std::to_string(player.at(i)->x) + " ";
		holder += std::to_string(player.at(i)->y) + " ";
		holder += std::to_string(player.at(i)->r) + " ";
		holder += std::to_string(player.at(i)->g) + " ";
		holder += std::to_string(player.at(i)->b) + " ";
	}

	return holder;
}