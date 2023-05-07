#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>
using namespace std;

class Piece{
    bool isKing;
    bool isWhite;
    bool isVoid;
    int X;
    int Y;

public:

    Piece(bool k , bool w, int x, int y){
        this->isKing = k;
        this->isWhite = w;
        this->X = x;
        this->Y = y;
        this->isVoid = false;
    }

    explicit Piece(bool v){
        this->isVoid = v;
        this->isKing = false;
        this->isWhite = false;
        this->X = 0;
        this->Y = 0;
    }

    void setKing(bool k) {
        this -> isKing = k;
    }

    void setVoid(bool v){
        this -> isVoid = v;
    }

    static void takeMove(Piece arr[8][8], int pos1, int pos2, int move1, int move2){
        Piece temp = arr[pos1][pos2];
        arr[pos1][pos2] = arr[move1][move2];
        arr[move1][move2] = temp;
        arr[pos1][pos2].X = move1;
        arr[pos1][pos2].Y = move2;
        arr[move1][move2].X = pos1;
        arr[move1][move2].Y = pos2;
        if(move1 == 7 || move1 == 0) {
            arr[move1][move2].setKing(true);
        }
    }

    bool getVoid() const{
        return isVoid;
    }

    friend void printBoard(Piece arr[8][8]);
    friend int validateMove(Piece arr[8][8], int player, int pos1, int pos2, int move1, int move2);
    friend int possiblePiece(Piece arr[8][8], int player, int pos1, int pos2);
    friend int* autoGame(Piece arr[8][8], int player, bool kill, bool after, int pos1, int pos2);
};

static Piece voidPiece(true);

void printBoard(Piece arr[8][8]);
int possiblePiece(Piece arr[8][8], int player, int pos1, int pos2);
int validateMove(Piece arr[8][8], int player, int pos1, int pos2, int move1, int move2);
int* afterMove(Piece arr[8][8], int player, bool kill, int pos1, int pos2);
int numFixer(int number);
void game(Piece arr[8][8]);

int main(){
    Piece b1(false, false, 0, 1);
    Piece b2(false, false, 0, 3);
    Piece b3(false, false, 0, 5);
    Piece b4(false, false, 0, 7);
    Piece b5(false, false, 1, 0);
    Piece b6(false, false, 1, 2);
    Piece b7(false, false, 1, 4);
    Piece b8(false, false, 1, 6);
    Piece b9(false, false, 2, 1);
    Piece b10(false, false, 2, 3);
    Piece b11(false, false, 2, 5);
    Piece b12(false, false, 2, 7);
    Piece w1(false, true, 7, 0);
    Piece w2(false, true, 7, 2);
    Piece w3(false, true, 7, 4);
    Piece w4(false, true, 7, 6);
    Piece w5(false, true, 6, 1);
    Piece w6(false, true, 6, 3);
    Piece w7(false, true, 6, 5);
    Piece w8(false, true, 6, 7);
    Piece w9(false, true, 5, 0);
    Piece w10(false, true, 5, 2);
    Piece w11(false, true, 5, 4);
    Piece w12(false, true, 5, 6);

    Piece board[8][8] = {
            voidPiece, b1, voidPiece, b2, voidPiece, b3, voidPiece, b4,
            b5, voidPiece, b6, voidPiece, b7, voidPiece, b8, voidPiece,
            voidPiece, b9, voidPiece, b10, voidPiece, b11, voidPiece, b12,
            voidPiece, voidPiece, voidPiece, voidPiece, voidPiece, voidPiece, voidPiece, voidPiece,
            voidPiece, voidPiece, voidPiece, voidPiece, voidPiece, voidPiece, voidPiece, voidPiece,
            w9, voidPiece, w10, voidPiece, w11, voidPiece, w12, voidPiece,
            voidPiece, w5, voidPiece, w6, voidPiece, w7, voidPiece, w8,
            w1, voidPiece , w2, voidPiece, w3, voidPiece, w4, voidPiece
    };

    printBoard(board);
    game(board);
    cout<<endl;
    system("pause");
    return 0;
}

int numFixer(int number){
    while(!(cin>>number)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Enter a valid number:";
    }
    return number;
}

