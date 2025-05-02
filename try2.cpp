
#include <iostream>
#include <conio.h>// For _kbhit() and _getch()
#include <windows.h> //  i used this for to enable using sleep()
#include <string>
#include <vector>

using namespace std;

//=========================================
//? Map class
// Handles layout and rendering(drawing the map , each frame)
//=========================================
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

    //  function we might need to use them to know the status of specific digit 
    char getAbove(int i) { return line1[i]; }
    char getGround(int i) { return line2[i]; }
    int getLength() { return (int)line1.length() - 1; }
};

//=========================================
//? Player class
// Handles state and movement
//=========================================
class Player {
public:
    int pos = 0; // represent the current location for the player
    bool is_jumping = false;
    int jump_duration = 2;
    int jump_counter = 0;

    //---------------------------------------------
    // function to congtrol gravity
    //---------------------------------------------
    void updateGravity(Map &map) {
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
        if (!is_jumping && (map.getGround(pos) == '#' || map.getGround(pos) == '_')) {
            is_jumping = true;
            jump_counter = jump_duration;
        }
    }

    //---------------------------------------------
    // move to LEFT function , 'a'  key
    //---------------------------------------------
    void moveLeft(Map &map) {
        int next = pos - 1;
        if (next >= 0) {
            if (is_jumping) {
                if (map.getAbove(next) == '_') pos = next;
            } else {
                if (map.getGround(next) == '_') pos = next;
                else if (map.getGround(pos) == '#' && map.getGround(next) == '#') pos = next; // _##_ case and user on the second block , so let him jump on the previous block
                else if (map.getGround(pos) == '_' && map.getGround(next) == '#') pos = pos; // _#_ case, if the user on the ground and their is block behind him , then we keep the current location
            }
        }
    }
    //---------------------------------------------
    // move to RIGHT function , 'd' key
    //---------------------------------------------
    void moveRight(Map &map) {
        int map_limit = map.getLength();
        int next = pos + 1;
        if (next <= map_limit) {
            if (is_jumping) {
                if (map.getAbove(next) == '_') pos = next;// here if the block upon him is line and he is jumping, then let me replace it
            } else {
                if (map.getGround(next) == '_') pos = next;
                else if (map.getGround(pos) == '#' && map.getGround(next) == '#') pos = next; // _##_ case and user on the first block , so let him jump on the next block
                else if (map.getGround(pos) == '_' && map.getGround(next) == '#') pos = pos; // _#_ case, if the user on the ground and their is block infront of him , then keep his location(pos) as it is
            }
        }
    }
};

//=========================================
//? Game class
// Controls loop and logic
//=========================================
class Game {
private:
    vector<string> layouts = {
        "__________\n__#___##__",
        "__#_______\n____#_____",
        "___##_#___\n_#__##__#_",
        "__________\n__##_##__#"
    };

    vector<Map> maps; // store all the maps
    Player player;
    int selected_map = 0; // it is the map the user chose
    int our_maps_number = 0;  // to count hom many maps we have

public:

    //---------------------------------------------
    // print all maps
    //---------------------------------------------
    void selectMap() {
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
    void hideCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;

        int map_position = our_maps_number * 5 + 2;
        COORD coord = {0, static_cast<SHORT>(map_position)};
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }


    void start() { //compine everythin together to run the game 
        selectMap();
        hideCursor();

        Map &map = maps[selected_map - 1]; // create object of the class Map, provide the choosen map number as parameter(index for the vector)
        

        while (true) {
            int map_position = our_maps_number * 5 + 2; // so we print the map the player will play on after everything we wrote eariler
            COORD coord = {0, static_cast<SHORT>(map_position)};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            //________________________________________________________

            map.draw(player.pos, player.is_jumping);// draw the map

            // check the user input (if a key was pressed)
            if (_kbhit()) {
                char key = _getch(); // Get the key immediately

                if (key == 'a') player.moveLeft(map);
                else if (key == 'd') player.moveRight(map);
                else if (key == 'w') player.jump(map);
                else if (key == 'q') break;
            }

            // player.updateGravity(map);
            // map.draw(player.pos, player.is_jumping); // moved below input

            player.updateGravity(map);
            Sleep(100);
        }
    }
};

//=========================================
// Main
//=========================================
int main() {
    Game game;
    game.start();
    return 0;
}
