#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "character.h"
#include "constants.h"
#include "functions.h"
#include "itemedit.h"
#include "png.h"
#include "variables.h"
#include "xml.h"

#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    setWindowTitle(QString("Isaac Character Editor Rewritten %1").arg(constants::Version));

    possibleInputs = Input::getPossibleUserInputs();
    spacebarComboBoxPtr = this->ui->spacebarComboBox;
    trinketComboBoxPtr = this->ui->trinketComboBox;
    mainWindowPtr = this;

    this->ui->redHeartLineEdit->setValidator(this->_healthValidator);
    this->ui->soulHeartLineEdit->setValidator(this->_healthValidator);
    this->ui->blackHeartLineEdit->setValidator(this->_healthValidator);

    this->ui->coinLineEdit->setValidator(this->_consumableValidator);
    this->ui->bombLineEdit->setValidator(this->_consumableValidator);
    this->ui->keyLineEdit->setValidator(this->_consumableValidator);
    this->ui->cardComboBox->view()->setMinimumWidth(constants::ComboboxViewMinWidth);
    this->ui->trinketComboBox->view()->setMinimumWidth(constants::ComboboxViewMinWidth);

    this->ui->nameLineEdit->hide();

    this->ui->folderButton->setIcon(QIcon(":/Resources/Buttons/FolderButton.png"));
    this->ui->notepadButton->setIcon(QIcon(":/Resources/Buttons/NotepadButton.png"));

    this->ui->compassButton->setIcon(QIcon(":/Resources/Buttons/CompassButton.png"));
    this->ui->compassButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->ui->randomSpacebarButton->setIcon(QIcon(":/Resources/Buttons/DiceButton.png"));
    this->ui->randomCardButton->setIcon(QIcon(":/Resources/Buttons/DiceButton.png"));
    this->ui->randomTrinketButton->setIcon(QIcon(":/Resources/Buttons/DiceButton.png"));
    this->ui->randomCostumeButton->setIcon(QIcon(":/Resources/Buttons/DiceButton.png"));

    this->ui->randomEverythingButton->setIcon(QIcon(":/Resources/Buttons/DiceButton2.png"));
    this->ui->randomEverythingButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

#if defined(Q_OS_MAC)
    //Needed to set the fonts on these for whatever reason
    this->ui->redHeartLineEdit->setFont(this->_font);
    this->ui->soulHeartLineEdit->setFont(this->_font);
    this->ui->blackHeartLineEdit->setFont(this->_font);
    this->ui->coinLineEdit->setFont(this->_font);
    this->ui->bombLineEdit->setFont(this->_font);
    this->ui->keyLineEdit->setFont(this->_font);
    this->ui->sortCheckBox->setFont(this->_font);
    this->ui->pillCheckBox->setFont(this->_font);
    this->ui->cardCheckBox->setFont(this->_font);
    this->ui->trinketCheckBox->setFont(this->_font);
#endif

    QApplication::setWindowIcon(QIcon(":Resources/Icons/PurpleKey.ico"));
    QApplication::setFont(this->_font);
    QWidget::setFixedSize(this->size());

    //Sets the path, the game combobox and draws the background.
    GenerateGameComboBox();
    LoadSettings();

    SetUpHealthAndConsumableLabels();
    GenerateCharacterComboBox();
    GenerateComboBoxes();

    //Generating ComboBoxes resets the spacebar item to 0
    //Workaround to set it to Isaac's spacebar item.
    for (int i = 0; i < this->ui->spacebarComboBox->count(); ++i)
        if (ui->spacebarComboBox->itemText(i) == "The D6")
            this->ui->spacebarComboBox->setCurrentIndex(i);
}

MainWindow::~MainWindow()
{
    SaveSettings();
    delete ui;

    delete this->_healthValidator;
    delete this->_consumableValidator;

    for (QLabel* heartLabel : this->_heartLabels) delete heartLabel;
}

bool MainWindow::DetectGodmode()
{
    return QDir(_isaacPath + "/resources/gfx/bosses/godmode").exists();
}

void MainWindow::DrawBackground(Background background)
{
    QPixmap result(this->size());

    if (background == Background::Default)
    {
        result.fill(Qt::transparent);
        QPainter painter(&result);
        painter.drawPixmap(0, 0, QPixmap(":/Resources/Background/Background.png"));
        painter.drawPixmap(0, 0, QPixmap(":/Resources/Background/BackgroundOverlay.png"));
        painter.drawPixmap(224, 10, QPixmap(":/Resources/Background/WhoAmI.png"));
        painter.drawPixmap(453, 135, QPixmap(":/Resources/Background/MyStuff.png"));
    }
    else if (background == Background::Vaporwave)
    {
        result.fill(Qt::transparent);
        QPainter painter(&result);
        painter.drawPixmap(0, 0, QPixmap(":/Resources/BackgroundVaporwave/BackgroundVaporwave.png"));
        painter.drawPixmap(0, 0, QPixmap(":/Resources/Background/BackgroundOverlay.png"));
        painter.drawPixmap(224, 10, QPixmap(":/Resources/BackgroundVaporwave/WhoAmI.png"));
        painter.drawPixmap(453, 135, QPixmap(":/Resources/BackgroundVaporwave/MyStuff.png"));
    }

    result = result.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, result);
    this->setPalette(palette);
}

