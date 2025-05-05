#include "String.h"
#define BUFFERSIZE 512
#define DELIMITER '\n'

std::ostream &operator<<(std::ostream &os, String s)
{
    os << s.tab;
    return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    char buff[BUFFERSIZE];
    is.getline(buff, BUFFERSIZE);
    int buffInd = 0;
    s.length = 0;
    while (buff[buffInd] != '\0')
    {
        s.length++;
        buffInd++;
    }
    s.tab = new char[s.length +1];
    int i = 0;
    while (i < s.length)
    {
        s.tab[i] = buff[i];
        i++;
    }
    s.tab[i] = '\0';
    return is;
}

String::String() : length(0), tab(nullptr) {}

String::String(const char *s) : length(strlen(s)), tab((char*)s) {}

String::String(int size) : length(size), tab(new char[size]) {}

String::String(const String &other) : length(other.length), tab(other.tab) {}

String &String::operator=(const String &other)
{
    String temp;
    temp.tab = this->tab;
    this->length = other.length;
    this->tab = other.tab;
    delete[] temp.tab;
    return *this;
}

String &String::operator=(char *s)
{
    String newString;
    newString.length = strlen(s);
    newString.tab = s;
    return *this;
}

String &String::operator+(char c)
{
    length++;
    char *newTab = new char[length];

    for (int i = 0; i < length - 1; i++)
    {
        newTab[i] = tab[i];
    }
    newTab[length - 1] = c;
    delete[] tab;
    tab = newTab;
    return *this;
}

String &String::operator+(char *s)
{
    int prevLen = length;
    length += strlen(s);
    char *newTab = new char[length];
    for (int i = 0; i < prevLen; i++)
    {
        newTab[i] = tab[i];
    }
    for (int i = prevLen; i < length; i++)
    {
        newTab[i] = s[i - prevLen];
    }
    delete[] tab;
    tab = newTab;
    return *this;
}

String &String::operator+(const String &other)
{
    int prevLen = length;
    length += other.length;
    char *newTab = new char[length];
    for (int i = 0; i < prevLen; i++)
    {
        newTab[i] = tab[i];
    }
    for (int i = prevLen; i < length; i++)
    {
        newTab[i] = other.tab[i - prevLen];
    }
    delete[] tab;
    tab = newTab;
    return *this;
}

String &String::operator+=(char *s)
{
    int prevLen = length;
    length += strlen(s);
    char *newTab = new char[length];
    for (int i = 0; i < prevLen; i++)
    {
        newTab[i] = tab[i];
    }
    for (int i = prevLen; i < length; i++)
    {
        newTab[i] = s[i - prevLen];
    }
    delete[] tab;
    tab = newTab;
    return *this;
}

String &String::operator+=(const String &other)
{
    int prevLen = length;
    length += other.length;
    char *newTab = new char[length];
    for (int i = 0; i < prevLen; i++)
    {
        newTab[i] = tab[i];
    }
    for (int i = prevLen; i < length; i++)
    {
        newTab[i] = other.tab[i - prevLen];
    }
    delete[] tab;
    tab = newTab;
    return *this;
}

String String::subStr(int begin, char separator)
{
    int i = begin;
    String subS;
    int newLength = 0;
    while (tab[i] != separator)
    {
        newLength++;
        if (i == length && tab[i] != separator)
        {
            String emptyString ("");
            return emptyString;
        }
        i++;
    }
    subS.length = newLength;
    subS.tab = new char [subS.length + 1];
    int j = 0;
    while(j + begin < begin + newLength)
    {
        subS.tab[j] = tab[j + begin];
        j++;
    }
    subS.tab[j] = '\0';
    return subS;
}

bool String::isEqual(String &other)
{
    if (other.length != this->length)
        return false;
    else
    {
        for (int i = 0; i < this->length; i++)
        {
            if (other.tab[i] != this->tab[i])
                return false;
        }
        return true;
    }
}

bool String::isEqual(const char* s)
{
    if(length != strlen(s))
        return false;
    else
    {
        for (int i = 0; i < this->length; i++)
        {
            if (s[i] != this->tab[i])
                return false;
        }
        return true;
    }
}

bool String::isANumber()
{
    int i=0; 
    while(i< length)
    {
        if(tab[i] < 48 || tab[i] > 57)
            return false;
        i++;
    }
    return true;
}

int String::strToI()
{
    if(length > 0)
        return atoi(tab);
    else
        return 0;
}

bool String::isCharInsideString(char chr)
{
    int i = 0;
    while (tab[i] != '\0')
    {
        if (tab[i] == chr)
            return true;
        i++;
    }
    return false;
}

int String::getLength()
{
    return this->length;
}

void String::setTabIndex(int i, char c)
{
    if(i > -1)
        this->tab[i] = c;
}

void String::setLength(int newLength)
{
    this->length = newLength;
}

char String::getTabIndex(int index)
{
    return this->tab[index];
}

String::~String() {}