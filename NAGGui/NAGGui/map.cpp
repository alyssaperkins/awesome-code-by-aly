#include "map.h"

// INITIALIZATION OF MAP
map::map() {
    //create map object
    readfile();
    setStateList();
}

void map::readfile() {
    //open file
    std::ifstream file("NameData.txt");

    //vars to hold data of each line
    std::string state;
    std::string isMale;
    std::string year;
    std::string name;
    std::string count;

    NameData* temp = nullptr;

    int x = 0;
    //parse each line of file until end
    while (!file.eof()) {
        // Get variables from file
        getline(file, state, ',');
        getline(file, isMale, ',');
        getline(file, year, ',');
        getline(file, name, ',');
        getline(file, count);

        temp = new NameData(isMale, state, year, count);

        //cout << temp->count << "  " << temp->isMale << "  " << temp->state << "  " << temp->year << endl;

        namemap[name].push_back(temp);
        x++;
    }

    file.close();
}

// UNIQUITY VECTOR MANAGEMENT
void map::clearUniquities() {
    uniquities.clear();
}

int map::searchHelper(std::string name, bool isMale, int fromYear, int toYear) {
    int totalCount = 0;

    std::vector<NameData*> nameVector = namemap[name];

    for (int i = 0; i < nameVector.size(); i++) {

        if (nameVector.at(i)->isMale == isMale && nameVector.at(i)->year >= fromYear && nameVector.at(i)->year <= toYear && stateList[nameVector.at(i)->state])
        {
            totalCount += nameVector.at(i)->count;
        }
    }
    //cout << "Total Count: " << totalCount << endl << endl;
    return totalCount;
}

void map::setUniquitiesForAllNames(std::string gender, int fromYear, int toYear) {
    bool isMale = false;

    // conversion of gender to isMale
    if (gender == "Male") {
        isMale = true;
    }

    //float nameCount = (float) searchHelper(name, isMale, fromYear, toYear);
    float totalCount = 0.0;
    int nameTotal = 0;
    std::unordered_map<std::string, std::vector<NameData*>>::iterator name_map_iter;

    for (name_map_iter = namemap.begin(); name_map_iter != namemap.end(); name_map_iter++) { // O(n)
        nameTotal = searchHelper(name_map_iter->first, isMale, fromYear, toYear);
        if (nameTotal != 0) {
            uniquities.push_back(std::make_pair(name_map_iter->first, (float)nameTotal));
        }
        totalCount += nameTotal;
    }

    for (int i = 0; i < uniquities.size(); i++) {
        uniquities[i].second /= totalCount;
    }

    //cout << "Total Count: " << totalCount << endl;
}

std::vector<std::pair<std::string, float>>& map::getUniquityVector() {
    return uniquities;
}

void map::setPercentileIndices() {
    firstIndex = ((double)uniquities.size() * (double)(1.0 / 4.0)) - 1;
    secondIndex = ((double)uniquities.size() * (double)(1.0 / 2.0)) - 1;
    thirdIndex = ((double)uniquities.size() * (double)(3.0 / 4.0)) - 1;
    fourthIndex = ((double)uniquities.size() * (double)(19.0 / 20.0)) - 1;
}

//Get index of name from vector
//Pass this to getPercentile and use to return specific uniquity value
int map::getNameIndex(std::string name) {

    setPercentileIndices();

    for (int i = 0; i < uniquities.size(); i++) { // O(n) worst case
        if (uniquities.at(i).first == name) { // Checks if name is found
            return i; // Returns index of name
        }
    }
    return -1; // Name not found for whatever reason
}

std::string map::getRanking(int nameIndex) {								//Percent of Total Uniquity Vector

    if (nameIndex < firstIndex) {									//0 - 24.99%
        return "UNIQUE";
    }
    else if (nameIndex >= firstIndex && nameIndex < secondIndex) { 	//25 - 49.99%
        return "RARE";
    }
    else if (nameIndex >= secondIndex && nameIndex < thirdIndex) { 	//50 - 74.99%
        return "UNCOMMON";
    }
    else if (nameIndex >= thirdIndex && nameIndex < fourthIndex) { 	//75 - 94.99%
        return "COMMON";
    }
    else {															//95 - 100%
        return "POPULAR";
    }
}

// INSERTION SORT
void map::insertionSort(std::vector<std::pair<std::string, float>>& vec, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        std::pair<std::string, float> temp = vec[i];
        int j = i - 1;
        while (j >= left && vec[j].second > temp.second) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = temp;
    }
}

