#include <Application.hpp>
#include <HomeScreen/HomeScreen.hpp>
#include <IngameScreen/IngameScreen.hpp>
#include <PuzzlesScreen/PuzzlesScreen.hpp>
#include <SettingScreen/SettingScreen.hpp>
#include <StatisticsScreen/StatisticsScreen.hpp>
#include <OptionScreen/OptionScreen.hpp>
#include <CustomScreen/CustomScreen.hpp>

Application::Application() {
    Theme::getInstance()->setThemeID(FileManager::LoadTheme());

    mScreen = new HomeScreen();
    clock.restart();

    windowSize = INTERFACE::WindowSize;
    windowPosition = Point(sf::VideoMode::getDesktopMode().width / 2 - windowSize.x / 2, 10);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    mWindow.create(sf::VideoMode(windowSize.x, windowSize.y), "ApplicationLion", sf::Style::Close, settings);
    mWindow.setFramerateLimit(60);
    mWindow.setPosition(windowPosition.to2i());
}

Application::~Application() {
    delete mScreen;
    Theme::destroyInstance();
}

void Application::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Application::processEvents() {
    sf::Event sfEvent;
    while (mWindow.pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) {
            mWindow.close();
            return;
        }
        mScreen->handleEvent(sfEvent);
    }
}

void Application::update() {
    if (!mWindow.isOpen()) {
        return;
    }
    sf::Time deltaTime = clock.getElapsedTime();
    clock.restart();
    if (mScreen->ifScreenChange()) {
        changeScreen(mScreen->getNextScreen());
    }
    mScreen->update(deltaTime);
}

void Application::render() {
    if (!mWindow.isOpen()) {
        return;
    }
    mWindow.clear(sf::Color::Red);
    mScreen->render(mWindow, sf::RenderStates::Default);
    mWindow.display();
}

void Application::changeScreen(ScreenType screenType) {
    if (ScreenType::None == screenType) {
        mWindow.close();
        return;
    }

    delete mScreen;
    switch (screenType) {
        case ScreenType::IngameScreen:
            mScreen = new IngameScreen();
            break;
        case ScreenType::HomeScreen:
            mScreen = new HomeScreen();
            break;
        case ScreenType::PuzzlesScreen:
            mScreen = new PuzzlesScreen();
            break;
        case ScreenType::SettingScreen:
            mScreen = new SettingScreen();
            break;
        case ScreenType::StatisticsScreen:
            mScreen = new StatisticsScreen();
            break;
        case ScreenType::OptionScreen:
            mScreen = new OptionScreen();
            break;
        case ScreenType::CustomScreen:
            mScreen = new CustomScreen();
            break;
        case ScreenType::None:
            mWindow.close();
            return;
        default:
            printf("Bug at Application::changeScreen\n");
            exit(1);
    }
    mScreen->resetScreenChange();
    mScreen->formatTheme();
}