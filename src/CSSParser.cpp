#include "CSSParser.h"

/* READING CSS*/

void conReadCSS(int *mode, String currLine, Node **beg, Node **end)
{
    while (currLine.isEqual("????") == 0)
    {
        if (currLine.isEqual("{")) // atrybuty globalne
        {
            String globalAtt;
            while (currLine.isCharInsideString('}') != true)
            {
                globalAtt += currLine;
                std::cin >> currLine;
            }
            globalAtt += currLine;
            prcLine(globalAtt, beg, end);
        }
        else if (currLine.isCharInsideString('{') && currLine.isEqual("{") == false && currLine.isCharInsideString('}') == true) // cały blok w jednej linii
        {
            prcLine(currLine, beg, end);
        }
        else if ((currLine.isCharInsideString('{') == false && currLine.getLength() > 1) || (currLine.isCharInsideString('{') == true && currLine.isCharInsideString('}') == false)) // blok CSS w kilku liniach
        {
            String block;
            while (currLine.isCharInsideString('}') != true)
            {
                block += currLine;
                std::cin >> currLine;
            }
            block += currLine;
            prcLine(block, beg, end);
        }
        std::cin >> currLine;
        if (std::cin.eof())
            break;
    }
    *mode = COMMODE;
}

void prcLine(String currLine, Node **beg, Node **end)
{
    int i = 0;
    int pos;
    if (*beg == nullptr)
        addMainNode(beg, end);
    getFreePos(end, &pos);
    if (pos == 9)
    {
        addMainNode(beg, end);
        getFreePos(end, &pos);
    }
    while (i < currLine.getLength())
    {
        String sel = currLine.subStr(i, '{');
        prcSel(sel, *end, pos);
        i += sel.getLength() + 1;
        String att = currLine.subStr(i, '}');
        prcAtt(att, *end, pos);
        i += att.getLength() + 1;
    }
    (*end)->CSSBlockCounter++;
}

void prcSel(String selectors, Node *end, int pos)
{
    if (selectors.isEqual("") != 1)
    {
        int j = 0;
        while (selectors.getTabIndex(j) <= ' ')
            j++;
        while (selectors.subStr(j, ',').isEqual("") != 1) // selektory po ,
        {
            String currSel = selectors.subStr(j, ',');
            j += currSel.getLength() + 1;
            while (selectors.getTabIndex(j) <= ' ')
                j++;
            addNewSel(end, pos, currSel);
        }
        if (selectors.subStr(j, ' ').isEqual("") != 1 && selectors.isCharInsideString(',')) // ostatni selektor gdy poprzednie byly po przecinku
        {
            String lastSel = selectors.subStr(j, '\0');
            if (lastSel.getTabIndex(lastSel.getLength() - 1) == ' ')
            {
                lastSel.setTabIndex(lastSel.getLength() - 1, '\0');
                lastSel.setLength(lastSel.getLength() - 1);
            }
            addNewSel(end, pos, lastSel);
        }
        else // pojedynczy selektor
        {
            if (selectors.getTabIndex(selectors.getLength() - 1) == ' ')
            {
                selectors.setTabIndex(selectors.getLength() - 1, '\0');
                selectors.setLength(selectors.getLength() - 1);
            }
            addNewSel(end, pos, selectors);
        }
    }
}

void prcAtt(String attributes, Node *end, int pos)
{
    int j = 0;
    while (j < attributes.getLength())
    {
        if (attributes.subStr(j, ':').isEqual("") != 1)
        {
            if (attributes.getTabIndex(j) == '\t' || attributes.getTabIndex(j) == ' ')
            {
                while (attributes.getTabIndex(j) <= ' ')
                    j++;
            }
            String name = attributes.subStr(j, ':');
            j += name.getLength() + 1;
            while (attributes.getTabIndex(j) <= ' ')
                j++;
            String value = attributes.subStr(j, ';');
            j += value.getLength() + 1;
            addNewAtt(end, pos, name, value);
        }
        else
            j = attributes.getLength() + 1;
    }
}

