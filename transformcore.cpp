#include "transformcore.h"

TransformCore::TransformCore()
{
    TransformListCurrent = 0;
    TransformListName.clear();
    TransformListItem.clear();
    vector<TransformItem> TransformList;
    TransformListName.push_back("");
    TransformListItem.push_back(TransformList);
}

void TransformCore::ItemAdd()
{
    TransformItem TI(Settings_);
    TransformListItem[TransformListCurrent].push_back(TI);
    SelectedItem = TransformListItem[TransformListCurrent].size() - 1;
}

void TransformCore::ItemRemove()
{
    if ((SelectedItem >= 0) && (SelectedItem < TransformListItem[TransformListCurrent].size()))
    {
        TransformListItem[TransformListCurrent].erase(TransformListItem[TransformListCurrent].begin() + SelectedItem);
    }
    SelectedItem = -1;
}

bool TransformCore::ItemMoveUp()
{
    if ((SelectedItem >= 1) && (SelectedItem < (TransformListItem[TransformListCurrent].size() - 0)))
    {
        TransformItem Temp = TransformListItem[TransformListCurrent][SelectedItem];
        TransformListItem[TransformListCurrent][SelectedItem] = TransformListItem[TransformListCurrent][SelectedItem - 1];
        SelectedItem--;
        TransformListItem[TransformListCurrent][SelectedItem] = Temp;
        return true;
    }
    else
    {
        return false;
    }
}

bool TransformCore::ItemMoveDown()
{
    if ((SelectedItem >= 0) && (SelectedItem < (TransformListItem[TransformListCurrent].size() - 1)))
    {
        TransformItem Temp = TransformListItem[TransformListCurrent][SelectedItem];
        TransformListItem[TransformListCurrent][SelectedItem] = TransformListItem[TransformListCurrent][SelectedItem + 1];
        SelectedItem++;
        TransformListItem[TransformListCurrent][SelectedItem] = Temp;
        return true;
    }
    else
    {
        return false;
    }
}

void TransformCore::ItemEnable()
{
    if ((SelectedItem >= 0) && (SelectedItem < TransformListItem[TransformListCurrent].size()))
    {
        TransformListItem[TransformListCurrent][SelectedItem].TransEnabled = !TransformListItem[TransformListCurrent][SelectedItem].TransEnabled;
    }
}

string TransformCore::GetListNames(int Idx)
{
    if (Idx >= 0)
    {
        return TransformListName[Idx];
    }
    string StrX = "";
    for (int I = 0; I < TransformListName.size(); I++)
    {
        StrX = StrX + TransformListName[I];
        StrX = StrX + "|";
    }
    return StrX;
}

string TransformCore::GetItemTextList(bool SelectedItem_)
{
    string StrX = "";
    int I1 = SelectedItem_ ? SelectedItem : 0;
    int I2 = SelectedItem_ ? (SelectedItem + 1) : TransformListItem[TransformListCurrent].size();
    if (I1 < 0)
    {
        return "";
    }
    for (int I = I1; I < I2; I++)
    {
        StrX = StrX + TransformListItem[TransformListCurrent][I].GetInfo();
        if (!SelectedItem_)
        {
            StrX = StrX + "|";
        }
    }
    return StrX;
}