void MainWindow::SetUpHealthAndConsumableLabels()
{
    this->_draw.PixmapToLabel(this->ui->redHeartImageLabel, ":/Resources/Health/RedHeartFull.png");
    this->_draw.PixmapToLabel(this->ui->soulHeartImageLabel, ":/Resources/Health/SoulHeartFull.png");
    this->_draw.PixmapToLabel(this->ui->blackHeartImageLabel, ":/Resources/Health/BlackHeartFull.png");

    this->_draw.PixmapToLabel(this->ui->coinImageLabel, ":/Resources/Consumables/Coin.png");
    this->_draw.PixmapToLabel(this->ui->bombImageLabel, ":/Resources/Consumables/Bomb.png");
    this->_draw.PixmapToLabel(this->ui->keyImageLabel, ":/Resources/Consumables/Key.png");
}

void MainWindow::GenerateComboBoxes()
{
    //Character ComboBox is excluded because it's only supposed to be called
    //when a character's name is changed and Afterbirth is enabled/disabled.

    GenerateSpacebarComboBox();
    GenerateCardComboBox();
    GenerateTrinketComboBox();
    GenerateCostumeComboBox();
    GenerateSkinColorComboBox();
}

void MainWindow::GenerateCharacterComboBox()
{
    QStringList characterNames;

    switch (game)
    {
        case Game::Rebirth:
            for (int i = 0; i < constants::RebirthCharacterCount; ++i)
                characterNames.append(characterMap.at(static_cast<Characters>(i)).Name);
            break;
        case Game::Afterbirth:
            for (int i = 0; i < constants::AfterbirthCharacterCount; ++i)
                characterNames.append(characterMap.at(static_cast<Characters>(i)).Name);
            break;
        case Game::AfterbirthPlus:
            for (int i = 0; i < constants::AfterbirthPlusCharacterCount; ++i)
                characterNames.append(characterMap.at(static_cast<Characters>(i)).Name);
            break;
        case Game::Antibirth:
            for (int i = 0; i < constants::RebirthCharacterCount; ++i)
                characterNames.append(characterMap.at(static_cast<Characters>(i)).Name);
            for (int i = constants::RebirthCharacterCount; i < constants::AntibirthCharacterCount; ++i)
                characterNames.append(characterMap.at(static_cast<Characters>(i + constants::AntibirthOffset)).Name);
            break;
    }

    auto previousCharacter = static_cast<int>(currentCharacter);
    int previousIndex = this->ui->characterComboBox->currentIndex();

    this->ui->characterComboBox->clear();
    this->ui->characterComboBox->addItems(characterNames);
    if (previousIndex > 0 && previousIndex < this->ui->characterComboBox->count())
    {
        if (!(game != Game::Antibirth && previousCharacter >= constants::AfterbirthPlusCharacterCount))
            this->ui->characterComboBox->setCurrentIndex(previousIndex);
        else if (game == Game::Antibirth && previousCharacter >= constants::RebirthCharacterCount)
            this->ui->characterComboBox->setCurrentIndex(previousIndex);
    }
}

