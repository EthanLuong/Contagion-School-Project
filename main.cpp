/* Prog2Contagion.cpp

   Program #2: Play the game of Contagion against another person
               This is a variation of Ataxx, a version of which can
               be played online at: http://www.classikgames.com/ataxx.html
   Class: CS 141
   Date: 1/27/2019
   Author: Ethan Luong

   Grading Rubric:
     55% Passes Codio run-time tests (some cases below are split into multiple tests)
          5 Handles both upper and lower case user input
          5 Handles making adjacent move for each player
         10 Handles making jump move for each player
          5 Handles pass move 
          2 Error message and retry when source position does not belong to player
          2 Error message and retry when destination position is not empty
          6 Error message and retry when destination is not one or two squares away
            in horizontal, vertical, or diagonal line
         15 Flips opponent pieces adjacent to move destination
          5 When board is filled correctly identifies winner and exits program

     45% Programming Style:
         10 Meaningful Identifier Names.
         10 Comments, header, and meaningful variable names
         10 Functional Decomposition 
         10 Appropriate data and control structures
          5 Code Layout
*/
#include <iostream>
#include <cstdlib>   // for exit() and abs()

using namespace std;

// The 25 board position variables may be global variables, but no other variables may be global.
char  p1, p2, p3, p4, p5,
      p6, p7, p8, p9,p10,
     p11,p12,p13,p14,p15,
     p16,p17,p18,p19,p20,
     p21,p22,p23,p24,p25;


//-----------------------------------------------------------------------------------------
// Display the game instructions
void displayInstructions()
{
    cout << " \n"
         << "Welcome to the 2-player game of Contagion, where the point of the game is    \n"
         << "to capture as much of the board as possible.  On each move you must enter \n"
         << "the row and column position of one of your current pieces (e.g. a1) and   \n"
         << "the row and column of an empty destination, which must be one or two      \n"
         << "squares away.  Moves can be made horizontally, vertically, or diagonally. \n"
         << " \n"
         << "If the destination is one square away, then an additional piece for you   \n"
         << "is placed in the destination square.  If the destination is two squares   \n"
         << "away (a jump move), then the original piece is moved to that destination. \n"
         << "jumping over a single square or any player's piece.                       \n"
         << " \n"
         << "After a piece has been moved, all opponent pieces adjacent to the         \n"
         << "destination are changed to match the piece of the user making the move.   \n"
         << "Player X moves first.     \n"
         << " \n"
         << "A valid first move, for instance, could be: a1 a2  which since it is just \n"
         << "one square away, would put an additional X on square a2.  Alternatively   \n"
         << "if the first move is:  a1 c3  then since it is two squares away, the piece\n"
         << "currently at a1 would be moved to destination c3.                         \n"
         << endl;
}


//-----------------------------------------------------------------------------------------
// Display the board, using the global board variables
// For reference here are the board row, col and board variable values:
//       1  2  3  4  5
//    ----------------
//  A |  1  2  3  4  5
//  B |  6  7  8  9 10
//  C | 11 12 13 14 15
//  D | 16 17 18 19 20
//  E | 21 22 23 24 25
//
void displayBoard()
{
    cout << "    1   2   3   4   5  \n"
         << "  ---------------------\n"
         << "A | " <<  p1 << " | " <<  p2 << " | " <<  p3 << " | " <<  p4 << " | " <<  p5 << " | A \n"
         << "  |---|---|---|---|---| \n"
         << "B | " <<  p6 << " | " <<  p7 << " | " <<  p8 << " | " <<  p9 << " | " << p10 << " | B \n"
         << "  |---|---|---|---|---| \n"
         << "C | " << p11 << " | " << p12 << " | " << p13 << " | " << p14 << " | " << p15 << " | C \n"
         << "  |---|---|---|---|---| \n"
         << "D | " << p16 << " | " << p17 << " | " << p18 << " | " << p19 << " | " << p20 << " | D \n"
         << "  |---|---|---|---|---| \n"
         << "E | " << p21 << " | " << p22 << " | " << p23 << " | " << p24 << " | " << p25 << " | E \n"
         << "  ---------------------\n"
         << "    1   2   3   4   5  \n"
         << endl;
}

