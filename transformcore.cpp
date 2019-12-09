#include "transformcore.h"

TransformCore::TransformCore()
{

}

void TransformCore::ItemAdd()
{
    TransformItem TI(Settings_);
    TransformList.push_back(TI);
    SelectedItem = TransformList.size() - 1;
}

void TransformCore::ItemRemove()
{
    if ((SelectedItem >= 0) && (SelectedItem < TransformList.size()))
    {
        TransformList.erase(TransformList.begin() + SelectedItem);
    }
    SelectedItem = -1;
}

bool TransformCore::ItemMoveUp()
{
    if ((SelectedItem >= 1) && (SelectedItem < (TransformList.size() - 0)))
    {
        TransformItem Temp = TransformList[SelectedItem];
        TransformList[SelectedItem] = TransformList[SelectedItem - 1];
        SelectedItem--;
        TransformList[SelectedItem] = Temp;
        return true;
    }
    else
    {
        return false;
    }
}

bool TransformCore::ItemMoveDown()
{
    if ((SelectedItem >= 0) && (SelectedItem < (TransformList.size() - 1)))
    {
        TransformItem Temp = TransformList[SelectedItem];
        TransformList[SelectedItem] = TransformList[SelectedItem + 1];
        SelectedItem++;
        TransformList[SelectedItem] = Temp;
        return true;
    }
    else
    {
        return false;
    }
}

void TransformCore::ItemEnable()
{
    if ((SelectedItem >= 0) && (SelectedItem < TransformList.size()))
    {
        TransformList[SelectedItem].TransEnabled = !TransformList[SelectedItem].TransEnabled;
    }
}

