#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string current_time_and_date()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}

int main()
{
	std::vector<std::string> v = { "->", ",", ".", "-", "'", "[]", "{}", ":", ";", "=", "+", "_", "*", "&", "()", "?", "/", "!", "<" , ">"};
	std::default_random_engine engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> dist{0, static_cast<int>(v.size()) - 1};
	auto rr = std::bind(dist, engine);
	int correct = 0;
	int wrong = 0;	
	auto t1 = std::chrono::high_resolution_clock::now();
	while(1)
	{
		system("clear");
		std::string ra = v[rr()];	
		auto t3 = std::chrono::high_resolution_clock::now();
	   	auto time_span2 = std::chrono::duration_cast<std::chrono::duration<double>>(t3 - t1);
		std::cout << ra << "   Correct: " << correct << "   Wrong: " << wrong << "   Time: " << time_span2.count() << "   |   FullTime: 60" <<  std::endl;
		std::string str;
		std::cin >> str;
		if(ra == str)
		{
			correct++;	
		}
		else
		{
			wrong++;
		}	
		auto t2 = std::chrono::high_resolution_clock::now();
		auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		if(time_span.count() > 60)
		{
			std::cout << "Time out!" << std::endl;
			std::cin.get();
			break;
		}
	}
	std::ofstream file;
	file.open("Data.txt", std::ios_base::app);
	std::stringstream ss;
	ss << "Correct: " << correct << "   |   Wrong: " << wrong << "   |   Data time: " <<  current_time_and_date() << "\n";
	file << ss.str();
	file.close();
	return 0;
}
