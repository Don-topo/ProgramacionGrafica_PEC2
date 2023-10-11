#include "TextureManager.h"
#include <fstream>

TextureManager::TextureManager()
{
}

void TextureManager::InitTextures()
{
	logoTexture = LoadTexture("resources/Menu/Logo.png");
	titleTexture = LoadTexture("resources/Menu/PacMan_MainLogo.png");
    tileset = LoadTexture("resources/TileMap/PacManTileset.png");
    tilemap = LoadTileMap("resources/TileMap/tilemap.txt", "resources/TileMap/collidermap.txt", "resources/TileMap/objectsmap.txt");
    pacmanLifesTexture = LoadTexture("resources/Game/IconLifes.png");
    pacmanTexture = LoadTexture("resources/Game/PacMan.png");
    pacmanDeadTexture = LoadTexture("resources/Game/PacManDead.png");
    ghostTexture = LoadTexture("resources/Game/Enemies.png");
}

void TextureManager::UnloadTextures()
{
    UnloadTexture(logoTexture);
    UnloadTexture(titleTexture);
    UnloadTexture(tileset);
    UnloadTileMap(tilemap);
    UnloadTexture(pacmanLifesTexture);
    UnloadTexture(pacmanTexture);
    UnloadTexture(pacmanDeadTexture);
    UnloadTexture(ghostTexture);
}

Texture2D& TextureManager::GetTexture(TextureType texture)
{
	switch (texture)
	{
	case TextureType::Logo:
		return logoTexture;
		break;
	case TextureType::Title:
		return titleTexture;
		break;
	case TextureType::Pacman:
        return pacmanTexture;
		break;
	case TextureType::PacmanDead:
        return pacmanDeadTexture;
		break;
	case TextureType::Ghost:
        return ghostTexture;
		break;
    case TextureType::PacmanLifes:
        return pacmanLifesTexture;
        break;
	default:
		break;
	}
}

void TextureManager::DrawTileMap()
{
	for (int y = 0; y < tilemap.tileCountY; y++)
	{
		for (int x = 0; x < tilemap.tileCountX; x++)
		{            
            Rectangle rectangle = {tilemap.tileSize * ((int)(tilemap.tiles[x + (y*tilemap.tileCountX)].value) % 10) , tilemap.tileSize * (int)(tilemap.tiles[x+(y*tilemap.tileCountX)].value / 10), tilemap.tileSize, tilemap.tileSize };
            DrawTextureRec(tileset, 
                rectangle, 
                Vector2 { 50.f + (x * tilemap.tileSize), 50.f + (y * tilemap.tileSize) },
                WHITE);
		}
	}
}

Tilemap TextureManager::LoadTileMap(const char* valuesMap, const char* collidersMap, const char* objectsMap)
{
    Tilemap map = { 0 };
    const char* fileExt;
    map.tileSize = 32;

    if ((fileExt = strrchr(valuesMap, '.')) != NULL)
    {
        // Check if file extension is supported
        if (strcmp(fileExt, ".txt") == 0)
        {
            int counter = 0;
            int temp = 0;

            // Read values from text file
            FILE* valuesFile = fopen(valuesMap, "rt");

            while (!feof(valuesFile))
            {
                fscanf(valuesFile, "%i", &temp);
                counter++;
            }

            rewind(valuesFile);        // Return to the beginning of the file, to read again

            map.tiles = (Tile*)malloc(counter * sizeof(Tile));

            map.tileCountX = 27;
            map.tileCountY = 23;
            counter = 0;

            while (!feof(valuesFile))
            {
                fscanf(valuesFile, "%i", &map.tiles[counter].value);
                counter++;
            }

            fclose(valuesFile);

            // Read values from text file
            // NOTE: Colliders map data MUST match values data, 
            // or we need to do a previous check like done with values data
            FILE* collidersFile = fopen(collidersMap, "rt");
            counter = 0;
            temp = 0;

            while (!feof(collidersFile))
            {
                fscanf(collidersFile, "%i", &temp);
                map.tiles[counter].collider = temp;

                counter++;
            }

            fclose(collidersFile);

            FILE* objectsFile = fopen(objectsMap, "rt");
            counter = 0;
            temp = 0;

            while (!feof(objectsFile)) {
                fscanf(collidersFile, "%i", &temp);
                if (temp != -1) map.tiles[counter].value = temp;

                counter++;
            }

            fclose(objectsFile);
        }
    }

    return map;
}

void TextureManager::UnloadTileMap(Tilemap tilemap)
{
	if (tilemap.tiles != NULL) free(tilemap.tiles);
}

void TextureManager::ReloadTilemap() {
    tilemap = LoadTileMap("resources/TileMap/tilemap.txt", "resources/TileMap/collidermap.txt", "resources/TileMap/objectsmap.txt");    
}
