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
    vector<string> TransformListName;
    vector<vector<TransformItem>> TransformListItem;
    int TransformListCurrent = 0;

    TransformCore();
    void ItemAdd();
    void ItemRemove();
    bool ItemMoveUp();
    bool ItemMoveDown();
    void ItemEnable();
    string GetListNames(int Idx);
    string GetItemTextList(bool SelectedItem_);
    void ListLoad(string FileName);
    void ListSave(string FileName);
    void ListAdd(string Name);
    void ListRem();
};

#endif // TRANSFORMCORE_H
