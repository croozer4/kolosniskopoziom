#include <iostream>

using namespace std;

void vec_avx_add_int(int* t1, int* t2, int* t3, int n)
{
    __asm
    {
        push esi; //zabezpiecz rejest
        push edi; //zabezpiecz rejest
        mov ecx, n; //do ecx wprowadzamy wartosc n
        shl ecx, 2; //przesuniecie bitowe o 2 miejsca w lewo, czyli mnozenie razy 4
        mov esi, t1; //do esi wprowadzamy adres t1
        mov edx, t2; //do edx wprowadzamy adres t2
        mov edi, t3; //do edi wprowadzamy adres t3
    petla:
        sub ecx, 32; //od wartosci rejestru ecx odejmujemy 32
        vmovdqu ymm0, ymmword ptr[esi + ecx]; //wyciagamy z t1 wartosc z kazdego rejestru
        vmovdqu ymm1, ymmword ptr[edx + ecx]; //wyciagamy z t2 wartosc z kazdego rejestru
        vpaddd ymm2, ymm1, ymm0; // dodajemy t1 i t2, wynik zapisujemy w ymm2
        vmovdqu ymmword ptr[edi + ecx], ymm2; // zapisujemy w t3
        jnz petla; // jezeli nie jest rowne 0 to wykonaj petle
        pop edi; // odzyskaj rejest
        pop esi; // odzyskaj rejest
    }

	
}

void vec_avx_sub_int(int* t1, int* t2, int* t3, int n)
{
    __asm
    {
        push esi; //zabezpiczamy rejestr esi
        push edi; //zabezpieczamy rejestr edi
        mov ecx, n; // do ecx wprowadzamy wartosc n
        shl ecx, 2; //mnozymy wartosc exc razy 4
        mov esi, t1; //przenosimy do rejestru esi adres t1
        mov edx, t2; //przenisimy do rejestru edx adres t2
        mov edi, t3; //przenosimy do rejestru edi adres t3
    petla:
        sub ecx, 32; //odejmujemy od ecx wartosc 32
        vmovdqu ymm0, ymmword ptr[esi + ecx]; // wyciagamy z t1 wartosc z kazdego rejestru
        vmovdqu ymm1, ymmword ptr[edx + ecx]; //wyciagamy z t2 wartosc z kazdego rejestru
        vpsubd ymm2, ymm1, ymm0; // odejmujemy rejestry t1 i t2, wynik zapisujemy w ymm2
        vmovdqu ymmword ptr[edi + ecx], ymm2; // przenosimy do t3
        jnz petla; //jezeli nie dotarlizmy do konca to petla sie wykonuje
        pop edi; // przywracamy rejestr edi
        pop esi; // przywracamy rejestr esi

    fxtoy:
        fyl2x;
        fld st;
        frndint;
        fsub st(1), st;
        fxch;
        f2xm1;
        fld1;
        fadd;
        fscale;
        fstp st(1);
        ret;
		
    }
}

void mtx2_avx_add_int(int** t1, int** t2, int** t3, int n, int m)
{
    __asm
    {
        push esi; //zabezpiczamy rejestr esi
        push edi; //zabezpieczamy rejestr edi
        mov eax, n; //przenosimy do eax wartosc n
    petlaN:
        mov esi, t1; //do esi przenosimy adres t1
        mov esi, [esi + eax * 4 - 4];  //przenosimy do esi adres t1[eax-1]
        mov edx, t2; //do edx przenosimy adres t2
        mov edx, [edx + eax * 4 - 4]; //przenosimy do edx adres t2[eax-1]
        mov edi, t3; //do edi przenosimy adres t3
        mov edi, [edi + eax * 4 - 4]; //przenosimy do edi adres t3[eax-1]
        mov ecx, m; //do ecx przenosimy wartosc m
        shl ecx, 2; //mnozymy wartosc ecx razy 4
    petlaM:
        sub ecx, 32; //odejmujemy od ecx wartosc 32
        vmovdqu ymm0, ymmword ptr[esi + ecx]; // wyciagamy z t1 wartosc z kazdego rejestru
        vmovdqu ymm1, ymmword ptr[edx + ecx]; // wyciagamy z t2 wartosc z kazdego rejestru
        vpaddd ymm2, ymm1, ymm0; // dodajemy t1 i t2, wynik zapisujemy w ymm2
        vmovdqu ymmword ptr[edi + ecx], ymm2; // zapisujemy w t3
        jnz petlaM; // jezeli nie dotarlizmy do konca to petla sie wykonuje
        dec eax; //odejmujemy od eax wartosc 1
        jnz petlaN; // jezeli nie dotarlizmy do konca to petla sie wykonuje
        pop edi; // przywracamy rejestr edi
        pop esi; // przywracamy rejestr esi
    }
}