char getValueAt (char rowPos, int colPos) {  //utility function to get value of a grid space
    char gridValue = ' ';
        if (rowPos == 'A') {
            switch(colPos){
                    case  1: gridValue =  p1; break;
                    case  2: gridValue =  p2; break;
                    case  3: gridValue =  p3; break;
                    case  4: gridValue =  p4; break;
                    case  5: gridValue =  p5; break;
            }
        }
        if (rowPos == 'B') {
            switch(colPos){
                    case  1: gridValue =  p6; break;
                    case  2: gridValue =  p7; break;
                    case  3: gridValue =  p8; break;
                    case  4: gridValue =  p9; break;
                    case  5: gridValue =  p10; break;
            }
        }
        if (rowPos == 'C') {
            switch(colPos){
                    case  1: gridValue =  p11; break;
                    case  2: gridValue =  p12; break;
                    case  3: gridValue =  p13; break;
                    case  4: gridValue =  p14; break;
                    case  5: gridValue =  p15; break;
            }
        }
        if (rowPos == 'D') {
            switch(colPos){
                    case  1: gridValue =  p16; break;
                    case  2: gridValue =  p17; break;
                    case  3: gridValue =  p18; break;
                    case  4: gridValue =  p19; break;
                    case  5: gridValue =  p20; break;
            }
        }
        if (rowPos == 'E') {
            switch(colPos){
                    case  1: gridValue =  p21; break;
                    case  2: gridValue =  p22; break;
                    case  3: gridValue =  p23; break;
                    case  4: gridValue =  p24; break;
                    case  5: gridValue =  p25; break;
            }
        }
    return gridValue;
}


void setValueAt(char rowPos, int colPos, char newValue) { //utility function to set value of a grid space
    if (rowPos == 'A') {
            switch(colPos){
                    case  1: p1 = newValue; break;
                    case  2: p2 = newValue; break;
                    case  3: p3 = newValue; break;
                    case  4: p4 = newValue; break;
                    case  5: p5 = newValue; break;
            }
        }
        if (rowPos == 'B') {
            switch(colPos){
                    case  1: p6 = newValue; break;
                    case  2: p7 = newValue; break;
                    case  3: p8 = newValue; break;
                    case  4: p9 = newValue; break;
                    case  5: p10 = newValue; break;
            }
        }
        if (rowPos == 'C') {
            switch(colPos){
                    case  1: p11 = newValue; break;
                    case  2: p12 = newValue; break;
                    case  3: p13 = newValue; break;
                    case  4: p14 = newValue; break;
                    case  5: p15 = newValue; break;
            }
        }
        if (rowPos == 'D') {
            switch(colPos){
                    case  1: p16 = newValue; break;
                    case  2: p17 = newValue; break;
                    case  3: p18 = newValue; break;
                    case  4: p19 = newValue; break;
                    case  5: p20 = newValue; break;
            }
        }
        if (rowPos == 'E') {
            switch(colPos){
                    case  1: p21 = newValue; break;
                    case  2: p22 = newValue; break;
                    case  3: p23 = newValue; break;
                    case  4: p24 = newValue; break;
                    case  5: p25 = newValue; break;
            }
        }
        
}


bool checkValidMove (char currentRow, int currentCol, char destRow, int destCol, char turnChar){ // funciton to check if move is valid for use in if condition
    bool valid = true;
    if (currentRow < 65 || currentRow > 69 || destRow < 65 || destRow > 69 || currentCol < 1 || currentCol > 5 || destCol < 1 || destCol > 5) { //checks if col/row entered is valid
        cout << "***Invalid move. Selected column or row is out of range." << endl;
        valid = false;
    }
    else if (getValueAt(currentRow, currentCol) != turnChar){ //checks if piece selected matches turnChar
        valid = false;
        cout << "*** Invalid move.  Current piece must belong to you. Please retry." << endl;
    }
    else if (getValueAt(destRow, destCol) != ' '){ //Checks if piece selected is empty
        valid = false;
        cout << "*** Invalid move.  Destination must be empty. Please retry.";
    }
    else if (abs(destRow - currentRow) > 2 || abs(destCol - currentCol) > 2 
             || (abs(destRow - currentRow) == 1 && abs(destCol - currentCol) == 2)
             || (abs(destRow - currentRow) == 2 && abs(destCol - currentCol) == 1)){ //checks spaces moved
        cout << "*** Invalid move.  A move must be one or two squares away. Please retry." << endl;
        valid = false;
    }
    
    return valid;
}

