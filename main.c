#include <stdio.h>
#include <stdlib.h>

 #define PART2
 #define PART3
// #define PART4
// #define PART5
// #define PART6

struct ceg
{
    char telephely[31];
    unsigned int dolgozok;
    double ertekeles;
    unsigned int epuletek;
};


// 1. feladat ->

struct ceg* kellmemoria(unsigned int meret)
{
    struct ceg* array = (struct ceg*)calloc(meret, sizeof(struct ceg));
    return array;
}

void torol(struct ceg* tomb)
{
    free(tomb);
}

void cegEgyetBeker(struct ceg* ceg)
{
    scanf("%30s",   ceg->telephely);
    scanf("%u",     &ceg->dolgozok);
    scanf("%lf",  &ceg->ertekeles);
    scanf("%u",     &ceg->epuletek);
}

void kiirtomb(struct ceg* ceg, unsigned int meret){

    for (int i = 0; i < meret; i++)
    {
        printf("%s ", ceg[i].telephely);
        printf("%u ", ceg[i].dolgozok);
        printf("%.2lf", ceg[i].ertekeles);
        printf("%u\n ", ceg[i].epuletek);
    }
    
}
// <- 1. feladat 


// 2. feladat ->
unsigned int feladat2(struct ceg* ceg, unsigned int meret){

    unsigned int szamlalo = 0;
    for (int i = 0; i < meret; i++)
    {
        if (ceg[i].dolgozok < 714)
        {
            szamlalo++;
        }
    }

    return szamlalo;
}
// <- 2. feladat 

// 3. feladat ->
void feladat3(const char *fajlnev){

    const unsigned int N = 4;
    struct ceg* tomb = kellmemoria(N);

    FILE* fajl = fopen(fajlnev, "r");

    for (unsigned int i = 0; i < N; i++)
    {
        fscanf(fajl,"%30s %u %lf %u",
                tomb[i].telephely,
                &tomb[i].dolgozok,
                &tomb[i].ertekeles,
                &tomb[i].epuletek
                );
    }

    fclose((fajl));

    kiirtomb(tomb, N);

    unsigned int kisebb = feladat2(tomb, N);
    printf("%u\n", kisebb);

    torol(tomb);
    
}
// <- 3. feladat 

// 4. feladat ->
void fajlba(struct ceg* ceg, unsigned int meret, const char *fajlnev)
{
    FILE* fajl = fopen(fajlnev, "w");

    for (int i = 0; i < meret; i++)
    {
        fprintf(fajl,"%u\n", ceg[i].dolgozok);
    }
    fclose(fajl);
}
// <- 4. feladat 

// 5. feladat ->
struct cseretarolo
{
    struct ceg *elso;
    struct ceg *masodik;
};

void kigyujtes(struct ceg* ceg, int szam1, int szam2, struct cseretarolo* cseretarolo)
{
    //A memóriacímek eltárolása
    cseretarolo->elso = &ceg[szam1];
    cseretarolo->masodik = &ceg[szam2];
}

void modosito(struct cseretarolo* cseretarolo)
{
    unsigned int temp;

    //1. A tempen eltároljuk a struct ceg *elso értékeit.
    temp = cseretarolo->elso->epuletek;

    //2. Az első cég adatait felülírjuk a második cég értékével.
    cseretarolo->elso->epuletek = cseretarolo->masodik->epuletek;

    //3. A második cég adatait felülírjuk az eredetileg elmentettel(temp)
    cseretarolo->masodik->epuletek = temp;
}
// <- 5. feladat 

// 6. feladat ->
struct ceg* nagytombcsinalo(struct ceg* ceg1, unsigned int cegMeret1, struct ceg* ceg2, unsigned int cegMeret2)
{
    // 1. Kiszámoljuk az új, nagy tömb teljes méretét
    unsigned int ujMeret = cegMeret1 + cegMeret2;