void mtx2_avx_sub_float(float** t1, float** t2, float** t3, int n, int m)
{
    __asm
    {
        push esi; // zabezpieczamy rejestr esi
        push edi; // zabezpieczamy rejestr edi
        mov eax, n; // przenosimy do eax wartosc n
    petlaN: // petla n
        mov esi, t1; // do esi przenosimy adres t1
        mov esi, dword ptr[esi + eax * 4 - 4]; // przenosimy do esi adres t1[eax-1]
        mov edx, t2; // do edx przenosimy adres t2
        mov edx, dword ptr[edx + eax * 4 - 4]; // przenosimy do edx adres t2[eax-1]
        mov edi, t3; // do edi przenosimy adres t3
        mov edi, dword ptr[edi + eax * 4 - 4]; // przenosimy do edi adres t3[eax-1]
        mov ecx, m; // do ecx przenosimy wartosc m
        shl ecx, 2; // mnozymy wartosc ecx razy 4
    petlaM:
        sub ecx, 32; // odejmujemy od ecx wartosc 32
        vmovups ymm0, ymmword ptr[esi + ecx]; // 
        vmovups ymm1, ymmword ptr[edx + ecx];
        vsubps ymm2, ymm1, ymm0;
        vmovups ymmword ptr[edi + ecx], ymm2;
        jnz petlaM;
        dec eax;
        jnz petlaN;
        pop edi;
        pop esi;
    }
}

