#include <iostream>
#include <thread>
#include <vector>
#include<mutex>
#include "Timer.h"

std::mutex m;

void progress(int number) {
	
	std::cout << number + 1 << "\t";

	std::cout << std::this_thread::get_id()<<"\t";
	
	srand(time(0));

	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < 10; i++) {
		
		int rand_dur = rand() % 2 + 0;

		std::this_thread::sleep_for(std::chrono::seconds(rand_dur));

		std::cout << "|";
		
	}
	
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout <<" " << elapsed_seconds.count() << "s\t";
	std::cout << std::endl;
}


void task2(int count_thread) {
	std::thread* t = new std::thread[count_thread];
	for (size_t i = 0; i < count_thread; i++) {
		t[i] = std::thread(progress, i);
	}
	for (size_t i = 0; i < count_thread; i++) {
		t[i].join();
	}
	consol_parameter::SetPosition(0, count_thread);
}


int main()
{
	setlocale(LC_ALL, "russian");
	
	

	int count_thread;
	std::cout << "Введите количество потоков: ";
	std::cin >> count_thread;

	std::vector <std::thread> threads;

	std::cout << "#\tid\tProgress Bar\tTime" << std::endl;



	for (int i = 0; i < count_thread; i++) {
		threads.push_back(std::thread(progress,i));
		threads[i].join();
	}
	
	//consol_parameter::SetPosition(0, count_thread);




	return 0;
}

