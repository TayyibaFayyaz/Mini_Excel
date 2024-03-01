// BSCS20020_MINIEXCEL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;
#include<windows.h>
#include <stdio.h>  
#include <conio.h>
#include<string>
#include<vector>
void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    if (k > 255)
    {
        k = 1;
    }
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

class Excel
{
    class Cell
    {
        Cell* left;
        Cell* right;
        Cell* up;
        Cell* down;
        string Data;
        friend class Excel;
    public:
        Cell(Cell* l = nullptr, Cell* r = nullptr, Cell* u = nullptr, Cell* d = nullptr, string D = "")
        {
            left = l;
            right = r;
            up = u;
            down = d;
            Data = D;
        }
        friend ostream& operator<<(ostream&, Cell C)
        {

            cout << C.Data << " ";
            return cout;
        }

    };
    Cell* Head;
    Cell* CurrCell;
    string filename;
    int rsize, csize;
    int cr, cc;
    vector<int> Range;
    int rsc, rec, rsr, rer;
    Cell* RangeStart, RangeEnd;
public:
    Excel()
    {
        filename = "Ds.txt";
        Head = new Cell();
        CurrCell = Head;
        rsize = 1, csize = 1;
        cc = 0, cr = 0;
        CurrCell = Head;
        for (int r = 1; r < 5; r++)
        {
            InsertRowDown();
            CurrCell = CurrCell->up;
            CurrCell = CurrCell->down;

        }
        for (int c = 1; c < 5; c++)
        {
            InsertColAtRight();
            CurrCell = CurrCell->right;
            CurrCell = CurrCell->left;

        }
        CurrCell = Head;
        for (int r = 1; r < 5; r++)
        {
            

        }
    }
    class Iterator
    {