    // 2. Memóriát foglalunk az új tömbnek (calloc biztosítja, hogy tiszta, nullázott memóriát kapjunk)
    struct ceg* nagytomb = (struct ceg*)calloc(ujMeret, sizeof(struct ceg));

    // 3. Bemásoljuk az első tömböt az új tömb elejére
    for (unsigned int i = 0; i < cegMeret1; i++)
    {
        nagytomb[i] = ceg1[i];
    }

    // 4. Bemásoljuk a második tömböt közvetlenül az első tömb után.
    // A nagytomb indexe itt a cegMeret1-től indul
    for (unsigned int i = 0; i < cegMeret2; i++)
    {
        nagytomb[cegMeret1 + i] = ceg2[i];
    }

    // 5. Visszatérünk az újonnan foglalt tömb címével
    return nagytomb;
}


// <- 6. feladat 

int main()
{
    printf("\n--START OF PART1--\n");
    unsigned int meret;
    scanf("%u", &meret);
    struct ceg *tomb;
    tomb=kellmemoria(meret);
    {
        unsigned int i;
        for (i=0;i < meret;i++)
            cegEgyetBeker(&tomb[i]);
    }
    kiirtomb(tomb, meret);
        
    printf("\n--END OF PART1--\n");
    
    #ifdef PART2
    printf("\n--START OF PART2--\n");
    unsigned int szamlalas = feladat2(tomb, meret);
    printf("%u\n", szamlalas);
    printf("\n--END OF PART2--\n");
    #endif
    
    char fajlnev3[50];
    scanf("%s", fajlnev3);
    #ifdef PART3
    printf("\n--START OF PART3--\n");
    feladat3(fajlnev3);
    printf("\n--END OF PART3--\n");
    #endif
    
    char fajlnev4[50];
    scanf("%s", fajlnev4);
    #ifdef PART4
    printf("\n--START OF PART4--\n");
    fajlba(tomb, meret, fajlnev4);
    printf("Fajl tartalma:\n");
    FILE* fp = fopen(fajlnev4, "r");
    char buffer[255];
    if (fp)
    {
        while(fgets(buffer, 255, fp)) {
            printf("%s", buffer);
        }
        fclose(fp);
    }
    printf("\n--END OF PART4--\n");
    #endif

    int index1, index2;
    scanf("%d %d", &index1, &index2);
    #ifdef PART5
    printf("\n--START OF PART5--\n");
    // Lemásoljuk, hogy ne az eredetit babráljuk
    struct ceg *masolat=kellmemoria(meret);
    unsigned int i;
    for (i=0; i < meret; i++)
        masolat[i]=tomb[i];
    struct cseretarolo gyujtemeny;
    kigyujtes(masolat, index1, index2, &gyujtemeny);
    modosito(&gyujtemeny);
    printf("Modositas utan:\n");
    kiirtomb(masolat,meret);
    torol(masolat);
    printf("\n--END OF PART5--\n");
    #endif
    
    unsigned int masikmeret;
    scanf("%u", &masikmeret);
    #ifdef PART6
    printf("\n--START OF PART6--\n");
    {
        // Lemásoljuk, hogy ne az eredetit babráljuk
        struct ceg *egyiktomb=kellmemoria(meret);
        unsigned int i;
        for (i=0; i < meret; i++)
            egyiktomb[i]=tomb[i];
        struct ceg* masiktomb = kellmemoria(masikmeret);
        for (i=0;i < masikmeret;i++)
            cegEgyetBeker(&masiktomb[i]);
        struct ceg* nagytomb = nagytombcsinalo(egyiktomb, meret, masiktomb, masikmeret);
        kiirtomb(nagytomb,meret+masikmeret);
        torol(egyiktomb);
        torol(masiktomb);
        torol(nagytomb);
    }
    printf("\n--END OF PART6--\n");
    #endif
    
    printf("\n--START OF PART1--\n");
    torol(tomb);
    printf("\n--END OF PART1--\n");
    
    return 0;
}