#include <iostream>
#include <random>
#include <time.h>
#include "Hannoi.h"



void main(int args, char* argv) {
	//std::random_device rd;
	//int a[LEN];
	//for (int i = 0; i < LEN; i++) {
	//	a[i] = rd() % 100 - 50;
	//}


	Bur::Hannoi(4, 1, 2, 3);



	system("pause");
}
