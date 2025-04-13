#pragma once
#include "String.h"
#include "structs.h"
#define COMMODE 0
#define READMODE 1

void stCommSec(int *mode, String currLine, Node **beg, Node **end);                // ????
void conReadCSS(int *mode, String currLine, Node **beg, Node **end);               // ****
void dispCSSSecAm(Node *beg, String currLine);                                     // ?
void dispSelAmountForSec(int secNumber, Node *beg, String currLine);               // i,S,?
void dispAttAmountForSec(int secNumber, Node *beg, String currLine);               // i,A,?
void dispSelForSec(int secNumber, int selNumber, Node *beg, String currLine);              // i,S,j
void dispAttValForSec(int secNumber, String attName, Node *beg, String currLine);  // i,A,n
void dispAllAttInst(String attName, Node *beg, String currLine);                   // n,A,?
void dispAllSelInst(String selName, Node *beg, String currLine);                   // z,S,?
void dispAttValForSel(Node *end, String selName, String attName, String currLine); // z,E,n
void delSec(int secNumber, Node **beg, Node **end, String currLine);               // i,D,*
void delAttFromSec(int secNumber, String attName, Node **beg, String currLine);    // i,D,n

void selComms(String currLine, String firComPart, String thiComPart, Node *beg);
void attComms(String currLine, String firComPart, String thiComPart, Node *beg);
void delComms(String currLine, String firComPart, String thiComPart, Node **beg, Node **end);

void prcLine(String currLine, Node **beg, Node **end);
void prcSel(String selectors, Node *end, int pos);
void prcAtt(String attributes, Node *end, int pos);