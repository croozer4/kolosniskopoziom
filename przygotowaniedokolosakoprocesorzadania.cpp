#include <iostream>

using namespace std;

float logarytm(float b, float x) {

	float wynik;
	_asm {
		fldl2e;
		fld x;
		fyl2x;
		fldl2e;
		fld b;
		fyl2x;
		fdiv;
		fstp wynik;
	}

	return wynik;
}

float zadanie2(float a, float b, float x) {
	
	float wynik;
	_asm {
		fld a; //a

		fld x; // x, a

		fmulp st(1), st; 
		fld b;
		fdivp st(1), st;

		fldpi; // pi , x, a

		mov eax, 180;
		push eax; // 180, pi, x, a
		fild dword ptr[esp];
		pop eax;

		fdivp st(1), st; // pi/180, x, a
		fmulp st(1), st; // x/(pi/180), a

		fcos;
		fld x;

		fldpi; // pi , x, cos(x * a / b)

		mov eax, 180;
		push eax; // 180, pi, x, cos(x * a / b)
		fild dword ptr[esp];
		pop eax;

		fdivp st(1), st; // pi/180, x, cos(x * a / b)
		fmulp st(1), st; // x/(pi/180), cos(x * a / b)

		fptan;
		fstp wynik;
		fld1;
		fdivrp st(1), st;
		fsubrp st(1), st;
		fabs;
		fsqrt;
		fldpi;
		fmulp st(1), st;
		fstp wynik;
	}

	return wynik;
}

double zadanie3(double* w) {
	double wynik;

	_asm {
		mov ecx, w;
		mov edx, 6;
		fld qword ptr[ecx + edx * 8 - 8];
		fld st;
		fmulp st(1), st;
		dec edx;

	petla :
		fld qword ptr[ecx + edx * 8 - 8];
		fld st;
		fmulp st(1), st;
		faddp st(1), st;
		dec edx;
		jnz petla;
		fsqrt;
		fstp wynik;
	}

	return wynik;
}

void zadanie4(float* v1, float* v2, float* v3, int n) {
	_asm {
		push esi;
		push edi;
		mov ecx, n;
		shl ecx, 2;
		mov esi, v1;
		mov edx, v2;
		mov edi, v3;

	petla:
		sub ecx, 32;
		vmovups ymm0, ymmword ptr[esi + ecx];
		vmovups ymm1, ymmword ptr[edx + ecx];
		vsubps ymm2, ymm1, ymm0;
		vmovups ymmword ptr[edi + ecx], ymm2;
		jnz petla;
		pop edi;
		pop esi;
	}
}

float zadanie5(float x, float y, float a, float b, float c){

	float wynik;
	_asm {
		vmovss xmm0, x;
		vmovss xmm1, y;
		vmovss xmm2, a;
		vmovss xmm3, b;
		vmovss xmm4, c;
		
		vmulss xmm2, xmm2, xmm0;
		vmulss xmm2, xmm2, xmm0;

		vmulss xmm4, xmm4, xmm0;
		vmulss xmm4, xmm4, xmm0;
		vmulss xmm4, xmm4, xmm0;

		vaddss xmm2, xmm2, xmm3;

		vsubss xmm0, xmm0, xmm4;

		vdivss xmm1, xmm2, xmm0;
		vmovss wynik, xmm1;

	}

	return wynik;
}

//KOLOS PIERWSZY TERMIN

double zadanie1v2(double a, double b, double y) {

	double wynik;
	_asm {
		fld b;
		fld a;
		fcomi st, st(1);
		jbe poprawny;
		mov eax, 2;
		push eax;
		fild dword ptr[esp];
		pop eax;
		fmulp st(1), st;
		jmp koniec;

	poprawny:
		fxch;
		mov eax, 5;
		push eax;
		fild dword ptr[esp];
		pop eax;
		fmulp st(1), st;
	koniec:
		fstp wynik;
	}

	return wynik;
}

float zadanie2v2(float a, float b, float x) {

	float wynik;

	_asm {
		fld a;
		fld x;
		fmulp st(1), st;
		fldpi;
		mov eax, 180;
		push eax;
		fild dword ptr[esp];
		pop eax;
		fdivp st(1), st;
		fmulp st(1), st;
		fcos;
		fld x;
		fld b;
		fdivp st(1), st;
		fldpi;
		mov eax, 180;
		push eax;
		fild dword ptr[esp];
		pop eax;
		fdivp st(1), st;
		fmulp st(1), st;
		fptan;
		fstp wynik;
		fsubrp st(1), st;
		fstp wynik;
	}

	return wynik;
}

double zadanie3v2(double* w) {

	double wynik;

	_asm {
		mov ecx, 128;
		mov eax, ecx;
		mov edx, w;
		fld qword ptr[edx + ecx * 8 - 8];
		dec ecx;

	petla:
		fld qword ptr[edx + ecx * 8 - 8];
		faddp st(1), st;
		dec ecx;
		jnz petla;

		push eax;
		fild dword ptr[esp];
		pop eax;
		fdivp st(1), st;
		fstp wynik;
	}

	return wynik;
}

