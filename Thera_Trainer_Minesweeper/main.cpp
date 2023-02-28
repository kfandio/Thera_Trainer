#include <iostream>
#include <stdlib.h>

using namespace std;

const int xSize = 5;
const int ySize = 5;

//Initialisiert alle Felder der Tabelle auf 0
void initTab(int M[xSize][ySize], int xSize, int ySize)
{

    for(int i=0; i < xSize;i++){

        for(int j=0;j<ySize;j++){

            M[i][j] = 0;
        }
    }

}

// Platziert die Boumben zufällig und initialisiert die 8 Felder um die Boomben herum
void initField(int M[xSize][ySize], int xSize, int ySize, int bombs)
{
    do{
        int x = rand()  %xSize;
        int y = rand()  %ySize;

        // Bomben plazieren
        if (M[x][y] != 9)
        {
            M[x][y] = 9; // Anzahl der Felder + 1
            bombs--;
        }

    }while(bombs!= 0);

    // Berechnung der Bomben benachbarten Werten (Die 8 Felder um die Bomben herum)
    for(int i = 0 ; i < xSize;i++)
    {
        for(int j = 0; j < ySize; j++)
        {
            if(M[i][j]!=9 && M[i+1][j+1] == 9 && j < ySize-1) M[i][j]++;
            if(M[i][j]!=9 && M[i+1][j] == 9) M[i][j]++;
            if(M[i][j]!=9 && M[i+1][j-1] == 9 && j > 0) M[i][j]++;
            if(M[i][j]!=9 && M[i][j+1] == 9 && j < ySize-1) M[i][j]++;
            if(M[i][j]!=9 && M[i][j-1] == 9 && j > 0) M[i][j]++;
            if(M[i][j]!=9 && M[i-1][j+1] ==9 && j < ySize-1) M[i][j]++;
            if(M[i][j]!=9 && M[i-1][j] ==9) M[i][j]++;
            if(M[i][j]!=9 && M[i-1][j-1] ==9 && j > 0) M[i][j]++;
        }
    }
}


// Boolesche Variable visible initialisiert auf Nichtsichtbar für alle Felder der Tabelle
void initTabBool(bool visible[xSize][ySize], int xSize, int ySize)
{
    for(int i = 0; i < xSize; i++)
    {
        for(int j = 0; j< ySize; j++)
        {
            visible[i][j] = false;
        }
    }
}


// Zeig die Tabelle
void displayField(bool visible[xSize][ySize], int M[xSize][ySize], int xSize, int ySize, char noCheckSymbol, char bombsSymbol){

    // Y Label
    for(int i = 0; i < xSize; i++){
        cout << "C" << i;
    }

    cout << endl <<" ";

    for(int i = 0; i < xSize; i++){

        for(int j = 0; j < ySize; j++){

            if(visible[i][j]==true)
            {
                if(M[i][j]!=9) cout << M[i][j] << " ";
                if(M[i][j]==9) cout << bombsSymbol << " ";
            }
        else cout<< noCheckSymbol  << " ";
        }

        cout << "L"<< i;
        cout << endl << " ";
    }
}

// Gib die Anzahl der sichtbaren Elemente zurück
int visibleElement(bool visible[xSize][ySize], int xSize, int ySize)
{
    int element;
    for(int i = 0; i < xSize; i++){

        for(int j = 0; j < ySize; j++){

            if(visible[i][j] == true){
                element = element + 1;
            }
        }
    }
    return(element);
}

// Alle Bomben sichtbar machen
void bombsDiscovery(bool visible[xSize][ySize], int M[xSize][ySize], int xSize, int ySize){

    for(int i = 0; i < xSize; i++){

        for(int j = 0; j < ySize; j++){

            if(M[i][j] == 9){
                visible[i][j] = true;
            }
        }
    }
}

// Zeigt der Wert
void valueDiscovery(bool visible[xSize][ySize], int i, int j){

    if(visible[i][j] == false)
    {
        visible[i][j] = true;

    }
}





/*-----------------------------------------------------------------------------------------------------------------------------------------------
  Abruf der Main-Funktion
 -----------------------------------------------------------------------------------------------------------------------------------------------*/

int main()
{
    int bombs = 14;

    int field[xSize][ySize], element, inputX, inputY;
    bool visible[xSize][ySize];
    char noCheckSymbol, bombsSymbol;


    noCheckSymbol = '*';
    bombsSymbol = '-';

    element = 0;

    initTab(field, xSize, ySize);

    initField(field, xSize, ySize, bombs);

    initTabBool(visible, xSize, ySize);

    do{
        displayField(visible, field, xSize, ySize, noCheckSymbol, bombsSymbol);

        do{
            cout << endl << "Gib die Linie ein, die sichtbar gemacht werden soll : ";
            cin >> inputX;
            cout << endl;

            if(inputX < 0 || inputX >= xSize)
                cerr << "Gib ein Wert zwischen 0 und 4 " << endl;

        }while(inputX < 0 && inputX > xSize);

        do{cout << endl << "Gib die Spalte ein, die sichtbar gemacht werden soll : " ;
            cin >> inputY;
            cout << endl;

            if(inputX < 0 || inputX >= xSize)
                cerr << "Gib ein Wert zwischen 0 und 4 " << endl;

        }while(inputY < 0 && inputY > ySize);

        if(field[inputX][inputY]!=9)
        {
            valueDiscovery(visible, inputX, inputY);
            element=visibleElement(visible, xSize, ySize);
        }

    }while((bombs + element < ySize*xSize) && (field[inputX][inputY]!=9));


        if(field[inputX][inputY]==9)
        {
        bombsDiscovery(visible, field, xSize, ySize);
        displayField(visible, field, xSize, ySize, noCheckSymbol, bombsSymbol);

        cout << endl << "Lost" <<endl << endl;

        }
    else{
        bombsDiscovery(visible, field, xSize, ySize);
        displayField(visible, field, xSize ,ySize, noCheckSymbol, bombsSymbol);
      cout << endl << "Win" <<endl << endl;

        }

    return 0;
}
