#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


const char matrix_bigram_strings[10][3] = { "th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te" };

const char matrix_trigram_strings[10][4] = { "the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die" };

const char languages[2][8] = { "english", "german" };

//Frequency values of English
const float frequency_eng[20] = { 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
//Frequency values of German
const float frequency_germ[20] = { 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };


float calculated_frequencies[20];
float distances[2] = { 0,0 };


/*
Clearing unwanted characters in text by using ASCII
Taking the text which we want to learn German or English, as parameter
*/
void filter_str(char str[]) {
	char temp = ' ';
	int i, j;
	for (i = 0; i < strlen(str); i++) {
		if (!(str[i] > 64 && str[i] < 91 || str[i]>96 && str[i] < 123)) {
			if (str[i] == 32) {
				continue;
			}
			str[i] = temp;
		}
	}

}

float calculate_percent(float strlength, float counter) {
	float percent = counter * 100 / strlength;
	return percent;
}

/*
Calculating all bigrams frequency one by one and adding calculated frequencies in calculated frequencies array. And printing frequencies matrix.
*/
void calculate_frequencies_bi(char str[]) {
	int i, j;
	int k = 0;
	int counter;
	for (i = 0; i < 10; i++)
	{
		counter = 0;
		for (j = 0; j < strlen(str); j++) {
			if (matrix_bigram_strings[i][k] == str[j]) {
				if (matrix_bigram_strings[i][k + 1] == str[j + 1]) {
					counter++; //
					calculated_frequencies[i] = calculate_percent(strlen(str), counter);
				}
			}
		}
		printf(matrix_bigram_strings[i]);
		printf(" %d", counter);
		printf("\n");
	}
	printf("----------------------------------------\n");
}
/*
Calculating all trigrams frequency one by one and adding calculated frequencies in calculated frequencies array. And printing frequencies matrix.
*/
void calculate_frequencies_tri(char str[]) {
	int i, j;
	int k = 0;
	int counter;
	for (i = 0; i < 10; i++)
	{
		counter = 0;
		for (j = 0; j < strlen(str); j++) {
			if (matrix_trigram_strings[i][k] == str[j]) {
				if (matrix_trigram_strings[i][k + 1] == str[j + 1]) {
					if (matrix_trigram_strings[i][k + 2] == str[j + 2]) {
						counter++;
						calculated_frequencies[i + 10] = calculate_percent(strlen(str), counter);
					}
				}
			}
		}
		printf(matrix_trigram_strings[i]);
		printf(" %d", counter);
		printf("\n");
	}
	printf("----------------------------------------\n");
}
/*
Need to know distances between calculated frequencies and known Englis or German frequencies for guess the language.
*/

void calculate_distances() {
	float engresult = 0;
	float germresult = 0;
	for (int i = 0; i < 20; i++)
	{
		engresult += pow(calculated_frequencies[i] - frequency_eng[i], 2); //pow fonksiyonuyla karelerini alip donguyle kendi kendine toplattik
	}
	for (int i = 0; i < 20; i++)
	{
		germresult += pow(calculated_frequencies[i] - frequency_germ[i], 2);
	}
	distances[0] = sqrt(engresult); //oklid icin birbirinden cikarip karelerini aldigimiz degerlerin sqrt fonksiyonu ile kokunu aldik ve distancese sirayla atadik
	distances[1] = sqrt(germresult);

}

/*
Whichever distance is closer to zero is the our guess.
*/

void detect_lang() {
	if (distances[0] < distances[1]) {
		printf("Guess: English");
	}
	else if (distances[1] < distances[0]) {
		printf("Guess: German");
	}
	else {
		printf("both of them?:D");
	}
}

int main()
{
	char exmp[] = "“Was immer du tun kannst oder zu können glaubst, fang an. In der Kühnheit liegt: Genie, Kraft und Magie”.";
	printf("Sample Text: “Was immer du tun kannst oder zu können glaubst, fang an. In der Kühnheit liegt: Genie, Kraft und Magie”.\n");
	filter_str(exmp);
	printf("Filtered Version: ");
	printf(exmp);
	printf("\n----------------------------------------\n");
	calculate_frequencies_bi(exmp);
	calculate_frequencies_tri(exmp);
	calculate_distances();
	detect_lang();

	return 0;
}