/* COMMANDS*/

void stCommSec(int *mode, String currLine, Node **beg, Node **end)
{
    while (currLine.isEqual("****") == 0)
    {
        if (currLine.isEqual("?") == 1 || (currLine.getTabIndex(0) == '?')) // znak ? może wystąpić w lini z eof
            dispCSSSecAm(*beg, currLine);
        else
        {
            int i = 0;
            while (currLine.getTabIndex(i) <= ' ')
                i++;
            String firComPart;
            String secComPart;
            String thiComPart;
            if (currLine.isCharInsideString(',')) // dzilenie komendy
            {
                firComPart = currLine.subStr(i, ',');
                i += firComPart.getLength() + 1;
                secComPart = currLine.subStr(i, ',');
                i += secComPart.getLength() + 1;
                thiComPart = currLine.subStr(i, '\0');
                i += thiComPart.getLength() + 1;
            }
            if (secComPart.isEqual("S") == 1)
            {
                selComms(currLine, firComPart, thiComPart, *beg);
            }
            else if (secComPart.isEqual("A") == 1)
            {
                attComms(currLine, firComPart, thiComPart, *beg);
            }
            else if (secComPart.isEqual("D") == 1)
            {
                delComms(currLine, firComPart, thiComPart, beg, end);
            }
            else if (secComPart.isEqual("E") == 1)
            {
                dispAttValForSel(*end, firComPart, thiComPart, currLine);
            }
        }
        if (std::cin.eof())
            break;
        std::cin >> currLine;
    }
    *mode = READMODE;
}

void selComms(String currLine, String firComPart, String thiComPart, Node *beg)
{
    if (firComPart.isANumber() && thiComPart.isEqual("?"))
        dispSelAmountForSec(firComPart.strToI(), beg, currLine);
    else if (firComPart.isANumber() == 0 && thiComPart.isEqual("?"))
        dispAllSelInst(firComPart, beg, currLine);
    else
        dispSelForSec(firComPart.strToI(), thiComPart.strToI(), beg, currLine);
}

void attComms(String currLine, String firComPart, String thiComPart, Node *beg)
{
    if (firComPart.isANumber() && thiComPart.isEqual("?"))
        dispAttAmountForSec(firComPart.strToI(), beg, currLine);
    else if (firComPart.isANumber() == 0 && thiComPart.isEqual("?"))
        dispAllAttInst(firComPart, beg, currLine);
    else
        dispAttValForSec(firComPart.strToI(), thiComPart, beg, currLine);
}
void delComms(String currLine, String firComPart, String thiComPart, Node **beg, Node **end)
{
    if (thiComPart.isEqual("*") == 1)
        delSec(firComPart.strToI(), beg, end, currLine);
    else
        delAttFromSec(firComPart.strToI(), thiComPart, beg, currLine);
}

void dispCSSSecAm(Node *beg, String currLine)
{
    Node *thisNode = beg;
    int CSSBlockCounter = 0;
    if (beg != nullptr)
    {
        while (thisNode != nullptr)
        {
            for (int i = 0; i < TABSIZE; i++)
            {
                if (thisNode->CSSBlock[i].attListBeg != nullptr)
                    CSSBlockCounter++;
            }
            thisNode = thisNode->next;
        }
    }
    std::cout << currLine << " " << "==" << " " << CSSBlockCounter << std::endl;
}

