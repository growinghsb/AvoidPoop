#pragma once

#pragma comment(lib, "Msimg32.lib")

#include "framework.h"
#include "AvoidPoopGame.h"
#include "Define.h"
#include "Sturct.h"

#include <crtdbg.h>
#include <math.h>

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>

using std::vector;
using std::list;
using std::map;
using std::unordered_map;
using std::string;
using std::wstring;
using std::to_string;
using std::to_wstring;
using std::abs;
using std::make_pair;

void ChangeStage(eEVENT_TYPE type, STAGE_MODE mode);