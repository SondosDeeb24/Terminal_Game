//=================================================================================================================================================================
//? importing the needed libraries and dependencies
//=================================================================================================================================================================

#include <iostream>
#include <conio.h>// For _kbhit() and _getch()
#include <windows.h> //  i used this for to enable using sleep()
#include <string>
#include <vector>

#include <chrono>

using namespace std;



//=================================================================================================================================================================
//? Interface class--------------------------------------------------------------------------------------------------------------------------------------------------
// Handles layout and rendering(drawing the map , each frame)
//=================================================================================================================================================================

class Interface{
public:

    // void after_game(){

    //     system("cls");// clear the screen to diplay the guide screen 
    //     while (true){
    //     // Sleep(10000);

    //     // Get console screen buffer info to get window size
    //     CONSOLE_SCREEN_BUFFER_INFO csbi;
    //     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    //     int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    //     int console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    //     // print the decorating lines (upper and lower lines of = sign )---------------------------------------
    //     COORD upper_line = {0, 1};
    //     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), upper_line);
    //     for(int i = 0 ; i < console_width; i++) cout << "=" ; 

    //     SHORT lower_start = console_height - 1; // set starting point for the lower line , used SHORT since COORD is expecting two shorts member, because if I put the expression direclty it will be considered as int which will raise an error, however using numebr is fine becuase  short accept values from -32243 to 322453 approxiemtly , if i want to use the expression i can write (SHORT)(console_height - 1)
    //     COORD lower_line = {0, lower_start};
    //     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), lower_line);
    //     for(int i = 0 ; i < console_width; i++) cout << "=" ; 
    //     //==================================================================================
    //     vector<string> result = {
    //     "                <<<<  Result  >>>>             ",
    //     "                                               ",
    //     "               Your Score is :                 ",
    //     "                              ",
    //     "             You finished the map in :         ",
    //     "                                               ",        
    //     }

    //     // check the user input (if a key was pressed)
    //     if (_kbhit()) {
    //         char key = _getch(); // Get the key immediately
    //         // if the player wants to play again
    //         if (key == 's'){
    //             // Sleep(1000);
    //             system("cls");
    //             break;
    //         }



    //     }
    // };
    //=====================================================================================================================================
    //?? Print the mpas and return the user's choice
    //=====================================================================================================================================

    int display_maps(){
        system("cls");// clear the screen to diplay the guide screen 
        while (true){

        // Get console screen buffer info to get window size ------------------------------------------------------------------------------------------
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // print the decorating lines (upper and lower lines of = sign )
        COORD upper_line = {0, 1};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), upper_line);
        for(int i = 0 ; i < console_width; i++) cout << "=" ; 