void MainWindow::GenerateSpacebarComboBox()
{
    QStringList spacebarList {
        "None", //0
        "The Bible",
        "The Book of Belial",
        "The Necronomicon",
        "The Poop",
        "Mr. Boom",
        "Tammy's Head",
        "Mom's Bra",
        "Kamikaze",
        "Mom's Pad",
        "Bob's Rotten Head", //10
        "Teleport",
        "Yum Heart",
        "Doctor's Remote",
        "Shoop Da Whoop",
        "Lemon Mishap",
        "Book of Shadows",
        "Anarchist Cookbook",
        "The Hourglass",
        "My Little Unicorn",
        "Book of Revelations", //20
        "The Nail",
        "We Need To Go Deeper",
        "Deck of Cards",
        "Monstro's Tooth",
        "The Gamekid",
        "The Book of Sin",
        "Mom's Bottle of Pills",
        "The D6",
        "Pinking Shears",
        "The Bean", //30
        "Monster Manual",
        "Dead Sea Scrolls",
        "Razor Blade",
        "Forget Me Now",
        "A Pony",
        "Guppy's Paw",
        "IV Bag",
        "Best Friend",
        "Remote Detonator",
        "Guppy's Head", //40
        "Prayer Card",
        "Notched Axe",
        "Crystal Ball",
        "Crack The Sky",
        "The Candle",
        "D20",
        "Spider Butt",
        "Dad's Key",
        "Portable Slot",
        "White Pony", //50
        "Blood Rights",
        "Telepathy For Dummies",
        "How To Jump",
        "D100",
        "D4",
        "D10",
        "Blank Card",
        "Book of Secrets",
        "Box of Spiders",
        "Red Candle", //60
        "The Jar",
        "Flush!",
        "The Satanic Bible",
        "Head of Krampus",
        "Butter Bean",
        "Magic Fingers",
        "Converter",
        "Pandora's Box",
        "Unicorn Stump",
        "Isaac's Tears", //70
        "Undefined",
        "Scissors",
        "Breath of Life",
        "Boomerang"
    };

    if (game == Game::Afterbirth || game == Game::AfterbirthPlus)
    {
        spacebarList.append(QStringList {
            "Diplopia",
            "Placebo",
            "Wooden Nickel",
            "Mega Bean",
            "Glass Cannon",
            "Box of Friends",
            "Friendly Ball",
            "Tear Detonator",
            "D12",
            "Ventricide Razor",
            "D8",
            "Teleport 2.0",
            "Kidney Bean",
            "Glowing Hour Glass",
            "Mine Crafter",
            "Jar of Flies",
            "D7",
            "Mom's Box",
            "Mega Blast"
        });
    }

    if (game == Game::AfterbirthPlus)
    {
        spacebarList.append(QStringList {
            "Plan C",
            "D1",
            "Void",
            "Pause",
            "Smelter",
            "Compost",
            "Dataminer",
            "Clicker",
            "MaMa Mega!",
            "Wait What?",
            "Crooked Penny",
            "Dull Razor",
            "Potato Peeler",
            "Metronome",
            "D infinity",
            "Eden's Soul",
            "Brown Nugget",
            "Sharp Straw",
            "Delirious"
        });
    }

    if (game == Game::Antibirth)
    {
        spacebarList.append(QStringList {
            "Sulfur",
            "Fortune Cookie",
            "Book of Despair",
            "D12 ",
            "Bowl of Tears",
            "Damocles",
            "Free Lemonade",
            "Red Key",
            "Black Mushroom",
            "Book of Virtues",
            "Alabaster Box",
            "Mom's Bracelet",
            "The Scooper",
            "Eternal D6",
            "Voodoo Pin",
            "Sharp Key",
            "Mega Mush",
            "Meat Cleaver",
            "Stitches",
            "R Key",
            "Eraser",
            "Yuck Heart",
            "Magic Skin"
        });
    }

    if (sortAlphabetically)
    {
        //Removes and inserts "None" so it's always the first, regardless of sorting.
        spacebarList.removeAt(0);
        spacebarList.sort();
        spacebarList.insert(0, "None");
    }

    ReplaceComboBoxItems(this->ui->spacebarComboBox, spacebarList);
}

void MainWindow::GenerateCardComboBox()
{
    QStringList cardList {
        "None", //0
        "O - The Fool", //1
        "I - The Magician", //2
        "II - The High Priestess", //3
        "III - The Empress", //4
        "IV - The Emperor", //5
        "V - The Hierophant", //6
        "VI - The Lovers", //7
        "VII - The Chariot", //8
        "VIII - Justice", //9
        "IX - The Hermit", //10
        "X - Wheel of Fortune", //11
        "XI - Strength", //12
        "XII - The Hanged Man", //13
        "XIII - Death", //14
        "XIV - Temperance", //15
        "XV - The Devil", //16
        "XVI - The Tower", //17
        "XVII - The Stars", //18
        "XVIII - The Moon", //19
        "XIX - The Sun", //20
        "XX - Judgement", //21
        "XXI - The World", //22
        "2 of Clubs", //23
        "2 of Diamonds", //24
        "2 of Spades", //25
        "2 of Hearts", //26
        "Joker", //27
        "Rune of Hagalaz", //28
        "Rune of Jera", //29
        "Rune of Ehwaz", //30
        "Rune of Dagaz", //31
        "Rune of Ansuz", //32
        "Rune of Perthro", //33
        "Rune of Berkano", //34
        "Rune of Algiz", //35
        "Chaos Card", //37
        "Credit Card", //38
        "Rules Card", //39
        "A Card Against Humanity", //40
        "Suicide King" //41
    };

    if (game == Game::Afterbirth || game == Game::AfterbirthPlus)
    {
        //Blank Rune is ID 36 in Afterbirth, moving the other Rebirth cards' IDs up by one
        cardList.insert(36, "Blank Rune"); //36
        cardList.append(QStringList {
            "Get Out of Jail Free Card", //42
            "? Card", //43
            "Dice Shard", //44
            "Emergency Contact" //45
        });
    }

    if (game == Game::AfterbirthPlus)
    {
        //Just screw up the order completely, because why not?
        cardList.insert(27, "Ace of Clubs");
        cardList.insert(28, "Ace of Diamonds");
        cardList.insert(29, "Ace of Spades");
        cardList.insert(30, "Ace of Hearts");
        cardList.insert(41, "Black Rune");

        cardList.append("Holy Card");
    }

    if (game == Game::Antibirth)
    {
        cardList.append(QStringList {
            "Rune of Gebo", //60
            "Rune of Kenaz", //61
            "Rune of Fehu", //62
            "Rune of Ingwaz", //63
            "Rune of Sowilo" //64
        });
    }

    ReplaceComboBoxItems(this->ui->cardComboBox, cardList);
}

