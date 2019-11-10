#ifndef TRANSFORMCORE_H
#define TRANSFORMCORE_H

#include "transformitem.h"

#include <vector>
#include <string>
#include "configfile.h"
#include "settings.h"

using namespace std;

class TransformCore
{
public:
    Settings * Settings_;
    int SelectedItem = -1;
    vector<TransformItem> TransformList;
    TransformCore();
    void ItemAdd();
    void ItemRemove();
    bool ItemMoveUp();
    bool ItemMoveDown();
    void ItemEnable();
    string GetItemTextList(bool SelectedItem_);
    void ListLoad(string FileName);
    void ListSave(string FileName);
};

#endif // TRANSFORMCORE_H