        SHORT lower_start = console_height - 1; // set starting point for the lower line , used SHORT since COORD is expecting two shorts member, because if I put the expression direclty it will be considered as int which will raise an error, however using numebr is fine becuase  short accept values from -32243 to 322453 approxiemtly , if i want to use the expression i can write (SHORT)(console_height - 1)
        COORD lower_line = {0, lower_start};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), lower_line);
        for(int i = 0 ; i < console_width; i++) cout << "=" ; 
        // -------------------------------------------------------------------------------------------------------------------------------------------

        vector<string> maps_options = {
            "_*_________|_|\n___#___##__|_|",
            "__#_____*__|_|\n____#______|_|",
            "___##_#__*_|_|\n_#__##__#__|_|",
            "_*_________|_|\n_*_##_##___|_|"
        };

        
        size_t split_1 = maps_options[0].find('\n');
        string line1_1 = maps_options[0].substr(0, split_1);
        string line2_1 = maps_options[0].substr(split_1 + 1);

        int map_start_horizental = (console_width - (size(line1_1) * 2)) / 3;
        int statment_position = (console_width - size(maps_options[0])) / 2 ;
        int map_start_vertical = (console_height - 5) / 4; // we have 2 lines vertically for each map, in total 4 lines for two maps and one line for desciption above all of them 

        // print greetings statment
        COORD map_position = { static_cast<SHORT>(statment_position), static_cast<SHORT>(map_start_vertical) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), map_position);
        cout << "        Available Maps       " <<endl;
        //
        COORD map_selection = { static_cast<SHORT>(statment_position), static_cast<SHORT>(map_start_vertical + 2) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), map_selection);
        cout << "Enter the Map number to play " <<endl;


        // ---------------------------------------------------------------------------------------------------------------------------
        //* print map number 1 (left top )
        // ---------------------------------------------------------------------------------------------------------------------------
        COORD first_map_name = { static_cast<SHORT>(map_start_horizental), static_cast<SHORT>(map_start_vertical * 2 + 3 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), first_map_name);
        cout << "    Map 1     " <<endl;

        COORD first_map_line1 = { static_cast<SHORT>(map_start_horizental), static_cast<SHORT>(map_start_vertical * 2 + 4 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), first_map_line1);
        cout << line1_1 <<endl;

        COORD first_map_line2 = { static_cast<SHORT>(map_start_horizental), static_cast<SHORT>(map_start_vertical * 2 + 5 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), first_map_line2);
        cout << line2_1 <<endl;

        // ---------------------------------------------------------------------------------------------------------------------------
        //*  print map number 2 (right top )
        // ---------------------------------------------------------------------------------------------------------------------------
        size_t split_2 = maps_options[1].find('\n');
        string line1_2 = maps_options[1].substr(0, split_2);
        string line2_2 = maps_options[1].substr(split_2 + 1);


        COORD second_map_name = { static_cast<SHORT>(map_start_horizental * 2 + size(line1_2)), static_cast<SHORT>(map_start_vertical * 2 + 3 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), second_map_name);
        cout << "    Map 2     " <<endl;

        // print the second map (  just changing the horizental placement , vertical doesn't changes )
        COORD second_map_line1 = { static_cast<SHORT>(map_start_horizental * 2 + size(line1_2)), static_cast<SHORT>(map_start_vertical * 2 + 4 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), second_map_line1);
        cout << line1_2 <<endl;

        //print the second line of the map
        COORD second_map_line2 = { static_cast<SHORT>(map_start_horizental * 2 + size(line1_2)), static_cast<SHORT>(map_start_vertical * 2 + 5 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), second_map_line2);
        cout << line2_2 <<endl;
        // ---------------------------------------------------------------------------------------------------------------------------
        //* print map number 3 (left bottom )
        // ---------------------------------------------------------------------------------------------------------------------------

        size_t split_3 = maps_options[2].find('\n');
        string line1_3 = maps_options[2].substr(0, split_3);
        string line2_3 = maps_options[2].substr(split_3 + 1);

        COORD third_map_name = { static_cast<SHORT>(map_start_horizental), static_cast<SHORT>(map_start_vertical * 3 + 6 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), third_map_name);
        cout << "    Map 3     " <<endl;

        COORD third_map_line1 = { static_cast<SHORT>(map_start_horizental), static_cast<SHORT>(map_start_vertical * 3 + 7 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), third_map_line1);
        cout << line1_3 <<endl;

        COORD third_map_line2 = { static_cast<SHORT>(map_start_horizental), static_cast<SHORT>(map_start_vertical * 3 + 8 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), third_map_line2);
        cout << line2_3 <<endl;
        
        // ---------------------------------------------------------------------------------------------------------------------------
        //* print map number 4 (right bottom )
        // ---------------------------------------------------------------------------------------------------------------------------
        size_t split_4 = maps_options[3].find('\n');
        string line1_4 = maps_options[3].substr(0, split_4);
        string line2_4 = maps_options[3].substr(split_4 + 1);

        COORD forth_map_name = { static_cast<SHORT>(map_start_horizental * 2 + size(line1_4)), static_cast<SHORT>(map_start_vertical * 3 + 6 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), forth_map_name);
        cout << "    Map 4     " <<endl;

        COORD forth_map_line1 = { static_cast<SHORT>(map_start_horizental * 2 + size(line1_4)), static_cast<SHORT>(map_start_vertical * 3 + 7 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), forth_map_line1);
        cout << line1_4 <<endl;

        COORD forth_map_line2 = { static_cast<SHORT>(map_start_horizental * 2 + size(line1_4)), static_cast<SHORT>(map_start_vertical * 3 + 8 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), forth_map_line2);
        cout << line2_4 <<endl;
        

        // ---------------------------------------------------------------------------------------------------------------------------

        // check the user's map choose
        if (_kbhit()) {
            char key = _getch(); // Get the key immediately

            if (key == '1'){
                system("cls");
                return 1;
                break;
            };
            if (key == '2'){
                system("cls");
                return 2;
                break;
            };
            if (key == '3'){
                system("cls");
                return 3;
                break;
            };
            if (key == '4'){
                system("cls");
                return 4;
                break;
            };
        }
        };
    };

    //=====================================================================================================================================
    //?? Print the instruction screen
    //=====================================================================================================================================

    void guide(){
        system("cls");// clear the screen to diplay the guide screen 
        while (true){
        // Sleep(10000);

        // Get console screen buffer info to get window size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // print the decorating lines (upper and lower lines of = sign )---------------------------------------
        COORD upper_line = {0, 1};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), upper_line);
        for(int i = 0 ; i < console_width; i++) cout << "=" ; 

        SHORT lower_start = console_height - 1; // set starting point for the lower line , used SHORT since COORD is expecting two shorts member, because if I put the expression direclty it will be considered as int which will raise an error, however using numebr is fine becuase  short accept values from -32243 to 322453 approxiemtly , if i want to use the expression i can write (SHORT)(console_height - 1)
        COORD lower_line = {0, lower_start};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), lower_line);
        for(int i = 0 ; i < console_width; i++) cout << "=" ; 
        // --------------------------------------------------------

        vector<string> guide = {
        "         <<<<  STEARO Game Guide  >>>>         ",
        "                                               ",
        "              A - to move left                 ",
        "              D - to move right                ",
        "              W - to jump upward               ",
        "             Q - to quit the game              ",
        "                                               ",
        "       Press > r < to return to main page      "
        };

        int guide_width = guide[0].size();
        int guide_height = guide.size();
        
        // calculate starting positions for center alignment
        int start_x = (console_width - guide_width) / 2;
        int start_y = (console_height - guide_height) / 2;


        //print the word STEARO on the screen 
        for (int i = 0; i < guide_height; ++i) {
            COORD pos = { static_cast<SHORT>(start_x), static_cast<SHORT>(start_y + i) }; // add i everytime so we  move to the next level 
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            cout << guide[i] << endl;
        }

        // check the user input (if a key was pressed)
        if (_kbhit()) {
            char key = _getch(); // Get the key immediately

            if (key == 'r'){
                // Sleep(1000);
                system("cls");
                break;

            };
        }
        };
    };

    //=================================================================================================================================================================

    // void decorate_screen(){}
    void draw_UI(){
        while (true){
        // Get console screen buffer info to get window size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // print the decorating lines (upper and lower lines of = sign )---------------------------------------
        COORD upper_line = {0, 1};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), upper_line);
        for(int i = 0 ; i < console_width; i++) cout << "=" ; 

        SHORT lower_start = console_height - 1; // set starting point for the lower line , used SHORT since COORD is expecting two shorts member, because if I put the expression direclty it will be considered as int which will raise an error, however using numebr is fine becuase  short accept values from -32243 to 322453 approxiemtly , if i want to use the expression i can write (SHORT)(console_height - 1)
        COORD lower_line = {0, lower_start};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), lower_line);
        for(int i = 0 ; i < console_width; i++) cout << "=" ; 
        // ----------------------------------------------------------------------------------------------------

        // The game title as string lines
        // vector<string> title = {
        //     "==== === ==== ==== ===   == ",
        //     "=     =  =    =  = =  = =  =",
        //     "====  =  ===  ==== ===  =  =",
        //     "   =  =  =    =  = =  = =  =",
        //     "====  =  ==== =  = =  =  == "
        // };

        vector<string> title = {
            "==== === ==== ==== ===   == ",
            "=     =  =    =  = =  = =  =",
            "====  =  ===  ==== ===  =  =",
            "   =  =  =    =  = =  = =  =",
            "====  =  ==== =  = =  =  == "
        };

        
        int title_width = title[0].size();
        int title_height = title.size();

        // some calculation for the word GAME placement
        string game = "GAME";
        int game_word = game.size();
        int start_game_word = (title_width - game_word) / 2;


        // calculate starting positions for center alignment
        int start_x = (console_width - title_width) / 2;
        int start_y = (console_height - title_height) / 2;

        //print the word STEARO on the screen 
        for (int i = 0; i < title_height; ++i) {
            COORD pos = { static_cast<SHORT>(start_x), static_cast<SHORT>(start_y + i) }; // add i everytime so we  move to the next level 
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            cout << title[i] << endl;
        }

        // print the word game , do some calculation to center it 
        COORD word_game = { static_cast<SHORT>( start_x + start_game_word ), static_cast<SHORT>(start_y + title_height + 2 ) }; // add i everytime so we  move to the next level 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), word_game);
        cout << "GAME" << endl;
        

        // Print play and guide buttons
        string start = "Play (s)";
        string guide = "Guide (space)";
        int control_buttons = (console_width - 5) / 3 ; 

        COORD play_button = { static_cast<SHORT>( control_buttons), static_cast<SHORT>(start_y + title_height + 5 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), play_button);
        cout << start <<endl;

        //line under play
        COORD play_line = { static_cast<SHORT>( control_buttons), static_cast<SHORT>(start_y + title_height + 6  ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), play_line);
        cout << "--------" <<endl;

        COORD guide_button = { static_cast<SHORT>( control_buttons*2 + 5), static_cast<SHORT>(start_y + title_height + 5 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), guide_button);
        cout << guide <<endl;

        // lind under guide
        COORD guide_line = { static_cast<SHORT>( control_buttons*2 + 5), static_cast<SHORT>(start_y + title_height + 6 ) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), guide_line);
        cout << "-------------" <<endl;


        // ---------------------------------------------------------------------------------------------------------------------------------

        // check the user input (if a key was pressed)
        if (_kbhit()) {
            char key = _getch(); // Get the key immediately

            if (key == ' ') this->guide() ;
            else if (key == 's'){
                // Sleep(10000);
                system("cls");
                break;
            };
        };
    };
    };

};
    
