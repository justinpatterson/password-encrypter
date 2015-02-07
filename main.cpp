//
//  main.cpp
//  GREE_Test
//
//  Created by Justin Patterson on 9/4/14.
//  Copyright (c) 2014 Patterson. All rights reserved.
//

#include <iostream>
#include<string>
#include<map>
using namespace std;

class Keyboard {
    char keys[40] = {
        '1','2','3','4','5','6','7','8','9','0',
        'q','w','e','r','t','y','u','i','o','p',
        'a','s','d','f','g','h','j','k','l',';',
        'z','x','c','v','b','n','m',',','.','/'
    };
    int lineLength = 10;
    int rowHeight = 4;
    int offsetValue = 1;
    int maxLen = 40;
    enum KeySetup {Normal,Horizontal,Vertical,Offset};
	KeySetup keyDirection = Normal;
    void confirmChange();
    void makeMap();
    
    map<char,char> keyMap;
    
    public:
        Keyboard();
        char currKeys[40];
        char getElement(int);
        void setOffset(int);
        void outputKeyboard();
        void setDirection(int);
        void setFlip(int);
        string convert(string);
    };

    Keyboard::Keyboard(){
        strncpy(currKeys, keys, 40);
    }
    char Keyboard::getElement(int i) {
        char returnKey;
        if(i<maxLen){
            if(i<0)
                returnKey = '-';
            else
                returnKey = currKeys[i];
        }
        else
            returnKey = '+';
        return returnKey;
    }

    void Keyboard::setOffset(int i) {
        keyDirection = Offset;
        offsetValue = -i;
        confirmChange();
    }

    void Keyboard::confirmChange(){
        int currRow = 0;
        char nextKeys[40];
        
        for(int k = 0; k<maxLen; k++){
            int nextVal = k;
            switch(keyDirection){
                case Normal:
                    nextVal = k;
                    break;
                case Horizontal:
                    nextVal = (currRow * lineLength) + ((lineLength-1) - (k%lineLength));
                    break;
                case Vertical:
                    nextVal = ((rowHeight - currRow - 1) * lineLength) + (k%lineLength);
                    break;
                case Offset:
                    nextVal = k+offsetValue;
                    if(nextVal>=maxLen) nextVal = (nextVal - maxLen);
                    else if (nextVal<0) nextVal = (maxLen + nextVal);
                    break;
            }
            char outputKey = getElement(nextVal);
            nextKeys[k] = outputKey;
            
            if((k+1)%lineLength==0) {
                if(k!=0){
                    currRow++;
                }
            }
        }
        strncpy(currKeys, nextKeys, 40);
    }

    void Keyboard::setDirection(int i) {
        if(i==0) keyDirection = Normal;
        else if(i==1) keyDirection = Horizontal;
        else if(i==2) keyDirection = Vertical;
        else if(i==3) keyDirection = Offset;
    }

    void Keyboard::setFlip(int i){
        if(i==0) keyDirection = Horizontal;
        else if(i==1) keyDirection = Vertical;
        confirmChange();
    }

    void Keyboard::outputKeyboard(){
        for(int k = 0; k<maxLen; k++){
            char outputKey = getElement(k);
            cout<<outputKey;
            if((k+1)%lineLength==0) {
                if(k!=0){
                    cout<<"\n";
                }
            }
        }
    }

    void Keyboard::makeMap(){
        for(int k = 0; k < maxLen; k++){
            keyMap[keys[k]] = currKeys[k];
        }
    }

    string Keyboard::convert(string s){
        makeMap();
        
        for(int i = 0; i < s.length(); i++){
            s[i] = keyMap.find(s[i])->second;
        }
        return s;
    }

int main(int argc, const char * argv[])
{
    Keyboard k;
    string s;
    cout << "Please input a series of commands to be conducted in order. \n(H = Horizontal Flip, V = Vertical Flip, O = Offset by Integer\n";
    cin >> s;
    cout << "\nYou have typed in: \n" << s << "\n";
    
    cout<<"START KEYBOARD\n";
    k.outputKeyboard();
    cout<<"\n";
    
    for(int i = 0; i < s.length(); i++){
        s[i] = toupper(s[i]);
        if(s[i]=='H'){
            k.setFlip(0);
        }
        else if(s[i]=='V'){
            k.setFlip(1);
        
        }
        else if(s[i]=='L'){
            int offInt;
            offInt = 1;
            k.setOffset(offInt);
        }
        else if(s[i]=='R'){
            int offInt;
            offInt=-1;
            k.setOffset(offInt);
        }
        else {
            cout<<"unknown letter\n";
        }
    }
    
    cout<<"\nEND KEYBOARD:\n";
    
    k.outputKeyboard();
    
    cout<<"\n\nNow, type and submit any phrase to see what it mutates to with the new keyboard.\n";
    string jumbleString;
    cin>>jumbleString;
    cout<<jumbleString<<" = "<<k.convert(jumbleString)<<"\n";
    
    
    return 0;
}

