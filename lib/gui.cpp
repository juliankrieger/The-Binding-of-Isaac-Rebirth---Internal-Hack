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
        if(event == Event::Return) {
            healthChecked = !healthChecked;
            this->hack->freezeHealth();
        }
        return true;
    });

    std::vector<bool> states(3);
    auto container = Container::Vertical({
        healthBox,
    });

    std::vector<Event> keys;

    auto component = Renderer(container, [&] {
        return vbox({container->Render()}) | frame | ftxui::size(HEIGHT, LESS_THAN, 10) |
               border;
    });

    screen.Loop(component);

}

