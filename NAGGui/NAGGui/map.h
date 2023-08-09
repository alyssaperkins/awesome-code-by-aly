#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <unordered_map>

struct NameData {

	NameData() {
		bool isMale = true;			//default male name
		std::string state = "";			//two letter state code
		int year = 0;				//birth year
		int count = 0;				//# of times this name appears in birth year
	}

	NameData(std::string isMale, std::string state, std::string year, std::string count) {

		if (isMale == "M") {
			this->isMale = true;
		}
		else {
			this->isMale = false;
		}

		this->state = state;
		this->year = std::stoi(year);
		this->count = std::stoi(count);
	}

	//Name will be the key of the map
	//Value is a vector of NameData structures that contain year/state specific data
	bool isMale = true;			//default male name
	std::string state = "";			//two letter state code
	int year = 0;				//birth year
	int count = 0;				//# of times this name appears in birth year
};

class map {
public:

	map();
	void clearUniquities();
	void setUniquitiesForAllNames(std::string gender, int fromYear, int toYear);
	//std::unordered_map<std::string, bool> getStateList();
	void updateStateList(std::vector<std::string>& states);
	void setAllStatesBool(bool input);
	std::vector<std::pair<std::string, float>>& getUniquityVector();
	void mergeSort(std::vector<std::pair<std::string, float>>& vec, int left, int right);
	void quickSort(std::vector<std::pair<std::string, float>>& vec, int low, int high);
	void combSort(std::vector<std::pair<std::string, float>>& vec);
	void timSort(std::vector<std::pair<std::string, float>>& vec, int n);
	void writeUniquities();
	void setRankingsVector(std::vector<std::string>& names);
	std::vector<std::pair<std::string, float>>& getRankingsVector();
	void clearRanksVec();

private:
	//Methods
	void readfile();		//read file of name data and store each line to a NDS and name map
	int searchHelper(std::string name, bool isMale, int fromYear, int toYear);
	void setStateList();
	void convertStateName(std::string& state);
	void merge(std::vector<std::pair<std::string, float>>& vec, int left, int mid, int right);
	void swap(std::pair<std::string, float>& a, std::pair<std::string, float>& b);
	int partition(std::vector<std::pair<std::string, float>>& vec, int low, int high);
	void setPercentileIndices();
	void insertionSort(std::vector<std::pair<std::string, float>>& vec, int left, int right);
	std::string getRanking(int index);
	int getNameIndex(std::string name);

	//Variables
	std::unordered_map<std::string, bool> stateList;
	std::unordered_map<std::string, std::vector<NameData*>> namemap;

	//Will update second to become the uniquity rating, this is the vector we will be passing to sort
	std::vector<std::pair<std::string, float>> uniquities;
	std::vector<std::pair<std::string, float>> nameRanks;

	//Partitions for each of five percentiles
	int firstIndex = 0;		//25%
	int secondIndex = 0;	//50%
	int thirdIndex = 0;		//75%
	int fourthIndex = 0;	//95%
};