void printBoard(Piece arr[8][8]) {
    system("cls");
    int number = 1;
    cout<<endl<<"     1   2   3   4   5   6   7   8"<<endl;
    for(int i = 0; i < 8; i++) {
        if(i == 0) {
            cout<<"   ---------------------------------"<<endl;
        } else {
            cout<<"   |---+---+---+---+---+---+---+---|"<<endl;
        }
        for(int j = 0; j < 8; j++) {
            if (j == 0) {
                cout<<" "<<number<<" |";
            } else {
                cout<<"|";
            }
            if(arr[i][j].isVoid) {
                cout<<"   ";
            } else if(arr[i][j].isWhite) {
                if(!arr[i][j].isKing) {
                    cout<<" w ";
                } else {
                    cout<<" W ";
                }
            } else {
                if(!arr[i][j].isKing) {
                    cout<<" b ";
                } else {
                    cout<<" B ";
                }
            }
            if(j == 7) {
                cout<<"|";
            }
        }
        cout<<endl;
        number ++;
        if(i == 7) {
            cout<<"   ---------------------------------";
        }
    }
}

int possiblePiece(Piece arr[8][8], int player, int pos1, int pos2) {
    if (player == 2) {
        if (!arr[pos1][pos2].isWhite && !arr[pos1][pos2].isVoid) {
            return 1;
        } else if (arr[pos1][pos2].isKing) {
            if(arr[pos1 + 1][pos2 + 1].isWhite && arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid && !arr[pos1 + 1][pos2 - 1].isVoid && arr[pos1 - 1][pos2 + 1].isWhite && arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 - 1][pos2 - 1].isVoid) {
                return 2;
            } else if (!arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid && !arr[pos1 + 1][pos2 - 1].isVoid && !arr[pos1 + 2][pos2 + 2].isWhite && !arr[pos1 + 2][pos2 - 2].isWhite && !arr[pos1 + 2][pos2 + 2].isVoid && !arr[pos1 + 2][pos2 - 2].isVoid && !arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 - 1][pos2 - 1].isVoid && !arr[pos1 - 2][pos2 + 2].isWhite && !arr[pos1 - 2][pos2 - 2].isWhite && !arr[pos1 - 2][pos2 + 2].isVoid && !arr[pos1 - 2][pos2 - 2].isVoid) {
                return 2;
            }
        } else if(arr[pos1 - 1][pos2 + 1].isWhite && arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 - 1][pos2 - 1].isVoid) {
            return 2;
        } else if (!arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 - 1][pos2 - 1].isVoid && !arr[pos1 - 2][pos2 + 2].isWhite && !arr[pos1 - 2][pos2 - 2].isWhite && !arr[pos1 - 2][pos2 + 2].isVoid && !arr[pos1 - 2][pos2 - 2].isVoid) {
            return 2;
        } else {
            return 0;
        }
    } else if (player == 1) {
        if (arr[pos1][pos2].isWhite && !arr[pos1][pos2].isVoid) {
            return 1;
        } else if (arr[pos1][pos2].isKing) {
            if (!arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid && !arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && !arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid) {
                return 2;
            } else if (arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid && arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && arr[pos1 - 2][pos2 - 2].isWhite && !arr[pos1 - 2][pos2 - 2].isVoid && arr[pos1 - 2][pos2 + 2].isWhite && !arr[pos1 - 2][pos2 + 2].isVoid && arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid && arr[pos1 + 2][pos2 - 2].isWhite && !arr[pos1 + 2][pos2 - 2].isVoid && arr[pos1 + 2][pos2 + 2].isWhite && !arr[pos1 + 2][pos2 + 2].isVoid) {
                return 2;
            }
        } else if (!arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && !arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid) {
            return 2;
        } else if (arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid && arr[pos1 + 2][pos2 - 2].isWhite && !arr[pos1 + 2][pos2 - 2].isVoid && arr[pos1 + 2][pos2 + 2].isWhite && !arr[pos1 + 2][pos2 + 2].isVoid) {
            return 2;
        } else {
            return 0;
        }
    }
}

