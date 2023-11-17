#include "SettingScreen.hpp"

SettingScreen::SettingScreen() : Screen() {
    currentScreen = ScreenType::SettingScreen;

    boardSize = Point(64, 64) * 8;    
    boardPosition = Point(100, INTERFACE::WindowSize.y / 2 - boardSize.y / 2);

    BackButtonSize = Point(130, 60);
    BackButtonPosition = Point(810, 500);

    Background = Image(theme->getBackgroundTexture(), Point(0, 0), INTERFACE::WindowSize, true, 0);
    BackButton = new Button(4, BackButtonPosition, BackButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Back");
    boardPrint = new BoardPrint(boardPosition, boardSize, &theme->getTextureBoard());

    std::vector<int> pieceList = Fen::FenToPosition(Fen::StartPosition).squarePieces;
    piecePrintList.assign(64, nullptr);
    for(int index = 0; index < 64; index++) {
        piecePrintList[index] = new PiecePrint(index, pieceList[index]);
        piecePrintList[index]->setRenderPosition(boardPosition);
        piecePrintList[index]->setRenderSize(boardSize / 8);
    }

    ThemeIndex themeIndex = theme->getThemeIndex();

    BackgroundOption = new ButtonOption(5, Point(810, 100 + 0 * 70), Point(300, 50), true, true, &theme->getFont(), theme->getColorDefault(), 20, ThemeData::BackgroundNameList, themeIndex.BackgroundIndex, 2);
    PieceOption      = new ButtonOption(6, Point(810, 100 + 1 * 70), Point(300, 50), true, true, &theme->getFont(), theme->getColorDefault(), 20, ThemeData::PieceNameList, themeIndex.PieceIndex, 2);
    BoardOption      = new ButtonOption(7, Point(810, 100 + 2 * 70), Point(300, 50), true, true, &theme->getFont(), theme->getColorDefault(), 20, ThemeData::BoardNameList, themeIndex.BoardIndex, 2);
    ButOption        = new ButtonOption(8, Point(810, 100 + 3 * 70), Point(300, 50), true, true, &theme->getFont(), theme->getColorDefault(), 20, ThemeData::ColorBM_NameList, themeIndex.ButtonIndex, 2);
    TextOption       = new ButtonOption(9, Point(810, 100 + 4 * 70), Point(300, 50), true, true, &theme->getFont(), theme->getColorDefault(), 20, ThemeData::FontNameList, themeIndex.TextIndex, 2);
}

SettingScreen::~SettingScreen() {
    delete BackButton;
    delete boardPrint;
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        delete *it;
    }
}

void SettingScreen::handleEvent(const sf::Event& event) {
    if (BackButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::HomeScreen;
    }

    bool isChange = false;
    if (BackgroundOption->handleEvent(event)) {
        theme->setBackground(BackgroundOption->getCurrentSelection());
        isChange = true;
    }
    if (PieceOption->handleEvent(event)) {
        theme->setPiece(PieceOption->getCurrentSelection());
        isChange = true;
    }
    if (BoardOption->handleEvent(event)) {
        theme->setBoard(BoardOption->getCurrentSelection());
        isChange = true;
    }
    if (ButOption->handleEvent(event)) {
        theme->setButton(ButOption->getCurrentSelection());
        isChange = true;
    }
    if (TextOption->handleEvent(event)) {
        theme->setText(TextOption->getCurrentSelection());
        isChange = true;
    }
    if (isChange) {
        FileInit::SaveTheme(theme->getThemeIndex());
        formatTheme();
    }
}

void SettingScreen::update(sf::Time deltaTime) {
}

void SettingScreen::render(sf::RenderTarget& target, sf::RenderStates states) {
    // BackButton->updateRender();
    // BackgroundOption->updateRender();
    // PieceOption->updateRender();
    // BoardOption->updateRender();
    // ButOption->updateRender();
    // TextOption->updateRender();
    boardPrint->update();
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        (*it)->update(theme);
    }
    
    Background.draw(target);
    boardPrint->draw(target);
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        target.draw(**it);
    }
    
    target.draw(*BackgroundOption);
    target.draw(*PieceOption);
    target.draw(*BoardOption);
    target.draw(*ButOption);
    target.draw(*TextOption);
    target.draw(*BackButton);
}

void SettingScreen::formatTheme() {
    Background.setTexture(theme->getBackgroundTexture());
    BackButton->setColorBM(theme->getColorDefault());
    BackgroundOption->setColorBM(theme->getColorDefault());
    PieceOption->setColorBM(theme->getColorDefault());
    BoardOption->setColorBM(theme->getColorDefault());
    ButOption->setColorBM(theme->getColorDefault());
    TextOption->setColorBM(theme->getColorDefault());
}