// MERGE SORT
void map::merge(std::vector<std::pair<std::string, float>>& vec, int left, int mid, int right) {

    //Need to make 2 sub vectors: A and B
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<std::pair<std::string, float>> A, B;

    //Copy values to sub vectors
    for (int i = 0; i < n1; i++) {
        A.push_back(vec[left + i]);
    }
    for (int j = 0; j < n2; j++) {
        B.push_back(vec[mid + 1 + j]);
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (A[i].second <= B[j].second) {
            // Assign pair to vector at k
            vec[k] = A[i];
            i++;
        }
        else {
            vec[k] = B[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vec[k] = A[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = B[j];
        j++;
        k++;
    }
}

void map::mergeSort(std::vector<std::pair<std::string, float>>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        merge(vec, left, mid, right);
    }
}

// QUICK SORT
void map::swap(std::pair<std::string, float>& a, std::pair<std::string, float>& b) {
    //swap vector pair of name and uniquity value
    std::pair<std::string, float> temp = a;
    a = b;
    b = temp;
}

int map::partition(std::vector<std::pair<std::string, float>>& vec, int low, int high) {
    //Choose which index to pivot at (using uniquities as the values to compare)
    float pivot = vec[low].second;
    int up = low, down = high;

    while (up < down) {

        for (int j = up; j < high; j++) {
            if (vec[up].second > pivot) {
                break;
            }
            up++;
        }

        for (int j = high; j > low; j--) {
            if (vec[down].second < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            swap(vec[up], vec[down]);
        }
    }
    swap(vec[low], vec[down]);
    return down;
}

void map::quickSort(std::vector<std::pair<std::string, float>>& vec, int low, int high) {
    if (low < high) {
        int pivot_index = partition(vec, low, high);
        quickSort(vec, low, pivot_index - 1);
        quickSort(vec, pivot_index + 1, high);
    }
}

// Comb Sort
void map::combSort(std::vector<std::pair<std::string, float>>& vec) {
    int end, gap;
    end = gap = vec.size();
    bool swapDone = true;

    while (gap > 1 || swapDone) {
        gap = floor(gap / 1.3);
        if (gap < 1) {
            gap = 1;
        }

        swapDone = false;
        for (int i = 0; i < end - gap; ++i) {
            if (vec[i].second > vec[i + gap].second) {
                std::swap(vec[i], vec[i + gap]);
                swapDone = true;
            }
        }
    }

}

// Tim Sort
void map::timSort(std::vector<std::pair<std::string, float>>& vec, int n) {
    const int RUN = 32;
    for (int i = 0; i < n; i += RUN) {
        insertionSort(vec, i, std::min((i + RUN - 1), (n - 1)));
    }

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);
            int right = std::min((left + 2 * size - 1), (n - 1));
            merge(vec, left, mid, right);
        }
    }
}

// STATE LIST MANAGEMENT
// std::unordered_map<std::string, bool> map::getStateList() {
// 	return stateList;
// }

void map::updateStateList(std::vector<std::string>& userStates) {
    for (auto state : userStates) {
        convertStateName(state);
        stateList[state] = true;
    }
}

void map::setStateList() {
    std::string stateAbbrev[51] = 
    { "AL", "AK", "AR", "AZ", "DC", "CA", "CO", "CT", "DE", "FL", "GA",
           "HI", "IA", "ID", "IL", "IN", "KS", "KY", "LA", "MA", "MD", "ME",
           "MI", "MN", "MO", "MS", "MT", "NC", "ND", "NE", "NH", "NJ", "NM",
           "NV", "NY", "OH", "OK", "OR", "PA", "RI", "SC", "SD", "TN", "TX",
           "UT", "VA", "VT", "WA", "WI", "WV", "WY" };

    for (auto state : stateAbbrev) {
        stateList.emplace(state, false);
    }
}

