#pragma once
#include <iostream>
#include <string.h>

class String
{
private:
    int length;
    char *tab;

protected:
    friend std::ostream &operator<<(std::ostream &os, String s);
    friend std::istream &operator>>(std::istream &is, String &s);

public:
    String();
    String(const char *s);
    String(int size);
    String(const String &other);
    String &operator=(const String &other);
    String &operator=(char *s);
    String &operator+(char c);
    String &operator+(char *s);
    String &operator+(const String &other);
    String &operator+=(char *s);
    String &operator+=(const String &other);
    String subStr(int begin, char separator);
    bool isEqual(String &other);
    bool isEqual(const char* s);
    bool isCharInsideString(char chr);
    int getLength();
    bool isANumber();
    int strToI();
    void setTabIndex(int i, char c);
    void setLength(int newLength);
    char getTabIndex(int index);
    ~String();
};