/*
Napište program, který implementuje manipulaci s velmi jednoduchou „databází“ záznamů o osobě s možností ukládání do souboru a možností řazení dle různých položek ovládaného z příkazové řádky pomocí parametrů.
Pro jednoznačnost zadání se prosím řiďte následujícími pokyny:

    Deklarujte datový typ struktury (ideální místo pro použití typedef), který pojmenujte TZaznam, ta bude mít následující položky:
        jmeno a prijmeni typu char*
        rc typu řetězce s napevno nastavenou maximální délkou 10 užitných znaků
        vek bezznaménkového celočíselného typu
        pohlavi typu TPohlavi (vizte dále)
    Deklarujte datový typ TPohlavi jako výčtový typ (enum) se dvěma konstantami:
        muz
        zena
    Jejich vhodnou hodnotu si zvolte sami.

    Ve svém řešení implementujte funkce s následujícími prototypy:
        TZaznam * zalozZaznam(const char *jmeno, const char *prijmeni, const char *rc, const unsigned int vek, const TPohlavi pohlavi);
            Funkce vytvoří nový záznam (alokuje odpovídající množství paměti pomocí funkce malloc()),
            položky jmeno a prijmeni též alokuje dynamicky pouze na potřebnou délku (dle předaných parametrů),
            nový záznam funkce naplní dle hodnot parametrů,
            a odkaz na nový záznam vrátí.
            V případě, že se nepodaří alokovat paměť, alokované části nového záznamu zase uvolní (funkce free()) a vrátí NULL. 
        void zrusZaznam(TZaznam * zaznam);
            Neobsahuje-li parametr pouze hodnotu NULL, tak funkce uvolní alokovanou pamět okupovanou odkazovaným záznamem.
            Pozor na to, že je třeba separátně uvolnit položky jmeno a prijmeni a pak vlastní záznam.
        void zrusZaznamy(TZaznam **zaznamy, size_t pocetZaznamu);
            Uvolní veškerou paměť alokovanou odkazovanými záznamy.
            Pro uvolnění jednotlivých záznamů použije funkci zrusZaznam().
        void vypisZaznamy(FILE *stream, const TZaznam **zaznamy, size_t pocetZaznamu);
            Funkce vypíše položky jednotlivých záznamů do proudu odkazovaného parametrem stream (můžete použít funkci fprintf()).
            Formát výstupu zvolte tak, aby výstup této funkce mohl sloužit jako vstup při načítání položek.
            (Tedy strohý bez doplňujících vysvětlení, pouze hodnoty oddělené bílými znaky, např. mezery či nové řádky.)

    Pro snadné získání parametrů předaných programu na příkazové řádce změňte hlavičku funkce main například takto (možností je více):
    int main(int argc, char **argv)
        argc pak bude obsahovat počet parametrů předaných programu
        argv pak bude představovat pole řetězců obsahující jednotlivé parametry

    (Pozor: na cvičeních jsem upozorňoval, ale raději zopakuji: v případě C (jiné jazyky mají někdy jinak) je obsazen první parametr (s indexem 0) názvem spouštěného programu, takže když spustíte například program takto:
    ./muj_program -cti soubor.txt
    [pod MS Windows bez „./“]
    bude řetězec "-cti" přítomen až v argv[1] a "soubor.txt" v argv[2] a argc bude rovno 3)

    Ve funkci main deklarujte ukazatel na ukazatel na TZaznam (dynamické pole ukazatelů na TZaznam):
    TZaznam ** zaznamy = NULL;
        Toto pole při čtení záznamů nejprve alokujte (funkce malloc()) a pak dle potřeby zvětšujte (funkce realloc()).
        Sem ukládejte jednotlivé záznamy.
        Pozor: jedná se o dynamické pole ukazatelů na TZaznam, ukládají se tam tedy pouze ukazatele na TZaznam vrácené funkcí zalozZaznam().
        (Tedy nikoli celé „záznamy“, nýbrž jen ukazatele na ně. Mějte toto na paměti při specifikaci velikosti paměti pro (re)alokaci.)

    Při načítání jmén a příjmení můžete očekávat, že žádné nebude delší než 100 znaků.
    Položky záznamů při načítání nebo ukládání oddělujte bílými znaky. Očekávejte, že žádný údaj nebude zadán s mezerou.
    Při načítání a vypisování typu pohlaví používejte písmena 'm' pro muže a 'z' pro ženu, i když interní reprezentace je pomocí typu TPohlavi.

Požadované chování programu

    Spustíme-li program bez parametrů nebo se špatným počtem parametrů, vypíše program nápovědu, jak se má spouštět.
    Program lze spustit dále 3 základními způsoby:
        ./program -novy nazev_souboru
        ./program -pln nazev_souboru
        ./program -cti nazev_souboru [-jm|-pr|-rc|-ve|-po]
    [pod MS Windows bez „./“]
    První dvě varianty budou načítat záznamy ze standardního vstupu, ukládat do paměti a až dočtou „do konce souboru“ (CTRL+D / CTRL+Z ENTER), uloží všechny záznamy v pořadí, jak na vstup přišly, do souboru předaného jako parametr.
    První varianta založí vždy nový soubor, pokud existuje, přepíše jej.
    Druhá varianta se pokusí otevřít existující soubor a záznamy dopsat na jeho konec, pokud soubor neexistuje, založí nový.
    Třetí varianta funguje mírně obráceně – načte veškeré záznamy ze souboru předaného parametrem a vypíše je na standardní výstup.
        Není-li uveden žádný další parametr, vypíše je ve stejném pořadí, v jakém jsou uloženy v souboru.
        Je-li přítomen další parametr, např. -pr, seřadí napřed záznamy dle odpovídající položky a teprve potom seřazené vypíše na standardní výstup.
        Přítomen může být nejvýše jeden parametr určující výsledné řazení, není možné tedy program spouštět např. takto: ./program -cti soubor.data -pr -ve

        Tabulka parametrů pro učení pořadí. parametr	řadit dle
        -jm	jména
        -pr	příjmení
        -rc	rodného čísla
        -ve	věku
        -po	pohlaví

        Pořadí se určuje vždy pro danou jednu položku záznamu, tedy má-li třeba být výstup seřazen dle jména, na ostatních položkách nezáleží a vzájemné pořadí záznamů se stejným jménem může být libovolné. (Jinak řečeno, netřeba řadit dle jména, pokud stejné pak příjmení, atd.)
        Řetězce (včetně rodného čísla) řaďte lexikograficky (vzestupně – nejmenší napřed) s pomocí funkce strcmp.
        Věk řaďte též vzestupně od nejmladších k nejstarším.
        V případě řazení dle pohlaví dejte napřed ženy, pak muže.
    Před ukončením programu, tedy i v případě chyby, nezapomeňte uvolnit alokovanou paměť.
    Pokud se nepodaří otevřít soubor požadovaným způsobem, program vypíše chybovou hlášku a ukončí činnost.

Poznámky

    Otevření souborů je vhodné provést na začátku programu před jakýmkoli načítáním dat. V případě chyby se tím vyhneme nutnosti uvolňovat alokovanou paměť.
    Pro seřazení záznamů lze využít funkce qsort() z hlavičkového souboru stdlib.h.
        Je třeba si uvědomit, že v dynamickém poli, které předáme funkci qsort(), nejsou přímo vlastní záznamy, ale ukazatele na ně (TZaznam ** zaznamy).
        Takže potom proměnné a a b předávané funkci pro porovnání položek nenesou ukazatele na vlastní záznamy, nýbrž zase ukazatele na ukazatele na záznamy.
        Protože je třeba řadit dle předaných parametrů dle různých položek, je třeba si připravit více porovnávacích funkcí cmp() pro qsort().
        Lze též využít funkce, která vrací ukazatel na funkci, např.:

        typedef enum {
                neradit = 0, dleJmena , dlePrijmeni, dleRC, dleVeku, dlePohlavi
        } TRaditDle;

        // ...

        int (* cmp(TRaditDle raditDle))(const void* a, const void *b) {
        	...
        }

        //...

        TRaditDle raditDle = ... ; // nastavit dle parametru

        	// vlastni serazeni dle 
        sort(zaznamy, pocetZaznamu, sizeof(TZaznam*), cmp(raditDle));

            Zde funkce cmp() může provést „return konkretni_radici_fce;“, kterou pak použije funkce qsort().
            Pozor: za příkazem return za konkretni_radici_fce nejsou kulaté závorky, ale rovnou středník. Je tomu tak proto, že nevracíme návratovou hodnotu konkretni_radici_fce, ale přímo danou funkci, resp. ukazatel na ni.
            Dále je všem jistě jasné, že konkretni_radici_fce musí mít odpovídající prototyp:
            int konkretni_radici_fce(const void*a, const void *b); 
    Příklad běhu programu níže vypisuje v případě výpisu na standardní výstup doplňující informace uživateli, aby věděl, co zadává. Toto nemusí být součástí vašich programů.
    V případě výpisu do souboru je nutné, aby žádné další výpisy kromě položek záznamů oddělených bílými znaky neproběhly, neboť to, co si váš program do souboru zapíše, musí být schopen při jiné volbě zase po sobě přečíst.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

char razeni = 0;

typedef enum {
	muz = 0, 
	zena = 1
} TPohlavi;

typedef struct {
	char * jmeno;
	char * prijmeni;
	char rc[11];
	unsigned char vek;
	TPohlavi pohlavi;
} TZaznam;

TZaznam * zalozZaznam(const char *jmeno, const char *prijmeni, const char *rc, const unsigned int vek, const TPohlavi pohlavi) {
	TZaznam * zaznam;

	if ((zaznam = (TZaznam *)malloc(sizeof(TZaznam))) == NULL )
		return NULL;
	if ((zaznam->jmeno = (char *)malloc(sizeof(char)*(strlen(jmeno) + 1))) == NULL) {
		free(zaznam);
		return NULL;
	}
	if ((zaznam->prijmeni = (char *)malloc(sizeof(char)*(strlen(prijmeni) + 1))) == NULL){
		free(zaznam->jmeno);
		free(zaznam);
		return NULL;
	}

	strcpy(zaznam->jmeno, jmeno);
	strcpy(zaznam->prijmeni, prijmeni);
	strcpy(zaznam->rc, rc);
	zaznam->vek = vek;
	zaznam->pohlavi = pohlavi;

	return zaznam;
}

void zrusZaznam(TZaznam * zaznam) {
	if (zaznam) {
		if (zaznam->jmeno)
			free(zaznam->jmeno);
		if(zaznam->prijmeni)
			free(zaznam->prijmeni);
		free(zaznam);
	}
}

void zrusZaznamy(TZaznam **zaznamy, size_t pocetZaznamu) {
	if (zaznamy) {
		for (int i = 0; i < pocetZaznamu; i++) {
			zrusZaznam(zaznamy[i]);
		}
		free(zaznamy);
	}
}

int print_help(void) {
	printf("Napoveda:\n");
    printf("\t-pln soubor\n");
    printf("\t-novy soubor\n");
    printf("\t-cti soubor [-jm|-pr|-rc|-ve|-po]\n");
	return 0;
}

void vypisZaznamy(FILE *stream, TZaznam **zaznamy, size_t pocetZaznamu) {
	for(int i = 0; i < pocetZaznamu; i++) {
		fprintf(stream, "%s\n%s\n%s\n%i\n%c\n\n", zaznamy[i]->jmeno, zaznamy[i]->prijmeni, 
				zaznamy[i]->rc, zaznamy[i]->vek, zaznamy[i]->pohlavi == 0 ? 'm' : 'z' );
	}
}

int cmp(const void *x, const void *y){
	TZaznam *a = *(TZaznam **)x;
	TZaznam *b = *(TZaznam **)y;

	switch (razeni) {
		case 1:
			return strcmp(a->jmeno, b->jmeno);
		case 2:
			return strcmp(a->prijmeni, b->prijmeni);
		case 3:
			return strcmp(a->rc, b->rc);
		case 4:
			if (a->vek > b->vek)
				return 1;
			else if (a->vek < b->vek)
				return -1;
			else 
				return 0;
		case 5: 
			if (a->pohlavi > b->pohlavi)
				return 1;
			else if (a->pohlavi < b->pohlavi)
				return -1;
			else 
				return 0;
		default:
			assert(0 && "Neznámé řazení!");
	}
	
} 

int main(int argc, char **argv) {
	
	FILE * datovy_soubor;
	char mod;

	if (argc < 3) {
	print_help();
	return 1;
	}
	
	/*input handling*/
	if (strcmp(argv[1],"-novy") == 0) {
		mod = 0;
		if ( (datovy_soubor = fopen(argv[2], "w")) == NULL ) {
			fprintf (stderr, "Nepodařilo se otevřít soubor %s\n", argv[2]);
			return 1;
		}
	}
	else if (strcmp(argv[1],"-pln") == 0) {
		mod = 0;
		if ( (datovy_soubor = fopen(argv[2], "a")) == NULL ) {
			fprintf (stderr, "Nepodařilo se otevřít soubor %s\n", argv[2]);
			return 1;
		}
	}
	else if ( strcmp(argv[1],"-cti") == 0) {
		mod = 1;
		if ( (datovy_soubor = fopen(argv[2], "r")) == NULL ) {
			fprintf (stderr, "Nepodařilo se otevřít soubor %s\n", argv[2]);
			return 1;
		}
		if (argc == 4) {
			if (strcmp(argv[3], "-jm") == 0)
				razeni = 1;
			else if (strcmp(argv[3], "-pr") == 0)
				razeni = 2;
			else if (strcmp(argv[3], "-rc") == 0)
				razeni = 3;
			else if (strcmp(argv[3], "-ve") == 0)
				razeni = 4;
			else if (strcmp(argv[3], "-po") == 0)
				razeni = 5;
			else {
				fprintf(stderr, "Chyba: Neplatný argument!\n");
				print_help();
				return 1;
			}
		}
			
	}	
	else {
		fprintf (stderr, "Chyba: Neplatný vstup!\n");
		print_help();
		return 1;
	}
		
	TZaznam ** zaznamy = NULL;
	if ((zaznamy = (TZaznam **)malloc(sizeof(TZaznam *))) == NULL) {
		fprintf (stderr, "Nepodařilo se alokovat paměť\n");
		return 0;
	}

	char jmeno[101];
	char prijmeni[101];
	char rc[11];
	unsigned char vek;
	char spohlavi[10];
	TPohlavi pohlavi;
	unsigned pzaznamu = 0, i = 0;

	if (mod == 0) {
		while (1) {
			printf("\nZadejte zaznam:\n");
			printf("Zadejte jmeno: ");
			if (scanf("%s", jmeno) != 1) break;
			printf("Zadejte prijmeni: ");
			if (scanf("%s", prijmeni) != 1) break;
			printf("Zadejte rodne cislo (bez lomitka): ");
			if (scanf("%10s", rc) != 1) break;
			printf("Zadejte vek: ");
			if (scanf("%hhu", &vek) != 1) break;
			printf("Zadejte pohlavi ('m' -- muz, 'z' -- zena): ");
			if (scanf("%s", spohlavi) != 1) break;
			
			if(strcmp(spohlavi,"m") == 0)
				pohlavi = 0;
			else if (strcmp(spohlavi,"z") == 0)
				pohlavi = 1;
			else {
				fprintf (stderr, "Chyba: Zadáno neznámé pohlaví %s\n", spohlavi);
				break;
			}
			
			if (i > 0)
				if ((zaznamy = (TZaznam **)realloc(zaznamy, (i+1) * sizeof(TZaznam *))) == NULL) {
					fprintf (stderr, "Nepodařilo se alokovat paměť\n");
					return 1;
				}
			
			if ( (zaznamy[i] = zalozZaznam(jmeno, prijmeni, rc, vek, pohlavi)) == NULL ) {
				fprintf (stderr, "Založení nového záznamu selhalo\n");
				return 1;
			}
			else {
				pzaznamu++;
				i++;	
			}
		}
	}
	else if (mod == 1) {
		while (fscanf(datovy_soubor, "%s %s %10s %hhu %s", jmeno, prijmeni, rc, &vek, spohlavi) == 5) {
			
			if(strcmp(spohlavi,"m") == 0)
				pohlavi = 0;
			else if (strcmp(spohlavi,"z") == 0)
				pohlavi = 1;
			else {
				fprintf (stderr, "Zadáno neznámé pohlaví %s\n", spohlavi);
				continue;
			}
			
			if (i > 0)
				if ((zaznamy = (TZaznam **)realloc(zaznamy, (i + 1) * sizeof(TZaznam *))) == NULL) {
					fprintf (stderr, "Nepodařilo se alokovat paměť\n");
					return 1;
				}
			
			if ((zaznamy[i] = zalozZaznam(jmeno, prijmeni, rc, vek, pohlavi)) == NULL) {
				fprintf (stderr, "Založení nového záznamu selhalo\n");
				return 1;
			}
			else {
				i++;
				pzaznamu++;
			}	
		}
	}
	
	if (razeni != 0)
		qsort(zaznamy, pzaznamu, sizeof(TZaznam *), cmp);
	
	vypisZaznamy(mod == 0 ? datovy_soubor : stdout, zaznamy, pzaznamu);
	
	zrusZaznamy(zaznamy, pzaznamu);
	
	fclose(datovy_soubor);
	
	return 0;
}
