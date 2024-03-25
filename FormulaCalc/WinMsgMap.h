// WinMsgMap.h

#pragma once
#include <unordered_map>
#include "Window.h"

class WinMsgMap
{
public:
	WinMsgMap() noexcept;
	std::string operator()( DWORD msg,LPARAM lp,WPARAM wp ) const noexcept;
private:
	std::unordered_map<DWORD,std::string> map;
};