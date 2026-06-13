//
// Created by sw_303 on 2026-06-09.
//

#ifndef CONTEXTMENUMANAGER_H
#define CONTEXTMENUMANAGER_H


class ContextMenu;


class ContextMenuManager {
    static ContextMenuManager* instance;
public:
    ContextMenuManager();
    ~ContextMenuManager()
    {
        if (instance) delete instance;
    }

    static ContextMenuManager* getInstance()
    {
        if (!instance) instance = new ContextMenuManager();
        return instance;
    }

    void OpenContextMenu(ContextMenu& menu);
};



#endif //CONTEXTMENUMANAGER_H