//=================================================================================================================================================================
//? Map class--------------------------------------------------------------------------------------------------------------------------------------------------
// Handles layout and rendering(drawing the map , each frame)
//=================================================================================================================================================================
class Map {
public:
    string line1;
    string line2;

    // string top = line1;
    // string bottom = line2;

    Map(string layout) {
        size_t split = layout.find('\n');
        line1 = layout.substr(0, split);
        line2 = layout.substr(split + 1);
    }

    void draw(int pos, bool is_jumping, int score) { //pos = the current location for the player

        string top = line1;
        string bottom = line2;
        // in the word file their is more explaination on this function (explain why I'm coping the layout strings to new variables)

        // the player is jumping 
        if (is_jumping) { // to control Moving While Jumping

            if (top[pos] == '_') top[pos] = '@'; // the block above him is line (he can jump and replace it)
            else bottom[pos] = '@'; 
        // the player is not jumping 
        } else {
            
            // if the digit he wants to step to it is block then, he can jump on it
            if (bottom[pos] == '#') top[pos] = '@'; 
            else bottom[pos] = '@'; 
        }


        // Get console screen buffer info to get window size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // print the decorating lines (upper and lower lines of = sign )---------------------------------------
        COORD upper_line = {0, 1};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), upper_line);
        for(int i = 0 ; i < console_width; i++) cout << "=" ; 

        SHORT lower_start = console_height - 1; // set starting point for the lower line , used SHORT since COORD is expecting two shorts member, because if I put the expression direclty it will be considered as int which will raise an error, however using numebr is fine becuase  short accept values from -32243 to 322453 approxiemtly , if i want to use the expression i can write (SHORT)(console_height - 1)
        COORD lower_line = {0, lower_start};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), lower_line);
        for(int i = 0 ; i < console_width; i++) cout << "=" ; 

        // // Get console screen buffer info to get window size
        // CONSOLE_SCREEN_BUFFER_INFO csbi;
        // GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        // int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        // int console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        int draw_map_x = (console_width - size(top) ) / 2 ;
        int draw_map_y = (console_height - size(top) ) / 3 ;

        // print the player score 
        int score_x_positon = (console_width - (size("  Score : "))*2 ) / 3 ;

        vector<string> score_layout = {
            "==============",
            " ", 
            "=============="
        };

        for (int i = 0; i < size(score_layout); i ++){

            COORD map_position = {static_cast<SHORT>(score_x_positon * 2 + size("  Score : ")), static_cast<SHORT>(draw_map_y * 2  + i )};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), map_position);

            if (score_layout[i] == " "){
                cout <<"  Score : " << score << "  " << endl;
            }
            else{
                cout << score_layout[i] << endl;
            }
        }
        // COORD map_position = {static_cast<SHORT>(score_x_positon * 2 + size("  Score : ")), static_cast<SHORT>(draw_map_y * 2 )};
    
        // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), map_position);

        // cout <<"  Score : " << score << "  " << endl;


        // store all the lines of the map in one vector (I might need this for future imporovement)
        vector <string> lines = {top, bottom};

        for (int i = 0; i < 2 ; i ++){
            COORD map_position = {static_cast<SHORT>(draw_map_x), static_cast<SHORT>(draw_map_y * 3  + i + 2)}; // we added two becuase we have to print the score firstly
    
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), map_position);
            cout << lines[i] << endl;
        }
        
    }
    //!



    //!!
    //function to check if there is star at the given position
    bool has_star(int pos, bool is_jumping){//!
        if (is_jumping && line1[pos] == '*') return true; //star in the top row
        if (!is_jumping && line2[pos] == '*') return true; // Star in the bottom
        // row 
        return false;
    }

    //funtion to remove a star from the map
    void remove_star(int pos, bool is_jumping){//!
        if (is_jumping && line1[pos] == '*') line1[pos] = '_'; // Replace star with empty space
        if (!is_jumping && line2[pos] == '*') line2[pos] = '_'; // Replace star with empty space
    }
    //  function we might need to use them to know the status of specific digit 
    char get_above(int i) { return line1[i]; }
    char get_ground(int i) { return line2[i]; }
    int get_length() { return (int)line1.length() - 1; }
};



