//
// Created by sw_303 on 2026-06-09.
//

#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H
#include <functional>

#include "Entity.h"
#include "Types.h"


//could be subject to change
//CommandDispatcher.Execute(
//    Command::RenameFile,
//    selectedFileId
//);
class ContextMenu : public Entity
{
public:
    ContextMenu() {}
    ~ContextMenu() {}

    void Initialize()
    {

    }
};

struct ContextMenuItems
{
    EntityID id;
    std::string header;
    std::function<int()> action;
};

#endif //CONTEXTMENU_H