void MainWindow::GenerateTrinketComboBox()
{
    QStringList trinketList {
        "None", //0
        "Swallowed Penny",
        "Petrified Poop",
        "AAA Battery",
        "Broken Remote",
        "Purple Heart",
        "Broken Magnet",
        "Rosary Bead",
        "Cartridge",
        "Pulse Worm",
        "Wiggle Worm", //10
        "Ring Worm",
        "Flat Worm",
        "Store Credit",
        "Callus",
        "Lucky Rock",
        "Mom's Toenail",
        "Black Lipstick",
        "Bible Tract",
        "Paper Clip",
        "Monkey's Paw", //20
        "Mysterious Paper",
        "Daemon's Tail",
        "Missing Poster",
        "Butt Penny",
        "Mysterious Candy",
        "Hook Worm",
        "Whip Worm",
        "Broken Ankh",
        "Fish Head",
        "Pinky Eye", //30
        "Push Pin",
        "Liberty Cap",
        "Umbilical Cord",
        "Child's Heart",
        "Curved Horn",
        "Rusted Key",
        "Goat Hoof",
        "Mom's Pearl",
        "Cancer",
        "Red Patch", //40
        "Match Stick",
        "Lucky Toe",
        "Cursed Skull",
        "Safety Cap",
        "Ace of Spades",
        "Isaac's Fork",
        //"Polaroid",
        "A Missing Page",
        "Bloody Penny",
        "Burnt Penny", //50
        "Flat Penny",
        "Counterfeit Coin",
        "Tick",
        "Isaac's Head",
        "Maggy's Faith",
        "Judas' Tongue",
        "\?\?\?'s Soul", //escapes a trigraph
        "Samson's Lock",
        "Cain's Eye",
        "Eve's Bird Foot", //60
        "The Left Hand"
    };

    if (game == Game::Afterbirth || game == Game::AfterbirthPlus)
    {
        trinketList.append(QStringList {
            "Shiny Rock",
            "Safety Scissors",
            "Rainbow Worm",
            "Tape Worm",
            "Lazy Worm",
            "Cracked Dice",
            "Super Magnet",
            "Faded Polaroid",
            "Louse",
            "Bob's Bladder",
            "Watch Battery",
            "Blasting Cap",
            "Stud Finder",
            "Error",
            "Poker Chip",
            "Blister",
            "Second Hand",
            "Endless Nameless",
            "Black Feather",
            "Blind Rage",
            "Golden Horse Shoe",
            "Store Key",
            "Rib of Greed",
            "Karma",
            "Lil Larva",
            "Mom's Locket",
            "NO!",
            "Child Leash",
            "Brown Cap"
        });
    }

    if (game == Game::AfterbirthPlus)
    {
        trinketList.append(QStringList {
            "Meconium",
            "Cracked Crown",
            "Used Diaper",
            "Fish Tail",
            "Black Tooth",
            "Ouroboros Worm",
            "Tonsil",
            "Nose Goblin",
            "Super Ball",
            "Vibrant Bulb",
            "Dim Bulb",
            "Fragmented Card",
            "Equality!",
            "Wish Bone",
            "Bag Lunch",
            "Lost Cork",
            "Crow Heart",
            "Walnut",
            "Duct Tape",
            "Silver Dollar",
            "Bloody Crown",
            "Pay To Win",
            "Locust of Wrath",
            "Locust of Pestilence",
            "Locust of Famine",
            "Locust of Death",
            "Locust of Conquest",
            "Bat Wing",
            "Stem Cell"
        });
    }

    if (game == Game::Antibirth)
    {
        trinketList.append(QStringList {
            "Jawbreaker",
            "Chewed Pen",
            "Blessed Penny",
            "Broken Syringe",
            "Exploded Firecracker",
            "Giant Bean",
            "A Lighter",
            "Broken Padlock",
            "Myosotis",
            " 'M",
            "Teardrop Charm",
            "Apple of Sodom",
            "Song of the Siren",
            "Beth's Faith",
            "Old Capacitator",
            "Brain Worm",
            "Perfection",
            "Devil's Crown",
            "Electric Penny"
        });
    }

    if (sortAlphabetically)
    {
        //Removes and inserts "None" so it's always the first, regardless of sorting.
        trinketList.removeAt(0);
        trinketList.sort();
        trinketList.insert(0, "None");
    }

    ReplaceComboBoxItems(this->ui->trinketComboBox, trinketList);
}

