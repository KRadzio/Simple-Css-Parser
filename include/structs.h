#pragma once
#include "String.h"
#define TABSIZE 8

struct Attribute
{
    String name;
    String value;
    Attribute *next = nullptr;
};

struct Selector
{
    String name;
    Selector *next = nullptr;
};

struct Block
{
    Attribute *attListBeg = nullptr;
    Selector *selListBeg = nullptr;
};

struct Node
{
    int CSSBlockCounter = 0;
    Block CSSBlock[TABSIZE];
    Node *prev = nullptr;
    Node *next = nullptr;
};

void addMainNode(Node **beg, Node **end);
void addNewSel(Node *end, int tabPos, String selName);
void addNewAtt(Node *end, int tabPos, String name, String value);

void getFreePos(Node **end, int *pos);
bool isNodeEmpty(Node *node);

void deleteAtt(Attribute **attList, String name, String currLine);
void deleteAttList(Attribute **currNode);
void deleteSelList(Selector **currNode);
void deleteMainNode(Node *currNode, Node **beg, Node **end);