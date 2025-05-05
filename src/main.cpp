#include "String.h"
#include "CSSParser.h"
#include "structs.h"

int main()
{
    Node *beg = nullptr;
    Node *end = nullptr;
    String currLine = String();
    int mode=READMODE;
    while (std::cin >> currLine)
    {
        if (mode == COMMODE)
            stCommSec(&mode, currLine, &beg, &end);
        else if (mode == READMODE)
            conReadCSS(&mode, currLine, &beg, &end);
    }
    return 0;
}