#include <iostream>
#include <string>
#include <array>
#include <unordered_set>
#include <set>
#include<algorithm>
#include <vector>
#include <map>
#include <ctype.h>
#include <chrono>

class Timer 
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start_Timepoint;
public:
	Timer() 
	{
		m_Start_Timepoint = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		Stop();
	}
	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start_Timepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
	
		auto duration = end - start;
		double ms = duration * 0.001;

		std::cout << duration << " microseconds (" << ms << "ms)" << std::endl;
	}
};

#if 0
std::string StringDetermineSubString(std::string s1, std::string s2);
#endif 
#if 0
std::string HashDetermineSubString(std::string s1, std::string s2);
#endif
#if 0
std::string TwoSetDetermineSubString(std::string s1, std::string s2);
#endif
#if 1
std::vector<char> CheckIntersection(std::map<int, char>& map1, std::map<int, char>& map2, std::vector<char>& container);
#endif
#if 1
std::vector<char> CheckIntersectionUsingAlphabet(std::map<int, char>& alphabet, std::map<int, char>& map1, std::map<int, char>& map2, std::vector<char>& container);
#endif
#if 1
std::string MapsDetermineSubString(std::string& s1, std::string& s2);
std::map<int, char> ConvertStringToMap(std::string& s1);
#endif 

std::array<std::string,2> SetUpSubStringCheck()//Helper function to make code look a bit cleaner in the main body
{
	std::string s1, s2;
	std::cout << "First string: ";
	std::cin >> s1;
	std::cout << "Second string: ";
	std::cin >> s2;
	std::array<std::string, 2> a = { s1,s2 };
	return a;
}

int main()
{
	int n;
	std::cout << "How many checks? ";
	std::cin >> n;


	for (int i = 0; i < n; i++)
	{
		std::array<std::string, 2> strings = SetUpSubStringCheck();
		/*
		std::cout << StringDetermineSubString(strings[0], strings[1]) << std::endl;
		*/
		/*
		std::cout << HashDetermineSubString(strings[0], strings[1]) << std::endl;
		*/
		/*
		std::cout << TwoSetDetermineSubString(strings[0], strings[1]) << std::endl;
		*/
		std::cout << MapsDetermineSubString(strings[0], strings[1]) << std::endl;
	}
	
	return 1;
}
//Only strings solve
#if 0
std::string StringDetermineSubString(std::string s1, std::string s2)
{
	int count = 0;
	std::string out;
	for (char c : s1)
	{
		if (s2.find(c) != std::string::npos)//if the second string does not include the character that it is the first then print no npos means the end of the string
		{
			count++;
			break;
		}
	}
	(count > 0) ? out = "YES" : out = "NO";
	return out;
}
#endif
//My Solve
#if 0
std::string HashDetermineSubString(std::string s1, std::string s2)
{
	std::unordered_set<char> firstStringChars;
	for (int i = 0; i < s1.size(); i++)
	{
		firstStringChars.insert(s1[i]);
	}
	std::unordered_set<char> secondStringChars;
	for (int i = 0; i < s2.size(); i++)
	{
		secondStringChars.insert(s2[i]);
	}
	for (int i = 0; i < s2.size(); i++)
	{
		if (firstStringChars.find(s2[i]) != firstStringChars.end()) 
		{
			return "YES";
		}
	}
	return "NO";
}
#endif
//My Solve 2
#if 0
std::string TwoSetDetermineSubString(std::string s1, std::string s2)
{
	std::set<char> firstStringChars;
	for (int i = 0; i < s1.size(); i++)
	{
		firstStringChars.insert(s1[i]);
	}
	std::set<char> secondStringChars;
	for (int i = 0; i < s2.size(); i++)
	{
		secondStringChars.insert(s2[i]);
	}
	std::vector<char> container;
	std::set_intersection(firstStringChars.begin(), firstStringChars.end(), secondStringChars.begin(), secondStringChars.end(), std::back_inserter(container));
		if (container.size() > 0)
		{
			return "YES";
		}
		else
		{
			return "NO";
		}
}
#endif
//My Solve 3 - using maps and helper functions
#if 1
std::string MapsDetermineSubString(std::string& s1, std::string& s2)
{
	std::cout << "First string size: " << s1.size() << "\nSecond string size: " << s2.size() << std::endl;
	std::string alphabetString = "abcdefghijklmnopqrstuvwxyz";
	std::map<int, char> firstString = ConvertStringToMap(s1);
	std::map<int, char> alphabetMap = ConvertStringToMap(alphabetString);
	std::map<int, char> secondString = ConvertStringToMap(s2);
	std::vector<char> container;
	
	if (s1.size() >= s2.size())//order it so the first string passed into the function is evaluated first
	{
		{
			Timer timer;
			container = CheckIntersectionUsingAlphabet(alphabetMap, firstString, secondString, container);
		}
		/*{
			Timer timer;
			container = CheckIntersection(firstString, secondString, container);
		}*/
	}
	else//if the second string is larger then it should be evaluated first
	{
		{
			Timer timer;
			container = CheckIntersectionUsingAlphabet(alphabetMap, secondString, firstString, container);
		}
		/*{
			Timer timer;
			container = CheckIntersection(secondString, firstString, container);
		}*/
		
	}

	if (container.size() > 0)//there were intersections between the strings
	{
		std::cout << "\nMatching substrings are: ";
		for (int i = 0; i < container.size(); i++)
		{
			std::cout << char(container[i]) << " ";//show these char's (this isn't necessary to the functions logic but does look nice, somewhat debug code)
		}
		return "\nYES";//give out the yes string for use in the main
	}
	else
	{
		return "\nNO";
	}
}
std::map<int, char> ConvertStringToMap(std::string& s1)
{
	std::map<int, char> tempMap;//this will be given out of the function once the data is in here
	for (int i = 0; i < s1.size(); i++)//loop through the string
	{
		tempMap.insert(std::pair<int, char>(s1[i], s1[i]));//use the insert function to pass in the values with incrementing integer keys
	}
	return tempMap;
}
std::vector<char> CheckIntersection(std::map<int, char>& map1, std::map<int, char>& map2, std::vector<char>& container)
{
	for (auto& v : map1)//loop through the first dictionary (or map to be cpp specific)
	{
		for (auto& v2 : map2)//go through the second 
		{
			if (v.second == v2.second)//check if the value exists in both regardless of place in the dictionary
			{
				container.push_back(v.second);//note this in the container for use back in the main function
			}
		}
	}
	return container;
}
std::vector<char> CheckIntersectionUsingAlphabet(std::map<int, char>& alphabet, std::map<int, char>& map1, std::map<int, char>& map2, std::vector<char>& container)
{
	for (auto& letter : alphabet)
	{
		if (map1.find(letter.first) != map1.end())
		{
			if (map2.find(letter.first) != map2.end())
			{
				container.push_back(letter.second);
			}
		}
	}
	return container;
}
#endif