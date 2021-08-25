/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Sprite.h"
#include "Game.h"
#include "VecInt2D.h"
#include <chrono>
#include <thread>



Game::Game(MainWindow& wnd)
	: 
	wnd(wnd), 
	gfx(wnd), 
	whiteBall(Sprites::wBall, { Graphics::ScreenWidth / 2 - 3, Graphics::ScreenHeight / 2 - 3 }, { 5, 5 }, { 5, 5 }, true),
	player1(Sprites::wBar, { 20, Graphics::ScreenHeight / 2 - 79 }, { 0, 0 }, { 5, 5 }, false),
	player2(Sprites::wBar, { Graphics::ScreenWidth - 1 - 16 - 20, Graphics::ScreenHeight / 2 - 79 }, { 0, 0 }, { 5, 5 }, false)
{
	whiteBall.Spawn();
}


void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

bool Game::GameExit() const
{
	return gameExit;
}

void Game::UpdateModel()
{

	player1.Control(wnd.kbd, 'W', 'S', 'A', 'D');
	player2.Control(wnd.kbd, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT);
	
	if (whiteBall.X2() < player1.X1() || whiteBall.X1() >= player2.X2())
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		whiteBall.Spawn(true);
	}
	if (whiteBall.isColliding(player1) || whiteBall.isColliding(player2))
	{
		if (!whiteBall.hasCollidedX)
		{
			whiteBall.InvertVX();
			whiteBall.hasCollidedX = true;
		}
	}
	else
		whiteBall.hasCollidedX = false;
	whiteBall.Update();
	player1.Update();
	player2.Update();
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		gameExit = true;
} 

void Game::ComposeFrame()
{
	whiteBall.Draw(gfx);
	player1.Draw(gfx);
	player2.Draw(gfx);
}