void MainWindow::GenerateCostumeComboBox()
{
    QStringList costumeList {
        "0: Nothing",
        "1: Puberty Hair",
        "2: I Found Pills (broken)",
        "3: Lord of the Flies",
        "4: Gnawed Leaf",
        "5: Guppy",
        "6: R U A Wizard",
        "7: Maggy's Hair",
        "8: Cain's Eyepatch",
        "9: Judas' Fez",
        "10: Eve's Hair",
        "11: Azazel's Horns & Wings",
        "12: Random Eden's Hair",
        "13: Samson's Hair",
        "14: Blindfold",
        "15: Faceless",
        "16: Santa Hat"
    };

    if (game == Game::Afterbirth || game == Game::AfterbirthPlus)
    {
        costumeList.append(QStringList {
            "17: Holy Glow",
            "18: Black Ghost",
            "19: Inverted Cross",
            "20: Fun Guy",
            "21: Seraphim",
            "22: Bob (Sloth)",
            "23: Spun",
            "24: Mom",
            "25: Cojoined",
            "26: Leviathan",
            "27: Crap",
            "28: Unknown",
            "29: Shaky Eyeless Head",
            "30: Boomerang",
            "31: Mega Satan",
            "32: Lazarus' Hair",
            "33: Lazarus 2's Hair",
            "34: Lilith's Hair",
            "35: Satoru Iwata"
        });
        costumeList.replace(2, "2: I Found Pills");
    }

    if (game == Game::AfterbirthPlus)
    {
        costumeList.append(QStringList {
            "36: Apollyon's Wings",
            "37: Monocle",
            "38: Adult",
            "39: Spider Fangs",
            "40: Bat Wings"
        });
    }

    ReplaceComboBoxItems(this->ui->costumeComboBox, costumeList);
}

void MainWindow::GenerateGameComboBox()
{
    QStringList gameList {
        "Rebirth",
        "Afterbirth",
        "Afterbirth+",
        "Antibirth"
    };

    ReplaceComboBoxItems(this->ui->gameComboBox, gameList);
}

void MainWindow::GenerateSkinColorComboBox()
{
    QStringList skinColorList {
        "Regular",
        "White",
        "Black",
        "Blue",
        "Red",
        "Green"
    };

    if (game == Game::AfterbirthPlus) skinColorList.append("Grey");

    ReplaceComboBoxItems(this->ui->skinColorComboBox, skinColorList);
}

void MainWindow::DefaultDrawFamiliar(std::vector<int> itemIDs)
{
    this->_draw.Familiar(this->ui->familiarImageLabel, itemIDs);
}

std::array<QLabel*, 12> MainWindow::SetUpHeartLabels()
{
    std::array<QLabel*, 12> heartLabels;
    int x = 62, y = 14;
    for(int i = 0; i < 12; ++i)
    {
        QLabel* tempHeartLabel = new QLabel(this);
        tempHeartLabel->setGeometry(x, y, constants::HeartLabelSize, constants::HeartLabelSize);
        x += constants::HeartLabelSize;
        if(i == 5)
        {
            y += constants::HeartLabelSize;
            x = 62;
        }
        heartLabels.at(i) = tempHeartLabel;
    }
    return heartLabels;
}

void MainWindow::SetCurrentCharacter(int characterToSet)
{
    //Happens when the ComboBox is cleared.
    if (characterToSet == -1) return;
    //Prevents an Antibirth crash.
    else if (characterToSet >= this->ui->characterComboBox->count()) return;

    if (game != Game::Antibirth) currentCharacter = static_cast<Characters>(characterToSet);
    else
    {
        if (characterToSet >= constants::RebirthCharacterCount) currentCharacter = static_cast<Characters>(characterToSet + constants::AntibirthOffset);
        else currentCharacter = static_cast<Characters>(characterToSet);
    }

    auto character = characterMap.at(currentCharacter);

    this->_draw.Character(this->ui->characterImageLabel, currentCharacter);
    this->_draw.Health(this->_heartLabels, character.RedHearts, character.SoulHearts, character.BlackHearts,
                       currentCharacter == Characters::TheKeeper);

    if (character.Pill == 1) this->_draw.Pill(this->ui->cardImageLabel);
    else if (character.Card > 0) this->_draw.Card(this->ui->cardImageLabel, this->ui->cardComboBox->itemText(character.Card));

    this->ui->redHeartLineEdit->setText(QString::number(character.RedHearts));
    this->ui->soulHeartLineEdit->setText(QString::number(character.SoulHearts));
    this->ui->blackHeartLineEdit->setText(QString::number(character.BlackHearts));

    this->ui->coinLineEdit->setText(QString::number(character.Coins));
    this->ui->bombLineEdit->setText(QString::number(character.Bombs));
    this->ui->keyLineEdit->setText(QString::number(character.Keys));

    this->ui->pillCheckBox->setChecked(character.Pill == 1);
    this->ui->cardCheckBox->setChecked(character.Card > 0);
    this->ui->cardComboBox->setCurrentIndex(character.Card);

    //Uses (skin color + 1) because it starts at -1 as opposed to 0.
    this->ui->skinColorComboBox->setCurrentIndex(character.SkinColor + 1);
    this->ui->costumeComboBox->setCurrentIndex(character.Costume);

    //Lazarus hair is messy.
    if (this->ui->costumeComboBox->currentIndex() < 0) this->ui->costumeComboBox->setCurrentIndex(0);

    //If character holds a trinket, get the trinkets name and loop through the ComboBox.
    //Once an index with the same name is found, set it.
    //This is used to make it work with both alphabetical sorting and not.
    if (character.Trinket > 0)
    {
        this->ui->trinketCheckBox->setChecked(true);
        QString trinket = GetKeyFromValue(trinketMap, character.Trinket);

        for (int i = 0; i < this->ui->trinketComboBox->count(); ++i)
            if (ui->trinketComboBox->itemText(i) == trinket)
                this->ui->trinketComboBox->setCurrentIndex(i);
    }
    else this->ui->trinketCheckBox->setChecked(false);

    //Almost the same thing, except this time with a spacebar item.
    if (character.Spacebar > 0)
    {
        QString spacebar = GetKeyFromValue(spacebarMap, character.Spacebar);

        for (int i = 0; i < this->ui->spacebarComboBox->count(); ++i)
            if (ui->spacebarComboBox->itemText(i) == spacebar)
                this->ui->spacebarComboBox->setCurrentIndex(i);
    }
    else this->ui->spacebarComboBox->setCurrentIndex(0);

    this->SetItems();
    this->DefaultDrawFamiliar(GetItemIDsFromItemList(character.Items));
    this->ui->canShootCheckBox->setChecked(character.CanShoot);
}

