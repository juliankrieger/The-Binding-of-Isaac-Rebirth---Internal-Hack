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

void InternalHack::freezeHealth(bool enable) {

    if(enable) {
        mem::Nop((BYTE*)(this->moduleBase + Offset::HEALTH_START), 6);
    } else {
        // original code: mov [esi+000024C0],eax
        mem::Patch((BYTE*)(this->moduleBase + Offset::HEALTH_START), (BYTE*)"\x89\x86\xC0\x24\x00\x00", 6);
    }
}

void InternalHack::freezeBombs(bool enable) {
    if(enable) {
        mem::Nop((BYTE*)(this->moduleBase + Offset::BOMB_DEC_START), 2);
    } else {
        // original code: dec [eax]
        mem::Patch((BYTE*)(this->moduleBase + Offset::BOMB_DEC_START),(BYTE*)"\xFF\x08", 2);
    }
}

void InternalHack::increaseBombs(bool enable) {
    if(enable) {
        // code: inc [eax]
        mem::Patch((BYTE*)(this->moduleBase + Offset::BOMB_DEC_START),(BYTE*)"\xFF\x00", 2);
    } else {
        // original code: dec [eax]
        mem::Patch((BYTE*)(this->moduleBase + Offset::BOMB_DEC_START),(BYTE*)"\xFF\x08", 2);
    }
}

