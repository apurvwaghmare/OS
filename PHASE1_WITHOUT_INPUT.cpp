// PHASE1 WITHOUT INPUT FILE


#include <iostream>
#include <string>
using namespace std;

class OS
{
private:
    char M[100][4], IR[4], R[4], buffer[40];
    int IC, SI;
    bool C;

public:
    void INIT();
    void LOAD();
    void STARTEXECUTION();
    void EXECUTEUSERPROGRAM();
    void MOS();
    void READ();
    void WRITE();
    void TERMINATE();
};

void OS::INIT()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '\0';
        }
    }
    IR[4] = {'\0'};
    R[4] = {'\0'};
    C = false;
}

void OS::LOAD()
{
    string input[] = {
        "$AMJ0001000120004",
        "GD20GD30GD40GD50PD20PD30LR20CR30BT11",
        "PD40PD50H",
        "$DTA",
        "VIT",
        "VIT",
        "NOT",
        "SAME",
        "$END0001"};

    int x = 0;
    for (const string &line : input)
    {
        if (line[0] == '$' && line[1] == 'A' && line[2] == 'M' && line[3] == 'J')
        {
            INIT();
        }
        else if (line[0] == '$' && line[1] == 'D' && line[2] == 'T' && line[3] == 'A')
        {
            STARTEXECUTION();
        }
        else if (line[0] == '$' && line[1] == 'E' && line[2] == 'N' && line[3] == 'D')
        {
            x = 0;
            continue;
        }
        else
        {
            int b = 0;

            for (; x < 100; x++)
            {
                for (int j = 0; j < 4; j++)
                {
                    M[x][j] = line[b];
                    b++;
                    cout << "M[" << x << "]" << "[" << j << "]: " << M[x][j] << endl;
                }
                if (b == 40 || line[b] == ' ' || line[b] == '\n')
                {
                    x++;
                    break;
                }
            }
        }
    }
}

void OS::STARTEXECUTION()
{
    IC = 0;
    EXECUTEUSERPROGRAM();
}

void OS::EXECUTEUSERPROGRAM()
{
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[IC][i];
        }
        IC++;

        int n = (IR[2] - '0') * 10 + (IR[3] - '0');

        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            for (int j = 0; j < 4; j++)
                R[j] = M[n][j];
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            for (int j = 0; j < 4; j++)
                M[n][j] = R[j];
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            C = true;
            for (int j = 0; j < 4; j++)
            {
                if (M[n][j] != R[j])
                {
                    C = false;
                    break;
                }
            }
        }
        else if (IR[0] == 'B' && IR[1] == 'T' && C == true)
        {
            IC = n;
        }
    }
}

void OS::MOS()
{
    switch (SI)
    {
    case 1:
        READ();
        break;
    case 2:
        WRITE();
        break;
    case 3:
        TERMINATE();
        break;
    }
}

void OS::READ()
{
    for (int i = 0; i < 40; i++)
        buffer[i] = '\0';

    cin.getline(buffer, 41);

    int b = 0;
    int n = (IR[2] - '0') * 10;

    for (int l = 0; l < 10; l++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[n][j] = buffer[b];
            b++;
        }
        if (b == 40)
        {
            break;
        }
        n++;
    }

    SI = 0;
}

void OS::WRITE()
{
    for (int i = 0; i < 40; i++)
        buffer[i] = '\0';

    int b = 0;
    int n = (IR[2] - '0') * 10;

    for (int l = 0; l < 10; l++)
    {
        for (int j = 0; j < 4; j++)
        {
            buffer[b] = M[n][j];
            cout << buffer[b];
            b++;
        }
        if (b == 40)
        {
            break;
        }
        n++;
    }
    cout << "\n";
    SI = 0;
}

void OS::TERMINATE()
{
    cout << "\n";
    cout << "\n";
    SI = 0;
}

int main()
{
    OS os;
    os.LOAD();
    return 0;
}
