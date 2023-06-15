#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;
void welcomeScreen();
void helpMenu();
bool isLocationExists(const string& filename, const string& location);
void addLocation(string& location);
void returnHelpMenuContent();
void deleteLocation(string& location);
bool containsWord(const string& sentence, const string& word);
void addDiseaseOnLocation(string& location, string& disease, int cases);
void listAllLocations();
void listAllDiseases();
void findWhereDiseaseExists(string& disease);
void findTotalCasesOfDisease(string& disease);
void findCasesOfDiseaseByLocation(string& disease, string &location);

int main(){
    welcomeScreen();
    while(true){
       string command;
       string disease;
        cout << "Console >";

        getline(cin, command);
        if(command == "help"){
            helpMenu();
        }
        else if(command == "Exit"){
            cout << "Exiting the program..." << endl;
            break;
        }
        else if(command.substr(0, 3) == "add"){
            string location = command.substr(4);
            addLocation(location);
        }
        else if(command.substr(0, 6) =="delete"){
            string location = command.substr(7);
            deleteLocation(location );
        }
        else if(command.substr(0,6) == "record"){
            string remainingPart = command.substr(7);
            //split that part by space 
            stringstream ss(remainingPart);
            string location;
            string disease;
            int cases;
            ss >> location >> disease >> cases;
            addDiseaseOnLocation(location, disease, cases);

        }
        else if(command == "list locations"){
            listAllLocations();
        }
        else if(command == "list diseases"){
            listAllDiseases();
        }
        else if(command.substr(0,5) =="where"){
            string disease = command.substr(6);
            findWhereDiseaseExists(disease);
        }
        else if(command.substr(0,5) == "cases"){
            string remainingPart = command.substr(6);
            stringstream ss(remainingPart);
            vector<string> commands;
            string command;
            while(getline(ss, command, ' ')){
                commands.push_back(command);
            }
            if(commands.size() > 1){
                string location = commands.at(0);
                string disease = commands.at(1);
                findCasesOfDiseaseByLocation(location, disease);
            }else{
                string disease = commands.at(0);
                findTotalCasesOfDisease(disease);
            }
        }
        else{
            cout << "Invalid command!" << endl;
        }

    }
    return 0;
}
//WELCOME SCREEN
void welcomeScreen(){
    cout << "##########################################################" << endl;
    cout << " *    Welcome to the Disease Cases Reporting System!         *" << endl;
    cout << " *  ***********************************************    *" << endl;
    cout << " *                                    *" << endl;
    cout << "It is developed by Mudahemuka Manzi as practical." << endl;
    cout << "evaluation for the end of Year 3." << endl;
    cout << "#############################################################" << endl;
    cout << "Starting Time: ";
    cout << endl;
    cout << "Neeed a help? Type 'help' then press Enter key." << endl;
    cout << endl;
}
//HELP MENU

void helpMenu(){
    cout << "########################################################################################" << endl;
    cout << "*                              HELP      MENU                                                       *" << endl;
    cout << "########################################################################################" << endl;
  returnHelpMenuContent();
}

void returnHelpMenuContent(){
    cout <<"add <Location>                       : Add a new location"<< endl;
    cout <<"delete <Location>                    : Delete an existing location"<< endl;
    cout <<"record <Location> <disease> <cases>  : Record a disease and its cases"<< endl;
    cout <<"list locations                       : List all existing locations"<< endl;
    cout <<"list diseases                        : List all existing Diseases in locations"<< endl;
    cout <<"where <disease>                      :Find where disease exists"<< endl;
    cout <<"cases <location> <disease>           : Find cases of disease in location"<< endl;
    cout <<"cases <disease>                      : Find total cases of a given disease"<< endl;
    cout <<"help                                 : Display all the commands"<< endl;
    cout <<"Exit                                 : Exit the program"<< endl;

}

//ADD LOCATION
void addLocation(string& location){
    string fileName = "store.csv";
    //open file
    ofstream file(fileName, ios::app);
     if(!file){
        cout << "Error in opening file!" << endl;
        return;
     }

    //check if location exists in store.csv file

    if(isLocationExists(fileName, location)){
        cout << "Location already exists!" << endl;
        return;
    }
    //if not, add location in csv file
    file << location << endl;
    cout << "Location "<<location<<" is successfully added!" << endl;
    file.close();
}

