//
// Created by julian.krieger on 9/6/2021.
//

#include <windows.h>
#include "gui.h"

#include "ftxui/component/component.hpp"  // for Slider, Checkbox, Vertical, Renderer, Button, Input, Menu, Radiobox, Toggle
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, Element, operator|, size, xflex, text, WIDTH, hbox, vbox, EQUAL, border, GREATER_THAN
#include "ftxui/component/event.hpp"
#include "hack.h"

using namespace ftxui;

void InternalGUI::init() {
    AllocConsole();

    // stream console to std out
    freopen_s(&this->file_ptr, "CONOUT$", "w", stdout);
}

void InternalGUI::close() {
    fclose(this->file_ptr);
    FreeConsole();
}

void DemoGUI::init() {

}

void DemoGUI::close() {

}

void GUI::draw() {

    auto screen = ScreenInteractive::TerminalOutput();

    // -- Layout -----------------------------------------------------------------

    std::wstring healthLabel = L"Toggle Health";
    bool healthChecked = false;
    Component healthBox = Checkbox(&healthLabel, &healthChecked);

    healthBox = CatchEvent(healthBox, [&](Event event) {
        if(event == Event::Return || event == Event::Character(' ')) {
            healthChecked = !healthChecked;
            this->hack->freezeHealth(healthChecked);
            return true;
        }
        return false;
    });

    std::wstring bombLabel = L"Toggle Freeze Bombs";
    bool bombChecked = false;
    Component bombBox = Checkbox(&bombLabel, &bombChecked);

    bombBox = CatchEvent(bombBox, [&](Event event) {
        if(event == Event::Return || event == Event::Character(' ')) {
            bombChecked = !bombChecked;
            this->hack->freezeBombs(bombChecked);
            return true;
        }
        return false;
    });

    std::wstring bombIncLabel = L"Toggle Increase Bombs";
    bool bombIncChecked = false;
    Component bombIncBox = Checkbox(&bombIncLabel, &bombIncChecked);

    bombIncBox = CatchEvent(bombIncBox, [&](Event event) {
        if(event == Event::Return || event == Event::Character(' ')) {
            bombIncChecked = !bombIncChecked;
            this->hack->increaseBombs(bombIncChecked);
            return true;
        }
        return false;
    });

    std::wstring noKeysNeeded = L"Toggle No Keys Needed";
    bool noKeysNeededChecked = false;
    Component noKeysNeededBox = Checkbox(&noKeysNeeded, &noKeysNeededChecked);

    noKeysNeededBox = CatchEvent(noKeysNeededBox, [&](Event event) {
        if(event == Event::Return || event == Event::Character(' ')) {
            noKeysNeededChecked = !noKeysNeededChecked;
            this->hack->noKeysNeeded(noKeysNeededChecked);
            return true;
        }
        return false;
    });

    std::wstring unlimitedMoney = L"Toggle Unlimited Money";
    bool unlimitedMoneyChecked = false;
    Component unlimitedMoneyBox = Checkbox(&unlimitedMoney, &unlimitedMoneyChecked);

    unlimitedMoneyBox = CatchEvent(unlimitedMoneyBox, [&](Event event) {
        if(event == Event::Return || event == Event::Character(' ')) {
            unlimitedMoneyChecked = !unlimitedMoneyChecked;
            this->hack->unlimitedMoney(unlimitedMoneyChecked);
            return true;
        }
        return false;
    });

    std::vector<bool> states(3);
    auto container = Container::Vertical({
        healthBox,
        bombBox,
        bombIncBox,
        noKeysNeededBox,
        unlimitedMoneyBox
    });

    std::vector<Event> keys;

    auto component = Renderer(container, [&] {
        return vbox({container->Render()}) | frame | ftxui::size(HEIGHT, LESS_THAN, 10) |
               border;
    });

    screen.Loop(component);

}