void zadanie4v2(double* v1, double* v2, double* v3, int n) {
	_asm {
		push esi;
		push edi;
		mov ecx, n;
		shl ecx, 3;
		mov esi, v1;
		mov edx, v2;
		mov edi, v3;

	petla:
		sub ecx, 32;
		vmovupd ymm0, ymmword ptr[esi + ecx];
		vmovupd ymm1, ymmword ptr[edx + ecx];
		vaddpd ymm2, ymm1, ymm0;
		vmovupd ymmword ptr[edi + ecx], ymm2;
		jnz petla;
		pop edi;
		pop esi;
	}
}

float zadanie5v2(float x, float y, float a, float b, float c) {

	float wynik;

	_asm {
		vmovss xmm0, x;
		vmovss xmm1, y;
		vmovss xmm2, a;
		vmovss xmm3, b;
		vmovss xmm4, c;

		vmulss xmm2, xmm2, xmm0;
		vmulss xmm2, xmm2, xmm0;
		vmulss xmm2, xmm2, xmm0;
		vaddss xmm2, xmm2, xmm3;

		vsubss xmm0, xmm0, xmm4;
		vdivss xmm1, xmm2, xmm0;
		vmovss wynik, xmm1;
	}

	return wynik;
}

int main()
{
	//zadanie 1 kolos poprawka

	float wynikLogarytmu = logarytm(4, 2);
	cout << "Wynik logarytmu to: " << wynikLogarytmu << endl;

	//zadanie 2 kolos poprawka

	float wynikZadanie2 = zadanie2(2, 3, 60);
	cout << "Wynik zadania2 to: " << wynikZadanie2 << endl;

	//zadanie3 kolos poprawka

	double* tablica = new double[6];

	for (int i = 0; i < 6; i++) {
		tablica[i] = i;
	}

	//for (int i = 0; i < 64; i++) {
	//	cout << tablica[i] << ", ";
	//}

	double wynikZadanie3 = zadanie3(tablica);
	cout << "Wynik zadania3 to: " << wynikZadanie3 << endl;

	int poprawny = 0;
	for (int i = 0; i < 64; i++) {
		poprawny += i;
	}

	cout << "Poprawny wynik zadania3 to: " << poprawny << endl;

	//zadanie4 kolos poprawka

	float* tablicazad41 = new float[16];
	float* tablicazad42 = new float[16];
	float* tablicazad43 = new float[16];

	for (int i = 0; i < 16; i++) {
		tablicazad41[i] = 1.5;
		tablicazad42[i] = 2.5;
		tablicazad43[i] = 0;
	}

	zadanie4(tablicazad41, tablicazad42, tablicazad43, 16);

	cout << "Tablica wynikowana zadania4: ";

	for (int i = 0; i < 16; i++) {
		cout << tablicazad43[i] << ", ";
	}

	//zadanie5 kolos poprawka

	float wynik5 = zadanie5(1,2,3,4,5);

	cout << "Wynik zadanie5 to: " << wynik5 << endl;

	//zadanie1v2 kolos 1 termin

	double wynik1v2 = zadanie1v2(1, 2, 3);

	cout << "Wynik zadania1v2 to: " << wynik1v2 << endl;

	//zadanie2v2 kolos 1 termin

	double wynik2v2 = zadanie2v2(1, 2, 60);

	cout << "Wynik zadania2v2 to: " << wynik2v2 << endl;

	//zadanie3v2 kolos 1 termin

	double* tablica3v2 = new double[128];
	
	double* tablicaTestowa = new double[5];
	tablicaTestowa[0] = 2;
	tablicaTestowa[1] = 2;
	tablicaTestowa[2] = 3;
	tablicaTestowa[3] = 3;
	tablicaTestowa[4] = 5;

	for (int i = 0; i < 64; i++) {
		tablica3v2[i] = 2;
	}	

	for (int i = 64; i < 128; i++) {
		tablica3v2[i] = 1;
	}

	//for (int i = 64; i < 128; i++) {
	//	tablica3v2[i] = 3;
	//}

	double wynik3v2 = zadanie3v2(tablica3v2);

	cout << "Wynik zadania3v2 to: " << wynik3v2 << endl;

	//zadanie4v2 kolos 1 termin

	double* tablicazad41v2 = new double[4];
	double* tablicazad42v2 = new double[4];
	double* tablicazad43v2 = new double[4];

	for (int i = 0; i < 4; i++) {
		tablicazad41v2[i] = 1.5;
		tablicazad42v2[i] = 3;
		tablicazad43v2[i] = 0;
	}

	tablicazad42v2[0] = 1;
	tablicazad42v2[1] = 2;
	tablicazad42v2[2] = 3;
	tablicazad42v2[3] = 4;

	zadanie4v2(tablicazad41v2, tablicazad42v2, tablicazad43v2, 4);

	cout << "Wynik zadania4v2 to: ";

	for (int i = 0; i < 4; i++) {
		cout << tablicazad43v2[i] << ", ";
	}

	//zadanie5v2 kolos 1 termin

	float wynik5v2 = zadanie5v2(1, 2, 3, 4, 5);

	cout << "Wynik zadania5v2 to: " << wynik5v2;

	return 0;
}

