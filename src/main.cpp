#include <iostream> 
#include <fstream>
#include <string>
#include <vector> 

// [Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
// intro: prompting user which language to go through rus - > eng or eng -> rus
// and selecting appropriate story options, and allowing user to select 
std::string intro(){
    std::string filepath = "stories/";
    std::cout << "Select language option: " << std::endl;
    std::cout << "1. Russian to English" << std::endl;
    std::cout << "2. English to Russian" << std::endl;
    std::string langChoice;
    std::cin >> langChoice; 
    if (langChoice == "1") {
        std::cout << "Selection made: Rus -> Eng." << std::endl; 
    } else if (langChoice == "2") {
        std::cout << "Selection made: Eng -> Rus." << std::endl; 
    } else {
        std::cout << "Invalid Entry; Default selection made(default = Rus -> Eng)." << std::endl; 
        langChoice = "1";    
    }
    std::cout << "Next, select a story:\n A)Колобок\nB)Репка\nC)Маша и Медведь" << std::endl; 
    std::string storyChoice;
    std::cin >> storyChoice;
    filepath += storyChoice + ".txt";
    std::cout << "Beginning story... " << std::endl; 
    return filepath + "!" + langChoice; 
}

// text parser: goes through the selected story and breaks it through sentences in order to dislay them 
// one by one to the user

// input handler: takes in users input and updates it to the user output file. 
void inputHandler(std::vector<std::string> factors){
    std::string storyChoice = factors[0]; 
    std::string langChoice = factors [1];
    if (langChoice == "1") {
        langChoice = "RuEn";
    } else { langChoice = "EnRu" ; } 
    std::string userInLine = factors[2]; 
    std::string filepath = "output/" + storyChoice + langChoice + ".txt";
    std::ofstream out(filepath, std::ios::out | std::ios::app); 
    out << userInLine << std::endl; 
    out.close();
}

void parser(std::string concatPathLang){
    std::string filepath = concatPathLang.substr(0, concatPathLang.find("!"));  
    std::string langChoice = concatPathLang.substr(concatPathLang.find("!") + 1); 
    std::ifstream in(filepath); 
    std::string storyChoice =filepath.substr(filepath.find("/")+ 1 , 1); 
    std::string userInLine; 
    if (!in.is_open()){
        std::cout << "File failed to open properly." << std::endl; 
    } else {
        std::string line; 
        while (getline (in, line)) {
            std::vector<std::string> factors;
            factors.push_back(storyChoice); 
            factors.push_back(langChoice);
            std::cout << line << std::endl; 
            std::getline(std::cin, userInLine); 
            factors.push_back(userInLine);
            inputHandler(factors); 
        }

    }
    in.close();
}


int main() {

    std::cout << "Russian Text Trainer!" << std::endl; 
    std::cout << "====================" << std::endl;
    std::cout << "Test Cryllic: хорошая книга\n" << std::endl; 
    parser(intro()); 
    return 0;
}
