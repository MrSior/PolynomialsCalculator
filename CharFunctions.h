#ifndef CHARFUNCTIONS_H
#define CHARFUNCTIONS_H

inline bool isSign(char i){
    return i == '+' || i == '-' || i == '*' || i == '^';
}

inline bool isLetter(char& i){
    if(i >= 65 && i <= 90) i += 32;
    return i >= 97 && i <= 125;
}

inline bool isNumber(char i){
    return i >= 48 && i <= 57;
}

#endif // CHARFUNCTIONS_H
