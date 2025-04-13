#include "structs.h"

void addMainNode(Node **beg, Node **end)
{
    if (*beg == nullptr)
    {
        (*beg) = new Node;
        *end = *beg;
    }
    else
    {
        (*end)->next = new Node;
        (*end)->next->prev = *end;
        *end = (*end)->next;
    }
}
void addNewSel(Node *end, int tabPos, String selName)
{
    if (end->CSSBlock[tabPos].selListBeg == nullptr)
    {
        end->CSSBlock[tabPos].selListBeg = new Selector;
        end->CSSBlock[tabPos].selListBeg->name = selName;
    }
    else
    {
        Selector *thisNode = end->CSSBlock[tabPos].selListBeg;
        while (thisNode->next != nullptr) // dla pierwszego wezła pomijamy tą petle
        {
            if (thisNode->name.isEqual(selName)) // duplikaty
                return;
            thisNode = thisNode->next;
        }
        if (thisNode->name.isEqual(selName)) // duplikaty dla pierwszego węzła
            return;
        thisNode->next = new Selector;
        thisNode = thisNode->next;
        thisNode->name = selName;
    }
}
void addNewAtt(Node *end, int tabPos, String name, String value)
{
    if (end->CSSBlock[tabPos].attListBeg == nullptr)
    {
        end->CSSBlock[tabPos].attListBeg = new Attribute;
        end->CSSBlock[tabPos].attListBeg->name = name;
        end->CSSBlock[tabPos].attListBeg->value = value;
    }
    else
    {
        Attribute *thisNode = end->CSSBlock[tabPos].attListBeg;
        while (thisNode->next != nullptr) // dla pierwszego wezła pomijamy tą petle
        {
            if (thisNode->name.isEqual(name) == 1) // duplikaty
            {
                thisNode->value = value;
                return;
            }
            thisNode = thisNode->next;
        }
        if (thisNode->name.isEqual(name) == 1) // duplikaty dla pierwszego węzła
        {
            thisNode->value = value;
            return;
        }
        thisNode->next = new Attribute;
        thisNode = thisNode->next;
        thisNode->name = name;
        thisNode->value = value;
    }
}
void deleteAtt(Attribute **attList, String name, String currLine)
{
    if (*attList != nullptr)
    {
        Attribute *thisNode = *attList;
        bool isDelated = false;
        while (thisNode->next != nullptr)
        {
            if (thisNode->name.isEqual(name) == 1 && thisNode == *attList) // usunięcie pierwszego węzła list o długości > 1
            {
                Attribute *temp = thisNode->next;
                *attList = temp;
                delete thisNode;
                isDelated = true;
            }
            if (thisNode->next->name.isEqual(name) == 1)
            {
                if (thisNode->next->next == nullptr)
                {
                    delete thisNode->next;
                    thisNode->next = nullptr;
                    isDelated = true;
                }
                else
                {
                    Attribute *temp = thisNode->next;
                    thisNode->next = temp->next;
                    delete temp;
                    isDelated = true;
                }
            }
            else
                thisNode = thisNode->next;
        }
        if (thisNode == *attList && thisNode->name.isEqual(name) == 1) // usunięcie atrybutu z listy z jednym węzłem
        {
            *attList = nullptr;
            isDelated = true;
            delete thisNode;
        }
        if (isDelated)
            std::cout << currLine << " " << "==" << " " << "deleted" << std::endl;
    }
}

void getFreePos(Node **end, int *pos) // ustawia na podamyn wskażniku pusta pozycje w tablicy jeżeli nie ma ustawia 9
{
    if (*end != nullptr)
    {
        for (int j = 0; j < TABSIZE; j++)
        {
            if ((*end)->CSSBlock[j].selListBeg == nullptr && (*end)->CSSBlock[j].attListBeg == nullptr)
            {
                *pos = j;
                return;
            }
        }
        *pos = 9;
    }
}

void deleteAttList(Attribute **currNode)
{
    if (*currNode != nullptr)
    {
        Attribute *thisNode = *currNode;
        if (thisNode == *currNode && thisNode->next == nullptr)
        {
            *currNode = nullptr;
        }
        if (thisNode->next != nullptr)
        {
            thisNode = thisNode->next;
            deleteAttList(&thisNode);
        }
        else
            delete thisNode;
    }
}

void deleteSelList(Selector **currNode)
{
    if (*currNode != nullptr)
    {
        Selector *thisNode = *currNode;
        if (thisNode == *currNode && thisNode->next == nullptr)
        {
            *currNode = nullptr;
        }
        if (thisNode->next != nullptr)
        {
            thisNode = thisNode->next;
            deleteSelList(&thisNode);
        }
        else
            delete thisNode;
    }
}

bool isNodeEmpty(Node *node)
{
    if (node->CSSBlockCounter == 0)
        return true;
    else
        return false;
}

void deleteMainNode(Node *currNode, Node **beg, Node **end)
{
    if (currNode->next == nullptr) // usuwanie na koncu listy
    {
        if (currNode == (*beg))
        {
            delete currNode;
            *beg = nullptr;
            *end = nullptr;
        }
        else
        {
            currNode->prev->next = nullptr;
            (*end) = currNode->prev;
            delete currNode;
        }
    }
    else // usuwanie na koncu lub w środku
    {
        if (currNode == (*beg))
        {
            *beg = currNode->next;
            (*beg)->prev = nullptr;
            delete currNode;
        }
        else
        {
            currNode->prev->next = currNode->next;
            currNode->next->prev = currNode->prev;
            delete currNode;
        }
    }
}