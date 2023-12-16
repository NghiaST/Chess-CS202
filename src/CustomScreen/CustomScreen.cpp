#include <CustomScreen/CustomScreen.hpp>
#include <Helpers/Fen.hpp>

CustomScreen::CustomScreen() : Screen() {
    currentScreen = ScreenType::CustomScreen;

    boardSize = Point(64, 64) * 8;
    boardPosition = Point(80, INTERFACE::WindowSize.y / 2 - boardSize.y / 2);

    buttonSize = Point(160, 55);
    actionButtonSize = Point(200, 30);

    ResetButtonPosition = Point(707, 290);
    ClearButtonPosition = Point(908, 290);

    PlayButtonPosition = Point(810, 380);
    SaveAndBackButtonPosition = Point(810, 460);
    BackButtonPosition = Point(810, 540);

    boardCustomManager = new BoardCustomManager(boardPosition, boardSize);

    Background = Image(theme->getBackgroundTexture(), Point(0, 0), INTERFACE::WindowSize, true, 0);
    ResetButton = new Button(4, ResetButtonPosition, actionButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 15, "Default");
    ClearButton = new Button(4, ClearButtonPosition, actionButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 15, "Clear");
    PlayButton = new Button(4, PlayButtonPosition, buttonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Play");
    SaveAndBackButton = new Button(4, SaveAndBackButtonPosition, buttonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Save and Back");
    BackButton = new Button(4, BackButtonPosition, buttonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Back");    
}

CustomScreen::~CustomScreen() {
    delete ResetButton;
    delete ClearButton;
    delete PlayButton;
    delete SaveAndBackButton;
    delete BackButton;
    delete boardCustomManager;
}

void CustomScreen::handleEvent(const sf::Event& event) {
    boardCustomManager->handleEvent(event);
    if (ResetButton->handleEvent(event)) {
        boardCustomManager->setDefault();
    }
    if (ClearButton->handleEvent(event)) {
        boardCustomManager->setClean();
    }
    if (PlayButton->handleEvent(event)) {
        if (boardCustomManager->isCustomBoardValid()) {
            FileManager::SaveGameFEN(*boardCustomManager->getBoard(), *boardCustomManager);
            isScreenChange = true;
            nextScreen = ScreenType::IngameScreen;
        }
    }
    if (SaveAndBackButton->handleEvent(event)) {
        if (boardCustomManager->isCustomBoardValid()) {
            FileManager::SaveGameFEN(*boardCustomManager->getBoard(), *boardCustomManager);
            isScreenChange = true;
            nextScreen = ScreenType::OptionScreen;
        }
    }
    if (BackButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::OptionScreen;
    }
}

void CustomScreen::update(sf::Time deltaTime) {
    // boardCustomManager->update(deltaTime);
}

void CustomScreen::render(sf::RenderTarget& target, sf::RenderStates states) {    
    target.draw(Background);
    target.draw(*boardCustomManager);
    target.draw(*BackButton);
    target.draw(*SaveAndBackButton);
    target.draw(*PlayButton);
    target.draw(*ClearButton);
    target.draw(*ResetButton);
}

void CustomScreen::formatTheme() {
    Background.setTexture(theme->getBackgroundTexture());
    ResetButton->setColorBM(theme->getColorDefault());
    ClearButton->setColorBM(theme->getColorDefault());
    PlayButton->setColorBM(theme->getColorDefault());
    SaveAndBackButton->setColorBM(theme->getColorDefault());
    BackButton->setColorBM(theme->getColorDefault());
}

