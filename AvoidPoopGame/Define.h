#pragma once

#define DS TimeManager::getInstance()->getDS()
#define ISPRESS(key) InputManager::getInstance()->isPress(key)
#define ISTIC(key) InputManager::getInstance()->isTic(key)
#define FIND_TEXTURE(tag) (Texture*)ResourceManager::getInstance()->findResource(tag)
#define WINDOW Core::getInstance()->getWindowSize()
#define COLLISION_REC(pos1, size1, pos2, size2) CollisionManager::getInstance()->ractangleVsRactangle(pos1, size1, pos2, size2)
#define COLOR_WHITE RGB(255, 255, 255)
#define COLOR_RED RGB(200, 0, 0)
#define COLOR_GREEN RGB(0, 249, 0)
#define COLOR_MAGENTA RGB(255, 0, 255)
#define COLOR_BLUE RGB(0, 0, 245)