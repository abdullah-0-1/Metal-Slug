#include "BG.h"

BG::BG()
{
    ri = 0;
    ci = 0;
}

int BG::GetRow() const
{
    return ri;
}

int BG::GetCol() const
{
    return ci;
}

// Setters
void BG::SetRow(int val)
{
    ri = val;
}

void BG::SetCol(int val)
{
    ci = val;
}