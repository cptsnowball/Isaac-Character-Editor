#include "variables.h"

bool godmodeEnabled = true;
bool nameImagesEnabled = true;
bool sortAlphabetically = false;
bool vaporwaveAesthetics = false;

Characters currentCharacter = Characters::Isaac;
Game game = Game::Rebirth;

Character _isaac(0, "Isaac", "playername_01_isaac.png", "Character_001_Isaac.png", "PlayerPortrait_01_Isaac.png", "PlayerPortraitBig_01_Isaac.png",
                 -1, 0, 6, 0, 0, 0, 1, 0, 0, 0, 0, 105, true);
Character _maggy(1, "Magdalene", "playername_02_magdalene.png", "Character_002_Magdalene.png", "PlayerPortrait_02_Magdalene.png", "PlayerPortraitBig_02_Magdalene.png",
                -1, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 45, true);
Character _cain(2, "Cain", "playername_03_cain.png", "Character_003_Cain.png", "PlayerPortrait_03_Cain.png", "PlayerPortraitBig_03_Cain.png",
                -1, 8, 4, 0, 0, 0, 0, 1, 0, 0, 19, 0, true, QStringList {"Lucky Foot"});
Character _judas(3, "Judas", "playername_04_judas.png", "Character_004_Judas.png", "PlayerPortrait_04_Judas.png", "PlayerPortraitBig_04_Judas.png",
                 -1, 9, 2, 0, 0, 3, 0, 0, 0, 0, 0, 34, true);
Character _blueBaby(4, "???", "playername_06_bluebaby.png", "Character_006_Bluebaby.png", "PlayerPortrait_06_BlueBaby.png", "PlayerPortraitBig_06_Bluebaby.png",
                    2, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 36, true);
Character _eve(5, "Eve", "playername_05_eve.png", "Character_005_Eve.png", "PlayerPortrait_05_Eve.png", "PlayerPortraitBig_05_Eve.png",
               -1, 10, 4, 0, 0, 0, 0, 0, 0, 0, 0, 126, true, QStringList {"Dead Bird", "Whore of Babylon"});
Character _samson(6, "Samson", "playername_07_samson.png", "Character_007_Samson.png", "PlayerPortrait_07_Samson.png", "PlayerPortraitBig_07_Samson.png",
                  -1, 13, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, true, QStringList {"Bloody Lust"});
Character _azazel(7, "Azazel", "playername_08_azazel.png", "Character_008_Azazel.png", "PlayerPortrait_08_Azazel.png", "PlayerPortraitBig_08_Azazel.png",
                  1, 11, 0, 0, 6, 0, 0, 0, 0, 1, 0, 0, true);
Character _lazarus(8, "Lazarus", "playername_10_lazarus.png", "Character_009_Lazarus.png", "PlayerPortrait_09_Lazarus.png", "PlayerPortraitBig_09_Lazarus.png",
                   -1, 32, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, true);
Character _eden(9,  "Eden", "playername_09_eden.png", "Character_009_Eden.png", "PlayerPortrait_09_Eden.png", "PlayerPortraitBig_09_Eden.png",
                -1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, true);
Character _theLost(10, "The Lost", "playername_12_thelost.png", "Character_012_TheLost.png", "PlayerPortrait_12_TheLost.png", "PlayerPortraitBig_12_TheLost.png",
                   0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 284, true, QStringList {"Holy Mantle"});
Character _lazarus2(11, "Lazarus II", "playername_10_lazarus.png", "Character_010_Lazarus2.png", "PlayerPortrait_10_Lazarus2.png", "PlayerPortraitBig_10_Lazarus2.png",
                    -1, 33, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, true, QStringList {"Anemic"});
Character _blackJudas(12, "Black Judas", "playername_04_judas.png", "Character_013_BlackJudas.png", "PlayerPortrait_BlackJudas.png", "PlayerPortraitBig_BlackJudas.png",
                      1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, true);
Character _lilith(13, "Lilith", "playername_13_lilith.png", "Character_014_Lilith.png", "PlayerPortrait_13_Lilith.png", "PlayerPortraitBig_Lilith.png",
                  1, 34, 2, 0, 4, 0, 0, 0, 0, 0, 0, 357, false, QStringList {"Cambion Conception"});
Character _theKeeper(14, "The Keeper", "playername_14_thekeeper.png", "Character_015_Keeper.png", "PlayerPortrait_14_Keeper.png", "PlayerPortraitBig_Keeper.png",
                     -1, 0, 4, 0, 0, 1, 1, 0, 0, 0, 83, 349, true);
