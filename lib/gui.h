//
// Created by julian.krieger on 9/6/2021.
//

#ifndef ISAACINTERNAL_GUI_H
#define ISAACINTERNAL_GUI_H

#include <utility>

#include "hack.h"

class GUI {

public:
    explicit GUI(Hack* hack){
        this->hack = hack;
    }

    virtual void init(){};
    void draw();
    virtual void close(){};

protected:
    Hack *hack;
};

class InternalGUI: public GUI {
public:
    explicit InternalGUI(Hack *hack) : GUI(hack) {
        file_ptr = nullptr;
    };
    void init() override;
    void close() override;

private:
    FILE* file_ptr;
};

class DemoGUI: public GUI {
public:
    explicit DemoGUI(Hack* hack): GUI(hack) {
    };
    void init() override;
    void close() override;
};

#endif //ISAACINTERNAL_GUI_H
