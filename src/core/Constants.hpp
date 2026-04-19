#pragma once

constexpr unsigned int WINDOW_WIDTH = 1920;
constexpr unsigned int WINDOW_HEIGHT = 1080;
constexpr unsigned int FRAMERATE_LIMIT = 300;

constexpr float MAP_WIDTH = 1920.f;
constexpr float MAP_HEIGHT = 1088.f;

constexpr float VIEWPORT_ZOOM_X = 0.50f;
constexpr float VIEWPORT_ZOOM_Y = 0.65f;

constexpr float VIEW_WIDTH = MAP_WIDTH * VIEWPORT_ZOOM_X;
constexpr float VIEW_HEIGHT = MAP_HEIGHT * VIEWPORT_ZOOM_Y;

constexpr float PLAYER_SCALE = 3.f; 
constexpr float PLAYER_SPEED = 250.f;
constexpr int PLAYER_MAX_HP = 100;
constexpr float PLAYER_START_X = MAP_WIDTH / 2.f;
constexpr float PLAYER_START_Y = MAP_HEIGHT / 2.f;

namespace Paths
{
    constexpr const char* TEXTURE_MAP = "assets/textures/mapa.png";
    constexpr const char* TEXTURE_PLAYER = "assets/textures/AnimationSheet.png";
}