bool isLocationExists(const string& filename, const string& location)
{
    ifstream file(filename);
    
    if (!file)
    {
        cout << "Error opening the file." << endl;
        return false;
    }
    
    string line;
    while (getline(file, line, '\n'))
    {
        stringstream ss(line);
        string currentLocation;
        getline(ss, currentLocation, ',');
        
        if (currentLocation == location)
        {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

//delete a location

void deleteLocation(string& location){
    string fileName = "store.csv";
    //open file
    ofstream file(fileName, ios::app);
     if(!file){
        cout << "Error in opening file!" << endl;
        return;
     }

    //check if location exists in store.csv file

    if(!isLocationExists(fileName, location)){
        cout << "Location " << location << " doesn't exists!" << endl;
        return;
    }
    file.close();
    //if found delete whole line that contains location in csv file
    ifstream file1(fileName);
    ofstream temp;
    temp.open("temp.csv");
    string line;
    while(getline(file1, line, '\n')){
        if(!containsWord(line, location)){
            temp << line << endl;
        }
    }
    temp.close();
    file1.close();
    remove("store.csv");
    rename("temp.csv", "store.csv");
    cout << "Location deleted successfully!" << endl;
}

bool containsWord(const string& sentence, const string& word)
{
    size_t found = sentence.find(word);
    
    if (found != string::npos)
        return true;
    
    return false;
}

void addDiseaseOnLocation(string& location, string& disease, int cases){
    string fileName = "store.csv";
    //open file
    ofstream file(fileName, ios::app);
     if(!file){
        cout << "Error in opening file!" << endl;
        return;
     }

    //check if location exists in store.csv file

    if(!isLocationExists(fileName, location)){
        cout << "Location " << location << " doesn't exists!" << endl;
        return;
    }
    file.close();
    //if found modify whole line that contains location in csv file and then add disease and cases
    ifstream file1(fileName);
    ofstream temp;
    temp.open("temp.csv");
    string line;
    while(getline(file1, line, '\n')){
        if(containsWord(line, location)){
           temp << line << "," << disease << "," << cases << endl;
        }else{
            temp<< line << endl;
        }
    }
    temp.close();
    file1.close();
    remove("store.csv");
    rename("temp.csv", "store.csv");

    // cout << "Disease recorded successfully" << endl;
}

//list all locations

void listAllLocations(){
    ifstream file("store.csv", ios::app);
    if(!file){
        cout << "Error in opening file!" << endl;
        return;
    }
    string line;
    
    while(getline(file, line, '\n')){
        stringstream ss(line);
        string location;
        getline(ss, location, ',');
        cout <<"        " << location << endl;
    }
}

//list all diseases
void listAllDiseases(){
    ifstream file("store.csv", ios::app);
    if(!file){
        cout << "Error in opening file!" << endl;
        return;
    }
    string line;
    while(getline(file, line, '\n')){
        vector<string> words;
        string word;
        stringstream ss(line);
        while(getline(ss, word, ',')){
            words.push_back(word);
        }
        if(words.size() > 1){
        cout << "        " << words.at(1) << endl;
        }
    }
}
//find where disease exists
void findWhereDiseaseExists(string& disease){
    ifstream file("store.csv", ios::app);
    if(!file){
        cout << "Error in opening file!" << endl;
        return;
    }
    string line;
    vector<string> locations;
    while(getline(file, line, '\n')){
        vector<string> words;
        string word;
        stringstream ss(line);
        while(getline(ss, word, ',')){
            words.push_back(word);
        }
        if(words.size() > 1){
            if(words.at(1) == disease){
                locations.push_back(words.at(0));
            }
        }
    }
    if(locations.size() > 0){
        cout << "    Disease '" << disease << "' exists in: " << endl;
        for(int i = 0; i < locations.size(); i++){
            if(i == 0)
                cout << "        [" << locations.at(i) << ", ";
            else if(i == locations.size() - 1)
                cout << locations.at(i) << "]" << endl;
            else
                cout << locations.at(i) << ", " << endl;
        
        }
    }
};

//find cases of disease in location
void findCasesOfDiseaseByLocation(string &location, string &disease){
    ifstream file("store.csv", ios::app);
    if(!file){
        cout << "Error in opening file!" << endl;
        return;
    }
    if(!isLocationExists("store.csv",location)){
        cout <<"No record found for "<< location << "!" << endl;
        return;
    }
    string line;
    int flag = 0;

    while(getline(file, line, '\n')){
        vector<string> words;
        string word;
        stringstream ss(line);
        while(getline(ss, word, ',')){
            words.push_back(word);
        }
        if(words.size() > 1){
            if(words.at(0) == location && words.at(1) == disease){
                cout << "Cases of "<<disease << " at "<< location <<" are: "<<words.at(2)<< endl;
                flag = 1;
            }
        }
    }
    if(!flag){
        cout <<"No record found for "<< disease << " in "<< location << "!" << endl;
    }
}

//find total cases of a given disease
void findTotalCasesOfDisease(string& disease){
    ifstream file("store.csv", ios::app);
    if(!file){
        cout << "Error in opening file!" << endl;
        return;
    }
    string line;
    int totalCases = 0;
    while(getline(file, line, '\n')){
        vector<string> words;
        string word;
        stringstream ss(line);
        while(getline(ss, word, ',')){
            words.push_back(word);
        }

        if(words.size() > 1){
            if(words.at(1) == disease){
                totalCases += stoi(words.at(2));
            }
        }
    }

    cout << "    Total cases of '" << disease << "' = " << totalCases << endl;
}