void MainWindow::SetRedHearts(QString value)
{
    auto character = &characterMap.at(currentCharacter);
    character->RedHearts = value.toInt();
    this->_draw.Health(this->_heartLabels, character->RedHearts, character->SoulHearts, character->BlackHearts,
                       currentCharacter == Characters::TheKeeper);
}

void MainWindow::SetSoulHearts(QString value)
{
    auto character = &characterMap.at(currentCharacter);
    character->SoulHearts = value.toInt();
    this->_draw.Health(this->_heartLabels, character->RedHearts, character->SoulHearts, character->BlackHearts,
                       currentCharacter == Characters::TheKeeper);
}

void MainWindow::SetBlackHearts(QString value)
{
    auto character = &characterMap.at(currentCharacter);
    character->BlackHearts = value.toInt();
    this->_draw.Health(this->_heartLabels, character->RedHearts, character->SoulHearts, character->BlackHearts,
                       currentCharacter == Characters::TheKeeper);
}

void MainWindow::SetCoins(QString value)
{
    characterMap.at(currentCharacter).Coins = value.toInt();

    //Jacob & Esau consumable syncing.
    if (currentCharacter == Characters::Jacob) characterMap.at(Characters::Esau).Coins = value.toInt();
    else if (currentCharacter == Characters::Esau) characterMap.at(Characters::Jacob).Coins = value.toInt();
}

void MainWindow::SetBombs(QString value)
{
    characterMap.at(currentCharacter).Bombs = value.toInt();

    if (currentCharacter == Characters::Jacob) characterMap.at(Characters::Esau).Bombs = value.toInt();
    else if (currentCharacter == Characters::Esau) characterMap.at(Characters::Jacob).Bombs = value.toInt();
}

void MainWindow::SetKeys(QString value)
{
    characterMap.at(currentCharacter).Keys = value.toInt();

    if (currentCharacter == Characters::Jacob) characterMap.at(Characters::Esau).Keys = value.toInt();
    else if (currentCharacter == Characters::Esau) characterMap.at(Characters::Jacob).Keys = value.toInt();
}

void MainWindow::SetItems()
{
    auto character = &characterMap.at(currentCharacter);
    this->ui->itemTextEdit->setPlainText(character->Items.join(", "));
}

void MainWindow::SetSpacebar(QString value)
{
    auto character = &characterMap.at(currentCharacter);
    int spacebar = spacebarMap[value];
    character->Spacebar = spacebar;
    this->_draw.Spacebar(this->ui->spacebarImageLabel, spacebar);
    this->_draw.Charge(this->ui->chargeImageLabel, spacebar);
}

void MainWindow::SetCard(int cardIndex)
{
    auto character = &characterMap.at(currentCharacter);
    //Antibirth cards are 19 IDs ahead of Rebirth ones.
    if (game == Game::Antibirth && cardIndex > 40) cardIndex += 19;
    character->Card = cardIndex;
    this->_draw.Card(this->ui->cardImageLabel, this->ui->cardComboBox->itemText(cardIndex));
}

void MainWindow::SetTrinket(QString value)
{
    auto character = &characterMap.at(currentCharacter);
    int trinket = trinketMap[value];
    character->Trinket = trinket;
    this->_draw.Trinket(this->ui->trinketImageLabel, trinket);
}

void MainWindow::SetCostume(int costumeIndex)
{
    //Blame Rebirth/Afterbirth switching.
    if (costumeIndex < 0) costumeIndex = 0;
    auto character = &characterMap.at(currentCharacter);
    character->Costume = costumeIndex;
}

