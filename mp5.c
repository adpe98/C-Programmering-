/*
 * Programmering i C
 * Modul 5
 *
 * Fil:          mp5.c
 * Författare:   Adam Pettersson
 * CS-användare: hed21apn
 * Användare:    Adam
 * Datum:        3 mars 2022
*/

#include <stdio.h>
void print_options(double rate);
int choice(void);
double exchange_rate(void);
double sum_func(double rate);
double request_price(void);
void print_sum(double sum, double rate);
int main(void)
{
    int nr;
    double rate, sum;
    rate = 1.00;

    printf("\nYour shopping assistant\n");

    while (nr != 3)
    {
        print_options(rate);
        nr = choice();

        switch(nr)
        {
              case 1: rate = exchange_rate();
                      break;

              case 2: sum = sum_func(rate);
                      print_sum(sum, rate);
                      break;

              case 3: printf("End of program!\n\n");
                      break;

              default: printf("Not a valid choice!\n");
                       break;
        }
    }
      return 0;

/*
* Beskrivning: printar menyn
* Input: Växlingskursen
* Output: inget retuneras
*/

}
void print_options(double rate)
{
    printf("\n1. Set exchange rate in SEK (current rate: %.2lf)\n", rate);
    printf("2. Convert prices from the foreign currency\n");
    printf("3. End\n\n");
    printf("Give your choice (1 - 3): ");
}

/*
* Beskrivning: Sparar ner valet i menyn och retunerar det
* Input: Ingen input
* Output: Retunerar ett heltal (int) som är menyvalet
*/
int choice(void)
{
    int nr;

    scanf("%d", &nr);
    printf("\n");

    return nr;
}

/*
* Beskrivning: Skriver ut och efterfrågar växklingskursen
* Input: Ingen input
* Output: Växlingskursen
*/

double exchange_rate(void)
{
    double rate;

    printf("Give exchange rate: ");
    scanf("%le", &rate);

    return rate;
}

/*
* Beskrivning: Funktionen beräknar summan av priset i sek
* Input: Växlingskursen
* Output: summan av priset i sek
*/

double sum_func(double rate)
{
    double sum, pris, sum_temp;

    do
    {
        pris = request_price();

        if(pris < 0)
        {
            break;
        }
        else
        {
            sum_temp = sum_temp + pris;
        }
    }
    while (pris >= 0);

    sum = sum_temp * rate;

    return sum;
}

/*
* Beskrivning: Efterfrågar priset som ska konverteras
* Input: Ingen input
* Output: priset av det som ska konverteras
*/

double request_price(void)
{
    double price;

    printf("Give price (finish with < 0): ");
    scanf("%lf", &price);

    return price;

/*
* Beskrivning: Printar ut den beräknade summan för priset i främmande och lokal valuta
* Input: priset i svensk valuta och växlingskursen
* Output: inget retuneras
*/

}

void print_sum(double sum, double rate)
{
    double foreign;

    foreign = sum/rate;

    printf("\nSum in foreign currency: %.2lf\n", foreign);
    printf("Sum in SEK: %.2lf\n", sum);
}