Character _apollyon(15, "Apollyon", "playername_15_apollyon.png", "Character_016_apollyon.png", "PlayerPortrait_15_Apollyon.png", "PlayerPortraitBig_Apollyon.png",
                     0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 467, true);

std::map<Characters, Character> characterMap {
    {Characters::Isaac, _isaac},
    {Characters::Maggy, _maggy},
    {Characters::Cain, _cain},
    {Characters::Judas, _judas},
    {Characters::BlueBaby, _blueBaby},
    {Characters::Eve, _eve},
    {Characters::Samson, _samson},
    {Characters::Azazel, _azazel},
    {Characters::Lazarus, _lazarus},
    {Characters::Eden, _eden},
    {Characters::TheLost, _theLost},
    {Characters::Lazarus2, _lazarus2},
    {Characters::BlackJudas, _blackJudas},
    {Characters::Lilith, _lilith},
    {Characters::TheKeeper, _theKeeper},
    {Characters::Apollyon, _apollyon}
};

std::map<QString, int> spacebarMap {
    {"None", 0}, {"The Bible", 33}, {"The Book of Belial", 34}, {"The Necronomicon", 35}, {"The Poop", 36},
    {"Mr. Boom", 37}, {"Tammy's Head", 38}, {"Mom's Bra", 39}, {"Kamikaze", 40}, {"Mom's Pad", 41},
    {"Bob's Rotten Head", 42}, {"Teleport", 44}, {"Yum Heart", 45}, {"Doctor's Remote", 47}, {"Shoop Da Whoop", 49},
    {"Lemon Mishap", 56}, {"Book of Shadows", 58}, {"Anarchist Cookbook", 65}, {"The Hourglass", 66}, {"My Little Unicorn", 77},
    {"Book of Revelations", 78}, {"The Nail", 83}, {"We Need To Go Deeper", 84}, {"Deck of Cards", 85}, {"Monstro's Tooth", 86},
    {"The Gamekid", 93}, {"The Book of Sin", 97}, {"Mom's Bottle of Pills", 102}, {"The D6", 105}, {"Pinking Shears", 107},
    {"The Bean", 111}, {"Monster Manual", 123}, {"Dead Sea Scrolls", 124}, {"Razor Blade", 126}, {"Forget Me Now", 127},
    {"A Pony", 130}, {"Guppy's Paw", 133}, {"IV Bag", 135}, {"Best Friend", 136}, {"Remote Detonator", 137},
    {"Guppy's Head", 145}, {"Prayer Card", 146}, {"Notched Axe", 147}, {"Crystal Ball", 158}, {"Crack The Sky", 160},
    {"The Candle", 164}, {"D20", 166}, {"Spider Butt", 171}, {"Dad's Key", 175}, {"Portable Slot", 177},
    {"White Pony", 181}, {"Blood Rights", 186}, {"Telepathy For Dummies", 192}, {"How To Jump", 282}, {"D100", 283},
    {"D4", 284}, {"D10", 285}, {"Blank Card", 286}, {"Book of Secrets", 287}, {"Box of Spiders", 288},
    {"Red Candle", 289}, {"The Jar", 290}, {"Flush!", 291}, {"The Satanic Bible", 292}, {"Head of Krampus", 293},
    {"Butter Bean", 294}, {"Magic Fingers", 295}, {"Converter", 296}, {"Pandora's Box", 297}, {"Unicorn Stump", 298},
    {"Isaac's Tears", 323}, {"Undefined", 324}, {"Scissors", 325}, {"Breath of Life", 326}, {"Boomerang", 338},
    {"Diplopia", 347}, {"Placebo", 348}, {"Wooden Nickel", 349}, {"Mega Bean", 351}, {"Glass Cannon", 352},
    {"Box of Friends", 357}, {"Friendly Ball", 382}, {"Tear Detonator", 383}, {"D12", 386}, {"Ventricide Razor", 396},
    {"D8", 406}, {"Teleport 2.0", 419}, {"Kidney Bean", 421}, {"Glowing Hour Glass", 422}, {"Mine Crafter", 427},
    {"Jar of Flies", 434}, {"D7", 437}, {"Mom's Box", 439}, {"Mega Blast", 441}
};

