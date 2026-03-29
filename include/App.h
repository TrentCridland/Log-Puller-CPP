#ifndef APP_H
#define APP_H

#include "Config.h"
#include "Util.h"

#include <iostream>
#include <string>

class App {
    public:
        App();
        ~App();
        void RunApp();
    private:
        void RunPull();
        void RunSet();
};

#endif