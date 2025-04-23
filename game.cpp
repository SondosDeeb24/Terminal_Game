//====================================================================================
//? working code
// here's the Features accomplished so far: 

// solved flickring pproblem
// displaying the maps to user and allowing him to choose which to play on
//* set up for collision logic (now student can't move forward when he face block)
//===================================================================================

#include <iostream>
#include <conio.h>
#include <windows.h> // For SetConsoleCursorPosition
#include <string>

using namespace std;

//================================================================================

// Maps set I created for user to choose from
const int our_maps_number = 2;
string maps[our_maps_number] = {
    "__________\n__#____#__", 
    "__________\n____#_____"
};


//======================================================================================================
//? draw the map and insert the player @ at the correct position
//======================================================================================================
void draw_map(int map_number, int &player_pos, int &player_index) { // the & to update the real value for each one of them back in main function
    // player_pos is the new position that player should move to 
    // player_index it the current location for the player on the map

    string selected_map = (map_number == 1) ? maps[0] : maps[1];  // to allow player to choose the map
    
    // split the string into two lines
    size_t newline_pos = selected_map.find('\n');
    string line1 = selected_map.substr(0, newline_pos);
    string line2 = selected_map.substr(newline_pos + 1);// I added one because I don't want the newline sign to be included

    //____________________________________________________________________________________________
    // logic to detect the collision with the blocks
    if (line2[player_pos] == '_') {
        line2[player_pos] = '@';
        player_index = player_pos;// update the current locations for the player on the map

    } else if (line2[player_pos] == '#') {//if next location is block , then stay on the current location
        line2[player_index] = '@';
        player_pos = player_index;// update player_pos(which is move) to be the current index
    }

    //____________________________________________________________________________________________
    // Print the modified map
    cout << line1 << endl;
    cout << line2 << endl;
}

//____________________________________________________________________________________________
// Prevent flickering: move cursor to (0, 2) to redraw the map every time player moves
void starting_point() {
    int map_position= our_maps_number * 5 + 2 ; // each map to be printed needs about 5 lines and finally we need 2 lines to print the map choosing question
    COORD coord = {0, static_cast<SHORT>(map_position)}; // position to print the map
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//================================================================================
//================================================================================

int main() {
    int move = 0;
    int map_long = 9;

    // print all the maps, so player can choose between them
    for (int i = 0; i < our_maps_number; i++) {
        cout << "\nMap " << i + 1 << endl;
        cout << maps[i] << endl;
    }
    // ____________________________________________________________________________________________
    int player_choosed;
    cout << "\nYou would like to choose map 1 or 2? ";
    cin >> player_choosed;
    // ____________________________________________________________________________________________
    // Hide blinking cursor for a cleaner game display
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    //------------------------------------------------------------

    int player_index = 0;// to detect where is the player

    // the game main loop
    while (true) {
        if (move < 0) move = 0;
        if (move > map_long) move = map_long;

        starting_point(); 
        draw_map(player_choosed, move, player_index);

        if (_kbhit()) {
            char key = _getch();
            if (key == 'd') move++; // clicking d mean player moves to right side
            else if (key == 'a') move--; // clicking a means palyer moves to left side
            else if (key == 'q') break;
        }

        Sleep(100);
    }

    return 0;
}

