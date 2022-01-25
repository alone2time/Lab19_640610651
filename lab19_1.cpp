#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream dest;
    dest.open(filename);
    string textl;
    while(getline(dest,textl)){

        int a = textl.find(':');
        string name;
        name = (textl.substr(0,a));
        names.push_back(name);

        textl = textl.erase(0,a+2);
        int x,y,z,all=0;
        char *chartext = const_cast<char*>(textl.c_str()); 
        sscanf(chartext,"%d %d %d",&x,&y,&z);
        all = x+y+z;
        scores.push_back(all);
        
        char gradecal = score2grade(all);
        grades.push_back(gradecal);
        
    }

    dest.close();

}

void getCommand(string &command , string &key){

    string command_and_key;
    cout << "Please input your command: ";
    getline(cin,command_and_key);

    int a = command_and_key.find(' ') , b = command_and_key.size();
    
    command = (command_and_key.substr(0,a));
    key = (command_and_key.substr(a+1,b));
   
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    
    int j=names.size(),count =0;
    cout << "---------------------------------\n";
    for(int i=0; i<j ; i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            count++;
        }
    }
    if(count == 0){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){

    int j=names.size(),count =0;
    cout << "---------------------------------\n";
    for(int i=0; i<j ; i++){
        if(key[0] == grades[i]){
            cout << names[i] <<" (" <<scores[i]<<')'<<endl;
            count++;
        }
    }
    if(count == 0){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
    
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}