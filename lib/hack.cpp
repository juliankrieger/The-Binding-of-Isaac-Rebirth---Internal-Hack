//
// Created by julian.krieger on 9/6/2021.
//

#include <sstream>
#include <iomanip>
#include "hack.h"

template< typename T >
std::string int_to_hex( T i )
{
    std::stringstream stream;
    stream << "0x"
           << std::setfill ('0') << std::setw(sizeof(T)*2)
           << std::hex << i;
    return stream.str();
}

InternalHack::InternalHack() {
    this->moduleBase = (uintptr_t)GetModuleHandle(nullptr);
}

void InternalHack::freezeHealth() {
    mem::Nop((BYTE*)(this->moduleBase + Offset::HEALTH_START), 6);
}
