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
//? Map class--------------------------------------------------------------------------------------------------------------------------------------------------
// Handles layout and rendering(drawing the map , each frame)
//=================================================================================================================================================================
class Map {
public:
    string line1;
    string line2;

    Map(string layout) {
        size_t split = layout.find('\n');
        line1 = layout.substr(0, split);
        line2 = layout.substr(split + 1);
    }

    void draw(int pos, bool is_jumping) { //pos = the current location for the player
        string top = line1;
        string bottom = line2;

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

        cout << top << "\n" << bottom << "\n";
    }

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
    // print all maps
    //---------------------------------------------
    void select_map() {
        cout << "Available Maps:\n";
        // this is for loop that print all the available maps so the user choose from them
        for (int i = 0; i < maps.size(); ++i) {
            cout << "\nMap " << i + 1 << ":\n";
            cout << maps[i].line1 << "\n" << maps[i].line2 << "\n";
        }
        cout << "\nChoose a map number: ";
        cin >> selected_map;
        if (selected_map < 1 || selected_map > maps.size()) selected_map = 1; // but default map in case if the user wrote invalid input
    }
    
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


        int map_position = our_maps_number * 5 + 2 + 10; // so we print the map the player will play on after everything we wrote eariler, the 4 is place for the clock 
        COORD coord = {0, static_cast<SHORT>(map_position)};

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // to identify the position for the map
    }
    //---------------------------------------------
    // manage the time in the system 
    //---------------------------------------------
    void draw_clock() {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count(); // here we calculate the time (in seconds) difference since start_time of the game till our exact moment

        minutes = elapsed / 60;
        seconds = elapsed % 60;
    

        // control the clock location on the screen 
        int clock_location = our_maps_number * 5 + 2; // I want it to be printed after all the maps options 
        COORD timer_pos = {0, static_cast<SHORT>(clock_location)}; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), timer_pos); // it's built-in function in windows console API, i'm using it here to control where things are being printed
        
        // print the clock on the screen
        cout << "============" << endl;
        cout << "Time: " << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << "        " << endl; // extra space to clear previous digits
        cout << "============" << endl;
    }
    
    //---------------------------------------------
    //---------------------------------------------
    void start() { //compine everythin together to run the game 

        select_map();
        Map &map = maps[selected_map - 1]; // create object of the class Map, provide the choosen map number as parameter(index for the vector)
        
        hide_cursor();
        
        bool finish_line_reached = false; // use it to check whether player reached the deadline
        start_time = std::chrono::steady_clock::now(); // initialize start_time varible to the current time when player started the game 

       
        
        //______________________________________________________________________________
        // start the game loop that will be drawind , redering and controlling the whole proceducers all time while game is running

        while (true) {
            draw_clock(); // show timer before drawing the map

            map.draw(player.pos, player.is_jumping);// draw the map

            //Show the score
            cout << "Score: " << player.score << "\n";//!

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
