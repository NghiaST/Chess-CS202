Note:
  

# Project Title

  

## My source code:

  

### Main Folder (root)

- main (.cpp, .hpp):
	- Run

- Chess (.cpp, .hpp):
	- class Chess

- Graphic (.cpp, .hpp):
	- class Graphic

### Folder: DataControl

- Button (.cpp, .hpp)
	- enum
		- ButtonStates { BTN_IDLE, BTN_HOVER, BTN_ACTIVE, BTN_HOLD }
	- class **Button**

- ButtonSimple (.hpp) 
	- <span style = "Color: rgb(2, 20, 250)"> XXXXXXXXXXXX </span>

- Color (.cpp, .hpp)
	- class **ColorButton**
	- class **ColorButMulti**
	- class **Color**
		- *make some Default Color*

- GameSettings (.cpp, .hpp)
	- class **GameSettings**
		- *have* : firstturn +  time + mode + difficulty

- Include (.cpp, .hpp)
	- class PIECE
		- enum 
			- TYPE
				- {NONE = 0, KING = 1, QUEEN, BISHOP, KNIGHT, ROOK, PAWN};
		- static const int ALLTYPE = 7;
	- class CHESS
		- enum 
			- COLOR
				- {NONE = 0, WHITE = 8, BLACK = 16};
		- static const int BLACKWHITE = COLOR::WHITE | COLOR::BLACK;
		- static const int BOTHCOLOR = 24;
	- class MOUSE:
		- enum 
			- STATUS
				- {NONE = 0, POINTED = 1, SELECTED = 2, HOLD = 3, UNPRESSED = 4};
	- class INTERFACE:
		- static const sf::Vector2f WINDOWSIZE;
		- static const double SIZEBOARD;
	- class **Point**
		- *param*: 
			- double x
			- double y
- Settings (.cpp, .hpp)
	- class **Settings**
		- *Have* : ThemeIndex + GameSettings

- StaticButton (.cpp, .hpp)
	- enum 
		- Button_ID
			- { Undefined = -1, ButtonHome = 1000, ButtonStart = 2000 }
	- class **<span style = "color: red"> StaticButton</span>**
		- ***: public Graphic, public sf::Drawable***
		- $Print\ Static\ Button$
		- Important functions:
			- void updateStaticRender()
			- void draw()
			- void render()

- Theme (.cpp, .hpp)
	- class **ThemeIndex**
		- *brief*: Store index of asset (Background, Piece, Board, Button, Text)
	- class **ThemePiece**
		- *brief*: Store data of all Piece
	- class ***<span style="color: red;">Theme</span>*** <span style="color: rgb(244, 28, 255);"> (Important)</span>
		- ***: private ThemeIndex***
		- Store all data of GUI
	- class **ThemeData**
		- *brief*: Contain Directory and some ThemeIndex

### Folder: IngameScreen

- Board (.cpp, .hpp)
	- class **Board**
		- ***: public sf::Transformable***
		- *brief*: Process everything in chess
		- *param*:
			- std::vector<Piece*> pieceList
			- ChessHistory* history
			- int gameStatus
		- Important functions:
			- UndoMove()
			- MakeMove()
			- NewGame()
		- enum:
			- GAMESTATUS (NONE, NEWGAME, ONGOING, ENDGAME)
			- MOVESTATUS (ILLEGAL, LEGAL, ENPASSANT, CASTLE)

- BoardPrint (.cpp, .hpp)
	- class **BoardPrint**
		- ***: public Graphic***
		- *brief*: print board only (no print piece)
		- enum:
			- STATUS {COMMON, SELECTED, PREMOVE, POSSIBLE, CHECK, CHECKMATE}

- ChessHistory (.cpp, .hpp)
	- class **ChessHistory**
		- *brief*: Manage all moves and status of board (to test if Enpassant or Castle)
		- Important functions:
			- void addMove(const MovingStore move)
			- void popMove()

- IngameScreen (.cpp, .hpp)
	- class **IngameScreen**
		- *brief*: Manage in-game Screen
		- *param*:
			- Board* board
			- Button* timeButton, saveButton, undoButton, redoButton, newgameButton, exitButton;
				- <span style = "color: blue">may be add all small button into a class (in the future)</span>

- Piece (.cpp, .hpp)
	- class **Piece**
		- ***: public Graphic***
		- *brief*: Manage piece print

- TimeButton (.cpp, .hpp)
	- <span style = "color: rgb(2, 20,250)"> XXXXXXX </span>

  

### Folder: Other

- resource.rc
	- add icon into .exe file
<!-- 
- '+': complete good
- '*': complete apart
- '-': complete a few
- ' ': haven't done
- '?': unknown

struct Chess;
+   struct ColorButton, ColorButMulti;
+   struct Theme;
*?  struct Settings;
+       struct Theme;
+           * theme for piece
+           * theme for board
+           * theme for background
+           * theme for text
+           * theme for button
-           * theme for analysis ????
+?       struct GameSettings;
            int turn;
            int time;
            int mode;
            int difficulty;
-       struct PlayerSettings; ?????
            int name;
-   struct Chess;
        bool isStart;
        int gameStatus; // 0: playing, 1: white win, 2: black win, 3: draw

+*-      struct Piece();
            int mousestatus; // 0: none, 1: pointed, 2: selected, 3: hold, 4: unpressed
            // int colorID;

            int ifMoveLegal();
            int ifCheck();
            bool ifCheckMate();

            struct King();
            struct Queen();
            struct Rook();
            struct Knight();
            struct Bishop();
            struct Pawn();
+*      struct Board();
            vector<vector<Piece>> piece(8, vector<Piece>(8));
            ifMoveLegal();
            MakeMove(int, int, int, int); //x, y -> x', y'
            int gameStatus;
            int colorID;
        struct Player(); // Human / computer
            int isHuman;
            int color;
            int time;
            int name;
        int mode;
        void UploadMode();
            -> Popular
                -> PvE
                -> PvP
                -> PEvE ?
            -> Custom
                -> piece handicap (chap quan)
                -> time handicap (chap thoi gian)
                -> Puzzle
                -> Analysis + Learn ??

    struct UserDetail;
        int name;
        int password;
        int email;
        struct PlayerStatistics; /// only save for games in General mode
            int win;
            int lose;
            int draw;
            int total;
            int -> struct GameHistory();
        int -> struct GameSettings();
        int -> struct PlayerSettings();

    struct AI_Stishfock();
        int difficulty;
        int color;
        int time;
        int name;
        int -> struct Analysis();
        int -> move Suggestion();

    // struct GameHistory();
    //     struct Move();
    //         struct Piece();
    //         struct Square();
    //         struct Player();
    //     struct Turn();
    //         struct Move();
    //         struct Player();
    //     struct Game();
    //         struct Turn();
    //         struct Player();
    //         struct Board();
    //         struct GameSettings();
    //         struct GameHistory();
    //         struct PlayerSettings();
    struct Action();
        struct Save();
        struct Load();
            void LoadGameFromText();
            void LoadGameFromBinary(); /// use for see/continue game history
        struct Restart();
        struct Undo();
        struct Redo();
        struct Exit();
    int Role (= Admin, Player);
    void FrontEnd (= GUI, CLI);
    void BackEnd (= AI, Human);
    void BacktoFront();
*/ -->