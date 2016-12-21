#pragma once

#include <QString>

namespace constants {
    const int RebirthCharacterCount = 13;
    const int AfterbirthCharacterCount = 15;
    const int AfterbirthPlusCharacterCount = 16;
    const int AntibirthCharacterCount = 16;
    const int UniqueCharacterCount = 17;
    const int AntibirthOffset = AfterbirthPlusCharacterCount - RebirthCharacterCount;

    const int RebirthPillCount = 9;
    const int AfterbirthPillCount = 4;
    const int TotalPillCount = RebirthPillCount + AfterbirthPillCount;
    const int RuneCount = 2;

    const int HeartLabelSize = 16;
    const int ComboboxViewMinWidth = 162;

    const QString Title = "Isaac Character Editor Rewritten";
    const QString Version = "v7.0";
}