int validateMove(Piece arr[8][8], int player, int pos1, int pos2, int move1, int move2) {
    bool valid = false, side;
    if (player == 2 || arr[pos1][pos2].isKing) {
        if (!arr[move1][move2].isVoid) {
            return 1;
        } else {
            for (int i = pos1 - 1, j = pos2 + 1; i > 0, j < 8; i--, j++) {
                if (move1 == i && move2 == j) {
                    valid = true;
                    side = 0;
                    break;
                }
            }
            for (int i = pos1 - 1, j = pos2 - 1; i > 0, j >= 0; i--, j--) {
                if (move1 == i && move2 == j) {
                    valid = true;
                    side = 1;
                    break;
                }
            }
        }
        if (valid) {
            if (side == 0) {
                if(arr[pos1][pos2].isKing && player == 1) {
                    if(move1 < pos1 - 2 && move2 > pos2 + 2) {
                        return 3;
                    } else if (move1 == pos1 - 2 && move2 == pos2 + 2) {
                        if(!arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid) {
                            return 4;
                        } else if (arr[pos1 - 1][pos2 + 1].isVoid) {
                            return 3;
                        } else if (arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid) {
                            arr[pos1 - 1][pos2 + 1].setVoid(true);
                            return 5;
                        }
                    } else {
                        return 0;
                    }
                } else if(move1 < pos1 - 2 && move2 > pos2 + 2) {
                    return 3;
                } else if (move1 == pos1 - 2 && move2 == pos2 + 2) {
                    if(arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid) {
                        return 4;
                    } else if (arr[pos1 - 1][pos2 + 1].isVoid) {
                        return 3;
                    } else if (!arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid) {
                        arr[pos1 - 1][pos2 + 1].setVoid(true);
                        return 5;
                    }
                } else {
                    return 0;
                }
            } else if (side == 1) {
                if(arr[pos1][pos2].isKing && player == 1) {
                    if(move1 < pos1 - 2 && move2 < pos2 - 2) {
                        return 3;
                    } else if (move1 == pos1 - 2 && move2 == pos2 - 2) {
                        if(!arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid) {
                            return 4;
                        } else if (arr[pos1 - 1][pos2 - 1].isVoid) {
                            return 3;
                        } else if (arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid) {
                            arr[pos1 - 1][pos2 - 1].setVoid(true);
                            return 5;
                        }
                    } else {
                        return 0;
                    }
                } else if(move1 < pos1 - 2 && move2 < pos2 - 2) {
                    return 3;
                } else if (move1 == pos1 - 2 && move2 == pos2 - 2) {
                    if(arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid) {
                        return 4;
                    } else if (arr[pos1 - 1][pos2 - 1].isVoid) {
                        return 3;
                    } else if (!arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid) {
                        arr[pos1 - 1][pos2 - 1].setVoid(true);
                        return 5;
                    }
                } else {
                    return 0;
                }
            }
        } else if (!arr[pos1][pos2].isKing) {
            return 2;
        }
    } if (player == 1 || arr[pos1][pos2].isKing) {
        if (!arr[move1][move2].isVoid) {
            return 1;
        } else {
            for (int i = pos1 + 1, j = pos2 + 1; i < 8, j < 8; i++, j++) {
                if (move1 == i && move2 == j) {
                    valid = true;
                    side = 0;
                    break;
                }
            }
            for (int i = pos1 + 1, j = pos2 - 1; i < 8, j >= 0; i++, j--) {
                if (move1 == i && move2 == j) {
                    valid = true;
                    side = 1;
                    break;
                }
            }
        }
        if (valid) {
            if (side == 0) {
                if (arr[pos1][pos2].isKing && player == 2) {
                    if(move1 > pos1 + 2 && move2 > pos2 + 2) {
                        return 3;
                    } else if (move1 == pos1 + 2 && move2 == pos2 + 2) {
                        if(arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid) {
                            return 4;
                        } else if (arr[pos1 + 1][pos2 + 1].isVoid) {
                            return 3;
                        } else if (!arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid) {
                            arr[pos1 + 1][pos2 + 1].setVoid(true);
                            return 5;
                        }
                    } else {
                        return 0;
                    }
                } else if(move1 > pos1 + 2 && move2 > pos2 + 2) {
                    return 3;
                } else if (move1 == pos1 + 2 && move2 == pos2 + 2) {
                    if(!arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid) {
                        return 4;
                    } else if (arr[pos1 + 1][pos2 + 1].isVoid) {
                        return 3;
                    } else if (arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid) {
                        arr[pos1 + 1][pos2 + 1].setVoid(true);
                        return 5;
                    }
                } else {
                    return 0;
                }
            } else if (side == 1) {
                if (arr[pos1][pos2].isKing && player == 2) {
                    if(move1 > pos1 + 2 && move2 < pos2 - 2) {
                        return 3;
                    } else if (move1 == pos1 + 2 && move2 == pos2 - 2) {
                        if(arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid) {
                            return 4;
                        } else if (arr[pos1 + 1][pos2 - 1].isVoid) {
                            return 3;
                        } else if (!arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid) {
                            arr[pos1 + 1][pos2 - 1].setVoid(true);
                            return 5;
                        }
                    } else {
                        return 0;
                    }
                } else if(move1 > pos1 + 2 && move2 < pos2 - 2) {
                    return 3;
                } else if (move1 == pos1 + 2 && move2 == pos2 - 2) {
                    if(!arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid) {
                        return 4;
                    } else if (arr[pos1 + 1][pos2 - 1].isVoid) {
                        return 3;
                    } else if (arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid) {
                        arr[pos1 + 1][pos2 - 1].setVoid(true);
                        return 5;
                    }
                } else {
                    return 0;
                }
            }
        } else if (!arr[pos1][pos2].isKing) {
            return 2;
        }
    }
}