void updatePoints (char p, int& oPoints, int& xPoints){ //checks board and updates points
    if (p == 'X') {
        xPoints = xPoints + 1;
    }
    else if ( p == 'O'){
        oPoints = oPoints + 1;
    }
}

void changeValueAt (char row, int col, char turnChar, char checkValue){ //function combines getValueAt and setValueAt for easier use in next function
    if (getValueAt(row, col) == checkValue){
        setValueAt(row, col, turnChar);
    }
}

void changeAdjacent (char row, int col, char turnChar){ //Checks gridspace and changes adjacent tiles
    char checkValue;       //sets character function is looking to change based on current turn character
    if (turnChar == 'X'){
        checkValue = 'O';
    }
    else if (turnChar == 'O'){
        checkValue = 'X';
    }
    
    if (row == 'A'){
        changeValueAt(row + 1, col, turnChar, checkValue);
        changeValueAt(row + 1, col + 1, turnChar, checkValue);
        changeValueAt(row + 1, col - 1, turnChar, checkValue);
        changeValueAt(row, col + 1, turnChar, checkValue);
        changeValueAt(row, col - 1, turnChar, checkValue);
    }
    else if (row == 'E'){
        changeValueAt(row - 1, col, turnChar, checkValue);
        changeValueAt(row - 1, col + 1, turnChar, checkValue);
        changeValueAt(row - 1, col - 1, turnChar, checkValue);
        changeValueAt(row, col + 1, turnChar, checkValue);
        changeValueAt(row, col - 1, turnChar, checkValue);
    }
    else if (col == 1){
        changeValueAt(row, col + 1, turnChar, checkValue);
        changeValueAt(row + 1, col + 1, turnChar, checkValue);
        changeValueAt(row - 1, col + 1, turnChar, checkValue);
        changeValueAt(row + 1, col, turnChar, checkValue);
        changeValueAt(row - 1, col, turnChar, checkValue);
    }
    else if (col == 5){
        changeValueAt(row, col - 1, turnChar, checkValue);
        changeValueAt(row + 1, col - 1, turnChar, checkValue);
        changeValueAt(row - 1, col - 1, turnChar, checkValue);
        changeValueAt(row + 1, col, turnChar, checkValue);
        changeValueAt(row - 1, col, turnChar, checkValue);
    }
    else{
        changeValueAt(row - 1, col, turnChar, checkValue);
        changeValueAt(row - 1, col + 1, turnChar, checkValue);
        changeValueAt(row - 1, col - 1, turnChar, checkValue);
        changeValueAt(row + 1, col, turnChar, checkValue);
        changeValueAt(row + 1, col + 1, turnChar, checkValue);
        changeValueAt(row + 1, col - 1, turnChar, checkValue);
        changeValueAt(row, col + 1, turnChar, checkValue);
        changeValueAt(row, col - 1, turnChar, checkValue);
    }
    
}
    
    
void checkWinner(int oPoints, int xPoints){ //checks winner and displays winner
    if (oPoints > xPoints){
        cout << "O Wins!";
    }
    else if (xPoints > oPoints){
        cout << "X Wins!";
    }
    else{
        cout << "Tie game.";
    }
    
    cout << endl << endl;
}


