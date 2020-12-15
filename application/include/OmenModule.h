#ifndef OMENLINUX_OMENMODULE_H
#define OMENLINUX_OMENMODULE_H

#include <QWidget>

typedef bool (*DetectModule)();
typedef QWidget* (*InitializeModule)();

typedef struct {
    const char* name;
    DetectModule detector;
    InitializeModule initialize;
} OmenModule;

#endif //OMENLINUX_OMENMODULE_H