std::map<QString, int> trinketMap {
    {"None", 0}, {"Swallowed Penny", 1}, {"Petrified Poop", 2}, {"AAA Battery", 3}, {"Broken Remote", 4}, {"Purple Heart", 5},
    {"Broken Magnet", 6}, {"Rosary Bead", 7}, {"Cartridge", 8}, {"Pulse Worm", 9}, {"Wiggle Worm", 10},
    {"Ring Worm", 11}, {"Flat Worm", 12}, {"Store Credit", 13}, {"Callus", 14}, {"Lucky Rock", 15},
    {"Mom's Toenail", 16}, {"Black Lipstick", 17}, {"Bible Tract", 18}, {"Paper Clip", 19}, {"Monkey's Paw", 20},
    {"Mysterious Paper", 21}, {"Daemon's Tail", 22}, {"Missing Poster", 23}, {"Butt Penny", 24}, {"Mysterious Candy", 25},
    {"Hook Worm", 26}, {"Whip Worm", 27}, {"Broken Ankh", 28}, {"Fish Head", 29}, {"Pinky Eye", 30},
    {"Push Pin", 31}, {"Liberty Cap", 32}, {"Umbilical Cord", 33}, {"Child's Heart", 34}, {"Curved Horn", 35},
    {"Rusted Key", 36}, {"Goat Hoof", 37}, {"Mom's Pearl", 38}, {"Cancer", 39}, {"Red Patch", 40},
    {"Match Stick", 41}, {"Lucky Toe", 42}, {"Cursed Skull", 43}, {"Safety Cap", 44}, {"Ace of Spades", 45},
    {"Isaac's Fork", 46}, {"A Missing Page", 48}, {"Bloody Penny", 49}, {"Burnt Penny", 50},
    {"Flat Penny", 51}, {"Counterfeit Coin", 52}, {"Tick", 53}, {"Isaac's Head", 54}, {"Maggy's Faith", 55},
    {"Judas' Tongue", 56}, {"\?\?\?'s Soul", 57}, {"Samson's Lock", 58}, {"Cain's Eye", 59}, {"Eve's Bird Foot", 60},
    {"The Left Hand", 61}, {"Shiny Rock", 62}, {"Safety Scissors", 63}, {"Rainbow Worm", 64}, {"Tape Worm", 65},
    {"Lazy Worm", 66}, {"Cracked Dice", 67}, {"Super Magnet", 68}, {"Faded Polaroid", 69}, {"Louse", 70},
    {"Bob's Bladder", 71}, {"Watch Battery", 72}, {"Blasting Cap", 73}, {"Stud Finder", 74}, {"Error", 75},
    {"Poker Chip", 76}, {"Blister", 77}, {"Second Hand", 78}, {"Endless Nameless", 79}, {"Black Feather", 80},
    {"Blind Rage", 81}, {"Golden Horse Shoe", 82}, {"Store Key", 83}, {"Rib of Greed", 84}, {"Karma", 85},
    {"Lil Larva", 86}, {"Mom's Locket", 87}, {"NO!", 88}, {"Child Leash", 89}, {"Brown Cap", 90}
};

std::map<Characters, QString> defaultNames {
    {Characters::Isaac, "Isaac"},
    {Characters::Maggy, "Magdalene"},
    {Characters::Cain, "Cain"},
    {Characters::Judas, "Judas"},
    {Characters::BlueBaby, "???"},
    {Characters::Eve, "Eve"},
    {Characters::Samson, "Samson"},
    {Characters::Azazel, "Azazel"},
    {Characters::Lazarus, "Lazarus"},
    {Characters::Eden, "Eden"},
    {Characters::TheLost, "The Lost"},
    {Characters::Lazarus2, "Lazarus II"},
    {Characters::BlackJudas, "Black Judas"},
    {Characters::Lilith, "Lilith"},
    {Characters::TheKeeper, "The Keeper"},
    {Characters::Apollyon, "Apollyon"}
};

std::map<Characters, QPoint> charSelectMenuOffsets {
    {Characters::Isaac, {0, 288}},
    {Characters::Maggy, {0, 352}},
    {Characters::Cain, {0, 320}},
    {Characters::Judas, {0, 384}},
    {Characters::BlueBaby, {0, 448}},
    {Characters::Eve, {0, 416}},
    {Characters::Samson, {0, 480}},
    {Characters::Azazel, {80, 320}},
    {Characters::Lazarus, {80, 288}},
    {Characters::Eden, {80, 352}},
    {Characters::TheLost, {80, 384}},
    {Characters::Lilith, {176, 480}},
    {Characters::TheKeeper, {176, 512}},
    {Characters::Apollyon, {0, 0}}
};

std::vector<Input> possibleInputs;

QComboBox* spacebarComboBoxPtr;
QComboBox* trinketComboBoxPtr;
MainWindow* mainWindowPtr;
