#pragma once
#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include "tim2utils.h"

void ErrMSG(std::wstring txt);
DWORD convertpng2tm2(std::wstring pngpath, std::wstring dirpath);
DWORD converttm2png(std::wstring tm2path, std::wstring dirpath);
DWORD convertimage(std::wstring imagepath, std::wstring dirpath);