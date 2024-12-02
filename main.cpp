#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif

#include <stdio.h>
#include <raylib.h>
#include <vector>
#include <string>


class GameObject {
public:
	Vector2 position = { 0 };
	Color color = RED;
};

class Ingredient {
public:
	int id = 0;
	std::string name;
	Ingredient(std::string n) {
		name = n;
	}
};

class Stack {
public:
	int id = 0;
	int quantity = 0;
};

class Recipe {
public:
	std::vector<Stack> input;
	int time = 0;
	std::vector<Stack> output;
};

// How do I setup the smallest possible test environment for these classes?

// I need a map
class Map {
public:
	int w = 100;
	int h = 100;
	int t_size = 16;
	int border = 5;
	Color border_color = BLACK;
	std::vector<int> tiles;

	// an initializer
	void initMap() {
		for (int y = 0; y < w; y++) {
			for (int x = 0; x < h; x++) {
				tiles.push_back(1);
			}
		}
	}
	// and a map renderer
	void render(Vector2 offset) {
		// loop the map and render tiles
		int p = 0;
		int l = 0;
		int offset_y = offset.y;
		int offset_x = offset.x;
		for (int t : tiles) {
			if (t == 1) {
				if (p == w) {
					p = 0;
					l++;
				}
				DrawRectangle(p * t_size + offset_y, l * t_size + offset_x, t_size, t_size, GREEN);
				DrawRectangleLines(p * t_size + offset_y, l * t_size + offset_x, t_size, t_size, border_color);
				p++;
			}
		}
	}
};


class Building {
public:
	Vector2 position;
};

class GameState {
public:
	std::vector<GameObject> items;
	Map map;
	bool isStarted = false;
};

int main() {
	InitWindow(800, 600, "Cpp test");
	SetTargetFPS(60);
	GameState state;
	GameObject circle;
	state.items.push_back(circle);
	GameObject e;
	e.position = Vector2{ 100,200 };
	state.items.push_back(e);
	state.map.initMap();

	Camera2D camera = {  };
	camera.target = Vector2{ 100,100 };
	camera.offset = Vector2{ 800 / 2.0f, 600 / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;


	while (!WindowShouldClose()) {

		camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
		if (camera.zoom > 5.0f) camera.zoom = 5.0f;
		else if (camera.zoom < 0.01f) camera.zoom = 0.01f;
		if (IsKeyPressed(KEY_R))
		{
			camera.zoom = 1.0f;
			camera.rotation = 0.0f;
		}
		if (IsKeyDown(KEY_RIGHT)) {
			camera.target.x += 10;
		}
		if (IsKeyDown(KEY_LEFT)) {
			camera.target.x -= 10;
		}
		if (IsKeyDown(KEY_UP)) {
			camera.target.y -= 10;
		}
		if (IsKeyDown(KEY_DOWN)) {
			camera.target.y += 10;
		}
		BeginDrawing();
		ClearBackground(SKYBLUE);
		BeginMode2D(camera);
		state.map.render(Vector2{ 10	,10 });
		for (const GameObject& o : state.items) {
			DrawCircleV(o.position, 20, o.color);
		}
		EndMode2D();
		DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}