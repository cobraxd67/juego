#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <mmsystem.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>	

using namespace std;

void gotoxy(int x, int y);

void cambiarmapa(string matriz[13][18], string nuevomapa[13][18], int &fila, int &columna, int &mapaActual, int fila1, int columna1, int mapaActual1);

void cargarmapa(string matriz[13][18], string nuevomapa[13][18]);

void elegiropcion(int &vida,string r1,string r2,string r3,string r4,int correcta,int &contador,char izq,char der);

void bloquear(char tecla, char arriba, char abajo, char izq, char der, int &fila, int &columna,string matriz[13][18], string pj);

void esperar(int s);

void esperarmilis(int m);

void transicion(int nmapaActual,int &pasa, string puerta, int &fila, int &columna);

void dibujarmapa(string matriz[13][18]);

void dibujarBloque(string bloque);

void matriztexto(string espaciotexto[13][20]);

void profe();

void explosion();

void barradevida(int &vida,bool &hablando);

void esperarEnter();

void revisarMuerte(int vida, string usuario,char tecla, char arriba, char abajo, char izq, char der,bool &repetirmenu,bool &intento);

char bloquearteclado(char t1, char t2, char t3, char t4);

string leerusuario();

int main() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(info);
	GetConsoleScreenBufferInfoEx(h, &info);
	info.dwSize.X = 120;
	info.dwSize.Y = 35;
	SetConsoleScreenBufferSize(h, info.dwSize);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 20;
	cfi.dwFontSize.Y = 28;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	// cambiar fuente
	
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	
	srand(time(NULL));
	
    string usuario, psw, usuarioGuardado, pswGuardada;
    bool inicio=true;
    bool intento=false;
	bool volver2=false;
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	keybd_event(VK_MENU, 0x38, 0, 0);      // ALT presionado
	keybd_event(VK_RETURN, 0x1C, 0, 0);    // ENTER presionado
	keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	while(intento==false){
		salto:
    	int vida = 3;
		intento=true;
	if(inicio==true){
        system("cls");
        SetConsoleOutputCP(CP_UTF8);
        cout << R"(
							            "E.E.T N°2"
	
						██████████████████████████████████████████████
						██                                          ██
						██  ██████████████████████████████████████  ██
						██  ██              ██   ██             ██  ██
						██  ██              ██   ██             ██  ██
						██████          █████████████           ██████
						            ████             ████
						        ████                     ████
						      ██        █████████████        ██
						      ██      ██    ██   ██  ██      ██	
						       ████████     ██   ██  ██      ██
						                    ██   ██  ██      ██
						                    ██   ██  ██      ██
						                    ██	 ████	     ██
						                    ██	 ██        ██
						                    ██ ██        ██
						                    ███        ██
						                  ██         ██
						                ██         ██
						              ██        ███
						            ██        ██ ██
						          ██        ██	 ██
						    	██       █████	 ██
						        ██      ██  ██	 ██
						        ██      ██  ██   ██     
						        ██      ███████████████████████
						        ██                           ██
						        ██                           ██
						        ███████████████████████████████			
						                    ██   ██
						                    ██   ██
						                    ███████		
					
						     "PULSA ENTER PARA INICAR EL PROYECTO"
		)";
        char tecla1;
        do{
        	tecla1 = getch();
		}
        while(tecla1!=13);
	}
	system("cls");

	gotoxy(0, 1);cout << "#################################";
	gotoxy(0, 2);cout << "######## JUEGO HECHO POR ########";
	gotoxy(0, 3);cout << "######## AGUSTIN ORNETTI ########";
	gotoxy(0, 4);cout << "###### TRABAJO COMPUTACION ######";
	gotoxy(0, 5);cout << "#################################";
	sleep(3);
	system("cls");
	gotoxy(0, 1);cout << "┌──────────────────────────────────────┐";
	gotoxy(0, 2);cout << "│usuario =                             │";
	gotoxy(0, 3);cout << "│contraseña =                          │";
	gotoxy(0, 4);cout << "└──────────────────────────────────────┘";
	gotoxy(11, 2);
	usuario = leerusuario();
	gotoxy(15, 3);
	psw = leerusuario();
	ifstream leer(usuario + ".txt");
	if (leer) {
	    leer >> usuarioGuardado;
	    leer >> pswGuardada;
	
	    if (psw == pswGuardada) {
	        gotoxy(14, 6);
	        cout << "Sesion cargada correctamente";
	        this_thread::sleep_for(chrono::seconds(1));
	    } else {
	        gotoxy(14, 6);
	        cout << "Contraseña incorrecta";
	        return 0;
	    }
	}
	leer.close();
	
	gotoxy(0, 7); cout << "Bienvenido " << usuario;
	sleep(2);
	while (_kbhit()) {
        _getch();
    }
	system("cls");
	
	string espaciotexto[13][20] = {
        {"/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",",","/"},
        {"/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/"}
    };

    string matriz15[13][18] = {
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".","f",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","2","3","2","#","#","#","#","#","#","#","#"}
    };

    string matriz14[13][18] = {
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".","e",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","2","3","2","#","#","#","#","#","#","#","#"}
    };

    string matriz13[13][18] = {
        {"#","#","#","#","#","#","#","2","3","2","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"5",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}
    };

    string matriz12[13][18] = {
        {"#","#","#","#","#","#","#","2","3","2","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","4"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}
    };

    string matriz11[13][18] = {
        {"#","#","#","#","#","#","#","2","3","2","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"4",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","5"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}
    };
    
    string matriz6[13][18] = {
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".","#",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".","#",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".","#",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".","#",".",".",".","#",".",".",".",".","l",".",".",".","#"},
        {"#",".",".",".","#",".",".",".","#",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".","#",".",".",".","#",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".","#",".",".",".","#",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".","#",".",".",".","#",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".","#",".",".",".","#",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".","#",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".","#",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","2","3","2","#","#","#","#","#","#","#","#","#","2","1","2","#","#"}
    };

    string matriz5[13][18] = {
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"#",".",".",".","h",".",".",".",".",".",".",".",".",".",".",".",".","|"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}
    };

    string matriz4[13][18] = {
        {"#","#","#","#","#","#","#","2","1","2","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"|",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","2","_","2","#","#","#","#","#","#","#","#"}
    };

    string matriz3[13][18] = {
        {"#","#","#","#","#","#","#","2","_","2","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".","t",".","#"},
        {"|",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}
    };

    string matriz7[13][18] = {
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"#",".",".","0",".",".",".",".",".",".",".",".",".",".",".",".",".","3"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}
    };

    string matriz2[13][18] = {
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"3",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","|"},
        {"2",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","2"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","2","_","2","#","#","#","#","#","#","#","#"}
    };

    string matriz1[13][18] = {
        {"#","#","#","#","#","#","#","2","_","2","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".","m",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","#","E","#","#","#","#","#","#","#","#","#"}
    };

    string matriz[13][18] = {
        {"#","#","#","#","#","#","#","2","_","2","#","#","#","#","#","#","#","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".","m",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".",".","#"},
        {"#","#","#","#","#","#","#","#","E","#","#","#","#","#","#","#","#","#"}
    };
    int fila = 5;
    int columna = 1;
    int mapaActual = 1;
    int opc;
    char izq = 'a';
    char arriba = 'w';
    char abajo = 's';
    char der = 'd';
	bool musica = false, matematicas=false, historia=false, electricidad=false;

	ifstream cargar(usuario + ".txt");
	if (cargar) {
	    cargar >> usuarioGuardado;
	    cargar >> pswGuardada;
		cargar >> fila;
	    cargar >> columna;
		cargar >> mapaActual;
	    cargar >> vida;
	    cargar >> arriba;
	    cargar >> abajo;
		cargar >> izq;
		cargar >> der;
		cargar >> matematicas;
		cargar >> historia;
		cargar >> electricidad;
	}
  	cargar.close();

    if (mapaActual == 2) {
		cargarmapa(matriz,matriz2);
    }
    if (mapaActual == 3) {
		cargarmapa(matriz,matriz3);
	}
    if (mapaActual == 4) {
		cargarmapa(matriz,matriz4);
    }
    if (mapaActual == 5) {
		cargarmapa(matriz,matriz5);
    }
    if (mapaActual == 6) {
		cargarmapa(matriz,matriz6);
    }

    matriz[fila][columna] = "i";

    char tecla, opcion, teclamenu,nueva;
    bool repetirmenu = false, menu = true, volver = false, ayuda = false, hablando = false, creador = false, ganaste=false, morir=false;
	int s=0,contador=0, opcion2=0;
    // MENU
    keybd_event(0x30,0, 0, 0); // tecla para que el texto cargue pq sino no carga
	keybd_event(0x30,0, KEYEVENTF_KEYUP, 0);
    while (intento==true) {
    	while (repetirmenu == false) {
    		PlaySound(NULL, NULL, 0);
	        if (menu) {
	            ayuda = false;
	            volver = false;
	            system("cls");
				gotoxy (5,-2); cout << "┌──────────────────┐";
				gotoxy (5,-1); cout << "│                  │";
				gotoxy (5,0); cout <<  "│                  │";
				gotoxy (5,1); cout <<  "│                  │";
				gotoxy (5,2); cout <<  "│──────────────────│";
				gotoxy (5,3); cout <<  "│                  │";
				gotoxy (5,4); cout <<  "│──────────────────│";
				gotoxy (5,5); cout <<  "│                  │";
				gotoxy (5,6); cout <<  "│──────────────────│";
				gotoxy (5,7); cout <<  "│                  │";
				gotoxy (5,8); cout <<  "│──────────────────│";
				gotoxy (5,9); cout <<  "│                  │";
				gotoxy (5,10); cout << "│──────────────────│";
				gotoxy (5,11); cout << "│                  │";
				gotoxy (5,12); cout << "└──────────────────┘";
	            gotoxy(7, 0); cout << " MENU\n";
	            if(s==0){
					gotoxy(8, 3); cout << " jugar <--";
				}else{
					gotoxy(8, 3); cout << " jugar";
				}
	            if(s==1){
	            	gotoxy(8, 5); cout << " opciones <--";
	            }else{
	            	gotoxy(8, 5); cout << " opciones ";
				}
				if(s==2){
	            	gotoxy(8, 7); cout << " ayuda <--";
	        	}else{
	            	gotoxy(8, 7); cout << " ayuda ";
				}
				if(s==3){
					gotoxy(8, 9); cout << " creador <--";	
	        	}else{
	            	gotoxy(8, 9); cout << " creador ";
				}
				if(s==4){
					gotoxy(8, 11); cout << " salir <--";	
	        	}else{
	            	gotoxy(8, 11); cout << " salir ";
				}
				
	            opcion = _getch();
	            
		        if (opcion==arriba){
		        	if(s>0){
						s--;
					}
		    	}
		        if (opcion==abajo){
		        	if(s<4){
						s++;
					}
		        }
				if (opcion == 13) {
					volver=true;   // Enter
			    	switch (s) {
			    		case 0:
			    			repetirmenu = true;
			    			break;
			        	case 1:
					        while (volver) {
						        system("cls");
								gotoxy (5,-2); cout << "┌──────────────────┐";
								gotoxy (5,-1); cout << "│                  │";
								gotoxy (5,0); cout <<  "│                  │";
								gotoxy (5,1); cout <<  "│                  │";
								gotoxy (5,2); cout <<  "│─────────────────────────────┐";
								gotoxy (5,3); cout <<  "│                             │";
								gotoxy (5,4); cout <<  "│─────────────────────────────│";
								gotoxy (5,5); cout <<  "│                             │";
								gotoxy (5,6); cout <<  "│─────────────────────────────│";
								gotoxy (5,7); cout <<  "│                             │";
								gotoxy (5,8); cout <<  "│─────────────────────────────│";
								gotoxy (5,9); cout <<  "│                             │";
								gotoxy (5,10); cout << "│─────────────────────────────│";
								gotoxy (5,11); cout << "│                             │";
								gotoxy (5,12); cout << "│─────────────────────────────│";
								gotoxy (5,13); cout << "│                             │";
								gotoxy (5,14); cout << "└─────────────────────────────┘";
						        gotoxy(8, 0); cout << "OPCIONES";
						        gotoxy(8, 3); cout << "volver al menu = esc";
						        gotoxy(8, 5); cout << "cambiar controles = espacio";
						        gotoxy(8, 7); cout << "arriba =" << arriba;
						        gotoxy(8, 9); cout << "abajo =" << abajo;
						        gotoxy(8, 11); cout << "izquierda =" << izq;
						        gotoxy(8, 13); cout << "derecha =" << der;
						        teclamenu = _getch();
						        if (teclamenu == 27) {
						            menu = true;
						            volver = false;
						        }
							    if (teclamenu == 32) {
							        system("cls");
									gotoxy (5,0); cout <<  "┌──────────────────────────────────┐";
									gotoxy (5,1); cout <<  "│                                  │";
									gotoxy (5,2); cout <<  "│──────────────────────────────────│";
									gotoxy (5,3); cout <<  "│                                  │";
									gotoxy (5,4); cout <<  "│──────────────────────────────────│";
									gotoxy (5,5); cout <<  "│                                  │";
									gotoxy (5,6); cout <<  "│──────────────────────────────────│";
									gotoxy (5,7); cout <<  "│                                  │";
									gotoxy (5,8); cout <<  "└──────────────────────────────────┘";
							        gotoxy(8, 1); cout << "Nueva tecla para arriba: ";
									arriba = bloquearteclado(0,0,0,0);
							        cout << arriba;
							        gotoxy(8, 3); cout << "Nueva tecla para abajo: ";
									abajo = bloquearteclado(arriba,0,0, 0);
							        cout << abajo;
							        gotoxy(8, 5); cout << "Nueva tecla para izquierda: ";
									izq = bloquearteclado(arriba,abajo, 0, 0);
							        cout << izq;
							        gotoxy(8, 7); cout << "Nueva tecla para derecha: ";
									der = bloquearteclado(arriba, abajo, izq, 0);
							        cout << der;
							        volver = true;
							    }
					    	}
			            	break;
			        	case 2: // Ayuda
			            	ayuda = true;
			            	menu = false;
			            	break;
			        	case 3: // Creador
			        		system("start index.html");
			        		creador = true;
			        		menu = false;
			            	break;
			            case 4: // Creador
							return 0;
			            	break;
			    	}
				}
	        }
	        
	        if (ayuda) {
	            system("cls");
				gotoxy (5,-2); cout << "┌──────────────────┐";
				gotoxy (5,-1); cout << "│                  │";
				gotoxy (5,0); cout <<  "│                  │";
				gotoxy (5,1); cout <<  "│                  │";
				gotoxy (5,2); cout <<  "│─────────────────────────────┐";
				gotoxy (5,3); cout <<  "│                             │";
				gotoxy (5,4); cout <<  "│─────────────────────────────│";
				gotoxy (5,5); cout <<  "│                             │";
				gotoxy (5,6); cout <<  "│─────────────────────────────│";
				gotoxy (5,7); cout <<  "│                             │";
				gotoxy (5,8); cout <<  "│─────────────────────────────│";
				gotoxy (5,9); cout <<  "│                             │";
				gotoxy (5,10); cout << "│─────────────────────────────│";
				gotoxy (5,11); cout << "│                             │";
				gotoxy (5,12); cout << "└─────────────────────────────┘";
	            gotoxy(8, 0); cout << "AYUDA";
	            gotoxy(8, 3); cout << " volver al menu = esc";
	            gotoxy(8, 5); cout << " personaje = azul";
	            gotoxy(8, 7); cout << " profesores = rojo claro";
	            gotoxy(8, 9); cout << " alumnos = violeta";
	            gotoxy(8, 11); cout << " salida = rojo";
	            teclamenu = _getch();
	            if (teclamenu == 27) {
	                menu = true;
	            	ayuda = false;
	            }
	        }      
			if (creador) {
	            system("cls");
				gotoxy (5,-2); cout << "┌──────────────────┐";
				gotoxy (5,-1); cout << "│                  │";
				gotoxy (5,0); cout <<  "│                  │";
				gotoxy (5,1); cout <<  "│                  │";
				gotoxy (5,2); cout <<  "│────────────────────────────┐";
				gotoxy (5,3); cout <<  "│                            │";
				gotoxy (5,4); cout <<  "│────────────────────────────│";
				gotoxy (5,5); cout <<  "│                            │";
				gotoxy (5,6); cout <<  "│────────────────────────────│";
				gotoxy (5,7); cout <<  "│                            │";
				gotoxy (5,8); cout <<  "│────────────────────────────│";
				gotoxy (5,9); cout <<  "│                            │";
				gotoxy (5,10); cout << "└────────────────────────────┘";
	            gotoxy(8, 0); cout << "CREADOR";
	            gotoxy(8, 3); cout << " volver al menu = esc";
	            gotoxy(8, 5); cout << " creador = ornetti agustin";
	            gotoxy(8, 7); cout << " escuela = E.E.T.N2";
	            gotoxy(8, 9); cout << " curso = 5to 1ra";
	            teclamenu = _getch();
	            if (teclamenu == 27) {
	                menu = true;
	                creador = false;
	            }
	        }
		}

        // JUEGO
        
    	PlaySound(TEXT("musica/mapa.wav"), NULL,
        SND_FILENAME | SND_ASYNC | SND_LOOP);
        while (repetirmenu == true) {
            system("cls");
    		hablando = false;
			dibujarmapa(matriz);
            // MINIMAPA
            if(mapaActual<10){
	            gotoxy(38, -1); cout << "PISO 1";
				gotoxy(38, 0);  cout << "     ┌─┐";
				gotoxy(38, 1);  cout << "     │ │";
				gotoxy(38, 2);  cout << "  ┌─┬┼─┤";
				gotoxy(38, 3);  cout << "  │ ├┤ │";
				gotoxy(38, 4);  cout << "  └─┴┤ │";
				gotoxy(38, 5);  cout << "     │ │";
				gotoxy(38, 6);  cout << "┌─┬─┬┼─┤";
				gotoxy(38, 7);  cout << "│ ┤ ├┤ │";
				gotoxy(38, 8);  cout << "└─┼─┼┴─┘";
				gotoxy(38, 9);  cout << "  │ │   ";
				gotoxy(38, 10); cout << "  └─┘   ";
			} else {
				gotoxy(38, -1); cout << "PISO 2";
				gotoxy(38, 0);  cout << " ┌─┐       ┌─┐ ";
				gotoxy(38, 1);  cout << " │ │       │ │ ";
				gotoxy(38, 2);  cout << "┌┴¯┴┬┼¯¯¯┼┬┴¯┴┐";
				gotoxy(38, 3);  cout << "│   ├┤   ├┤   │";
				gotoxy(38, 4);  cout << "└───┴┴───┴┴───┘";
			}
            if (hablando == false) {
                gotoxy(2, 14);
                cout << "esc = opciones || ";
                cout << "controles = ";
                cout << arriba;
                cout << izq;
                cout << abajo;
                cout << der;
                gotoxy(2, 15);
                cout << "interactuar = e";
            }
			if(mapaActual<10){
	            if (mapaActual == 1) { gotoxy(41, 9);  cout << "●"; }
	            if (mapaActual == 2) { gotoxy(41, 7);  cout << "●"; }
	            if (mapaActual == 7) { gotoxy(39, 7);  cout << "●"; }
	            if (matematicas == false) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					gotoxy(39, 7); cout << "●";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
	            if (matematicas == true) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					gotoxy(39, 7); cout << "●";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
	            if (mapaActual == 3) { gotoxy(44, 7);  cout << "●"; }
	            if (mapaActual == 4) { gotoxy(44, 4);  cout << "●"; }
	            if (mapaActual == 5) { gotoxy(41, 3);  cout << "●"; }
	            if (historia == false) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					gotoxy(41, 3); cout << "●";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
	            if (historia == true) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					gotoxy(41, 3); cout << "●";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
	            if (mapaActual == 6) { gotoxy(44, 1);  cout << "●"; }
			}else{			
	            if (mapaActual == 11) { gotoxy(45, 3);  cout << "●"; }
	            if (mapaActual == 12) { gotoxy(40, 3);  cout << "●"; }
	            if (mapaActual == 13) { gotoxy(50, 3);  cout << "●"; }
	            if (mapaActual == 14) { gotoxy(40, 1);  cout << "●"; }
	            if (electricidad == false) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					gotoxy(40, 1); cout << "●";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
	            if (electricidad == true) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					gotoxy(40, 1); cout << "●";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
	            if (mapaActual == 15) { gotoxy(50, 1);  cout << "●"; }
			}
            // MINIMAPA

            // PERSONAJES	
            if (mapaActual == 7) {
                if (matriz[fila][columna+1] == "0" || matriz[fila-1][columna] == "0" ||
                    matriz[fila+1][columna] == "0" || matriz[fila][columna-1] == "0") {
                	if(tecla == 'e' && matematicas==false && contador<3){
	                    hablando = true;
	                    system("cls");
	            	    if(hablando && musica==false){
							PlaySound(TEXT("musica/06 - Rival.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	   	 					musica = true;
						}
						contador=0;
		                matriztexto(espaciotexto);
		                barradevida(vida,hablando);
	                    gotoxy(2, 4); cout << "profe de matematicas :";
						profe();
	                    gotoxy(3, 6); cout << "cuanto es 5x5?";
	                    elegiropcion(vida,"20","25","35","30",2,contador,izq,der);
	                    barradevida(vida,hablando);
						revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
						if(!intento){
							goto salto;
						}
	                    esperar(2);
	                    system("cls");
	                	matriztexto(espaciotexto);
	                	barradevida(vida,hablando);
						gotoxy(2, 4); cout << "profe de matematicas :";
						profe();
	                    gotoxy(3, 6); cout << "ok, siguiente pregunta ";
	                    esperar(2);
	                    gotoxy(3, 6); cout << "                        ";	
	                    gotoxy(3, 6); cout << "cuanto es 5^3?";
	                    elegiropcion(vida,"15","120","50","125",4,contador,izq,der);
	                    barradevida(vida,hablando);
						revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
						if(!intento){
							goto salto;
						}
	                    esperar(1);	 
	                    system("cls");
						matriztexto(espaciotexto);
	                	barradevida(vida,hablando);
						gotoxy(2, 4); cout << "profe de matematicas :";
						profe();
	                    gotoxy(3, 6); cout << "ok, siguiente pregunta ";
	                    esperar(2);
	                    gotoxy(3, 6); cout << "                        ";
	                    gotoxy(3, 6); cout << "cuanto es 4!?";
	                    elegiropcion(vida,"24","22","20","18",1,contador,izq,der);
	                    barradevida(vida,hablando);
						revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
						if(!intento){
							goto salto;
						}
	                    esperar(1);
	                    if(contador==3){
	                    	matematicas=true;
	                    	PlaySound(TEXT("musica/aprobado.wav"), NULL,
							SND_FILENAME | SND_ASYNC);
	                    	system("cls");
	                    	barradevida(vida,hablando);
	                    	matriztexto(espaciotexto);
	                    	gotoxy(2, 4); cout << "profe de matematicas :";
							profe();
	                    	gotoxy(3, 6); cout << "BIEN aprobaste ";
	                    	sleep(5);
						}else {
							system("cls");
							barradevida(vida,hablando);
	                    	matriztexto(espaciotexto);
							profe();
	                    	gotoxy(2, 4); cout << "profe de matematicas :";
	                    	gotoxy(3, 6); cout << "desaprobaste... ";
	                    	gotoxy(3, 7); cout << "volve a intentar ";
						}
                	}else if(tecla == 'e' && matematicas==true && contador==3){
                		system("cls");
                		matriztexto(espaciotexto);
                		profe();
                		gotoxy(2, 4); cout << "profe de matematicas :";
                		gotoxy(3, 6); cout << "podes continuar con la ";
                		gotoxy(3,7); cout << "profe de historia";
                		gotoxy(0, 14); cout << "                                        ";
					}
                }
            }
			if (mapaActual == 5) {
                if (matriz[fila][columna+1] == "h" || matriz[fila-1][columna] == "h" ||
                    matriz[fila+1][columna] == "h" || matriz[fila][columna-1] == "h") {
                	if(tecla == 'e' && historia==false && matematicas==true && contador<6){
                		contador=3;
	                    hablando = true;
	                    system("cls");
	            	    if(hablando && musica==false){
							PlaySound(TEXT("musica/06 - Rival.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	   	 					musica = true;
						}
		                matriztexto(espaciotexto);
		                barradevida(vida,hablando);
	                    gotoxy(2, 4); cout << "profe de historia :";
						profe();
	                    gotoxy(3, 6); cout << "cuando es el dia de la";
	                    gotoxy(3, 7); cout << "revolucion?";
	                    elegiropcion(vida,"20/06","25/05","09/07","24/03",2,contador,izq,der);
	                    barradevida(vida,hablando);
	                    revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
	                    if(!intento){
							goto salto;
						}
	                    esperar(3);
	                    system("cls");
	                	matriztexto(espaciotexto);
	                	barradevida(vida,hablando);
						gotoxy(2, 4); cout << "profe de historia :";
						profe();
	                    gotoxy(3, 6); cout << "ok, siguiente pregunta ";
	                    esperar(2);
	                    gotoxy(3, 6); cout << "                        ";
	                    gotoxy(3, 6); cout << "quien es el creador de";
	                    gotoxy(3, 7); cout << "la bandera";
	                    elegiropcion(vida,"Manuel.B","S.Martin","Irigoyen","Urquiza",1,contador,izq,der);
	                    barradevida(vida,hablando);
	                    revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
	                    if(!intento){
							goto salto;
						}
	                    esperar(1);
	                    system("cls");
	                	matriztexto(espaciotexto);
	                	barradevida(vida,hablando);
						gotoxy(2, 4); cout << "profe de historia :";
						profe();
	                    gotoxy(3, 6); cout << "ok, siguiente pregunta ";
	                    esperar(2);
	                    gotoxy(3, 6); cout << "                        ";
	                    gotoxy(3, 6); cout << "cuando es el dia de";
	                    gotoxy(3, 7); cout << "la independencia?";
	                    elegiropcion(vida,"9/07","25/05","20/06","17/08",1,contador,izq,der);
	                    barradevida(vida,hablando);
	                    revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
	                    if(!intento){
							goto salto;
						}
	                    esperar(1);
	                    if(contador==6){
	                    	historia = true;
	                    	system("cls");
	                    	PlaySound(TEXT("musica/aprobado.wav"), NULL,
							SND_FILENAME | SND_ASYNC);
	                    	barradevida(vida,hablando);
	                    	matriztexto(espaciotexto);
	                    	gotoxy(2, 4); cout << "profe de historia :";
							profe();
	                    	gotoxy(3, 6); cout << "BIEN aprobaste ";
	                    	sleep(5);
						}else {
							system("cls");
							barradevida(vida,hablando);
	                    	matriztexto(espaciotexto);
							profe();
	                    	gotoxy(2, 4); cout << "profe de historia :";
	                    	gotoxy(3, 6); cout << "desaprobaste... ";
	                    	gotoxy(3, 7); cout << "volve a intentar ";
						}
                	}else if(tecla == 'e' && historia==true && contador == 6){
                		system("cls");
                		matriztexto(espaciotexto);
                		profe();
                		gotoxy(2, 4); cout << "profe de historia :";
                		gotoxy(3, 6); cout << "podes continuar con el ";
                		gotoxy(3,7); cout << "profe de electricidad";
                		gotoxy(0, 14); cout << "                                        ";
					}else if(tecla == 'e' && matematicas == false){
                		system("cls");
                		matriztexto(espaciotexto);
                		profe();
                		gotoxy(2, 4); cout << "profe de historia :";
                		gotoxy(3, 6); cout << "primero aprobá matematicas";
                		gotoxy(0, 14); cout << "                                        ";	
					}
                }
            }
			if (mapaActual == 14) {
                if (matriz[fila][columna+1] == "e" || matriz[fila-1][columna] == "e" ||
                    matriz[fila+1][columna] == "e" || matriz[fila][columna-1] == "e") {
                	if(tecla == 'e' && electricidad==false && historia==true && contador<9){
	                    hablando = true;
	                    system("cls");
	            	    if(hablando && musica==false){
							PlaySound(TEXT("musica/06 - Rival.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	   	 					musica = true;
						}
						contador=6;
		                matriztexto(espaciotexto);
		                barradevida(vida,hablando);
	                    gotoxy(2, 4); cout << "profe de electricidad :";
						profe();
	                    gotoxy(3, 6); cout << "cual es la ley de ohm?";
	                    elegiropcion(vida,"i=v/r","v=i/r","R=I/V","I=V*R",1,contador,izq,der);
	                    barradevida(vida,hablando);
						revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
						if(!intento){
							goto salto;
						}
	                    esperar(2);
	                    system("cls");
	                	matriztexto(espaciotexto);
	                	barradevida(vida,hablando);
						gotoxy(2, 4); cout << "profe de electricidad :";
						profe();
	                    gotoxy(3, 6); cout << "ok, siguiente pregunta ";
	                    esperar(2);
	                    gotoxy(3, 6); cout << "                        ";	
	                    gotoxy(3, 6); cout << "cual es la unidad de voltaje?";
	                    elegiropcion(vida,"amp","ohm","watts","volt",4,contador,izq,der);
	                    barradevida(vida,hablando);
						revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
						if(!intento){
							goto salto;
						}
	                    esperar(1);	 
	                    system("cls");
						matriztexto(espaciotexto);
	                	barradevida(vida,hablando);
						gotoxy(2, 4); cout << "profe de electricidad :";
						profe();
	                    gotoxy(3, 6); cout << "ok, siguiente pregunta ";
	                    esperar(2);
	                    gotoxy(3, 6); cout << "                        ";
	                    gotoxy(3, 6); cout << "cual es la unidad de potencia?";
	                    elegiropcion(vida,"Watt","ohm","volt","amper",1,contador,izq,der);
	                    barradevida(vida,hablando);
						revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
						if(!intento){
							goto salto;
						}
	                    esperar(1);
	                    if(contador==9){
	                    	electricidad=true;
	                    	system("cls");
	                    	barradevida(vida,hablando);
	                    	matriztexto(espaciotexto);
	                    	PlaySound(TEXT("musica/aprobado.wav"), NULL,
							SND_FILENAME | SND_ASYNC);
	                    	gotoxy(2, 4); cout << "profe de electricidad :";
							profe();
	                    	gotoxy(3, 6); cout << "BIEN aprobaste ";
	                    	sleep(5);
						}else {
							system("cls");
							barradevida(vida,hablando);
	                    	matriztexto(espaciotexto);
							profe();
	                    	gotoxy(2, 4); cout << "profe de electricidad :";
	                    	gotoxy(3, 6); cout << "desaprobaste... ";
	                    	gotoxy(3, 7); cout << "volve a intentar ";
						}
                	}else if(tecla == 'e' && electricidad==true && contador==9){
                		system("cls");
                		matriztexto(espaciotexto);
                		profe();
                		gotoxy(2, 4); cout << "profe de electricidad :";
                		gotoxy(3, 6); cout << "muy bien...";
                		gotoxy(3,7); cout << "ya podes irte de la escuela";
                		gotoxy(0, 14); cout << "                                        ";
					}
					else if(tecla == 'e' && historia == false){
                		system("cls");
                		matriztexto(espaciotexto);
                		profe();
                		gotoxy(2, 4); cout << "profe de electricidad :";
                		gotoxy(3, 6); cout << "primero aprobá historia";
                		gotoxy(0, 14); cout << "                                        ";	
					}
                }
            }
            if (mapaActual == 3 && tecla=='e') {
                if (matriz[fila][columna+1] == "t" || matriz[fila-1][columna] == "t" ||
                    matriz[fila+1][columna] == "t" || matriz[fila][columna-1] == "t") {
                    system("cls");
                    hablando=true;
	            	if(hablando && musica==false){
						PlaySound(TEXT("musica/npc.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	   	 				musica = true;
					}
					if(historia==false){
	                    matriztexto(espaciotexto);
			            barradevida(vida,hablando);
	                    gotoxy(2, 4); cout << "thiago : ";
	                    profe();
	                    gotoxy(2, 6); cout << "Holaaaaaaaa";	
						esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 6); cout << "por allá está la profe de        ";
	                    gotoxy(2, 7); cout << "historia    ";
						esperarEnter();
						gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 7); cout << "                                 ";
	                    gotoxy(2, 6); cout << "estas profes son muy estrictas";
	                    gotoxy(2, 7); cout << "hay que responder todo bien...";
	                    esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 7); cout << "                                 ";
	                    gotoxy(2, 6); cout << "ami me desaprobo la de historia";
	                    gotoxy(2, 7); cout << "es una....";
	                    esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 7); cout << "                                 ";
	                    gotoxy(2, 6); cout << "bueno no importa, suerte.";
					}else{
						matriztexto(espaciotexto);
			            barradevida(vida,hablando);
	                    gotoxy(2, 4); cout << "thiago : ";
	                    profe();
	                    gotoxy(2, 6); cout << "No amigo aprobaste historia";	
						esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 6); cout << "tenes un re aura amigo        ";
	                    gotoxy(2, 7); cout << "te quiero    ";
						esperarEnter();
						gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 7); cout << "                                 ";
	                    gotoxy(2, 6); cout << "igual era mentira yo no ";
	                    gotoxy(2, 7); cout << "desaprobe";
	                    esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 7); cout << "                                 ";
	                    gotoxy(2, 6); cout << "XDDDD";
					}
                }
            }

            if (mapaActual == 1 && tecla=='e') {
                if (matriz[fila][columna+1] == "m" || matriz[fila-1][columna] == "m" ||
                    matriz[fila+1][columna] == "m" || matriz[fila][columna-1] == "m") {
                    system("cls");
                    hablando=true;
	            	if(hablando && musica==false){
						PlaySound(TEXT("musica/npc.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	   	 				musica = true;
					}
					if(matematicas==false && historia==false && electricidad==false){
	                    matriztexto(espaciotexto);
			            barradevida(vida,hablando);
	                    gotoxy(2, 4); cout << "preceptor : ";
	                    profe();
	                    gotoxy(2, 6); cout << "Hola, bienvenido a la tecnica n°2";
						esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 6); cout << "como pudiste ver, por la salida  ";
	                    gotoxy(2, 7); cout << "no es posible irse, pero...";
						esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 7); cout << "                                 ";
	                    gotoxy(2, 6); cout << "hay una forma, y es..";
	                    gotoxy(2, 7); cout << "aprobando las 3 materias, suerte";
					}else{
						matriztexto(espaciotexto);
			            barradevida(vida,hablando);
	                    gotoxy(2, 4); cout << "preceptor : ";
	                    profe();
	                    gotoxy(2, 6); cout << "Pudiste aprobar todas las ";
	                    gotoxy(2, 7); cout << "materias ";
						esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 6); cout << "muy bien, ya te podes ir ";
	                    gotoxy(2, 7); cout << "espero te hayas divertido";
					}
				}
			}
        	if (mapaActual == 6 && tecla=='e') {
                if (matriz[fila][columna+1] == "l" || matriz[fila-1][columna] == "l" ||
                    matriz[fila+1][columna] == "l" || matriz[fila][columna-1] == "l") {
                    system("cls");
                    hablando=true;
	            	if(hablando && musica==false){
						PlaySound(TEXT("musica/npc.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	   	 				musica = true;
					}
					if(electricidad==false){
	                    matriztexto(espaciotexto);
			            barradevida(vida,hablando);
	                    gotoxy(2, 4); cout << "lauty (triste) : ";
	                    profe();
	                    gotoxy(2, 6); cout << "hola......";	
						esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 6); cout << "por allá está el profe de        ";
	                    gotoxy(2, 7); cout << "electricidad....    ";
						esperarEnter();
						gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 7); cout << "                                 ";
	                    gotoxy(2, 6); cout << "lo odio..";
	                    gotoxy(2, 7); cout << "me desaprobo :c...";
	                    esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 7); cout << "                                 ";
	                    gotoxy(2, 6); cout << "suerte amix.";
					}else{
						matriztexto(espaciotexto);
			            barradevida(vida,hablando);
	                    gotoxy(2, 4); cout << "lauty (envidioso) : ";
	                    profe();
	                    gotoxy(2, 6); cout << "holaaa";	
						esperarEnter();
	                    gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 6); cout << "le diste su merecido a ese       ";
	                    gotoxy(2, 7); cout << "desgraciado....    ";
						esperarEnter();
						gotoxy(2, 6); cout << "                                 ";
	                    gotoxy(2, 7); cout << "                                 ";
	                    gotoxy(2, 6); cout << "la siguiente..";
	                    gotoxy(2, 7); cout << "aprobare :)...";
					}
                }
            }
        	if (mapaActual == 15 && tecla=='e') {
                if (matriz[fila][columna+1] == "f" || matriz[fila-1][columna] == "f" ||
                    matriz[fila+1][columna] == "f" || matriz[fila][columna-1] == "f") {
				    system("cls");
                    hablando=true;
	            	if(hablando && musica==false){
						PlaySound(TEXT("musica/npc.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	   	 				musica = true;
					}
				    if(opcion2==0){
					    matriztexto(espaciotexto);
					    barradevida(vida,hablando);
					    profe();
					    gotoxy(2, 4); cout << "joaquin : ";
					    gotoxy(4, 6); cout << "hola queres una vida? xd";
					    esperarEnter();
						gotoxy(2, 6); cout << "                                 ";
					    gotoxy(4, 6); cout << "hay un 50% de probabilidad de";
					    gotoxy(4, 7); cout << "que te sume una vida";
					    esperarEnter();
						gotoxy(2, 6); cout << "                                 ";
		                gotoxy(2, 7); cout << "                                 ";
						gotoxy(4, 6); cout << "pero tambien hay 50% de que";
					    gotoxy(4, 7); cout << "te quite una vida";
					    esperarEnter();
						gotoxy(2, 6); cout << "                                 ";
		                gotoxy(2, 7); cout << "                                 ";
						gotoxy(4, 6); cout << "solo es 1 intento";
					    gotoxy(4, 7); cout << "queres probar?";
						while (_kbhit()) {
				        _getch();
					    }
					    Sleep(150);
						int seleccion = 1;
					    while (true){
							gotoxy (6,14); cout <<  "┌──────────┐";
							gotoxy (6,15); cout <<  "│    si    │";
							gotoxy (6,16); cout <<  "└──────────┘";
							gotoxy (18,14); cout << "┌──────────┐";
							gotoxy (18,15); cout << "│    no    │";
							gotoxy (18,16); cout << "└──────────┘";
					        
							if(seleccion == 1){
					        	gotoxy(7,15); cout << "> ";
							}else{
								gotoxy(7,15); cout << "  ";
							}
							if(seleccion == 2){
					        	gotoxy(19,15); cout << "> ";
							}else{
								gotoxy(19,15); cout << "  ";
							}
							
					        tecla = _getch();
					
					        if(tecla==izq && seleccion>1)
					            seleccion--;
					
					        if(tecla==der && seleccion<2)
					            seleccion++;
					
							if (tecla == 13) {
							    if (seleccion == 1) {
							        opcion2 = 3;
							
							        int probabilidad = rand() % 100;
							
							        if (probabilidad < 50) {
							            if(vida==3){
							            	gotoxy(2, 6); cout << "                                 ";
							            	gotoxy(2, 7); cout << "                                 ";
											gotoxy(4, 6); cout << "ya tenes el maximo de vida";
							            	opcion2=5;
										}else{
											gotoxy(2, 6); cout << "                                 ";
							                gotoxy(2, 7); cout << "                                 ";
											gotoxy(4, 6); cout << "ganaste una vida, muy bien";
											vida++;
											opcion2=3;
											barradevida(vida,hablando);
										}
							        
									} else {
										gotoxy(2, 6); cout << "                                 ";
						                gotoxy(2, 7); cout << "                                 ";
										gotoxy(4, 6); cout << "perdiste una vida";
									    gotoxy(4, 7); cout << "tonto";
										vida--;
										opcion2=4;
										revisarMuerte(vida,usuario,tecla,arriba,abajo,izq,der,repetirmenu,intento);
										if(!intento){
											goto salto;
										}
										barradevida(vida,hablando);
							        }
							
							    } else {
							        opcion2 = 4;
							    }
							
							    break;
							}
					    }
					}else if(opcion2==3){
						matriztexto(espaciotexto);
					    barradevida(vida,hablando);
					    profe();
					    gotoxy(2, 4); cout << "joaquin : ";
					    gotoxy(4, 6); cout << "muy bien, ganaste una vida";
					}else if(opcion2==4){
						matriztexto(espaciotexto);
					    barradevida(vida,hablando);
					    profe();
					    gotoxy(2, 4); cout << "joaquin : ";
					    gotoxy(4, 6); cout << "perdiste una vida";
					    gotoxy(4, 7); cout << "alto tonto";
					}else if(opcion2==5){
						matriztexto(espaciotexto);
					    barradevida(vida,hablando);
					    profe();
					    gotoxy(2, 4); cout << "joaquin : ";
					    gotoxy(4, 6); cout << "ya tenes 3 vidas";
					    gotoxy(4, 7); cout << "no podes tener mas :v";
					}
				}
			}
            if(contador==9){
            	ganaste=true;
			}
            
 			if (hablando==false && musica) {
    			PlaySound(TEXT("musica/mapa.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    			musica = false;
			}
            // PERSONAJES

            // BARRA DE VIDA
 			barradevida(vida,hablando);
            // BARRA DE VIDA
			
            tecla = _getch();
            matriz[fila][columna] = ".";
			//bloqueos
            
			if (tecla == arriba) fila--;
            if (tecla == abajo) fila++;
            if (tecla == izq) columna--;
            if (tecla == der) columna++;
            
        	bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "#");
        	bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "m");
        	bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "t");
        	bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "0");
        	bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "2");
        	bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "h");
        	bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "f");
        	bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "e");
        	bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "l");
       
        	if(ganaste==false){
        		bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "E");
			}
		
        	if (mapaActual==1) {bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "|");}
        	if (mapaActual==2) {bloquear(tecla, arriba, abajo, izq, 0, fila, columna, matriz, "|");}
        	if (mapaActual==2) {bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "-");}
        	if (mapaActual==3) {bloquear(tecla, arriba, abajo, 0, der, fila, columna, matriz, "|");}
        	if (mapaActual==3) {bloquear(tecla, arriba, abajo, izq, der, fila, columna, matriz, "-");}
            // bloqueos

            // MAPEADO
            if (mapaActual == 1 || mapaActual == 2) {
                if (matriz[fila][columna] == "_") {
                    if (mapaActual == 1) {
						cambiarmapa(matriz, matriz2,fila,columna,mapaActual,11,8,2);
                    } else {
						cambiarmapa(matriz, matriz1,fila,columna,mapaActual,1,8,1);
                    }
                }
            }
				
            if (mapaActual == 2) {
                if (matriz[fila][columna] == "|") {
					cambiarmapa(matriz, matriz3,fila,columna,mapaActual,6,1,3);
                }
            }else if (mapaActual == 3 && matriz[fila][columna] == "|") {
				cambiarmapa(matriz, matriz2,fila,columna,mapaActual,6,16,2);
            }
            
            if (mapaActual == 2) {
                if (matriz[fila][columna] == "3") {
					cambiarmapa(matriz, matriz7,fila,columna,mapaActual,6,16,7);
                }
            }else if (mapaActual == 7 && matriz[fila][columna] == "3") {
				cambiarmapa(matriz, matriz2,fila,columna,mapaActual,6,1,2);
            }

            if (mapaActual == 3) {
                if (matriz[fila][columna] == "_") {
					cambiarmapa(matriz, matriz4,fila,columna,mapaActual,11,8,4);
 
                }
            } else if (mapaActual == 4 && matriz[fila][columna] == "_") {
				cambiarmapa(matriz, matriz3,fila,columna,mapaActual,1,8,3);

            }

            if (mapaActual == 4) {
                if (matriz[fila][columna] == "|") {
					cambiarmapa(matriz, matriz5,fila,columna,mapaActual,6,16,5);
                }
            } else if (mapaActual == 5 && matriz[fila][columna] == "|") {
				cambiarmapa(matriz, matriz4,fila,columna,mapaActual,6,1,4);
            }
            
            if (mapaActual == 4) {
                if (matriz[fila][columna] == "1") {
					cambiarmapa(matriz, matriz6,fila,columna,mapaActual,11,14,6);
                }	
            } else if (mapaActual == 6 && matriz[fila][columna] == "1") {
				cambiarmapa(matriz, matriz4,fila,columna,mapaActual,1,8,4);
            }
            
            if (mapaActual == 6) {
                if (matriz[fila][columna] == "3") {
					cambiarmapa(matriz, matriz11,fila,columna,mapaActual,1,8,11);
                }	
            } else if (mapaActual == 11 && matriz[fila][columna] == "3") {
				cambiarmapa(matriz, matriz6,fila,columna,mapaActual,11,2,6);
            }
            
            if (mapaActual == 11) {
                if (matriz[fila][columna] == "4") {
					cambiarmapa(matriz, matriz12,fila,columna,mapaActual,6,16,12);
                }	
            } else if (mapaActual == 12 && matriz[fila][columna] == "4") {
				cambiarmapa(matriz, matriz11,fila,columna,mapaActual,6,1,11);
            }
            
            if (mapaActual == 11) {
                if (matriz[fila][columna] == "5") {
					cambiarmapa(matriz, matriz13,fila,columna,mapaActual,6,1,13);
                }	
            } else if (mapaActual == 13 && matriz[fila][columna] == "5") {
				cambiarmapa(matriz, matriz11,fila,columna,mapaActual,6,16,11);
            }
            
            if (mapaActual == 12) {
                if (matriz[fila][columna] == "3") {
					cambiarmapa(matriz, matriz14,fila,columna,mapaActual,11,8,14);
                }	
            } else if (mapaActual == 14 && matriz[fila][columna] == "3") {
				cambiarmapa(matriz, matriz12,fila,columna,mapaActual,1,8,12);
            }
            
            if (mapaActual == 13) {
                if (matriz[fila][columna] == "3") {
					cambiarmapa(matriz, matriz15,fila,columna,mapaActual,11,8,15);
                }	
            } else if (mapaActual == 15 && matriz[fila][columna] == "3") {
				cambiarmapa(matriz, matriz13,fila,columna,mapaActual,1,8,13);
            }

            // MAPEADO

            // PERDER

            if (morir==true) {
                system("color 40");
                system("cls");
                SetConsoleOutputCP(CP_UTF8);
                gotoxy(30, 8);
                cout << R"(

				██████  ███████ ██████  ██████  ██ ███████ ████████ ███████
                ██   ██ ██      ██   ██ ██   ██ ██ ██         ██    ██
                ██████  █████   ██████  ██   ██ ██ ███████    ██    █████
                ██      ██      ██   ██ ██   ██ ██      ██    ██    ██
                ██      ███████ ██   ██ ██████  ██ ███████    ██    ███████ ██ ██ ██

                )";
                gotoxy(25, 25);
                cout << "                                                                        ";
                remove((usuario + ".txt").c_str());
                return 0;
            }
            
            if (matriz[fila][columna] == "E") {
				system("color 20");
				system("cls");
				SetConsoleOutputCP(CP_UTF8);
				PlaySound(TEXT("musica/aprobado.wav"), NULL, SND_FILENAME | SND_ASYNC);
				gotoxy(0, 2);
				cout << R"(
	
						 ██████   █████  ███    ██  █████  ███████ ████████ ███████
						██       ██   ██ ████   ██ ██   ██ ██         ██    ██
						██   ███ ███████ ██ ██  ██ ███████ ███████    ██    █████
						██    ██ ██   ██ ██  ██ ██ ██   ██      ██    ██    ██
						 ██████  ██   ██ ██   ████ ██   ██ ███████    ██    ███████
				
				)";
				gotoxy(10, 25);
				cout << "                                                                        ";
				gotoxy(5,12);cout << " queres volver a jugar?";
				int seleccion=1;
				while(true){
					gotoxy (6,14); cout <<  "┌──────────┐";
					gotoxy (6,15); cout <<  "│    si    │";
					gotoxy (6,16); cout <<  "└──────────┘";
					gotoxy (18,14); cout << "┌──────────┐";
					gotoxy (18,15); cout << "│    no    │";
					gotoxy (18,16); cout << "└──────────┘";
			        
					if(seleccion == 1){
			        	gotoxy(7,15); cout << "> ";
					}else{
						gotoxy(7,15); cout << "  ";
					}
					if(seleccion == 2){
			        	gotoxy(19,15); cout << "> ";
					}else{
						gotoxy(19,15); cout << "  ";
					}
					
			        tecla = _getch();
			
			        if(tecla==izq && seleccion>1)
			            seleccion--;
			
			        if(tecla==der && seleccion<2)
			            seleccion++;
			
					if (tecla == 13) {
					    if (seleccion == 1) {
					    	system("cls");
							system("color 07");
							remove((usuario + ".txt").c_str());
							goto salto;
							break;
					    } else {
					        remove((usuario + ".txt").c_str());
                			return 0;
					    }
					    break;
					}
			    }
            }
            // PERDER

            ofstream guardar(usuario + ".txt");
            guardar << usuario << endl;
            guardar << psw  << endl;
            guardar << fila  << endl;
            guardar << columna << endl;
            guardar << mapaActual << endl;
            guardar << vida   << endl;
            guardar << arriba << endl;
            guardar << abajo << endl;
            guardar << izq  << endl;
            guardar << der  << endl;
            guardar << matematicas  << endl;
            guardar << historia  << endl;
            guardar << electricidad  << endl;
            guardar.close();
            if (matriz[fila][columna] == "E" ){
            	vida=0;}
            
			matriz[fila][columna] = "i";
			
            if (tecla == 27){
                repetirmenu = false;
			}
        }
    }
}
}
void gotoxy(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    COORD coord;
    coord.X = x + 53;
    coord.Y = y + 15;
    SetConsoleCursorPosition(hConsole, coord);
}
void cambiarmapa(string matriz[13][18], string nuevomapa[13][18], int &fila, int &columna, int &mapaActual, int fila1, int columna1, int mapaActual1){
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 18; j++){
            matriz[i][j] = nuevomapa[i][j];
        }
	}
    mapaActual=mapaActual1;
    fila=fila1;
    columna=columna1;
}

