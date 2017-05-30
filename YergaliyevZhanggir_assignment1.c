#include <stdio.h>
#include <string.h>

typedef struct{
	int id;
	int day;
	int qty;
	char type[81];
	double total_cost;
	char arrangement[81];
	char payment[81];
	int delivery;
	char courier[81];
} MillionRoses;

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *file;
	file = fopen("flowerSalesDB_October2011.txt", "r");
	if (file == NULL) {
		printf("Problem opening file.");
		return 1;
	}

	int i=168;
	MillionRoses my[i];

	int x;
	for (x = 1 ; ; x++){

		printf("Input any day of the month:");
		int date;
		scanf("%i", &date);

		if (date > 31 || date < 1){
			printf("error\n");
			break;
		} else {

			int orderAmount = 0;
			int quantity = 0;
			int small = 0, big = 0, gft = 0;
			int result;
			char smallB[] = "small_bouquet";
			char bigB[] = "big_bouquet";
			char gift[] = "gift";
			char cake[] = "birthday_cake";
			char balloon[] = "balloons";
			double cost = 0;
			double cash = 0, qiwi = 0, yandex_money = 0, Epay_Kazkom = 0, halyq_bank = 0, paypal = 0, web_money = 0;
			int delAmount = 0;
			int delCost = 0;

			for(i=1; i <= 168; i++){
				fscanf(file,"%i %i %i %s %lf %s %s %i %s", &my[i].id, &my[i].day, &my[i].qty, my[i].type, &my[i].total_cost, my[i].arrangement, my[i].payment, &my[i].delivery, my[i].courier);

				if (date == my[i].day){
					orderAmount = orderAmount+1;
				}

				if (date == my[i].day){
					quantity = quantity + my[i].qty;
				}
				result = strcmp(smallB, my[i].type);
				if (date == my[i].day && result == 0){
					small = small + 1;
				}
				result = strcmp(bigB, my[i].type);
				if (date == my[i].day && result == 0){
					big = big + 1;
				}
				result = strcmp(gift, my[i].type);
				if (date == my[i].day && result == 0){
					gft = gft + 1;
				}

				if (date == my[i].day){
					cost = cost + my[i].total_cost;
				}
				if (date == my[i].day){
						cash = cash + my[i].total_cost;
				}
				if (date == my[i].day && my[i].delivery != 0){
					delAmount = delAmount+1;
				}
				if (date == my[i].day){
					delCost = delCost + my[i].delivery;
				}
			}
			printf("That day, %i orders were placed \n", orderAmount);
			printf("The amount of flowers that were purchased was: %i \n", quantity);
			printf("The number of small bouquets were %i and the number of big bouquets were %i \n", small, big);
			printf("The number of gifts were %i \n", gft);
			for(i=1; i <= 168; i++){
				if (gft != 0){
					result = strcmp(cake, my[i].arrangement);
					if (date == my[i].day && result == 0){
							printf("   %s, \n", cake);
					}
					result = strcmp(balloon, my[i].arrangement);
					if (date == my[i].day && result == 0){
										printf("   %s, \n", balloon);
					}
				}
			}
			printf("The total cost of the orders was: %f \n", cost);
			printf("%f \n", cash);
			printf("%i deliveries were made \n", delAmount);
			printf("The amount of money spent on the delivery was: %i \n", delCost);

		}
	}
	fclose(file);

	return 0;
}
