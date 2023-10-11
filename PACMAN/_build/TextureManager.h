#pragma once

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

enum class TextureType {
	Logo = 0,
	Title,
	Pacman,
	PacmanDead,
	PacmanLifes,
	Ghost,
	Tileset,
};

typedef struct Tile {
	int value;                  // Tile index value (in tileset)
	bool collider;              // Tile collider (0 -> walkable)
	Color color;                // Tile color (could be useful)
} Tile;

// LESSON 05: Tilemap struct
typedef struct Tilemap {
	Tile* tiles;                // Tiles data
	int tileCountX;             // Tiles counter X
	int tileCountY;             // Tiles counter Y
	int tileSize;               // Tile size (XY)
	Vector2 position;           // Tilemap position in screen
} Tilemap;

class TextureManager
{
public:
	TextureManager();
	void InitTextures();
	void UnloadTextures();
	Texture2D& GetTexture(TextureType texture);
	void DrawTileMap();
	Tilemap LoadTileMap(const char* valuesMap, const char* collidersMap, const char* objectsMap);
	Tilemap GetTileMap() { return tilemap; };
	void ReloadTilemap();
private:
	Texture2D logoTexture;
	Texture2D titleTexture;
	Tilemap tilemap;
	Texture2D tileset;
	void UnloadTileMap(Tilemap tilemap);
	Texture2D pacmanLifesTexture;
	Texture2D pacmanTexture;
	Texture2D pacmanDeadTexture;
	Texture2D ghostTexture;
};