void MainWindow::SetSkinColor(int skinColorIndex)
{
    //Uses (skin color - 1) because the colors start at -1 as opposed to 0.
    auto character = &characterMap.at(currentCharacter);
    character->SkinColor = skinColorIndex - 1;
}

void MainWindow::SetTears(int checkState)
{
    auto character = &characterMap.at(currentCharacter);
    if(checkState == Qt::Checked) character->CanShoot = true;
    else if(checkState == Qt::Unchecked) character->CanShoot = false;
}

void MainWindow::PillCheckBoxChanged(int checkState)
{
    auto character = &characterMap.at(currentCharacter);
    if (checkState == Qt::Checked)
    {
        if (this->ui->cardCheckBox->isChecked())
            this->ui->cardCheckBox->setChecked(false);
        character->Pill = 1;
        this->_draw.Pill(this->ui->cardImageLabel);
    }
    else if (checkState == Qt::Unchecked)
    {
        character->Pill = 0;
        this->ui->cardImageLabel->clear();
    }
}

void MainWindow::CardCheckBoxChanged(int checkState)
{
    if (checkState == Qt::Checked)
    {
        if (this->ui->pillCheckBox->isChecked())
            this->ui->pillCheckBox->setChecked(false);
        this->ui->cardComboBox->setEnabled(true);
    }
    else if (checkState == Qt::Unchecked)
    {
        this->ui->cardComboBox->setCurrentIndex(0);
        this->ui->cardComboBox->setEnabled(false);
    }
}

void MainWindow::TrinketCheckBoxChanged(int checkState)
{
    if (checkState == Qt::Checked)
        this->ui->trinketComboBox->setEnabled(true);
    else if (checkState == Qt::Unchecked)
    {
        this->ui->trinketComboBox->setCurrentIndex(0);
        this->ui->trinketComboBox->setEnabled(false);
    }
}

void MainWindow::SortCheckBoxChanged(int checkState)
{
    if (checkState == Qt::Checked) sortAlphabetically = true;
    else if (checkState == Qt::Unchecked) sortAlphabetically = false;
    GenerateComboBoxes();
}

void MainWindow::GameComboBoxChanged(int gameIndex)
{
    game = static_cast<Game>(gameIndex);
    switch (game)
    {
        case Game::Rebirth:
        case Game::Antibirth:
        //Enable tears for all Rebirth characters because canShoot is Afterbirth exclusive
        //Leave Afterbirth characters intact because they need Afterbirth enabled anyways.
            for (int i = 0; i < constants::RebirthCharacterCount; ++i)
                characterMap.at(static_cast<Characters>(i)).CanShoot = true;
            this->ui->canShootCheckBox->setEnabled(false);
            this->ui->nameImagesCheckBox->setEnabled(false);
            break;
        case Game::Afterbirth:
        case Game::AfterbirthPlus:
            this->ui->canShootCheckBox->setEnabled(true);
            this->ui->nameImagesCheckBox->setEnabled(true);
            break;
    }

    GenerateCharacterComboBox();
    GenerateComboBoxes();
    this->ui->itemTextEdit->ProcessItems();
}

void MainWindow::NameImagesCheckBoxChanged(int checkState)
{
    nameImagesEnabled = (checkState == Qt::Checked);
}

void MainWindow::PathTextEditChanged()
{
    this->_isaacPath = this->ui->pathTextEdit->toPlainText();
}

void MainWindow::EditNameButtonClicked()
{
    if(this->ui->editNameButton->text() == "Edit")
    {
        this->ui->nameLineEdit->show();
        this->ui->characterComboBox->hide();

        this->ui->nameLineEdit->setText(characterMap.at(currentCharacter).Name);
        this->ui->editNameButton->setText("Save");

        this->ui->nameLineEdit->setFocus(Qt::OtherFocusReason);
        this->ui->nameLineEdit->selectAll();
    }
    else if(this->ui->editNameButton->text() == "Save")
    {
        this->ui->nameLineEdit->hide();
        this->ui->characterComboBox->show();

        characterMap.at(currentCharacter).Name = this->ui->nameLineEdit->text();
        this->ui->editNameButton->setText("Edit");
        GenerateCharacterComboBox();
    }
}

