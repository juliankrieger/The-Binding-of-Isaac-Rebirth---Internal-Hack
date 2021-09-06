//
// Created by julian.krieger on 9/6/2021.
//

#ifndef ISAACEXTERNAL_HACK_H
#define ISAACEXTERNAL_HACK_H
#include <iostream>
#include "../lib/mem.h"
#include "../lib/Offset.h"
#include <ftxui/screen/screen.hpp>


class Hack {
public:
    virtual void freezeHealth(){

    };
    Hack() = default;

protected:
    uintptr_t moduleBase;

};

class InternalHack: public Hack {
public:
    InternalHack();
    void freezeHealth() override;
};

class DemoHack: public Hack {
public:
    DemoHack() = default;
};


#endif //ISAACEXTERNAL_HACK_H
