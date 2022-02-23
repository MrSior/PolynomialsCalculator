#ifndef CHARFUNCTIONS_H
#define CHARFUNCTIONS_H

inline bool isSign(char i){
    return i == '+' || i == '-' || i == '*' || i == '^';
}

inline bool isLetter(char i){
    return i >= 97 && i <= 125;
}

inline bool isNumber(char i){
    return i >= 48 && i <= 57;
}

#endif // CHARFUNCTIONS_H