void MainWindow::RestoreDefaultPath()
{
    this->ui->pathTextEdit->setText(this->_defaultPath);
    QTextCursor cursor(this->ui->pathTextEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    this->ui->pathTextEdit->setTextCursor(cursor);
}

void MainWindow::CompassButtonClicked()
{
    //Sets the path text box to a directory selected by the user.
    QString dir = QFileDialog::getExistingDirectory(this,
        tr("Select your Isaac directory."),
        QDir::currentPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dir != QString::null) this->ui->pathTextEdit->setPlainText(dir);

    QTextCursor cursor(this->ui->pathTextEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    this->ui->pathTextEdit->setTextCursor(cursor);
}

void MainWindow::NotepadButtonClicked()
{
    //Opens the file in a default text editor.
    if (QFile(this->_isaacPath + "/resources/players.xml").exists())
        QDesktopServices::openUrl(QUrl("file:///" + this->_isaacPath + "/resources/players.xml"));
    else QMessageBox(QMessageBox::Warning, "Information", "players.xml can't be opened.").exec();
}

void MainWindow::FolderButtonClicked()
{
    //Opens the Isaac folder.
    if (QDir(this->_isaacPath).exists())
        QDesktopServices::openUrl(QUrl("file:///" + this->_isaacPath));
    else QMessageBox(QMessageBox::Warning, "Information", "The Binding of Isaac path can't be opened.").exec();
}

void MainWindow::PurgeButtonClicked()
{
    XML(this->_isaacPath).DeleteXML();
    if (nameImagesEnabled && this->ui->nameImagesCheckBox->isEnabled()) PNG(this->_isaacPath).DeletePNGs();
}

void MainWindow::ReadButtonClicked()
{
    XML(this->_isaacPath).ReadXML();
}

void MainWindow::ExportButtonClicked()
{
    godmodeEnabled = DetectGodmode();
    XML(this->_isaacPath).WriteXML();
    if (nameImagesEnabled && this->ui->nameImagesCheckBox->isEnabled()) PNG(this->_isaacPath).SavePNGs();
}

void MainWindow::RandomSpacebarButtonClicked()
{
    this->_rng.SetRandomComboBoxIndex(this->ui->spacebarComboBox);
}

void MainWindow::RandomCardButtonClicked()
{
    if(this->ui->cardCheckBox->isChecked())
        this->_rng.SetRandomComboBoxIndex(this->ui->cardComboBox);
}

void MainWindow::RandomTrinketButtonClicked()
{
    if(this->ui->trinketCheckBox->isChecked())
        this->_rng.SetRandomComboBoxIndex(this->ui->trinketComboBox);
}

void MainWindow::RandomCostumeButtonClicked()
{
    this->_rng.SetRandomComboBoxIndex(this->ui->costumeComboBox);
    this->_rng.SetRandomComboBoxIndex(this->ui->skinColorComboBox);
}

void MainWindow::RandomEverythingButtonClicked()
{
    RandomCostumeButtonClicked();

    this->ui->cardCheckBox->setChecked(this->_rng.RandomInt(0, 1));
    if(this->ui->cardCheckBox->isChecked()) RandomCardButtonClicked();

    this->ui->trinketCheckBox->setChecked(this->_rng.RandomInt(0, 1));
    if(this->ui->trinketCheckBox->isChecked()) RandomTrinketButtonClicked();

    int redHearts = 0, soulHearts = 0, blackHearts = 0;
    for(int i = 0; i < 6; ++i)
    {
        switch(this->_rng.RandomInt(0, 3))
        {
            case 1:
                ++redHearts;
                break;
            case 2:
                ++soulHearts;
                break;
            case 3:
                ++blackHearts;
                break;
        }
    }

    this->ui->redHeartLineEdit->setText(QString::number(redHearts));
    this->ui->soulHeartLineEdit->setText(QString::number(soulHearts));
    this->ui->blackHeartLineEdit->setText(QString::number(blackHearts));

    this->ui->coinLineEdit->setText(QString::number(this->_rng.RandomInt(0, 2)));
    this->ui->bombLineEdit->setText(QString::number(this->_rng.RandomInt(0, 2)));
    this->ui->keyLineEdit->setText(QString::number(this->_rng.RandomInt(0, 2)));

    QString randomItemsString = "";
    randomItemsString += possibleInputs.at(this->_rng.RandomInt(0, possibleInputs.size() - 1)).Name;
    randomItemsString += ", ";
    randomItemsString += possibleInputs.at(this->_rng.RandomInt(0, possibleInputs.size() - 1)).Name;
    this->ui->itemTextEdit->setText(randomItemsString);
    this->ui->itemTextEdit->ProcessItems();
}

void MainWindow::LoadSettings()
{
    QSettings settings("Portal-chan", "Isaac Character Editor");
    settings.beginGroup("Editor");

    game = GameFromString(settings.value("gamevariant", "afterbirth").toString());
    this->ui->gameComboBox->setCurrentIndex(static_cast<int>(game));
    this->ui->sortCheckBox->setChecked(settings.value("sortalphabetically", false).toBool());
    this->ui->nameImagesCheckBox->setChecked(settings.value("nameimages", true).toBool());
    this->DrawBackground(settings.value("vaporwave", false).toBool() ? Background::Vaporwave : Background::Default);
    this->ui->pathTextEdit->setPlainText(settings.value("path", this->_defaultPath).toString());
    settings.endGroup();
}

void MainWindow::SaveSettings()
{
    QSettings settings("Portal-chan", "Isaac Character Editor");
    settings.beginGroup("Editor");
    settings.setValue("gamevariant", StringFromGame(game));
    settings.setValue("sortalphabetically", sortAlphabetically);
    settings.setValue("nameimages", nameImagesEnabled);
    settings.setValue("vaporwave", vaporwaveAesthetics);
    settings.setValue("path", this->_isaacPath);
    settings.endGroup();
}
