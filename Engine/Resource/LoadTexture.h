#pragma once

#include <Resource/Texture.h>

#include <FC/String.h>

std::pair<Texture*, u8*> LoadBMP(const String& path);
