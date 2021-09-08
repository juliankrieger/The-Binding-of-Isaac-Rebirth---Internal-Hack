//
// Created by julian.krieger on 9/5/2021.
//

#ifndef ISAACEXTERNAL_OFFSET_H
#define ISAACEXTERNAL_OFFSET_H


enum Offset {
    HEALTH_START = 0x14FFB6,
    BOMB_DEC_START = 0x1660A3, // FF08 -> FF00,
    KEY_TST_START = 0x150B90, // num of keys are tested here, it jumps away if keys goes negative. Replace with 15 NOP
    LOAD_ITEM_COST = 0x11AC03,
    SET_MONEY_ENTRY = 0x150653
};


#endif //ISAACEXTERNAL_OFFSET_H
