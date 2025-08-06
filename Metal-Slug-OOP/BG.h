#pragma once

class BG
{
    int ri, ci;
public:
    BG();

    // Getters
    int GetRow() const;
    int GetCol() const;

    // Setters
    void SetRow(int val);
    void SetCol(int val);
};