//=================================================================================================================================================================
//? Player class --------------------------------------------------------------------------------------------------------------------------------------------------
// Handles state and movement
//=================================================================================================================================================================
class Player {
public:
    int pos = 0; // represent the current location for the player
    bool is_jumping = false;
    int jump_duration = 2;
    int jump_counter = 0;
    int score = 0;

    //---------------------------------------------
    // function to congtrol gravity
    //---------------------------------------------
    void update_gravity(Map &map) {
        if (is_jumping) {
            jump_counter--;
            if (jump_counter <= 0) {
                is_jumping = false;
            }
        }
    }
    //---------------------------------------------
    // Jump function
    //---------------------------------------------
    void jump(Map &map) {
        if (!is_jumping && (map.get_ground(pos) == '#' || map.get_ground(pos) == '_')) {
            is_jumping = true;
            jump_counter = jump_duration;
        }
    }

    //---------------------------------------------
    // move to LEFT function , 'a'  key
    //---------------------------------------------
    void move_left(Map &map) {
        int next = pos - 1;
        if (next >= 0) {
            if (is_jumping) {
                if (map.get_above(next) == '_' || map.get_above(next) == '*' ) pos = next;//!
            } else {
                if (map.get_ground(next) == '_' || map.get_ground(next) == '*') pos = next;//! // _##_ case and user on the second block , so let him jump on the previous block
                else if (map.get_ground(pos) == '_' && map.get_ground(next) == '#') pos = pos; // _#_ case, if the user on the ground and their is block behind him , then we keep the current location
            }
        }
    }
    //---------------------------------------------
    // move to RIGHT function , 'd' key
    //---------------------------------------------
    void move_right(Map &map, bool &finish_line_reached) {
        int map_limit = map.get_length();
        int next = pos + 1;
        if (next <= map_limit) {
            if (is_jumping) {
                if (map.get_above(next) =='|' ) {// if the player reached the finish line, then let him be inside the two vertical line |_| -> |@|
                    pos = next + 1; 
                    finish_line_reached = true;
                }
                if (map.get_above(next) == '_' || map.get_above(next) == '*') pos = next;// here if the block upon him is line and he is jumping, then let me replace it


            } else {
                if (map.get_ground(next) == '|' ) {// if the player reached the finish line, then let him be inside the two vertical line |_| -> |@|
                    pos = next + 1 ; 
                    finish_line_reached = true;
                }
                if (map.get_ground(next) == '_' || map.get_ground(next) == '*') pos = next;
                else if (map.get_ground(pos) == '#' && map.get_ground(next) == '#') pos = next; // _##_ case and user on the first block , so let him jump on the next block
                else if (map.get_ground(pos) == '_' && map.get_ground(next) == '#') pos = pos; // _#_ case, if the user on the ground and their is block infront of him , then keep his location(pos) as it is
            }
        }
    }
};

