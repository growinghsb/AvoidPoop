#pragma once

#define DS TimeManager::getInstance()->getDS()
#define ISPRESS(key) InputManager::getInstance()->isPress(key)
#define ISTIC(key) InputManager::getInstance()->isTic(key)
#define WINDOW Core::getInstance()->getWindowSize()
#define COLOR_WHITE RGB(255, 255, 255)