#include <iostream>
#include <map>

void showSalaries(std::map<std::string, double> Salary);
void mult(std::pair<std::string, double>);
void changeSalary(std::map<std::string, double> Salary);

int main()
{
    //const char GET_OUT = 'n';
    const char STAY_HERE = 'y';
    
    const int ANSWER_OUT = 0;
    const int ANSWER_STAY = 1;
    
    std::map <std::string, double> Salary;
    
    std::cout << "Insert name, press Enter, then insert Salary. Enjoy";
    std::cout << std::endl;
    
    int wanna_get_out = ANSWER_OUT;
    
    do {
        std::string name;
        std::cout << "Name: ";
        std::cin >> name;
        
        double salary; 
        std::cout << "Salary: ";
        while(!(std::cin >> salary))
        {
            std::cout << "Wrong salary format" << std::endl;;
            std::cin.clear();
            fflush(stdin);
            std::cout << "Type one more time: ";
        }
        
        std::cout << "Add one more employee? (Y/n):" << std::endl;
        char answer;
        std::cin >> answer;
        
        answer = tolower(answer);
        
        if(answer == STAY_HERE)
        {
            wanna_get_out = ANSWER_STAY;
        }
    
        Salary.insert(std::pair<std::string, double>(name, salary));
        
    } while(wanna_get_out);
    
    int wanted;
    
    while(1) {
        std::cout << "Insert number to became some functionality: " << std::endl;
        std::cout << "1. Show salaries table; " << std::endl;
        std::cout << "2." << std::endl;
        std::cout << "3." << std::endl;
        std::cout << "4. Exit" << std::endl;
        
        std::cin >> wanted;
    
        switch(wanted)
        {
            case 1:
                showSalaries(Salary);
                break;
            case 2:
                changeSalary(Salary);
                break;
            case 4:
                exit(0);
                break;
            default:
                std::cout << "I have abilities, I will find you!";
                std::cout << std::endl;
        }
    }
}

void showSalaries(std::map<std::string, double> Salary)
{
    for(auto out = Salary.begin(); out != Salary.end(); ++out)
    {
        std::cout << "--------------------------------" << std::endl;
        std::cout << out->first << " : " << out->second << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }
}

void changeSalary(std::map<std::string, double> Salary)
{
    std::foreach(Salary.begin(), Salary.end(), mult);
}

void mult(std::pair<std::string, double>)
{
    double multiplier;
    std::cout << "Insert a value: ";
    while(!(std::cin >> multiplier))
    {
        std::cout << "Wrong format" << std::endl;;
        std::cin.clear();
        fflush(stdin);
        std::cout << "Type one more time: ";
    }
    
    //pair.second.
    
}