void TransformCore::ListLoad(string FileName)
{
    EdenClass::ConfigFile CF;
    CF.FileLoad(Eden::File(FileName));
    TransformListItem[TransformListCurrent].clear();

    TransformListCurrent = 0;
    TransformListName.clear();
    TransformListItem.clear();

    CF.ParamGet("ListCurrent", TransformListCurrent);
    int Lists = CF.ParamGetI("Lists");
    for (int I_ = 0; I_ < Lists; I_++)
    {
        string N = Eden::ToStr(I_);
        CF.ParamGet("List" + Eden::ToStr(I_) + "Name", N);
        int Items = CF.ParamGetI("List" + Eden::ToStr(I_) + "Items");

        TransformListName.push_back(N);
        vector<TransformItem> TransformList;

        for (int I = 0; I < Items; I++)
        {
            TransformItem ItemX(Settings_);

            string ItemId = "List" + Eden::ToStr(I_) + "Item" + Eden::ToStr(I);
            CF.ParamGet(ItemId + "TransEnabled", ItemX.TransEnabled);
            CF.ParamGet(ItemId + "TransType", ItemX.TransType);

            CF.ParamGet(ItemId + "Trans0Type", ItemX.Trans0Type);
            CF.ParamGet(ItemId + "Trans0File", ItemX.Trans0File);
            CF.ParamGet(ItemId + "Trans0Gamma", ItemX.Trans0Gamma);
            CF.ParamGet(ItemId + "Trans0BriR", ItemX.Trans0BriR);
            CF.ParamGet(ItemId + "Trans0BriG", ItemX.Trans0BriG);
            CF.ParamGet(ItemId + "Trans0BriB", ItemX.Trans0BriB);
            CF.ParamGet(ItemId + "Trans0ConR", ItemX.Trans0ConR);
            CF.ParamGet(ItemId + "Trans0ConG", ItemX.Trans0ConG);
            CF.ParamGet(ItemId + "Trans0ConB", ItemX.Trans0ConB);
            CF.ParamGet(ItemId + "Trans0ConBiasR", ItemX.Trans0ConBiasR);
            CF.ParamGet(ItemId + "Trans0ConBiasG", ItemX.Trans0ConBiasG);
            CF.ParamGet(ItemId + "Trans0ConBiasB", ItemX.Trans0ConBiasB);
            CF.ParamGet(ItemId + "Trans0InvR", ItemX.Trans0InvR);
            CF.ParamGet(ItemId + "Trans0InvG", ItemX.Trans0InvG);
            CF.ParamGet(ItemId + "Trans0InvB", ItemX.Trans0InvB);
            CF.ParamGet(ItemId + "Trans0GammaR", ItemX.Trans0GammaR);
            CF.ParamGet(ItemId + "Trans0GammaG", ItemX.Trans0GammaG);
            CF.ParamGet(ItemId + "Trans0GammaB", ItemX.Trans0GammaB);

            CF.ParamGet(ItemId + "Trans1Type", ItemX.Trans1Type);
            CF.ParamGet(ItemId + "Trans1File", ItemX.Trans1File);
            CF.ParamGet(ItemId + "Trans1Gamma", ItemX.Trans1Gamma);
            CF.ParamGet(ItemId + "Trans1Sat", ItemX.Trans1Sat);
            CF.ParamGet(ItemId + "Trans1Chan", ItemX.Trans1Chan);
            CF.ParamGet(ItemId + "Trans1YuvType", ItemX.Trans1YuvType);
            CF.ParamGet(ItemId + "Trans1YuvWeightR", ItemX.Trans1YuvWeightR);
            CF.ParamGet(ItemId + "Trans1YuvWeightG", ItemX.Trans1YuvWeightG);
            CF.ParamGet(ItemId + "Trans1YuvWeightB", ItemX.Trans1YuvWeightB);
            CF.ParamGet(ItemId + "Trans1YuvLuma", ItemX.Trans1YuvLuma);

            CF.ParamGet(ItemId + "Trans2Offset1R", ItemX.Trans2Offset1R);
            CF.ParamGet(ItemId + "Trans2Offset1G", ItemX.Trans2Offset1G);
            CF.ParamGet(ItemId + "Trans2Offset1B", ItemX.Trans2Offset1B);
            CF.ParamGet(ItemId + "Trans2GainR", ItemX.Trans2GainR);
            CF.ParamGet(ItemId + "Trans2GainG", ItemX.Trans2GainG);
            CF.ParamGet(ItemId + "Trans2GainB", ItemX.Trans2GainB);
            CF.ParamGet(ItemId + "Trans2Offset2R", ItemX.Trans2Offset2R);
            CF.ParamGet(ItemId + "Trans2Offset2G", ItemX.Trans2Offset2G);
            CF.ParamGet(ItemId + "Trans2Offset2B", ItemX.Trans2Offset2B);
            CF.ParamGet(ItemId + "Trans2Common", ItemX.Trans2Common);
            CF.ParamGet(ItemId + "Trans2Gamma", ItemX.Trans2Gamma);
            for (int II = 0; II < 25; II++)
            {
                CF.ParamGet(ItemId + "Trans2MatrixR" + Eden::ToStr(II), ItemX.Trans2MatrixR[II]);
                CF.ParamGet(ItemId + "Trans2MatrixG" + Eden::ToStr(II), ItemX.Trans2MatrixG[II]);
                CF.ParamGet(ItemId + "Trans2MatrixB" + Eden::ToStr(II), ItemX.Trans2MatrixB[II]);
            }

            CF.ParamGet(ItemId + "Trans3ItemCount", ItemX.Trans3ItemCount);
            CF.ParamGet(ItemId + "Trans3CurrentItem", ItemX.Trans3CurrentItem);
            for (int II = 0; II < (ItemX.Trans3ItemCount * 4); II++)
            {
                ItemX.Trans3Prop.push_back(CF.ParamGetI(ItemId + "Trans3Prop" + Eden::ToStr(II)));
            }
            for (int II = 0; II < (ItemX.Trans3ItemCount * 4); II++)
            {
                ItemX.Trans3Rot.push_back(CF.ParamGetI(ItemId + "Trans3Rot" + Eden::ToStr(II)));
            }
            for (int II = 0; II < (ItemX.Trans3ItemCount * 25); II++)
            {
                ItemX.Trans3Matrix.push_back(CF.ParamGetI(ItemId + "Trans3Matrix" + Eden::ToStr(II)));
            }

            CF.ParamGet(ItemId + "Trans4Type", ItemX.Trans4Type);
            CF.ParamGet(ItemId + "Trans4Size", ItemX.Trans4Size);
            CF.ParamGet(ItemId + "Trans4Size1W", ItemX.Trans4Size1W);
            CF.ParamGet(ItemId + "Trans4Size1H", ItemX.Trans4Size1H);
            CF.ParamGet(ItemId + "Trans4Size2W", ItemX.Trans4Size2W);
            CF.ParamGet(ItemId + "Trans4Size2H", ItemX.Trans4Size2H);
            CF.ParamGet(ItemId + "Trans4Scale", ItemX.Trans4Scale);
            CF.ParamGet(ItemId + "Trans4LcdType", ItemX.Trans4LcdType);
            CF.ParamGet(ItemId + "Trans4LcdOp", ItemX.Trans4LcdOp);
            CF.ParamGet(ItemId + "Trans4LcdChromaB", ItemX.Trans4LcdChromaB);
            CF.ParamGet(ItemId + "Trans4LcdChromaV", ItemX.Trans4LcdChromaV);
            CF.ParamGet(ItemId + "Trans4LcdChromaX", ItemX.Trans4LcdChromaX);
            CF.ParamGet(ItemId + "Trans4LcdWeightR", ItemX.Trans4LcdWeightR);
            CF.ParamGet(ItemId + "Trans4LcdWeightG", ItemX.Trans4LcdWeightG);
            CF.ParamGet(ItemId + "Trans4LcdWeightB", ItemX.Trans4LcdWeightB);
            CF.ParamGet(ItemId + "Trans4LcdInterpolation", ItemX.Trans4LcdInterpolation);

            CF.ParamGet(ItemId + "Trans5Rotate", ItemX.Trans5Rotate);

            TransformList.push_back(ItemX);
        }

        TransformListItem.push_back(TransformList);
    }

    if (TransformListName.size() == 0)
    {
        TransformListName.push_back("Default");
        vector<TransformItem> TransformList0;
        TransformListItem.push_back(TransformList0);
    }
}