void dispSelAmountForSec(int secNumber, Node *beg, String currLine)
{
    if (beg != nullptr)
    {
        Node *thisNode = beg;
        int secCounter = 0;
        while (thisNode != nullptr)
        {
            for (int j = 0; j < TABSIZE; j++)
            {
                if (thisNode->CSSBlock[j].attListBeg != nullptr)
                    secCounter++;
                if (secCounter == secNumber)
                {
                    Selector *selCurrNode = thisNode->CSSBlock[j].selListBeg;
                    int selCounter = 0;
                    while (selCurrNode != nullptr)
                    {
                        selCounter++;
                        selCurrNode = selCurrNode->next;
                    }
                    std::cout << currLine << " " << "==" << " " << selCounter << std::endl;
                    return;
                }
            }
            thisNode = thisNode->next;
        }
    }
}
void dispAttAmountForSec(int secNumber, Node *beg, String currLine)
{
    if (beg != nullptr)
    {
        Node *thisNode = beg;
        int secCounter = 0;
        while (thisNode != nullptr)
        {
            for (int j = 0; j < TABSIZE; j++)
            {
                if (thisNode->CSSBlock[j].attListBeg != nullptr)
                    secCounter++;
                if (secCounter == secNumber)
                {
                    Attribute *attCurrNode = thisNode->CSSBlock[j].attListBeg;
                    int attCounter = 0;
                    while (attCurrNode != nullptr)
                    {
                        attCounter++;
                        attCurrNode = attCurrNode->next;
                    }
                    std::cout << currLine << " " << "==" << " " << attCounter << std::endl;
                    return;
                }
            }
            thisNode = thisNode->next;
        }
    }
}
void dispSelForSec(int secNumber, int selNumber, Node *beg, String currLine)
{
    if (beg != nullptr)
    {
        Node *thisNode = beg;
        int CSSBlockCounter = 0;
        while (thisNode != nullptr)
        {
            for (int k = 0; k < TABSIZE; k++)
            {
                if (thisNode->CSSBlock[k].attListBeg != nullptr)
                    CSSBlockCounter++;
                if (CSSBlockCounter == secNumber)
                {
                    Selector *selCurrNode = thisNode->CSSBlock[k].selListBeg;
                    int counterSel = 0;
                    while (selCurrNode != nullptr)
                    {
                        counterSel++;
                        if (counterSel == selNumber)
                        {
                            std::cout << currLine << " " << "==" << " " << selCurrNode->name << std::endl;
                            return;
                        }
                        selCurrNode = selCurrNode->next;
                    }
                }
            }
            thisNode = thisNode->next;
        }
    }
}

void dispAttValForSec(int secNumber, String attName, Node *beg, String currLine)
{
    if (beg != nullptr)
    {
        Node *thisNode = beg;
        int CSSBlockCounter = 0;
        while (thisNode != nullptr)
        {
            for (int j = 0; j < TABSIZE; j++)
            {
                if (thisNode->CSSBlock[j].attListBeg != nullptr)
                    CSSBlockCounter++;
                if (CSSBlockCounter == secNumber)
                {
                    Attribute *attCurrNode = thisNode->CSSBlock[j].attListBeg;
                    while (attCurrNode != nullptr)
                    {
                        if (attCurrNode->name.isEqual(attName))
                        {
                            std::cout << currLine << " " << "==" << " " << attCurrNode->value << std::endl;
                            return;
                        }
                        attCurrNode = attCurrNode->next;
                    }
                }
            }
            thisNode = thisNode->next;
        }
    }
}
void dispAllAttInst(String attName, Node *beg, String currLine)
{
    if (beg != nullptr)
    {
        Node *thisNode = beg;
        int CSSBlockCounter = 0;
        while (thisNode != nullptr)
        {
            for (int j = 0; j < TABSIZE; j++)
            {
                if (thisNode->CSSBlock[j].attListBeg != nullptr)
                {
                    Attribute *attCurrNode = thisNode->CSSBlock[j].attListBeg;
                    while (attCurrNode != nullptr)
                    {
                        if (attCurrNode->name.isEqual(attName))
                        {
                            CSSBlockCounter++;
                            break;
                        }
                        attCurrNode = attCurrNode->next;
                    }
                }
            }
            thisNode = thisNode->next;
        }
        std::cout << currLine << " " << "==" << " " << CSSBlockCounter << std::endl;
    }
}
void dispAllSelInst(String selName, Node *beg, String currLine)
{
    if (beg != nullptr)
    {
        Node *thisNode = beg;
        int CSSBlockCounter = 0;
        while (thisNode != nullptr)
        {
            for (int j = 0; j < TABSIZE; j++)
            {
                if (thisNode->CSSBlock[j].selListBeg != nullptr)
                {
                    Selector *selCurrNode = thisNode->CSSBlock[j].selListBeg;
                    while (selCurrNode != nullptr)
                    {
                        if (selCurrNode->name.isEqual(selName))
                            CSSBlockCounter++;
                        selCurrNode = selCurrNode->next;
                    }
                }
            }
            thisNode = thisNode->next;
        }
        std::cout << currLine << " " << "==" << " " << CSSBlockCounter << std::endl;
    }
}