void vec_avx_sub_float(float* t1, float* t2, float* t3, int n)
{
    __asm
    {
        push esi;
        push edi;
        mov ecx, n;
        shl ecx, 2;
        mov esi, t1;
        mov edx, t2;
        mov edi, t3;
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

//14

double wielomian_v5(double a, double b, double c, double d, double x)
{
    double wynik = 0;
    __asm
    {
        vmovsd xmm0, x; //przeniesienie x do rejestru xmm0 za pomoca vmovsd
        vmovsd xmm1, a; //przeniesienie a do rejestru xmm1 za pomoca vmovsd
        vmovsd xmm2, b; //przeniesienie b do rejestru xmm2 za pomoca vmovsd
        vmovsd xmm3, c; //przeniesienie c do rejestru xmm3 za pomoca vmovsd
        vmovsd xmm4, d; //przeniesienie d do rejestru xmm4 za pomoca vmovsd
        vfmadd213sd xmm1, xmm0, xmm2; ax + b; //pomnozenie a przez x i dodanie b za pomocą instrukcji vfmadd213sd która mnoży rejest drugi przez pierwszy i dodaje rejest trzeci
        vfmadd213sd xmm1, xmm0, xmm3; (ax + b)x + c; //pomnozenie wyrazenia ax+b przez x i dodanie c za pomocą instrukcji vfmadd213sd która mnoży rejest drugi przez pierwszy i dodaje rejest trzeci
        vfmadd213sd xmm0, xmm1, xmm4; ((ax + b)x + c)x + d; //pomnozenie wyrazenia ((ax+b)x+c) przez x i dodanie d za pomocą instrukcji vfmadd213sd która mnoży rejest drugi przez pierwszy i dodaje rejest trzeci
        vmovsd wynik, xmm0; //przeniesienie wyniku z rejestru xmm0 do wyniku
    }
    return wynik;
}

double wielomian_moj(double a, double b, double c, double d, double x) {
	double wynik = 0;

    __asm {
		vmovsd xmm0, x; //przeniesienie x do rejestru xmm0 za pomoca vmovsd
		vmovsd xmm1, a; //przeniesienie a do rejestru xmm1 za pomoca vmovsd
		vmovsd xmm2, b; //przeniesienie b do rejestru xmm2 za pomoca vmovsd
		vmovsd xmm3, c; //przeniesienie c do rejestru xmm3 za pomoca vmovsd
		vmovsd xmm4, d; //przeniesienie d do rejestru xmm4 za pomoca vmovsd
		
		vfmadd213sd xmm1, xmm0, xmm2; ax + b; //pomnozenie a przez x i dodanie b za pomocą instrukcji vfmadd123sd która mnoży rejest pierwszy przez drugi i dodaje rejest trzeci
		vfmadd213sd xmm1, xmm0, xmm3; (x(ax + b)) + c; //pomnozenie wyrazenia ax+b przez x i dodanie c za pomocą instrukcji vfmadd123sd która mnoży rejest pierwszy przez drugi i dodaje rejest trzeci
        vfmadd213sd xmm0, xmm1, xmm4; (x(x(ax + b)) + c) + d; //pomnozenie wyrazenia (x(ax + b)) + c przez x i dodanie d za pomocą instrukcji vfmadd123sd która mnoży rejest pierwszy przez drugi i dodaje rejest trzeci
		
		vmovsd wynik, xmm0; //przeniesienie wyniku z rejestru xmm1 do wyniku
    }

    return wynik;
}

void Transponuj4x4(double** tab)
{
    __asm
    {
        // ; transponuje macierz tab o domyślnym rozmiarze 4x4
        // ; elementy qword lub double/INT64 lub zespolone single
        push esi; // 
        mov esi, tab ;//wskaznik na tabele przeniosimy do rejestru esi
            mov eax, [esi] ;//wskaznik na pierwszy wiersz tabeli przenosimy do eax
            mov ecx, [esi + 8] ;//wskaznik na trzeci wiersz tabeli przenosimy do ecx
            mov edx, [esi + 12] ;//wskaznik na czwarty wiersz tabeli przenosimy do edx
            mov esi, [esi + 4] ;//wskaznik na drugi wiersz tabeli przenosimy do esi

            vmovdqu ymm0, ymmword ptr[eax] ; // przeniesienie pierwszego wiersza do rejestru ymm0
            vmovdqu ymm1, ymmword ptr[ecx] // przeniesienie trzeciego wiersza do rejestru ymm1
            vperm2i128 ymm2, ymm0, ymm1, 20h // zamiana kolejności elementów w rejestrze ymm0 i ymm1
            vperm2i128 ymm4, ymm0, ymm1, 31h // zamiana kolejności elementów w rejestrze ymm0 i ymm1

            vmovdqu ymm0, ymmword ptr[esi] // przeniesienie drugiego wiersza do rejestru ymm0
            vmovdqu ymm1, ymmword ptr[edx] // przeniesienie czwartego wiersza do rejestru ymm1
            vperm2i128 ymm3, ymm0, ymm1, 20h // zamiana kolejności elementów w rejestrze ymm0 i ymm1
            vperm2i128 ymm5, ymm0, ymm1, 31h // zamiana kolejności elementów w rejestrze ymm0 i ymm1

            vpunpcklqdq ymm0, ymm2, ymm3 // złączenie kolejno wierszy w rejestrze ymm0
            vpunpckhqdq ymm1, ymm2, ymm3 // złączenie kolejno wierszy w rejestrze ymm1
            vpunpcklqdq ymm2, ymm4, ymm5 // złączenie kolejno wierszy w rejestrze ymm2
            vpunpckhqdq ymm3, ymm4, ymm5 // złączenie kolejno wierszy w rejestrze ymm3

            vmovdqu ymmword ptr[eax], ymm0 // przeniesienie wyniku do pierwszego wiersza tabeli
            vmovdqu ymmword ptr[esi], ymm1 // przeniesienie wyniku do drugiego wiersza tabeli
            vmovdqu ymmword ptr[ecx], ymm2 // przeniesienie wyniku do trzeciego wiersza tabeli
            vmovdqu ymmword ptr[edx], ymm3 // przeniesienie wyniku do czwartego wiersza tabeli
            pop esi; // przeniesienie wskaznika z rejestru esi do stosu

            push esi;
			mov esi, tab ;//wskaznik na tabele przeniosimy do rejestru esi
            mov eax, esi; //pierwszy
            mov ecx, [esi + 8]; // trzeci
            mov edx, [esi + 12]; // czwarty
            mov esi, [esi + 4]; // drugi

			vmovdqu ymm0, ymmword ptr[eax] ; // przeniesienie pierwszego wiersza do rejestru ymm0
            vmovdqu ymm1, ymmword ptr[ecx];

            vperm2i128 ymm2, ymm0, ymm1, 20h; // zamiana kolejności elementów w rejestrze ymm0 i ymm1
            vperm2i128 ymm4, ymm0, ymm1, 31h; // 
			
			vmovdqu ymm0, ymmword ptr[esi] ; // przeniesienie drugiego wiersza do rejestru ymm0
			vmovdqu ymm1, ymmword ptr[edx];

			vperm2i128 ymm3, ymm0, ymm1, 20h; // zamiana kolejności elementów w rejestrze ymm0 i ymm1
			vperm2i128 ymm5, ymm0, ymm1, 31h; //
			

    }
}

//15

int ileBitow(int n) {
    _asm {
        mov eax, n;
        shl eax, 4;
        ret;
    }
}

void cos() {
    _asm {
        Mov ecx, 11223344h
        Mov eax, 87654321h
        Shr eax, 4 //przesuwa bity w prawo o ilość podanych w b 
        Bts eax, 0;
    }
}

int zwrocWieksza(int a, int b) {

    int wynik;
	
    _asm {
		mov eax, a;
		mov ebx, b;
		cmp eax, ebx;
		ja awieksza;
		mov wynik, ebx;
		jmp koniec;
    awieksza:
        mov wynik, eax;
    koniec:
    }

    return wynik;
}

int main()
{

    int* tab0 = new int[8];
    int* tab1 = new int[8];
    int* tab2 = new int[8];

    for (int i = 0; i < 8; i++) {
        tab0[i] = 0;
        tab1[i] = 3;
        tab2[i] = 2;
    }

    cout << endl << "pierwszy wektor: " << endl;

    for (int i = 0; i < 8; i++) {
        cout << tab1[i] << " ";
    }

    cout << endl << "drugi wektor: " << endl;

    for (int i = 0; i < 8; i++) {
        cout << tab2[i] << " ";
    }

    cout << endl << "dodawanie: " << endl;

    vec_avx_add_int(tab1, tab2, tab0, 8);

    for (int i = 0; i < 8; i++) {
        cout << tab0[i] << " ";
    }

    cout << endl << "odejmowanie: " << endl;

    //vec_avx_sub_int(tab1, tab2, tab0, 8);

    for (int i = 0; i < 8; i++) {
        cout << tab0[i] << " ";
    }

    cout << endl << "MACIERZE" << endl;

    int** macierz0 = new int*[8];
    int** macierz1 = new int*[8];
    int** macierz2 = new int*[8];

    for (int i = 0; i < 8; i++) {
        macierz0[i] = new int[8];
        macierz1[i] = new int[8];
        macierz2[i] = new int[8];

        for (int j = 0; j < 8; j++) {
            macierz0[i][j] = 0;
            macierz1[i][j] = 1;
            macierz2[i][j] = 2;
        }
    }
    cout << endl << "macierz pierwsza: " << endl;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << macierz1[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "macierz druga: " << endl;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << macierz2[i][j] << " ";
        }
        cout << endl;
    }

    mtx2_avx_add_int(macierz1, macierz2, macierz0, 8, 8);

    cout << endl << "dodawanie macierzy: " << endl;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << macierz0[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "liczby zmiennoprzecinkowe" << endl;

    float* tabfloat0 = new float[8];
    float* tabfloat1 = new float[8];
    float* tabfloat2 = new float[8];

    for (int i = 0; i < 8; i++) {
        tabfloat0[i] = 0;
        tabfloat1[i] = 3.5;
        tabfloat2[i] = 2.5;
    }

    vec_avx_sub_float(tabfloat1, tabfloat2, tabfloat0, 8);

    cout << endl << "odejmowanie zmiennoprzecinkowych" << endl;

    for (int i = 0; i < 8; i++) {
        cout << tabfloat0[i] << " ";
    }

    cout << endl <<"funkcja wielomianu: " << endl;

    double wynikWielomianu = wielomian_v5(3, 4, 5, 6, 2);

    cout << "wynik wielomiuanu to: " << wynikWielomianu << endl;

    double wynikWielomianuMojego = wielomian_moj(3, 4, 5, 6, 2);

	cout << "wynik wielomiuanu mojego to: " << wynikWielomianuMojego << endl;
    
	//macierz dynaminczna 4x4

    int l = 0;
	double** macierzDyn = new double*[4];
	for (int i = 0; i < 4; i++) {
		macierzDyn[i] = new double[4];
        for (int j = 0; j < 4; j++) {
            macierzDyn[i][j] = l;
            l++;
        }
	}

    //Transponuj4x4(macierzDyn);

    cout << "wyswietlam macierz po transponowaniu: " << endl;
	
	for(int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << macierzDyn[i][j] << " ";
		}
		cout << endl;
	}

    int nwielkosc = 8;

    cout << "tu dziala jeszcze" << endl;
	
    cout << "Wieksza liczba to " << zwrocWieksza(-2, -1);
	
    cos();
    return 0;
}