void cargarmapa(string matriz[13][18], string nuevomapa[13][18]){
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 18; j++){
            matriz[i][j] = nuevomapa[i][j];
        }
	}
}

void elegiropcion(int &vida,string r1,string r2,string r3,string r4,int correcta,int &contador,char izq,char der){
    while (_kbhit()) {
        _getch();
    }
    Sleep(150);
    int seleccion = 0;
    char tecla;
    while (true){
    	
		gotoxy (-6,14); cout << "┌──────────┐";
		gotoxy (-6,15); cout << "│          │";
		gotoxy (-6,16); cout << "└──────────┘";
		gotoxy (6,14); cout << "┌──────────┐";
		gotoxy (6,15); cout << "│          │";
		gotoxy (6,16); cout << "└──────────┘";
		gotoxy (18,14); cout << "┌──────────┐";
		gotoxy (18,15); cout << "│          │";
		gotoxy (18,16); cout << "└──────────┘";
		gotoxy (30,14); cout << "┌──────────┐";
		gotoxy (30,15); cout << "│          │";
		gotoxy (30,16); cout << "└──────────┘";
        
		if(seleccion == 0){
        	gotoxy(-5,15); cout << "> " << r1;
		}else{
			gotoxy(-5,15); cout << "  " << r1;
		}
		if(seleccion == 1){
        	gotoxy(7,15); cout << "> "<< r2;
		}else{
			gotoxy(7,15); cout << "  " << r2;
		}
		if(seleccion == 2){
        	gotoxy(19,15); cout << "> " << r3;
		}else{
			gotoxy(19,15); cout << "  " << r3;
		}
		if(seleccion == 3){
        	gotoxy(31,15); cout << "> " << r4;
		}else{
			gotoxy(31,15); cout << "  " << r4;
		}
		
        tecla = _getch();

        if(tecla==izq && seleccion>0)
            seleccion--;

        if(tecla==der && seleccion<3)
            seleccion++;

        if(tecla==13)   // Enter
            break;
    }

    if(seleccion+1 == correcta)
    {
		gotoxy (19,-8); cout << "┌──────────┐";
		gotoxy (19,-7); cout << "│          │";
		gotoxy (19,-6); cout << "└──────────┘";
		gotoxy (18,-5); cout << "/";
        gotoxy(22,-7);
        cout << "Bien";
        contador++;
    }
    else
    {
		gotoxy (19,-8); cout << "┌──────────┐";
		gotoxy (19,-7); cout << "│          │";	
		gotoxy (19,-6); cout << "└──────────┘";
		gotoxy (18,-5); cout << "/";
        gotoxy(22,-7);
        cout << "Mal";
        vida--;
    }
}
void bloquear(char tecla, char arriba, char abajo, char izq, char der, int &fila, int &columna,string matriz[13][18], string pj){

	if (matriz[fila][columna] == pj) {
		if (tecla == arriba) {fila++;}
		if (tecla == abajo) {fila--;}
		if (tecla == izq) {columna++;}
		if (tecla == der) {columna--;}
	}
}

