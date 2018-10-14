#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Funcţie pentru Task 6

int ac_retea (int IP_2[5], int alt_IP[6])
{
    int verif = 1, i;
    for(i = 1; i <= alt_IP[5] / 8; i++) {
        if ((alt_IP[i] ^ IP_2[i]) != 0){
            verif = 0;
            //verifică dacă octeţii compleţi din partea de reţea coincid
        }
    }
    if(((alt_IP[alt_IP[5] / 8 + 1] >> (8 - (alt_IP[5] % 8))) ^
            (IP_2[alt_IP[5] / 8 + 1]>>(8 - (alt_IP[5] % 8)))) != 0) {
        verif = 0;
        //verifică dacă octetul incomplet din partea de reţea coincide
        //alt_IP[5] este masca de reţea a IP-ului respectiv
    }
    return verif;
}

//Funcţie pentru Task 7

void binar(int IP[5])
{
    int i, j, cat, rest[9];
    for(i = 1 ; i <= 4 ; i++) {
        cat = IP[i];
        for(j = 1 ; j <= 8 ; j++) {
            rest[j] = 0;
        }
        j = 1;
        do {
            rest[j] = cat % 2;
            cat /= 2;
            j++;
        } while(cat > 0);
        for(j = 8 ; j >= 1 ; j--) {
            printf("%d", rest[j]);
        }
        if(i == 4) break;
        printf(".");
    }
}

//Funcţie pentru Task 8

void baza_32(int IP[5])
{
    int i , j, cat, rest[9];
    for(i = 1 ; i <= 4 ; i++) {
        cat = IP[i];
        j = 1;
        do {
            rest[j] = cat % 32;
            cat /= 32;
            j++;
        } while(cat > 0);
        for(j = (j - 1) ; j >= 1 ; j--) {
            if(rest[j] >= 10) {
                printf("%c", 55 + rest[j]);
            }
            else {
                printf("%d", rest[j]);
            }
        }
        if(i == 4) break;
        printf(".");
    }
}

int main()
{
    int set_date, d, IP_1[5], IP_2[5], MASCA_X, MASCA[5], NUM, i;
    //MASCA_X este forma prefixată a măştii de reţea
    scanf("%d", &set_date);
    for(d = 1 ; d <= set_date ; d++) {
        if(set_date > 1) {
            printf("%d\n", set_date);
        }
        scanf("%d.%d.%d.%d/%d %d.%d.%d.%d %d", 
		&IP_1[1], &IP_1[2], &IP_1[3], &IP_1[4], &MASCA_X, 
		&IP_2[1], &IP_2[2], &IP_2[3], &IP_2[4], &NUM);
	int  NET[NUM + 1][6];
        for(i = 1 ; i <= NUM ; i++) {
            scanf(" %d.%d.%d.%d/%d", &NET[i][1], &NET[i][2],
			&NET[i][3], &NET[i][4], &NET[i][5]);
            //NET[n][5] este masca de reţea a IP-ului nr n
        }

        //Task 0

        printf("-0 %d.%d.%d.%d\n", IP_1[1], IP_1[2], IP_1[3], IP_1[4]);

        //Task 1

        int copie_masca, m;
        copie_masca = MASCA_X; m = 1;
        while(copie_masca >= 8){
            MASCA[m] = 255;
            copie_masca -= 8;
            m++;
        }
        for(i = m ; i <= 4 ; i++) {
            MASCA[i] = 0;
        }
        for(i = 1 ; i <= copie_masca ; i++) {
            MASCA[m] += pow(2, (8 - i));
        }
        printf("-1 %d.%d.%d.%d\n", MASCA[1], MASCA[2], MASCA[3], MASCA[4]);

        //Task 2

        int adresa_retea[4];
        for(i = 1 ; i <= 4 ; i++) {
            adresa_retea[i] = IP_1[i] & MASCA[i];
        }
        printf("-2 %d.%d.%d.%d\n", adresa_retea[1], adresa_retea[2],
                adresa_retea[3], adresa_retea[4]);

        //Task 3

        int adresa_broadcast[4];
        for(i = 1 ; i <= 4 ; i++) {
            adresa_broadcast[i] = IP_1[i] | (MASCA[i] ^ 255);
        }
        printf("-3 %d.%d.%d.%d\n", adresa_broadcast[1], adresa_broadcast[2],
                adresa_broadcast[3], adresa_broadcast[4]);

        //Task 4

        int verif = 1;
        //dacă verif = 1, atunci IP_1 şi IP_2 fac parte din aceeaşi reţea
        printf("-4 ");
        for(i = 1 ; i <= MASCA_X / 8 ; i++) {
            if ((IP_1[i] ^ IP_2[i]) != 0){
                verif = 0;
                //verif dacă octeţii compleţi din partea de reţea coincid
            }
        }
        if(((IP_1[MASCA_X / 8 + 1] >> (8 - (MASCA_X % 8))) ^
                (IP_2[MASCA_X / 8 + 1] >> (8 - (MASCA_X % 8)))) != 0) {
            verif = 0;
            //verifică dacă octetul incomplet din partea de reţea coincide
        }
        if(verif == 0) printf("nu\n");
        if(verif == 1) printf("da\n");

        //Task 5

        printf("-5 %x.%x.%x.%x %o.%o.%o.%o\n",
		IP_1[1], IP_1[2], IP_1[3], IP_1[4],
                IP_2[1], IP_2[2], IP_2[3], IP_2[4]);

        //Task 6

        if(verif == 1) {
            printf("-6 0");
        }
        else {
            printf("-6");
            for(i = 1 ; i <= NUM ; i++) {
                if(ac_retea(IP_2, NET[i]) == 1) {
                    printf(" %d", i);
                }
            }
        }

        //Task 7

        printf("\n-7 ");
        binar(IP_1);
        printf(" ");
        binar(IP_2);

        //Task 8

        printf("\n-8 ");
        baza_32(IP_1);
        printf(" ");
        baza_32(IP_2);
        printf("\n");

    }

    return 0;
}

