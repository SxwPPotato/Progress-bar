#include <iostream>
#include <thread>
#include <vector>
#include<mutex>
#include "Timer.h"

std::mutex m;

void info(int number) {
	std::cout << number + 1 << "\t";

	std::cout << std::this_thread::get_id() << "\t"<<std::endl;
}


void progress(int number) {	
	
	srand(time(0));
	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < 10; i++) {
		
		int rand_dur = (rand() % 2 + 0) * (number + (rand() % 2 + 0));

		std::this_thread::sleep_for(std::chrono::seconds(rand_dur));
		std::lock_guard<std::mutex> MutexLockGuard(m);
		//m.lock();

		consol_parameter::SetPosition(i+16, number + 2);
		std::cout << "|";
		
		//m.unlock();
	}
	
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::lock_guard<std::mutex> MutexLockGuard(m);
	consol_parameter::SetPosition( 29, number + 2);
	std::cout <<" " << elapsed_seconds.count() << "s\t";
	std::cout << std::endl;
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
		threads.push_back(std::thread(info,i));
		threads[i].join();
	}
	for (int i = 0; i < count_thread; i++) {
		threads[i] = std::thread(progress, i);
		//threads[i].join();
	}

	for (int i = 0; i < count_thread; i++) {
		
		threads[i].join();
	}
	
	//consol_parameter::SetPosition(0, count_thread);
	//std::lock_guard<std::mutex> MutexLockGuard(m);



	return 0;
}