string TransformCore::GetItemTextList(bool SelectedItem_)
{
    string StrX = "";
    int I1 = SelectedItem_ ? SelectedItem : 0;
    int I2 = SelectedItem_ ? (SelectedItem + 1) : TransformList.size();
    if (I1 < 0)
    {
        return "";
    }
    for (int I = I1; I < I2; I++)
    {
        StrX = StrX + TransformList[I].GetInfo();
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
    CF.FileLoad(FileName);
    int Items = CF.ParamGetI("Items");
    TransformList.clear();
    for (int I = 0; I < Items; I++)
    {
        TransformItem ItemX(Settings_);

        string ItemId = "Item" + Eden::ToStr(I);
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
}

void TransformCore::ListSave(string FileName)
{
    EdenClass::ConfigFile CF;
    CF.ParamSet("Items", (int)TransformList.size());
    for (int I = 0; I < TransformList.size(); I++)
    {
        string ItemId = "Item" + Eden::ToStr(I);
        CF.ParamSet(ItemId + "TransEnabled", TransformList[I].TransEnabled);
        CF.ParamSet(ItemId + "TransType", TransformList[I].TransType);

        CF.ParamSet(ItemId + "Trans0Type", TransformList[I].Trans0Type);
        CF.ParamSet(ItemId + "Trans0File", TransformList[I].Trans0File);
        CF.ParamSet(ItemId + "Trans0Gamma", TransformList[I].Trans0Gamma);
        CF.ParamSet(ItemId + "Trans0BriR", TransformList[I].Trans0BriR);
        CF.ParamSet(ItemId + "Trans0BriG", TransformList[I].Trans0BriG);
        CF.ParamSet(ItemId + "Trans0BriB", TransformList[I].Trans0BriB);
        CF.ParamSet(ItemId + "Trans0ConR", TransformList[I].Trans0ConR);
        CF.ParamSet(ItemId + "Trans0ConG", TransformList[I].Trans0ConG);
        CF.ParamSet(ItemId + "Trans0ConB", TransformList[I].Trans0ConB);
        CF.ParamSet(ItemId + "Trans0ConBiasR", TransformList[I].Trans0ConBiasR);
        CF.ParamSet(ItemId + "Trans0ConBiasG", TransformList[I].Trans0ConBiasG);
        CF.ParamSet(ItemId + "Trans0ConBiasB", TransformList[I].Trans0ConBiasB);
        CF.ParamSet(ItemId + "Trans0InvR", TransformList[I].Trans0InvR);
        CF.ParamSet(ItemId + "Trans0InvG", TransformList[I].Trans0InvG);
        CF.ParamSet(ItemId + "Trans0InvB", TransformList[I].Trans0InvB);
        CF.ParamSet(ItemId + "Trans0GammaR", TransformList[I].Trans0GammaR);
        CF.ParamSet(ItemId + "Trans0GammaG", TransformList[I].Trans0GammaG);
        CF.ParamSet(ItemId + "Trans0GammaB", TransformList[I].Trans0GammaB);

        CF.ParamSet(ItemId + "Trans1Type", TransformList[I].Trans1Type);
        CF.ParamSet(ItemId + "Trans1File", TransformList[I].Trans1File);
        CF.ParamSet(ItemId + "Trans1Gamma", TransformList[I].Trans1Gamma);
        CF.ParamSet(ItemId + "Trans1Sat", TransformList[I].Trans1Sat);
        CF.ParamSet(ItemId + "Trans1Chan", TransformList[I].Trans1Chan);
        CF.ParamSet(ItemId + "Trans1YuvType", TransformList[I].Trans1YuvType);
        CF.ParamSet(ItemId + "Trans1YuvWeightR", TransformList[I].Trans1YuvWeightR);
        CF.ParamSet(ItemId + "Trans1YuvWeightG", TransformList[I].Trans1YuvWeightG);
        CF.ParamSet(ItemId + "Trans1YuvWeightB", TransformList[I].Trans1YuvWeightB);
        CF.ParamSet(ItemId + "Trans1YuvLuma", TransformList[I].Trans1YuvLuma);

        CF.ParamSet(ItemId + "Trans2Offset1R", TransformList[I].Trans2Offset1R);
        CF.ParamSet(ItemId + "Trans2Offset1G", TransformList[I].Trans2Offset1G);
        CF.ParamSet(ItemId + "Trans2Offset1B", TransformList[I].Trans2Offset1B);
        CF.ParamSet(ItemId + "Trans2GainR", TransformList[I].Trans2GainR);
        CF.ParamSet(ItemId + "Trans2GainG", TransformList[I].Trans2GainG);
        CF.ParamSet(ItemId + "Trans2GainB", TransformList[I].Trans2GainB);
        CF.ParamSet(ItemId + "Trans2Offset2R", TransformList[I].Trans2Offset2R);
        CF.ParamSet(ItemId + "Trans2Offset2G", TransformList[I].Trans2Offset2G);
        CF.ParamSet(ItemId + "Trans2Offset2B", TransformList[I].Trans2Offset2B);
        CF.ParamSet(ItemId + "Trans2Common", TransformList[I].Trans2Common);
        for (int II = 0; II < 25; II++)
        {
            CF.ParamSet(ItemId + "Trans2MatrixR" + Eden::ToStr(II), TransformList[I].Trans2MatrixR[II]);
            CF.ParamSet(ItemId + "Trans2MatrixG" + Eden::ToStr(II), TransformList[I].Trans2MatrixG[II]);
            CF.ParamSet(ItemId + "Trans2MatrixB" + Eden::ToStr(II), TransformList[I].Trans2MatrixB[II]);
        }

        CF.ParamSet(ItemId + "Trans3ItemCount", TransformList[I].Trans3ItemCount);
        CF.ParamSet(ItemId + "Trans3CurrentItem", TransformList[I].Trans3CurrentItem);
        for (int II = 0; II < (TransformList[I].Trans3ItemCount * 4); II++)
        {
            CF.ParamSet(ItemId + "Trans3Prop" + Eden::ToStr(II), TransformList[I].Trans3Prop[II]);
        }
        for (int II = 0; II < (TransformList[I].Trans3ItemCount * 4); II++)
        {
            CF.ParamSet(ItemId + "Trans3Rot" + Eden::ToStr(II), TransformList[I].Trans3Rot[II]);
        }
        for (int II = 0; II < (TransformList[I].Trans3ItemCount * 25); II++)
        {
            CF.ParamSet(ItemId + "Trans3Matrix" + Eden::ToStr(II), TransformList[I].Trans3Matrix[II]);
        }

        CF.ParamSet(ItemId + "Trans4Type", TransformList[I].Trans4Type);
        CF.ParamSet(ItemId + "Trans4Size", TransformList[I].Trans4Size);
        CF.ParamSet(ItemId + "Trans4Size1W", TransformList[I].Trans4Size1W);
        CF.ParamSet(ItemId + "Trans4Size1H", TransformList[I].Trans4Size1H);
        CF.ParamSet(ItemId + "Trans4Size2W", TransformList[I].Trans4Size2W);
        CF.ParamSet(ItemId + "Trans4Size2H", TransformList[I].Trans4Size2H);
        CF.ParamSet(ItemId + "Trans4Scale", TransformList[I].Trans4Scale);
        CF.ParamSet(ItemId + "Trans4LcdType", TransformList[I].Trans4LcdType);
        CF.ParamSet(ItemId + "Trans4LcdOp", TransformList[I].Trans4LcdOp);
        CF.ParamSet(ItemId + "Trans4LcdChromaB", TransformList[I].Trans4LcdChromaB);
        CF.ParamSet(ItemId + "Trans4LcdChromaV", TransformList[I].Trans4LcdChromaV);
        CF.ParamSet(ItemId + "Trans4LcdChromaX", TransformList[I].Trans4LcdChromaX);
        CF.ParamSet(ItemId + "Trans4LcdWeightR", TransformList[I].Trans4LcdWeightR);
        CF.ParamSet(ItemId + "Trans4LcdWeightG", TransformList[I].Trans4LcdWeightG);
        CF.ParamSet(ItemId + "Trans4LcdWeightB", TransformList[I].Trans4LcdWeightB);
        CF.ParamSet(ItemId + "Trans4LcdInterpolation", TransformList[I].Trans4LcdInterpolation);

        CF.ParamSet(ItemId + "Trans5Rotate", TransformList[I].Trans5Rotate);
    }
    CF.FileSave(FileName);
}
