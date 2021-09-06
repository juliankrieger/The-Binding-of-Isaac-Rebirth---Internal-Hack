//
// Created by julian.krieger on 9/6/2021.
//

#include <gui.h>

int main() {
    auto gui = DemoGUI(new DemoHack);
    gui.init();
    gui.draw();
    gui.close();
    return 0;
}