void map::convertStateName(std::string& state) {

    if (state == "Alabama") {
        state = "AL";
    }
    else if (state == "Alaska") {
        state = "AK";
    }
    else if (state == "Arizona") {
        state = "AZ";
    }
    else if (state == "Arkansas") {
        state = "AR";
    }
    else if (state == "California") {
        state = "CA";
    }
    else if (state == "Colorado") {
        state = "CO";
    }
    else if (state == "Connecticut") {
        state = "CT";
    }
    else if (state == "D.C.") {
        state = "DC";
    }
    else if (state == "Delaware") {
        state = "DE";
    }
    else if (state == "Florida") {
        state = "FL";
    }
    else if (state == "Georgia") {
        state = "GA";
    }
    else if (state == "Hawaii") {
        state = "HI";
    }
    else if (state == "Idaho") {
        state = "ID";
    }
    else if (state == "Illinois") {
        state = "IL";
    }
    else if (state == "Indiana") {
        state = "IN";
    }
    else if (state == "Iowa") {
        state = "IA";
    }
    else if (state == "Kansas") {
        state = "KS";
    }
    else if (state == "Kentucky") {
        state = "KY";
    }
    else if (state == "Louisiana") {
        state = "LA";
    }
    else if (state == "Maine") {
        state = "ME";
    }
    else if (state == "Maryland") {
        state = "MD";
    }
    else if (state == "Massachusetts") {
        state = "MA";
    }
    else if (state == "Michigan") {
        state = "MI";
    }
    else if (state == "Minnesota") {
        state = "MN";
    }
    else if (state == "Mississippi") {
        state = "MS";
    }
    else if (state == "Missouri") {
        state = "MO";
    }
    else if (state == "Montana") {
        state = "MT";
    }
    else if (state == "Nebraska") {
        state = "NE";
    }
    else if (state == "Nevada") {
        state = "NV";
    }
    else if (state == "New Hampshire") {
        state = "NH";
    }
    else if (state == "New Jersey") {
        state = "NJ";
    }
    else if (state == "New Mexico") {
        state = "NM";
    }
    else if (state == "New York") {
        state = "NY";
    }
    else if (state == "North Carolina") {
        state = "NC";
    }
    else if (state == "North Dakota") {
        state = "ND";
    }
    else if (state == "Ohio") {
        state = "OH";
    }
    else if (state == "Oklahoma") {
        state = "OK";
    }
    else if (state == "Oregon") {
        state = "OR";
    }
    else if (state == "Pennsylvania") {
        state = "PA";
    }
    else if (state == "Rhode Island") {
        state = "RI";
    }
    else if (state == "South Carolina") {
        state = "SC";
    }
    else if (state == "South Dakota") {
        state = "SD";
    }
    else if (state == "Tennessee") {
        state = "TN";
    }
    else if (state == "Texas") {
        state = "TX";
    }
    else if (state == "Utah") {
        state = "UT";
    }
    else if (state == "Virginia") {
        state = "VA";
    }
    else if (state == "Vermont") {
        state = "VT";
    }
    else if (state == "Washington") {
        state = "WA";
    }
    else if (state == "Wisconsin") {
        state = "WI";
    }
    else if (state == "West Virginia") {
        state = "WV";
    }
    else {
        state = "WY";
    }
}

void map::setAllStatesBool(bool input) {
    std::unordered_map<std::string, bool>::iterator state_list_iter;

    for (state_list_iter = stateList.begin(); state_list_iter != stateList.end(); state_list_iter++) {
        state_list_iter->second = input;
    }
}

void map::writeUniquities() {

    setPercentileIndices();

    int i = 0;

    std::ofstream output1("Unique.csv");
    while (i < firstIndex) {
        output1 << uniquities.at(i).first << "," << uniquities.at(i).second << std::endl;
        i++;
    }
    output1.close();

    std::ofstream output2("Rare.csv");
    while (i < secondIndex) {
        output2 << uniquities.at(i).first << "," << uniquities.at(i).second << std::endl;
        i++;
    }
    output2.close();

    std::ofstream output3("Uncommon.csv");
    while (i < thirdIndex) {
        output3 << uniquities.at(i).first << "," << uniquities.at(i).second << std::endl;
        i++;
    }
    output3.close();

    std::ofstream output4("Common.csv");
    while (i < fourthIndex) {
        output4 << uniquities.at(i).first << "," << uniquities.at(i).second << std::endl;
        i++;
    }
    output4.close();

    std::ofstream output5("Popular.csv");
    while (i < uniquities.size()) {
        output5 << uniquities.at(i).first << "," << uniquities.at(i).second << std::endl;
        i++;
    }
    output5.close();
}

std::vector<std::pair<std::string, float>>& map::getRankingsVector()
{
    return nameRanks;
}

void map::clearRanksVec()
{
    nameRanks.clear();
}

void map::setRankingsVector(std::vector<std::string>& names)
{   

    int index = 0;
    std::string ranking = "";
    for (int i = 0; i < names.size() && i < 10; i++) {
        index = getNameIndex(names[i]);
        if (index != -1) {
            ranking = getRanking(index);
            nameRanks.push_back(std::make_pair(ranking, uniquities[index].second));
        }
        else {
            nameRanks.push_back(std::make_pair("Name Not Found" , 0.0));
        }
        
    }


}


