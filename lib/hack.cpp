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

void InternalHack::noKeysNeeded(bool enable) {
    if(enable) {
        mem::Nop((BYTE*)(this->moduleBase + Offset::KEY_TST_START), 15);
    } else {
        /**
         * Original code:
         * tst eax, eax
         * jng isaac-ng.exe+150CF4
         * dec eax,
         * mov [esi+24D8], eax
         */
         auto original = (BYTE*)(
                 "\x85\xC0"
                 "\x0F\x8E\x5C\x01\x00\x00"
                 "\x48"
                 "\x89\x96\xD8\x24\x00\x00"
                 );
         mem::Patch((BYTE*)(this->moduleBase + Offset::KEY_TST_START), original, 15);
    }
}

void InternalHack::unlimitedMoney(bool enable) {
    if(enable) {
        auto newFunc = (BYTE*)(
                "\xB8\x63\x00\x00\x00" // mov eax, 99
                "\x90\x90" // NOP NOP
                );
        mem::Patch((BYTE*)(this->moduleBase + Offset::SET_MONEY_ENTRY), newFunc, 7);
    } else {
        auto original = (BYTE*)(
                "\x8B\x09" //mov ecx, [ecx]
                "\x85\xC9" //tst ecx, ecx
                "\x0F\x4F\xC1" //cmovg eax, ecx
                );
        mem::Patch((BYTE*)(this->moduleBase + Offset::SET_MONEY_ENTRY), original, 7);
    }
}