//-----------------------------------------------------------------------------------------
int main() {
    // Set initial values for the global board variables to all be blank
    p1=p2=p3=p4=p5=p6=p7=p8=p9=p10=p11=p12=p13=p14=p15=p16=p17=p18=p19=p20=p21=p22=p23=p24=p25= ' ';
    // Set corner starting positions
    p1=p25= 'X';
    p5=p21= 'O';
    
    
    // Variables to store user input for current row and column, and destination row and column
    char currentRow;
    int currentCol;
    char destRow;
    int destCol;
    int xPoints;
    int oPoints;
    
    //Variables for each turn
    int turn = 1;
    char turnChar = ' ';
        
    cout << "Welcome to the 2-player game of Contagion. \n"
         << endl;

    // Main loop to play game
    while( true) {
        xPoints = 0;
        oPoints = 0;
        if (turn % 2 == 0){
            turnChar = 'O';
        }
        else{
            turnChar = 'X';
        }
    
        // Display board and handle first character of user input
        displayBoard();
        cout << turn << ". Enter 'i' for instructions, 'x' to exit, or move for " << turnChar << " : ";
        cin >> currentRow;
        currentRow = toupper(currentRow);
        cout << endl;
        
        // Check to see if user input was 'i' for instructions or 'x' to exit
        if( currentRow == 'I') {
            displayInstructions();
            continue;       // Loop back up to retry move
        }
        else if( currentRow == 'X') {
            
            updatePoints(p1, oPoints, xPoints); //Update score
            updatePoints(p2, oPoints, xPoints);
            updatePoints(p3, oPoints, xPoints);
            updatePoints(p4, oPoints, xPoints);
            updatePoints(p5, oPoints, xPoints);
            updatePoints(p6, oPoints, xPoints);
            updatePoints(p7, oPoints, xPoints);
            updatePoints(p8, oPoints, xPoints);
            updatePoints(p9, oPoints, xPoints);
            updatePoints(p10, oPoints, xPoints);
            updatePoints(p11, oPoints, xPoints);
            updatePoints(p12, oPoints, xPoints);
            updatePoints(p13, oPoints, xPoints);
            updatePoints(p14, oPoints, xPoints);
            updatePoints(p15, oPoints, xPoints);
            updatePoints(p16, oPoints, xPoints);
            updatePoints(p17, oPoints, xPoints);
            updatePoints(p18, oPoints, xPoints);
            updatePoints(p19, oPoints, xPoints);
            updatePoints(p20, oPoints, xPoints);
            updatePoints(p21, oPoints, xPoints);
            updatePoints(p22, oPoints, xPoints);
            updatePoints(p23, oPoints, xPoints);
            updatePoints(p24, oPoints, xPoints);
            updatePoints(p25, oPoints, xPoints);
            
            
            displayBoard();
            
            checkWinner(oPoints, xPoints);

            cout << "Exiting program... \n"
                 << endl;
            break;  // Break out of enclosing loop, to exit the game.
        }
        else if (currentRow == 'P'){
            //increment turn and pass
            turn++;
            continue;
        }
        else {
            // User input was not 'i' for instructions or 'x' to exit or 'p' to pass, so a move is being made
            cin >> currentCol;
            cin >> destRow;
            destRow = toupper(destRow);
            cin >> destCol;
        }
        
        //check if move is valid and make the move if it is
        if (checkValidMove(currentRow, currentCol, destRow, destCol, turnChar)){
            if (abs(destRow - currentRow) <= 1 && abs(destCol - currentCol) <= 1){
                setValueAt(destRow, destCol, turnChar);
            }
            else {
                setValueAt(destRow, destCol, turnChar);
                setValueAt(currentRow, currentCol, ' ');
            }
            changeAdjacent(destRow, destCol, turnChar);
            
            
        }
        else {
            continue; //retry if move is invalid
        }
        
        updatePoints(p1, oPoints, xPoints); //Update score
        updatePoints(p2, oPoints, xPoints);
        updatePoints(p3, oPoints, xPoints);
        updatePoints(p4, oPoints, xPoints);
        updatePoints(p5, oPoints, xPoints);
        updatePoints(p6, oPoints, xPoints);
        updatePoints(p7, oPoints, xPoints);
        updatePoints(p8, oPoints, xPoints);
        updatePoints(p9, oPoints, xPoints);
        updatePoints(p10, oPoints, xPoints);
        updatePoints(p11, oPoints, xPoints);
        updatePoints(p12, oPoints, xPoints);
        updatePoints(p13, oPoints, xPoints);
        updatePoints(p14, oPoints, xPoints);
        updatePoints(p15, oPoints, xPoints);
        updatePoints(p16, oPoints, xPoints);
        updatePoints(p17, oPoints, xPoints);
        updatePoints(p18, oPoints, xPoints);
        updatePoints(p19, oPoints, xPoints);
        updatePoints(p20, oPoints, xPoints);
        updatePoints(p21, oPoints, xPoints);
        updatePoints(p22, oPoints, xPoints);
        updatePoints(p23, oPoints, xPoints);
        updatePoints(p24, oPoints, xPoints);
        updatePoints(p25, oPoints, xPoints);
        
        if(xPoints + oPoints == 25){
            displayBoard();
            checkWinner(oPoints, xPoints);
            
            cout << "Exiting program...";
            break;
        }
                        
        turn++; //increment turn
    } //end while( true)

    return 0;
} // end main()

