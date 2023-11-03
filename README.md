Note:
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
*/