void TransformCore::ListSave(string FileName)
{
    EdenClass::ConfigFile CF;
    CF.ParamSet("ListCurrent", TransformListCurrent);
    CF.ParamSet("Lists", (int)TransformListName.size());
    for (int I_ = 0; I_ < TransformListName.size(); I_++)
    {
        CF.ParamSet("List" + Eden::ToStr(I_) + "Name", TransformListName[I_]);
        CF.ParamSet("List" + Eden::ToStr(I_) + "Items", (int)TransformListItem[I_].size());
        for (int I = 0; I < TransformListItem[I_].size(); I++)
        {
            string ItemId = "List" + Eden::ToStr(I_) + "Item" + Eden::ToStr(I);
            CF.ParamSet(ItemId + "TransEnabled", TransformListItem[I_][I].TransEnabled);
            CF.ParamSet(ItemId + "TransType", TransformListItem[I_][I].TransType);

            CF.ParamSet(ItemId + "Trans0Type", TransformListItem[I_][I].Trans0Type);
            CF.ParamSet(ItemId + "Trans0File", TransformListItem[I_][I].Trans0File);
            CF.ParamSet(ItemId + "Trans0Gamma", TransformListItem[I_][I].Trans0Gamma);
            CF.ParamSet(ItemId + "Trans0BriR", TransformListItem[I_][I].Trans0BriR);
            CF.ParamSet(ItemId + "Trans0BriG", TransformListItem[I_][I].Trans0BriG);
            CF.ParamSet(ItemId + "Trans0BriB", TransformListItem[I_][I].Trans0BriB);
            CF.ParamSet(ItemId + "Trans0ConR", TransformListItem[I_][I].Trans0ConR);
            CF.ParamSet(ItemId + "Trans0ConG", TransformListItem[I_][I].Trans0ConG);
            CF.ParamSet(ItemId + "Trans0ConB", TransformListItem[I_][I].Trans0ConB);
            CF.ParamSet(ItemId + "Trans0ConBiasR", TransformListItem[I_][I].Trans0ConBiasR);
            CF.ParamSet(ItemId + "Trans0ConBiasG", TransformListItem[I_][I].Trans0ConBiasG);
            CF.ParamSet(ItemId + "Trans0ConBiasB", TransformListItem[I_][I].Trans0ConBiasB);
            CF.ParamSet(ItemId + "Trans0InvR", TransformListItem[I_][I].Trans0InvR);
            CF.ParamSet(ItemId + "Trans0InvG", TransformListItem[I_][I].Trans0InvG);
            CF.ParamSet(ItemId + "Trans0InvB", TransformListItem[I_][I].Trans0InvB);
            CF.ParamSet(ItemId + "Trans0GammaR", TransformListItem[I_][I].Trans0GammaR);
            CF.ParamSet(ItemId + "Trans0GammaG", TransformListItem[I_][I].Trans0GammaG);
            CF.ParamSet(ItemId + "Trans0GammaB", TransformListItem[I_][I].Trans0GammaB);

            CF.ParamSet(ItemId + "Trans1Type", TransformListItem[I_][I].Trans1Type);
            CF.ParamSet(ItemId + "Trans1File", TransformListItem[I_][I].Trans1File);
            CF.ParamSet(ItemId + "Trans1Gamma", TransformListItem[I_][I].Trans1Gamma);
            CF.ParamSet(ItemId + "Trans1Sat", TransformListItem[I_][I].Trans1Sat);
            CF.ParamSet(ItemId + "Trans1Chan", TransformListItem[I_][I].Trans1Chan);
            CF.ParamSet(ItemId + "Trans1YuvType", TransformListItem[I_][I].Trans1YuvType);
            CF.ParamSet(ItemId + "Trans1YuvWeightR", TransformListItem[I_][I].Trans1YuvWeightR);
            CF.ParamSet(ItemId + "Trans1YuvWeightG", TransformListItem[I_][I].Trans1YuvWeightG);
            CF.ParamSet(ItemId + "Trans1YuvWeightB", TransformListItem[I_][I].Trans1YuvWeightB);
            CF.ParamSet(ItemId + "Trans1YuvLuma", TransformListItem[I_][I].Trans1YuvLuma);

            CF.ParamSet(ItemId + "Trans2Offset1R", TransformListItem[I_][I].Trans2Offset1R);
            CF.ParamSet(ItemId + "Trans2Offset1G", TransformListItem[I_][I].Trans2Offset1G);
            CF.ParamSet(ItemId + "Trans2Offset1B", TransformListItem[I_][I].Trans2Offset1B);
            CF.ParamSet(ItemId + "Trans2GainR", TransformListItem[I_][I].Trans2GainR);
            CF.ParamSet(ItemId + "Trans2GainG", TransformListItem[I_][I].Trans2GainG);
            CF.ParamSet(ItemId + "Trans2GainB", TransformListItem[I_][I].Trans2GainB);
            CF.ParamSet(ItemId + "Trans2Offset2R", TransformListItem[I_][I].Trans2Offset2R);
            CF.ParamSet(ItemId + "Trans2Offset2G", TransformListItem[I_][I].Trans2Offset2G);
            CF.ParamSet(ItemId + "Trans2Offset2B", TransformListItem[I_][I].Trans2Offset2B);
            CF.ParamSet(ItemId + "Trans2Common", TransformListItem[I_][I].Trans2Common);
            for (int II = 0; II < 25; II++)
            {
                CF.ParamSet(ItemId + "Trans2MatrixR" + Eden::ToStr(II), TransformListItem[I_][I].Trans2MatrixR[II]);
                CF.ParamSet(ItemId + "Trans2MatrixG" + Eden::ToStr(II), TransformListItem[I_][I].Trans2MatrixG[II]);
                CF.ParamSet(ItemId + "Trans2MatrixB" + Eden::ToStr(II), TransformListItem[I_][I].Trans2MatrixB[II]);
            }

            CF.ParamSet(ItemId + "Trans3ItemCount", TransformListItem[I_][I].Trans3ItemCount);
            CF.ParamSet(ItemId + "Trans3CurrentItem", TransformListItem[I_][I].Trans3CurrentItem);
            for (int II = 0; II < (TransformListItem[I_][I].Trans3ItemCount * 4); II++)
            {
                CF.ParamSet(ItemId + "Trans3Prop" + Eden::ToStr(II), TransformListItem[I_][I].Trans3Prop[II]);
            }
            for (int II = 0; II < (TransformListItem[I_][I].Trans3ItemCount * 4); II++)
            {
                CF.ParamSet(ItemId + "Trans3Rot" + Eden::ToStr(II), TransformListItem[I_][I].Trans3Rot[II]);
            }
            for (int II = 0; II < (TransformListItem[I_][I].Trans3ItemCount * 25); II++)
            {
                CF.ParamSet(ItemId + "Trans3Matrix" + Eden::ToStr(II), TransformListItem[I_][I].Trans3Matrix[II]);
            }

            CF.ParamSet(ItemId + "Trans4Type", TransformListItem[I_][I].Trans4Type);
            CF.ParamSet(ItemId + "Trans4Size", TransformListItem[I_][I].Trans4Size);
            CF.ParamSet(ItemId + "Trans4Size1W", TransformListItem[I_][I].Trans4Size1W);
            CF.ParamSet(ItemId + "Trans4Size1H", TransformListItem[I_][I].Trans4Size1H);
            CF.ParamSet(ItemId + "Trans4Size2W", TransformListItem[I_][I].Trans4Size2W);
            CF.ParamSet(ItemId + "Trans4Size2H", TransformListItem[I_][I].Trans4Size2H);
            CF.ParamSet(ItemId + "Trans4Scale", TransformListItem[I_][I].Trans4Scale);
            CF.ParamSet(ItemId + "Trans4LcdType", TransformListItem[I_][I].Trans4LcdType);
            CF.ParamSet(ItemId + "Trans4LcdOp", TransformListItem[I_][I].Trans4LcdOp);
            CF.ParamSet(ItemId + "Trans4LcdChromaB", TransformListItem[I_][I].Trans4LcdChromaB);
            CF.ParamSet(ItemId + "Trans4LcdChromaV", TransformListItem[I_][I].Trans4LcdChromaV);
            CF.ParamSet(ItemId + "Trans4LcdChromaX", TransformListItem[I_][I].Trans4LcdChromaX);
            CF.ParamSet(ItemId + "Trans4LcdWeightR", TransformListItem[I_][I].Trans4LcdWeightR);
            CF.ParamSet(ItemId + "Trans4LcdWeightG", TransformListItem[I_][I].Trans4LcdWeightG);
            CF.ParamSet(ItemId + "Trans4LcdWeightB", TransformListItem[I_][I].Trans4LcdWeightB);
            CF.ParamSet(ItemId + "Trans4LcdInterpolation", TransformListItem[I_][I].Trans4LcdInterpolation);

            CF.ParamSet(ItemId + "Trans5Rotate", TransformListItem[I_][I].Trans5Rotate);
        }
    }
    CF.FileSave(Eden::File(FileName));
}