void esperar(int s){
	this_thread::sleep_for(chrono::seconds(s));
}
void esperarmilis(int m){
	this_thread::sleep_for(chrono::milliseconds(m));
}

void dibujarmapa(string matriz[13][18]){
	for (int i = 0; i < 13; i++) {
		gotoxy(0,0+i);
		for (int j = 0; j < 18; j++) {
			dibujarBloque(matriz[i][j]);
		}
		cout << endl;
	}
}
void matriztexto(string espaciotexto[14][20]){
	for (int i = 0; i < 13; i++) {
		gotoxy(-2,0+i);
		for (int j = 0; j < 20; j++) {
			dibujarBloque(espaciotexto[i][j]);
		}
		cout << endl;
	}
}

void dibujarBloque(string bloque){
	if (bloque == "#"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Blanco/grisxd
	    cout << "██";
	}
	else if (bloque == "."){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Verde claro
	    cout << "██";
	}
	else if (bloque == "i"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); // Azul claro
	    cout << "██";
	}
	else if (bloque == "f"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // Azul claro
	    cout << "██";
	}
	else if (bloque == "|"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // amarillo
	    cout << "██";
	}
	else if (bloque == "_"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // amarillo
	    cout << "██";
	}
	else if (bloque == "2"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // amarillo
	    cout << "██";
	}
	else if (bloque == "3"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // amarillo
	    cout << "██";
	}
	else if (bloque == "4"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // amarillo
	    cout << "██";
	}
	else if (bloque == "5"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // amarillo
	    cout << "██";
	}
	else if (bloque == "1"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // amarillo
	    cout << "██";
	}
	else if (bloque == "0"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Rojo claro
	    cout << "██";
	}
	else if (bloque == "i"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Rojo claro
	    cout << "██";
	}
	else if (bloque == "e"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Rojo claro
	    cout << "██";
	}
	else if (bloque == "h"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Rojo claro
	    cout << "██";
	}
	else if (bloque == "m"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Violeta
	    cout << "██";
	}
	else if (bloque == "l"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // Violeta
	    cout << "██";
	}
	else if (bloque == "t"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); 
	    cout << "██";
	}
	else if (bloque == "E"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Rojo oscuro
	    cout << "██";
	}
	else if (bloque == "-"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Amarillo
	    cout << "██";
	}
	else if (bloque == "/"){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Blanco
	    cout << "██";
	}
	else if (bloque == ","){
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0); // Negro
	    cout << "██";
	}
	else{
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Rojo
	    cout << "??";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Restaurar color
}
void profe(){
	gotoxy(15,-4); cout << "O";
	gotoxy(15,-3); cout << "|";
	gotoxy(14,-3); cout << "/";
	gotoxy(16,-3); cout << "\\";
    gotoxy(14,-2); cout << "/";
	gotoxy(16,-2); cout << "\\";
}
void explosion(){
	int x=50,limite=16;
	bool a=true;
	gotoxy (19,-8); cout << "┌──────────┐";
	gotoxy (19,-7); cout << "│          │";	
	gotoxy (19,-6); cout << "└──────────┘";
	gotoxy (18,-5); cout << "/";
    gotoxy(22,-7);
    cout << "!!!!";
    esperarmilis(500);
    gotoxy (19,-8); cout << "            ";
	gotoxy (19,-7); cout << "            ";	
	gotoxy (19,-6); cout << "            ";
	gotoxy (18,-5); cout << "  ";
	while(a==true){
		gotoxy(x,-5); cout << "u\\_u\\       /";
		gotoxy(x,-4); cout << " |º_º|_____/ ";
		gotoxy(x,-3); cout << "     |_____| ";
		gotoxy(x,-2); cout << "     |     | ";
		esperarmilis(20);
		gotoxy(x,-5); cout << "                ";
		gotoxy(x,-4); cout << "                          ";
		gotoxy(x,-3); cout << "                          ";
		gotoxy(x,-2); cout << "             ";
		if (limite<x){
			x--;
		}
		if (x==16){
			PlaySound(TEXT("musica/explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
			gotoxy(13,-5); cout << " \\ \\      /  /";
			gotoxy(13,-4); cout << " \\  \\    / /  ";
			gotoxy(13,-3); cout << " explosion pum";
			gotoxy(13,-2); cout << " /  /   \\  \\  ";
			
			HWND hwnd = GetConsoleWindow();
			RECT r;
			GetWindowRect(hwnd, &r);
			for(int i=0;i<10;i++){
			    SetWindowPos(hwnd,0,r.left+5,r.top,0,0,SWP_NOSIZE);
			    Sleep(20);
			    SetWindowPos(hwnd,0,r.left-5,r.top,0,0,SWP_NOSIZE);
			    Sleep(20);
			}
			esperarmilis(400);
			gotoxy(13,-5); cout << "                   ";
			gotoxy(13,-4); cout << "                   ";
			gotoxy(13,-3); cout << "                   ";
			gotoxy(13,-2); cout << "                   ";
			esperar(1);
			a=false;
		}
	}
    gotoxy(2, 4); cout <<  " ???????????????      ";
    gotoxy(3, 6); cout <<  "                      ";
    gotoxy(3, 6); cout <<  "  ya no hay nadie xd  ";
    gotoxy(3,7); cout <<   "                      ";
    gotoxy(0, 14); cout << "                      ";
    keybd_event(VK_MENU, 0x38, 0, 0);      // ALT presionado
	keybd_event(VK_RETURN, 0x1C, 0, 0);    // ENTER presionado
	keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, 0, 0);      // ALT presionado
	keybd_event(VK_RETURN, 0x1C, 0, 0);    // ENTER presionado
	keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}
void barradevida(int &vida,bool &hablando){
    gotoxy(-9, 0);
    int a=-8,b=-6;
    if (hablando){
    	a-=1;
    	b-=1;
	}
    cout << "Vida: ";
    gotoxy(a,1);  cout << "┌────┐";
    gotoxy(a,2);  cout << "│    │";
    gotoxy(a,3);  cout << "│    │";
    gotoxy(a,4);  cout << "│    │";
    gotoxy(a,5); cout <<  "│    │";
    gotoxy(a,6); cout <<  "│    │";
    gotoxy(a,7); cout <<  "│    │";
    gotoxy(a,8); cout <<  "│    │";
    gotoxy(a,9); cout <<  "│    │";
    gotoxy(a,10); cout << "│    │";
    gotoxy(a,11); cout << "└────┘";
    for (int i = 0; i < vida; i++) {
        gotoxy(b,8 - i * 3);  cout << "██";
    	gotoxy(b,9 - i * 3);  cout << "██";
    	gotoxy(b,10 - i * 3); cout << "██";
    }
}

void esperarEnter() {

    char tecla;
    do {
        tecla = _getch();
    } while (tecla != 13);
	
    while (_kbhit())
        _getch();
}
void revisarMuerte(int vida, string usuario,char tecla, char arriba, char abajo, char izq, char der,bool &repetirmenu,bool &intento){
    if(vida <= 0){
    	sleep(2);
        system("color 40");
        system("cls");
        SetConsoleOutputCP(CP_UTF8);

        gotoxy(0, 0);
        cout << R"(
       						██████  ███████ ██████  ██████  ██ ███████ ████████ ███████
      						██   ██ ██      ██   ██ ██   ██ ██ ██         ██    ██
      						██████  █████   ██████  ██   ██ ██ ███████    ██    █████
      						██      ██      ██   ██ ██   ██ ██      ██    ██    ██
      						██      ███████ ██   ██ ██████  ██ ███████    ██    ███████

        )";
        gotoxy(25, 25);
		gotoxy(5,12);cout << " queres volver a intentarlo?";
		int seleccion=1;
		while(true){
			gotoxy (6,14); cout <<  "┌──────────┐";
			gotoxy (6,15); cout <<  "│    si    │";
			gotoxy (6,16); cout <<  "└──────────┘";
			gotoxy (18,14); cout << "┌──────────┐";
			gotoxy (18,15); cout << "│    no    │";
			gotoxy (18,16); cout << "└──────────┘";
	        
			if(seleccion == 1){
	        	gotoxy(7,15); cout << "> ";
			}else{
				gotoxy(7,15); cout << "  ";
			}
			if(seleccion == 2){
	        	gotoxy(19,15); cout << "> ";
			}else{
				gotoxy(19,15); cout << "  ";
			}
			
	        tecla = _getch();
	
	        if(tecla==izq && seleccion>1)
	            seleccion--;
	
	        if(tecla==der && seleccion<2)
	            seleccion++;
	
			if (tecla == 13) {
			    if (seleccion == 1) {
			    	system("cls");
					system("color 07");
					remove((usuario + ".txt").c_str());
					repetirmenu = false;
					intento=false;
			    } else {
			        remove((usuario + ".txt").c_str());
        			exit(0);
			    }
			    break;
			}
	    }
    }
}

char bloquearteclado(char t1, char t2, char t3, char t4) {
    char nueva;
    do {
        nueva = getch();
        if (nueva == 0 || nueva == (char)224) {
            getch();
            nueva = 0;
            continue;
        }

        if (nueva >= 'A' && nueva <= 'Z')
            nueva += 32;

    } while (nueva < 'a' || nueva > 'z' || nueva == t1 || nueva == t2 || nueva == t3 || nueva == t4);

    return nueva;
}

string leerusuario(){
    string texto;
    char tecla;

    while (true) {
        tecla = _getch();

        if (tecla == 13) {
            if (!texto.empty()) {
                cout << endl;
                return texto;
            }
        }

        else if (tecla == 8) {
            if (!texto.empty()) {
                texto.pop_back();
                cout << "\b \b";
            }
        }

        else if (tecla != ' ' && tecla != '\t') {
            texto += tecla;
            cout << tecla;
        }
    }
}