//===========================================================================================================================================================
//? Game class--------------------------------------------------------------------------------------------------------------------------------------------------
// Controls loop and logic
//===========================================================================================================================================================
class Game {
private:
    vector<string> layouts = {
        "_*_________|_|\n___#___##__|_|",
        "__#_____*__|_|\n____#______|_|",
        "___##_#__*_|_|\n_#__##__#__|_|",
        "_*_________|_|\n_*_##_##___|_|"
    };

    vector<Map> maps; // store all the maps
    Player player;
    int selected_map = 0; // it is the map the user chose
    int our_maps_number = 0;  // to count hom many maps we have

    chrono::steady_clock::time_point start_time; // creating variable called start_time , the steady clock keeping the timing running regaredless of pause of the game
    // it store fixed point in time , we'll use it as reference 
    int seconds, minutes ;

public:
    //---------------------------------------------
    // constructor function
    //---------------------------------------------
    Game() {
        for (const auto &layout : layouts) { //the loop stops when it reaches the end of the layouts vector
            maps.emplace_back(layout); // emplace_back it create(construct) in-place  object (like in the vector directly)
        }
        our_maps_number = maps.size(); // initialize it here after filling maps
    }
    
    //---------------------------------------------
    // hide the cursor and solve flickring problem
    //---------------------------------------------
    void hide_cursor() {
        CONSOLE_CURSOR_INFO cursorInfo;

        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

        // int map_position = our_maps_number * 5 + 2 + 10; // so we print the map the player will play on after everything we wrote eariler, the 4 is place for the clock 
        // COORD coord = {0, static_cast<SHORT>(map_position)};
        // int game_position = -13
        COORD coord = {0, 0};
        // COORD coord = {static_cast<SHORT>(draw_map_x), static_cast<SHORT>(draw_map_y)};

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // to identify the position for the map
    }
    //---------------------------------------------
    // draw the clock on the screen 
    //---------------------------------------------
    void draw_clock() {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count(); // here we calculate the time (in seconds) difference since start_time of the game till our exact moment

        minutes = elapsed / 60;
        seconds = elapsed % 60;
    

        //!
        vector<string> time_layout = {
            "==============",
            " ", 
            "=============="
        };

        // Get console screen buffer info to get window size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int console_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        int draw_clock_x = (console_width - size(time_layout[0])*2 )/ 3;
        int draw_clock_y = (console_height - size(time_layout[0]) )/ 3;

        for (int i = 0; i < size(time_layout) ; i ++){
            COORD timer_pos = {static_cast<SHORT>(draw_clock_x), static_cast<SHORT>(draw_clock_y * 2 + i )};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), timer_pos);
            if(time_layout[i] == " "){
                cout << " Time : " << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << " " << endl;

            }else{
                cout << time_layout[i] << endl;
            }
        }
    }
    
    //---------------------------------------------
    //---------------------------------------------
    void start() { //compine everythin together to run the game 

        hide_cursor();

        Interface UI;
        UI.draw_UI();
        int selected_map = UI.display_maps();
        
        // select_map();
        Map &map = maps[selected_map - 1]; // create object of the class Map, provide the choosen map number as parameter(index for the vector)
        
        bool finish_line_reached = false; // use it to check whether player reached the deadline
        start_time = std::chrono::steady_clock::now(); // initialize start_time varible to the current time when player started the game 

       
        
        //______________________________________________________________________________
        // start the game loop that will be drawind , redering and controlling the whole proceducers all time while game is running

        while (true) {
            draw_clock(); // show timer before drawing the map

            map.draw(player.pos, player.is_jumping, player.score);// draw the map

            //Show the score
            // cout << "Score: " << player.score << "\n";//!

            // check if the user reached the finishe line
            if(finish_line_reached){
                auto now = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count(); // here we calculate the time (in seconds) difference since start_time of the game till our exact moment

                minutes = elapsed / 60;
                seconds = elapsed % 60;
    
                cout << "Congrats!" << endl << "Your finished the map in "  << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << endl;
                Sleep(30000); // 30000 millisecond is 30 second, half minute
                break;
            }

            // check the user input (if a key was pressed)
            if (_kbhit()) {
                char key = _getch(); // Get the key immediately

                if (key == 'a') player.move_left(map);
                else if (key == 'd') player.move_right(map, finish_line_reached);
                else if (key == 'w') player.jump(map);
                else if (key == 'q') break;
            }

            // Check for stars (score collection)//!
            if (map.has_star(player.pos, player.is_jumping)) {
                map.remove_star(player.pos, player.is_jumping);
                player.score += 10; // Add 10 points for each star
            }

            

            player.update_gravity(map);

            Sleep(100); // it gives 0.1 second ( 100 millisecond) pause for the game loop, to make the movement clear, visiable and smooth
        }
    }
};

//===========================================================================================================================================================
// main function
//===========================================================================================================================================================
int main() {
    Game game;
    game.start();

    return 0;
}