void dispAttValForSel(Node *end, String selName, String attName, String currLine)
{
    if (end != nullptr)
    {
        Node *thisNode = end;
        while (thisNode != nullptr)
        {
            for (int i = TABSIZE - 1; i > -1; i--)
            {
                if (thisNode->CSSBlock[i].selListBeg != nullptr)
                {
                    Selector *currSel = thisNode->CSSBlock[i].selListBeg;
                    while (currSel != nullptr)
                    {
                        if (currSel->name.isEqual(selName) == 1)
                        {
                            Attribute *currAtt = thisNode->CSSBlock[i].attListBeg;
                            while (currAtt != nullptr)
                            {
                                if (currAtt->name.isEqual(attName) == 1)
                                {
                                    std::cout << currLine << " " << "==" << " " << currAtt->value << std::endl;
                                    return;
                                }
                                currAtt = currAtt->next;
                            }
                        }
                        currSel = currSel->next;
                    }
                }
            }
            thisNode = thisNode->prev;
        }
    }
}

void delSec(int secNumber, Node **beg, Node **end, String currLine)
{
    if (beg != nullptr)
    {
        Node *thisNode = *beg;
        int CSSBlockCounter = 0;
        while (thisNode != nullptr)
        {
            for (int j = 0; j < TABSIZE; j++)
            {
                if (thisNode->CSSBlock[j].attListBeg != nullptr)
                    CSSBlockCounter++;
                if (CSSBlockCounter == secNumber)
                {
                    deleteAttList(&(thisNode->CSSBlock[j].attListBeg));
                    thisNode->CSSBlock[j].attListBeg = nullptr;
                    deleteSelList(&(thisNode->CSSBlock[j].selListBeg));
                    thisNode->CSSBlock[j].selListBeg = nullptr;
                    thisNode->CSSBlockCounter--;
                    if (isNodeEmpty(thisNode))
                        deleteMainNode(thisNode, beg, end);
                    std::cout << currLine << " " << "==" << " " << "deleted" << std::endl;
                    return;
                }
            }
            thisNode = thisNode->next;
        }
    }
}

void delAttFromSec(int secNumber, String attName, Node **beg, String currLine)
{
    if (beg != nullptr)
    {
        Node *thisNode = *beg;
        int CSSBlockCounter = 0;
        while (thisNode != nullptr)
        {
            for (int j = 0; j < TABSIZE; j++)
            {
                if (thisNode->CSSBlock[j].attListBeg != nullptr)
                    CSSBlockCounter++;
                if (CSSBlockCounter == secNumber)
                {
                    deleteAtt(&(thisNode->CSSBlock[j].attListBeg), attName, currLine);
                    if (thisNode->CSSBlock[j].attListBeg == nullptr)
                    {
                        thisNode->CSSBlockCounter--;
                        deleteSelList(&(thisNode->CSSBlock[j].selListBeg));
                        thisNode->CSSBlock[j].selListBeg = nullptr;
                    }
                    return;
                }
            }
            thisNode = thisNode->next;
        }
    }
}