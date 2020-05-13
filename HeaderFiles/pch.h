#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

#define _AMD64_ 1

#include <sdkddkver.h>
#include <windows.h>

#include <wrl.h>
#include <shellapi.h>

#include "../HeaderFiles/d3dx12.h"
#include <d3d12.h>

#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include <vector>
#include <string>

#include <d3dcompiler.h> //Allows to compile MHLSL (Microsoft High Level Shader Language) into bytecode.
#include <dxgi1_6.h>  //Latest DXGI header.

#include <D3Dcompiler.h>