int* autoGame(Piece arr[8][8], int player, bool kill, bool after, int pos1, int pos2) {
    static int returnValues[3] = {0, 0, 0};
    int pieceCount = 0, immovableCount = 0;
    if (!kill && after) {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                 if (player == 1) {
                     if (arr[i][j].isWhite) {
                         pieceCount++;
                         if (arr[i][j].isKing) {
                             if(arr[pos1 + 1][pos2 + 1].isWhite && arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid && !arr[pos1 + 1][pos2 - 1].isVoid && arr[pos1 - 1][pos2 + 1].isWhite && arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 - 1][pos2 - 1].isVoid) {
                                 immovableCount++;
                             } else if (!arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid && !arr[pos1 + 1][pos2 - 1].isVoid && !arr[pos1 + 2][pos2 + 2].isWhite && !arr[pos1 + 2][pos2 - 2].isWhite && !arr[pos1 + 2][pos2 + 2].isVoid && !arr[pos1 + 2][pos2 - 2].isVoid && !arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 - 1][pos2 - 1].isVoid && !arr[pos1 - 2][pos2 + 2].isWhite && !arr[pos1 - 2][pos2 - 2].isWhite && !arr[pos1 - 2][pos2 + 2].isVoid && !arr[pos1 - 2][pos2 - 2].isVoid) {
                                 immovableCount++;
                             }
                         } else if(arr[pos1 - 1][pos2 + 1].isWhite && arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 - 1][pos2 - 1].isVoid) {
                             immovableCount++;
                         } else if (!arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 - 1][pos2 - 1].isVoid && !arr[pos1 - 2][pos2 + 2].isWhite && !arr[pos1 - 2][pos2 - 2].isWhite && !arr[pos1 - 2][pos2 + 2].isVoid && !arr[pos1 - 2][pos2 - 2].isVoid) {
                             immovableCount++;
                         }
                     }
                 } else {
                     if (!arr[i][j].isWhite) {
                         pieceCount++;
                         if (arr[i][j].isKing) {
                             if (!arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid && !arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && !arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && !arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid) {
                                 immovableCount++;
                             } else if (arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid && arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && arr[pos1 - 2][pos2 - 2].isWhite && !arr[pos1 - 2][pos2 - 2].isVoid && arr[pos1 - 2][pos2 + 2].isWhite && !arr[pos1 - 2][pos2 + 2].isVoid && arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid && arr[pos1 + 2][pos2 - 2].isWhite && !arr[pos1 + 2][pos2 - 2].isVoid && arr[pos1 + 2][pos2 + 2].isWhite && !arr[pos1 + 2][pos2 + 2].isVoid) {
                                 immovableCount++;
                             }
                         } else if (!arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && !arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid) {
                             immovableCount++;
                         } else if (arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid && arr[pos1 + 2][pos2 - 2].isWhite && !arr[pos1 + 2][pos2 - 2].isVoid && arr[pos1 + 2][pos2 + 2].isWhite && !arr[pos1 + 2][pos2 + 2].isVoid) {
                             immovableCount ++;
                         }
                     }
                 }
            }
        }
        if (pieceCount == immovableCount) {
            returnValues[0] = 2;
            return returnValues;
        } else {
            returnValues[0] = 0;
            return returnValues;
        }
    } else {
        int option;
        if (player == 2) {
            if (!arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid &&
                !arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && pos1 - 2 >= 0 && pos2 - 2 >= 0 &&
                pos2 + 2 < 8 && arr[pos1 - 2][pos2 - 2].isVoid && arr[pos1 - 2][pos2 + 2].isVoid) {
                cout << "\nChoose Move" << endl << endl;
                cout << "1. Left Diagonal\n2. Right Diagonal" << endl;
                cout << "\nChoice: ";
                cin >> option;
                if (option == 1) {
                    cout << "\nTaking left diagonal move....";
                    usleep(1500000);
                    arr[pos1 - 1][pos2 - 1].setVoid(true);
                    Piece::takeMove(arr, pos1, pos2, pos1 - 2, pos2 - 2);
                    returnValues[0] = 1;
                    returnValues[1] = pos1 - 2;
                    returnValues[2] = pos2 - 2;
                    return returnValues;
                } else if (option == 2) {
                    cout << "\nTaking right diagonal move....";
                    usleep(1500000);
                    arr[pos1 - 1][pos2 + 1].setVoid(true);
                    Piece::takeMove(arr, pos1, pos2, pos1 - 2, pos2 + 2);
                    returnValues[0] = 1;
                    returnValues[1] = pos1 - 2;
                    returnValues[2] = pos2 + 2;
                    return returnValues;
                }
            } else if (!arr[pos1 - 1][pos2 - 1].isWhite && !arr[pos1 - 1][pos2 - 1].isVoid && pos1 - 2 >= 0 &&
                       pos2 - 2 >= 0 && arr[pos1 - 2][pos2 - 2].isVoid) {
                cout << "\nTaking left diagonal move....";
                usleep(1500000);
                arr[pos1 - 1][pos2 - 1].setVoid(true);
                Piece::takeMove(arr, pos1, pos2, pos1 - 2, pos2 - 2);
                returnValues[0] = 1;
                returnValues[1] = pos1 - 2;
                returnValues[2] = pos2 - 2;
                return returnValues;
            } else if (!arr[pos1 - 1][pos2 + 1].isWhite && !arr[pos1 - 1][pos2 + 1].isVoid && pos1 - 2 >= 0 &&
                       pos2 + 2 < 8 && arr[pos1 - 2][pos2 + 2].isVoid) {
                cout << "\nTaking right diagonal move....";
                usleep(1500000);
                arr[pos1 - 1][pos2 + 1].setVoid(true);
                Piece::takeMove(arr, pos1, pos2, pos1 - 2, pos2 + 2);
                returnValues[0] = 1;
                returnValues[1] = pos1 - 2;
                returnValues[2] = pos2 + 2;
                return returnValues;
            } else {
                returnValues[0] = 0;
                return returnValues;
            }
        } else if (player == 1) {
            if (arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && arr[pos1 + 1][pos2 + 1].isWhite &&
                !arr[pos1 + 1][pos2 + 1].isVoid && pos1 + 2 < 8 && pos2 - 2 >= 0 && pos2 + 2 < 8 &&
                arr[pos1 + 2][pos2 - 2].isVoid && arr[pos1 + 2][pos2 + 2].isVoid) {
                cout << "\nChoose Move" << endl << endl;
                cout << "1. Left Diagonal\n2. Right Diagonal" << endl;
                cout << "\nChoice: ";
                cin >> option;
                if (option == 1) {
                    cout << "\nTaking left diagonal move....";
                    usleep(1500000);
                    arr[pos1 + 1][pos2 - 1].setVoid(true);
                    Piece::takeMove(arr, pos1, pos2, pos1 + 2, pos2 - 2);
                    returnValues[0] = 1;
                    returnValues[1] = pos1 + 2;
                    returnValues[2] = pos2 - 2;
                    return returnValues;
                } else if (option == 2) {
                    cout << "\nTaking right diagonal move....";
                    usleep(1500000);
                    arr[pos1 + 1][pos2 + 1].setVoid(true);
                    Piece::takeMove(arr, pos1, pos2, pos1 + 2, pos2 + 2);
                    returnValues[0] = 1;
                    returnValues[1] = pos1 + 2;
                    returnValues[2] = pos2 + 2;
                    return returnValues;
                }
            } else if (arr[pos1 + 1][pos2 - 1].isWhite && !arr[pos1 + 1][pos2 - 1].isVoid && pos1 + 2 < 8 &&
                       pos2 - 2 >= 0 && arr[pos1 + 2][pos2 - 2].isVoid) {
                cout << "\nTaking left diagonal move....";
                usleep(1500000);
                arr[pos1 + 1][pos2 - 1].setVoid(true);
                Piece::takeMove(arr, pos1, pos2, pos1 + 2, pos2 - 2);
                returnValues[0] = 1;
                returnValues[1] = pos1 + 2;
                returnValues[2] = pos2 - 2;
                return returnValues;
            } else if (arr[pos1 + 1][pos2 + 1].isWhite && !arr[pos1 + 1][pos2 + 1].isVoid && pos1 + 2 < 8 &&
                       pos2 + 2 < 8 && arr[pos1 + 2][pos2 + 2].isVoid) {
                cout << "\nTaking right diagonal move....";
                usleep(1500000);
                arr[pos1 + 1][pos2 + 1].setVoid(true);
                Piece::takeMove(arr, pos1, pos2, pos1 + 2, pos2 + 2);
                returnValues[0] = 1;
                returnValues[1] = pos1 + 2;
                returnValues[2] = pos2 + 2;
                return returnValues;
            } else {
                returnValues[0] = 0;
                return returnValues;
            }
        }
    }
}