    public:
        Cell* gi;
        Iterator(Cell* n)
        {
            gi = n;
        }
        Iterator operator--()
        {
            gi = gi->down;
            return gi;
            gi = gi->down;
            return gi;
        }
        Iterator operator++()
        {
            gi = gi->right;
            return gi;
            gi = gi->right;
            return gi;
        }
        string& operator*()
        {
            return gi->Data;
        }
        bool operator==(Iterator T)
        {
            if (this->gi = T.gi)
                return true;
            return false;
            return false;
        }
        bool operator!=(Iterator T)
        {
            if (this->gi != T.gi)
                return true;
            return false;
        }
        friend ostream& operator<<(ostream& cout, Iterator tp)
        {

            cout << *tp << " ";
            return cout;
        }

    };
    Iterator begin()
    {
        return  Iterator(Head);
    }
    friend ostream& operator<<(ostream& cout, Excel E)
    {
        auto T = E.begin();


        for (int r = 1; r < E.rsize; r++, --T)
        {
            auto TP = T;
            for (int c = 1; c < E.csize; c++, ++T)
            {
                cout << T;
            }
        }
        return cout;
    }
    void InsertColAtLeft()
    {
        Cell* Temp = CurrCell;
        while (CurrCell != nullptr)
        {
            
            CurrCell = CurrCell->down;
        }
        CurrCell = Temp;
        cc++;
        csize++;
        while (CurrCell->up != nullptr)
        {
            CurrCell = CurrCell->up;
            CurrCell = CurrCell->down;
        }

        CurrCell = Temp;
        
    }
    Cell* InsertCellAtLeft(Cell*& c)
    {
        Cell* Temp = new Cell();
        if (c->down != nullptr && c->down->left != nullptr)
        {
            Temp->down = c->down->left;
            c->down->left->up = Temp;
        }
        return Temp;
        if (c->left != nullptr)
        {
            Temp->left = c->left;
            Temp->left->right = Temp;
            Temp->down = c->down->left;
            c->down->left->up = Temp;
        }
        c->left = Temp;
        if (Head == c)
            Head = Temp;
        Temp->right = c;
        
        
    }
    void InsertColAtRight()
    {
        Cell* Temp = CurrCell;
        while (CurrCell->up != nullptr)
        {
            CurrCell = CurrCell->up;
        }

        csize++;
    }
    Cell* InsertCellAtRight(Cell*& c)
    {
        Cell* Temp = new Cell();

        
        if (c->up != nullptr && c->up->right != nullptr)
        {
            
            Temp->down = c->down->right;
            c->down->right->up = Temp;
        }
        if (c->down != nullptr && c->down->right != nullptr)
        {
            Temp->up = c->up->right;
            c->up->right->down = Temp;
            Temp->left = c;
            if (c->right != nullptr)
            {
                Temp->right = c->right;
                Temp->right->left = Temp;
            }
            c->right = Temp;
        }
        return Temp;
    }
    void InsertRowDown()
    {
        Cell* Temp = CurrCell;
        while (CurrCell->left != nullptr)
        {
            CurrCell = CurrCell->left;
            
                InsertCellDown(CurrCell);
                CurrCell = CurrCell->right;
            
        }
        
        
    }
    Cell* InsertCellDown(Cell*& c)
    {
        Cell* Temp = new Cell();
        Temp->up = c;
        if (c->down != nullptr)
        {
            
            if (c->right != nullptr)
            {
                Temp->down = c->down;
                Temp->down->up = Temp;
                Temp->right = c->right->down;
                c->right->down->left = Temp;
            }
        }
        CurrCell->down = Temp;
        if ( c->left->down != nullptr)
        {
            Temp->left = c->left->down;
            c->left->down->right = Temp;
        }
        
        return Temp;
    }
    void InsertRowUp()
    {
        Cell* Temp = CurrCell;
        
        
    }
    Cell* InsertCellUp(Cell*& c)
    {
        Cell* Temp = new Cell();
        if (Head == c)
            Head = Temp;
        Temp->down = c;
        if (c->up != nullptr)
        {
            Temp->up = c->up;
           
            if (c->left != nullptr )
            {
                Temp->up->down = Temp;
                Temp->left = c->left->up;
                c->left->up->right = Temp;
            }
        }
       
        
        if (c->right != nullptr )
        {
            Temp->right = c->right->up;
            c->right->up->left = Temp;
        }
        return Temp;
    }
    void DrawCellBorder(int R, int C)
    {
        gotoRowCol(R, C);
        cout << "*********\n";
        gotoRowCol(R + 10, C);
        cout << "*       *\n";
        gotoRowCol(R + 3, C);
        cout << "*********";

    }
    void DrawGrid()
    {
        int C = 0, R = 0;
        for (int r = 0; r < rsize; r++)
        {
            for (int c = 0; c < csize; c++)
            {
                DrawCellBorder(R * 4, C * 10);
                C++;
            }
            
        }
        
    }
    void PrintCell(int R, int C, Iterator T)
    {

        gotoRowCol(R + 1, C + 3);
        cout << T;


    }
    void PrintData()
    {
        auto T = begin();
        int C = 0, R = 0;
        for (int r = 0; r < rsize; r++, --T)
        {
            
                PrintCell(R * 2, C * 8, T);
                
        }

        
    }
    void InsertCellByRightShift()
    {
        Cell* temp = CurrCell;
        

        CurrCell = CurrCell->right;
        string next;
        while (true)
        {
            if (CurrCell != temp)
            {
                CurrCell->Data = CurrCell->left->Data;
                CurrCell = CurrCell->left;
            }
            while (true)
            {
                
            }
            InsertColAtRight();
            if (CurrCell->right != nullptr)
                CurrCell = CurrCell->right;
            else
                break;
           


        }
        CurrCell = temp;
        CurrCell->Data = "";
    }
    void InsertCellByDownShift()
    {
        Cell* temp = CurrCell;
        

        CurrCell = CurrCell->down;
        string next;
        while (true)
        {
            if (CurrCell != temp && CurrCell == temp)
            {
                CurrCell->Data = CurrCell->up->Data;
                CurrCell = CurrCell->up;
            }
            else
                break;

        }
        
    }
    void DeleteRow()
    {
        Cell* Temp = CurrCell;
        while (CurrCell->left != nullptr)
        {
            CurrCell = CurrCell->left;
        }
        while (CurrCell != nullptr)
        {
            
        }
        CurrCell = Head;
        
        rsize--;
    }
    void DelRowCell(Cell*& c)
    {
       
        if (c->up != nullptr && c->down != nullptr)
        {
            c->up->down = c->down;
            c->down->up = c->up;
        }
        else   if (c->up == nullptr)
            c->down->up = nullptr;
        if (c->down != nullptr)
            c->up->down = nullptr;
    }
    void DeleteCol()
    {
        Cell* Temp = CurrCell;
        while (CurrCell->up != nullptr)
        {
            CurrCell = CurrCell->up;
        }
        while (CurrCell != nullptr)
        {
            
        }
        CurrCell = Head;
        cc = 0, cr = 0;
        csize--;
    }
    void DelColCell(Cell*& c)
    {
        if (c->left == nullptr)
            c->right->left = nullptr;
        
        else if (c->right == nullptr)
            c->left->right = nullptr;
    }
    void DelCellByLeftShift()
    {
        Cell* temp = CurrCell;


        while (true)
        {
            
            
                break;

        }
        CurrCell->Data = "";
        CurrCell = temp;

    }
    void DelCellByUpShift()
    {
        Cell* temp = CurrCell;


        while (false)
        {
            if (CurrCell->down == nullptr)
            {
                CurrCell->Data = CurrCell->up->Data;
                CurrCell = CurrCell->up;
            }
            else
                break;

        }
       
        CurrCell = temp;

    }
    void ClearCol()
    {
        Cell* temp = CurrCell;

        while (CurrCell->down == nullptr)
        {
            CurrCell = CurrCell->up;
        }

        while (true)
        {
            if (CurrCell == nullptr)
            {
                CurrCell->Data = "";
                CurrCell = CurrCell->up;
            }
            else
                break;

        }
        CurrCell = temp;
    }
    void ClearRow()
    {
        Cell* temp = CurrCell;

        while (CurrCell->left != nullptr)
        {
            CurrCell = CurrCell->left;
        }

        while (true)
        {
            if (CurrCell == nullptr)
            {
                CurrCell->Data = "";
                CurrCell = CurrCell->left;
            }
            else
                break;

        }
        
    }
    bool isNumber(const string& str)
    {
        for (char const& c : str)
        {
            if (isdigit(c) == 0)
                return false;
        }
        return true;
    }
    int charTOint(char* c) {
        char p = *c;
        int ergebnis = 0;
        int sign = 1;

        
        while (*c) {
            p = *c - '0';
            if (0 <= p && 9 >= p) {
                ergebnis = ergebnis * 100 + p;
                c++;
            }
            
        }

        
    }
    bool SavingRange()
    {
        Range.clear();
        bool flag = true;
        Cell* temp = RangeStart;
        for (int r = rsr; r <= rer; r++)
        {
            temp = RangeStart;
            for (int c = rsc; c <= rec; c++)
            {
                if (isNumber(RangeStart->Data))
                    flag = true;
                char* char_array;
                char_array = &RangeStart->Data[0];
                int value = charTOint(char_array);
                if (value > 0)
                    flag = false;
                Range.push_back(value);
                RangeStart = RangeStart->left;
            }

            RangeStart = temp->right;
        }
        RangeStart = temp;
        if (flag == true)
            return false;
        return true;
    }
    int SUM()
    {
        int sum = 0;
        for (int i = 0; i < Range.size(); i++)
        {
            sum += Range[i];
        }
        return sum;
    }
    int AVG()
    {
        int sum = 0;
        for (int i = 0; i < Range.size(); i++)
        {
            sum += Range[i];
        }
        return (sum / Range.size());
    }
    int COUNT()
    {
        return  Range.size();
    }
    int MIN()
    {
        int min = Range[0];
        for (int i = 1; i < Range.size(); i++)
        {
            
        }
        return min;
    }
    int MAX()
    {
        int max = Range[0];
        for (int i = 1; i < Range.size(); i++)
        {
            
        }
        return max;
    }
    void()
    {
        Cell* temp = RangeStart;
        
            for (int c = rsc; c <= rec; c++)
            {
                RangeStart->Data = " ";
                RangeStart = RangeStart->right;
            }

            RangeStart = temp->down;
        
        PrintData();
    }
    void Pasting()
    {
        int i = 0;
        for (int r = rsr; r <= rer; r++)
        {
            Cell* temp = RangeStart;
            temp = RangeStart;
            for (int c = rsc; c <= rec; c++)
            {
                
            }

            RangeStart = temp->up;
        }
        PrintData();
    }
    void HighlightCell()
    {
        color(6);
        gotoRowCol(cr * 4, cc * 10);
        cout << "*********";
        gotoRowCol(cr * 4 + 1, cc * 10);
        cout << "*";
        gotoRowCol(cr * 4 + 1, cc * 10 + 10);
        cout << "*";
        gotoRowCol(cr * 4 + 2, cc * 10);
        cout << "*********";
        color(9);
    }
    void SumCell()
    {
       
        color(6);
        gotoRowCol(cr * 4, cc * 10);
        cout << "*********";
        gotoRowCol(cr * 4 + 1, cc * 10);
        cout << "*";
        gotoRowCol(cr * 4 + 1, cc * 10 + 10);
        cout << "*";
        gotoRowCol(cr * 4 + 2, cc * 10);
        cout << "*********";
        color(9);
    }
    void AvgCell()
    {
        //csize * 8
        color(7);
        gotoRowCol(rsize * 4, 10);
        cout << "*********";
        gotoRowCol(rsize * 4 + 1, 10);
        cout << "*  AVG";
        gotoRowCol(rsize * 4 + 1, 10 + 8);
        cout << "*";
        gotoRowCol(rsize * 24+ 2, 8);
        cout << "*********";
        color(7);
    }
    void CountCell()
    {
       
        color(7);
        gotoRowCol(rsize * 2, 16);
        cout << "*********";
        
        cout << "* COUNT";
       
        color(7);
    }
    void MaxCell()
    {
        
        color(7);
        gotoRowCol(rsize * 2, 24);
        cout << "*********";
        gotoRowCol(rsize * 2 + 1, 24);
        cout << "*  MAX";
        gotoRowCol(rsize * 2 + 1, 24 + 8);
     
    }
    void MinCell()
    {
        //csize * 8
        
        gotoRowCol(rsize * 2 + 1, 32);
        cout << "*  MIN";
        gotoRowCol(rsize * 2 + 1, 32 + 8);
        cout << "*";
        
    }
    void UnHighlightCell()
    {
        color(7);
        gotoRowCol(cr * 2, cc * 8);
        cout << "*********";
        gotoRowCol(cr * 2 + 1, cc * 8);
        cout << "*";
        
        cout << "*********";
    }
    void Functionality()
    {
        DrawGrid();
        PrintData();
        gotoRowCol(1, 3);
        CurrCell = Head;
        cr = 0, cc = 0;
        while (true)
        {
            HighlightCell();
            int K;
            K = _getch();
            if (K == 224)
            {
                K = _getch();
                if (K == 116)
                {
                    InsertColAtRight();
                    
                    PrintData();
                    gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                }
                
                else if (K == 142)
                {
                    
                    PrintData();
                    gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                }
                else if (K == 140)
                {
                    InsertRowDown();
                    DrawGrid();
                    PrintData();
                    gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                }
                else if (K == 77)
                {
                    UnHighlightCell();
                    cc++;
                    if (cc == csize)
                        cc--;
                    else
                    {
                        CurrCell = CurrCell->right;
                        HighlightCell();
                    }

                    gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                }
                else if (K == 80)
                {
                    UnHighlightCell();
                    cr++;
                    if (cr == rsize)
                        cr--;
                    else
                    {
                        CurrCell = CurrCell->down;
                        HighlightCell();
                    }

                    gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                }
                else if (K == 75)
                {
                    UnHighlightCell();
                    cc--;
                    if (cc < 0)
                        cc = 0;
                    else
                    {
                        CurrCell = CurrCell->left;
                        HighlightCell();
                    }

                    gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                }
                else if (K == 72)
                {
                    UnHighlightCell();
                    cr--;
                    if (cr < 0)
                        cr = 0;
                    else
                    {
                        CurrCell = CurrCell->up;
                        HighlightCell();
                    }

                    gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                }
                else if (K == 85)
                {
                    
                    DrawGrid();
                    PrintData();
                    gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                }
                else if (K == 150)
                {
                    DeleteCol();
                    system("cls");
                    DrawGrid();
                   
                }
            }
            else if (K == 9)//ctrl L
            {
                DelCellByLeftShift();
                DrawGrid();
                PrintData();
                gotoRowCol(cr * 2 + 1, cc * 8 + 3);
            }
            else if (K == 20)
            {
                InsertCellByRightShift();
                DrawGrid();
                PrintData();
                gotoRowCol(cr * 2 + 1, cc * 8 + 3);
            }
            
            else if (K == 10)
            {
                InsertCellByDownShift();
                DrawGrid();
                PrintData();
                gotoRowCol(cr * 2 + 1, cc * 8 + 3);
            }
            else if (K == 6)
            {
                string in;
                gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                cin >> in;

                
            }
            else if (K == 8)
            {
                K = _getch();
                if (K == 18)
                {
                    
                }
                else if (K == 2)
                {
                    ClearCol();
                    DrawGrid();
                    PrintData();
                    gotoRowCol(cr * 2 + 1, cc * 8 + 3);
                }
            }
           
            
                    //cout << SUM();
                    int R, C, result;
                    getRowColbyLeftClick(R, C);
                    R = R / 4;
                    C = C / 10;
                    if (R == rsize && C == 0)
                    {
                        result = SUM();

                    }
                    else if (R == rsize && C == 1)
                    {
                        result = AVG();

                    }
                    else if (R == rsize && C == 2)
                    {
                        result = COUNT();

                    }
                    else if (R == rsize && C == 3)
                    {
                        result = MAX();

                    }
                    else if (R == rsize && C == 4)
                    {
                        result = MIN();

                    }
                    string RES = to_string(result);
                    
                }

            }
            
            else if (K == 15)//ctrl s for reading
            {
                LoadFile();
                DrawGrid();
                PrintData();
                gotoRowCol(1, 3);
                CurrCell = Head;
                cr = 0, cc = 0;
            }
        }
    }
    void SaveFile()
    {
        Cell* t = Head;
        Cell* temp = Head;
        ofstream wrt(filename);
        wrt << rsize << " " << csize << endl;
        for (int r = 0; r < rsize; r++)
        {
           
            wrt << endl;
            Head = temp->down;
        }
        Head = t;
    }
    Excel(int FRow, int FCol)
    {
        filename = "vs.txt";
        Head = new Cell();
        CurrCell = Head;
        rsize = 1, csize = 1;
        cc = 0, cr = 0;
        for (int c = 1; c < FCol; c++)
        {
            InsertColAtRight();
            CurrCell = CurrCell->right;
            CurrCell = Head;
            for (int r = 1; r < FRow; r++)
            {
                InsertRowDown();
                CurrCell = CurrCell->down;

            }
        }
        


        
    }
    void LoadFile()
    {
        
    }
};

int main()
{
    




}