void TransformCore::ListAdd(string Name)
{
    vector<TransformItem> TransformList;
    for (int I = 0; I < TransformListItem[TransformListCurrent].size(); I++)
    {
        TransformItem TI(Settings_);
        TI.TransEnabled = TransformListItem[TransformListCurrent][I].TransEnabled;
        TI.TransType = TransformListItem[TransformListCurrent][I].TransType;

        TI.Trans0Type = TransformListItem[TransformListCurrent][I].Trans0Type;
        TI.Trans0File = TransformListItem[TransformListCurrent][I].Trans0File;
        TI.Trans0Gamma = TransformListItem[TransformListCurrent][I].Trans0Gamma;
        TI.Trans0BriR = TransformListItem[TransformListCurrent][I].Trans0BriR;
        TI.Trans0BriG = TransformListItem[TransformListCurrent][I].Trans0BriG;
        TI.Trans0BriB = TransformListItem[TransformListCurrent][I].Trans0BriB;
        TI.Trans0ConR = TransformListItem[TransformListCurrent][I].Trans0ConR;
        TI.Trans0ConG = TransformListItem[TransformListCurrent][I].Trans0ConG;
        TI.Trans0ConB = TransformListItem[TransformListCurrent][I].Trans0ConB;
        TI.Trans0ConBiasR = TransformListItem[TransformListCurrent][I].Trans0ConBiasR;
        TI.Trans0ConBiasG = TransformListItem[TransformListCurrent][I].Trans0ConBiasG;
        TI.Trans0ConBiasB = TransformListItem[TransformListCurrent][I].Trans0ConBiasB;
        TI.Trans0InvR = TransformListItem[TransformListCurrent][I].Trans0InvR;
        TI.Trans0InvG = TransformListItem[TransformListCurrent][I].Trans0InvG;
        TI.Trans0InvB = TransformListItem[TransformListCurrent][I].Trans0InvB;
        TI.Trans0GammaR = TransformListItem[TransformListCurrent][I].Trans0GammaR;
        TI.Trans0GammaG = TransformListItem[TransformListCurrent][I].Trans0GammaG;
        TI.Trans0GammaB = TransformListItem[TransformListCurrent][I].Trans0GammaB;

        TI.Trans1Type = TransformListItem[TransformListCurrent][I].Trans1Type;
        TI.Trans1File = TransformListItem[TransformListCurrent][I].Trans1File;
        TI.Trans1Gamma = TransformListItem[TransformListCurrent][I].Trans1Gamma;
        TI.Trans1Sat = TransformListItem[TransformListCurrent][I].Trans1Sat;
        TI.Trans1Chan = TransformListItem[TransformListCurrent][I].Trans1Chan;
        TI.Trans1YuvType = TransformListItem[TransformListCurrent][I].Trans1YuvType;
        TI.Trans1YuvWeightR = TransformListItem[TransformListCurrent][I].Trans1YuvWeightR;
        TI.Trans1YuvWeightG = TransformListItem[TransformListCurrent][I].Trans1YuvWeightG;
        TI.Trans1YuvWeightB = TransformListItem[TransformListCurrent][I].Trans1YuvWeightB;
        TI.Trans1YuvLuma = TransformListItem[TransformListCurrent][I].Trans1YuvLuma;

        TI.Trans2Offset1R = TransformListItem[TransformListCurrent][I].Trans2Offset1R;
        TI.Trans2Offset1G = TransformListItem[TransformListCurrent][I].Trans2Offset1G;
        TI.Trans2Offset1B = TransformListItem[TransformListCurrent][I].Trans2Offset1B;
        TI.Trans2GainR = TransformListItem[TransformListCurrent][I].Trans2GainR;
        TI.Trans2GainG = TransformListItem[TransformListCurrent][I].Trans2GainG;
        TI.Trans2GainB = TransformListItem[TransformListCurrent][I].Trans2GainB;
        TI.Trans2Offset2R = TransformListItem[TransformListCurrent][I].Trans2Offset2R;
        TI.Trans2Offset2G = TransformListItem[TransformListCurrent][I].Trans2Offset2G;
        TI.Trans2Offset2B = TransformListItem[TransformListCurrent][I].Trans2Offset2B;
        TI.Trans2Common = TransformListItem[TransformListCurrent][I].Trans2Common;
        for (int II = 0; II < 25; II++)
        {
            TI.Trans2MatrixR[II] = TransformListItem[TransformListCurrent][I].Trans2MatrixR[II];
            TI.Trans2MatrixG[II] = TransformListItem[TransformListCurrent][I].Trans2MatrixG[II];
            TI.Trans2MatrixB[II] = TransformListItem[TransformListCurrent][I].Trans2MatrixB[II];
        }

        TI.Trans3ItemCount = TransformListItem[TransformListCurrent][I].Trans3ItemCount;
        TI.Trans3CurrentItem = TransformListItem[TransformListCurrent][I].Trans3CurrentItem;
        for (int II = 0; II < (TransformListItem[TransformListCurrent][I].Trans3ItemCount * 4); II++)
        {
            TI.Trans3Prop.push_back(TransformListItem[TransformListCurrent][I].Trans3Prop[II]);
        }
        for (int II = 0; II < (TransformListItem[TransformListCurrent][I].Trans3ItemCount * 4); II++)
        {
            TI.Trans3Rot.push_back(TransformListItem[TransformListCurrent][I].Trans3Rot[II]);
        }
        for (int II = 0; II < (TransformListItem[TransformListCurrent][I].Trans3ItemCount * 25); II++)
        {
            TI.Trans3Matrix.push_back(TransformListItem[TransformListCurrent][I].Trans3Matrix[II]);
        }

        TI.Trans4Type = TransformListItem[TransformListCurrent][I].Trans4Type;
        TI.Trans4Size = TransformListItem[TransformListCurrent][I].Trans4Size;
        TI.Trans4Size1W = TransformListItem[TransformListCurrent][I].Trans4Size1W;
        TI.Trans4Size1H = TransformListItem[TransformListCurrent][I].Trans4Size1H;
        TI.Trans4Size2W = TransformListItem[TransformListCurrent][I].Trans4Size2W;
        TI.Trans4Size2H = TransformListItem[TransformListCurrent][I].Trans4Size2H;
        TI.Trans4Scale = TransformListItem[TransformListCurrent][I].Trans4Scale;
        TI.Trans4LcdType = TransformListItem[TransformListCurrent][I].Trans4LcdType;
        TI.Trans4LcdOp = TransformListItem[TransformListCurrent][I].Trans4LcdOp;
        TI.Trans4LcdChromaB = TransformListItem[TransformListCurrent][I].Trans4LcdChromaB;
        TI.Trans4LcdChromaV = TransformListItem[TransformListCurrent][I].Trans4LcdChromaV;
        TI.Trans4LcdChromaX = TransformListItem[TransformListCurrent][I].Trans4LcdChromaX;
        TI.Trans4LcdWeightR = TransformListItem[TransformListCurrent][I].Trans4LcdWeightR;
        TI.Trans4LcdWeightG = TransformListItem[TransformListCurrent][I].Trans4LcdWeightG;
        TI.Trans4LcdWeightB = TransformListItem[TransformListCurrent][I].Trans4LcdWeightB;
        TI.Trans4LcdInterpolation = TransformListItem[TransformListCurrent][I].Trans4LcdInterpolation;

        TI.Trans5Rotate = TransformListItem[TransformListCurrent][I].Trans5Rotate;

        TransformList.push_back(TI);
    }

    bool ToAdd = true;
    for (int I = 0; I < TransformListName.size(); I++)
    {
        if (TransformListName[I] > Name)
        {
            vector<string>::iterator I_1 = TransformListName.begin();
            vector<vector<TransformItem>>::iterator I_2 = TransformListItem.begin();
            I_1 += I;
            I_2 += I;
            TransformListName.insert(I_1, Name);
            TransformListItem.insert(I_2, TransformList);
            TransformListCurrent = I;
            ToAdd = false;
            break;
        }
    }

    if (ToAdd)
    {
        TransformListName.push_back(Name);
        TransformListItem.push_back(TransformList);
        TransformListCurrent = TransformListName.size() - 1;
    }
}

void TransformCore::ListRem()
{
    if (TransformListName.size() > 1)
    {
        vector<string>::iterator I_1 = TransformListName.begin();
        vector<vector<TransformItem>>::iterator I_2 = TransformListItem.begin();
        I_1 += TransformListCurrent;
        I_2 += TransformListCurrent;
        TransformListName.erase(I_1);
        TransformListItem.erase(I_2);
        if (TransformListCurrent >= TransformListName.size())
        {
            TransformListCurrent = TransformListName.size() - 1;
        }
    }
}