void game(Piece arr[8][8]){
    string player = "Player 1";
    int playerNumber = 1, count = 0, death1 = 0, death2 = 0;
    while(true) {
        int piece = 0, move = 0, pos1 = 0, pos2 = 0, move1 = 0, move2 = 0;
        bool isMove = false, isPiece = false, kill = false, after = false;
        bool automove = false, change = false;
        cout << "\n\n7 - change piece";
        cout << endl << endl << player << endl;
        while (!isPiece) {
            cout << "\nChoose piece:";
            piece = numFixer(piece);
            pos1 = piece / 10;
            pos2 = piece % 10;
            pos1--;
            pos2--;
            if (pos1 > 7 || pos1 < 0 || pos2 > 7 || pos2 < 0) {
                cout << "Enter a valid position!"<<endl;
                continue;
            } else if (arr[pos1][pos2].getVoid()) {
                cout << "No piece at location!"<<endl;
                continue;
            }
            int code = possiblePiece(arr, playerNumber, pos1, pos2);
            switch (code) {
                case 1:
                    cout<<"Can't choose opponent piece!"<<endl;
                    break;
                case 2:
                    cout<<"Piece can't move!"<<endl;
                    break;
                default:
                    isPiece = true;
                    break;
            }
        }
        while(true) {
            int *autoCode = autoGame(arr, playerNumber, kill, after, pos1, pos2);
            if (autoCode[0] == 0) {
                break;
            } else if (autoCode[0] == 1) {
                automove = true;
                pos1 = autoCode[1];
                pos2 = autoCode[2];
                printBoard(arr);
            }
        }
        if(automove) {
            if(count % 2 == 0) {
                player = "Player 2";
                playerNumber = 2;
            } else if(count % 2 == 1) {
                player = "Player 1";
                playerNumber = 1;
            }
            count ++;
            continue;
        }
        while (!isMove) {
            cout << "Choose move:";
            move = numFixer(move);
            if(move == 7) {
                change = true;
                break;
            }
            move1 = move / 10;
            move2 = move % 10;
            move1--;
            move2--;
            if (move1 > 7 || move1 < 0 || move2 > 7 || move2 < 0) {
                cout << "Enter a valid position!"<<endl<<endl;
                continue;
            }
            int code = validateMove(arr, playerNumber, pos1, pos2, move1, move2);
            switch (code) {
                case 1:
                    cout<<"Piece present at location!"<<endl<<endl;
                    break;
                case 2:
                    cout<<"You can only move diagonally forward!"<<endl<<endl;
                    break;
                case 3:
                    cout<<"Can't move more than 1 square at a time!"<<endl<<endl;
                    break;
                case 4:
                    cout<<"Can't jump over your own piece"<<endl<<endl;
                    break;
                case 5:
                    kill = true;
                    if (playerNumber == 1) {
                        death2++;
                    } else {
                        death1++;
                    }
                default:
                    Piece::takeMove(arr, pos1, pos2, move1, move2);
                    isMove = true;
                    break;
            }
        }
        if(change) {
            system("cls");
            printBoard(arr);
            continue;
        }
        printBoard(arr);
        if (death1 == 12) {
            cout<<"\n\nPlayer 2 wins!";
            break;
        } else if (death2 == 12) {
            cout<<"\n\nPlayer 1 wins!";
            break;
        }
        after = true;
        while(true){
            int* code = autoGame(arr, playerNumber, kill, after, move1 ,move2);
            if(code[0] == 0) {
                break;
            } else if (code[0] == 1){
                move1 = code[1];
                move2 = code[2];
                printBoard(arr);
            } else {
                if (playerNumber == 1) {
                    cout<<"\n\nPlayer 1 wins!";
                    return;
                } else if (playerNumber == 2) {
                    cout<<"\n\nPlayer 2 wins!";
                    return;
                }
            }
        }
        if(count % 2 == 0) {
            player = "Player 2";
            playerNumber = 2;
        } else if(count % 2 == 1) {
            player = "Player 1";
            playerNumber = 1;
        }
        count ++;
    }
}