# Isaac-Internal

A very basic internal hack for The Binding of Isaac - Rebirth. 

It uses a [FTXUI TUI](https://github.com/ArthurSonzogni/FTXUI) to make different hacks toggleable. 

## Features
- Freeze Health (Replace the health subtraction instruction with NOPs)
- Freeze Money at 9999
- Freeze Bombs at 99
- Freeze Keys at 99

## Planned Features
- Reverse PlayerEntity to gain access to the item pool
- Unlock Achievements

## How to use
- Clone the project
- Cd into the project folder
- Run cmake --build cmake-build-debug --target DLL
- Inject DLL with any cheap injector, you can use guidedhacking's injector or Cheat Engine for this. Isaac is an indy game, so we don't need to manual map here.
