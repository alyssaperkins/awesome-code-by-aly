#pragma once

#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
#include <string>

public ref class MapWrapper {
	private:
		map* m_Map;
	public:
		MapWrapper() {
			m_Map = new map();
		}

		~MapWrapper() {
			delete m_Map;
		}

		void setUniquitiesForAllNames(System::String^ gender, int fromYear, int toYear) {
			std::string genderStr = msclr::interop::marshal_as<std::string>(gender);
			m_Map->setUniquitiesForAllNames(genderStr, fromYear, toYear);
		}

		std::vector<std::pair<std::string, float>>& getUniquityVector()
		{
			return m_Map->getUniquityVector();
		}

		void MapWrapper::setAllStatesBool(bool input) {
			m_Map->setAllStatesBool(input);
		}

		void MapWrapper::updateStateList(std::vector<std::string> vecUserStates) {
			
			m_Map->updateStateList(vecUserStates);
		}

		
		void MapWrapper::mergeSort(std::vector<std::pair<std::string, float>>& vec, int left, int right)
		{
			m_Map->mergeSort(vec, left, right);
		}

		void MapWrapper::quickSort(std::vector<std::pair<std::string, float>>& vec, int low, int high)
		{
			m_Map->quickSort(vec, low, high);
		}

		void MapWrapper::timSort(std::vector<std::pair<std::string, float>>& vec, int n)
		{
			m_Map->timSort(vec, n);
		}

		void MapWrapper::combSort(std::vector<std::pair<std::string, float>>& vec)
		{
			m_Map->combSort(vec);
		}

		void MapWrapper::setRankingsVector(std::vector<std::string>& names) {
			m_Map->setRankingsVector(names);
		}

		std::vector<std::pair<std::string, float>>& MapWrapper::getRankingsVector() {
			return m_Map->getRankingsVector();
		}

		void MapWrapper::clearRanksVec() {
			m_Map->clearRanksVec();
		}


		void MapWrapper::clearUniquities() {
			m_Map->clearUniquities();
		}

	};