#include <iostream>

class Helper
{
public:
    void insert_string(char * name, int length)
    {
        char temp[length];
        std::cout << "Insert the name. " << (length - 1) << " characters maximum: " << std::endl;
        std::cin >> temp;
        
        for (int i = 0; i<length; ++i)
        {
            name[i] = temp[i];
        }
        
        name[length] = '\0';
    }
    
    template <typename T>
    void insert_struct(T ch)
    {
        
    }
};

class Characteristics
{
    int strength = 0; 
    int agility = 0;
    int intelligence = 0;
    int luck = 0;
    int points = 60;
    
    int usedPoints()
    {
        return (
            this->strength + 
            this->agility +
            this->intelligence +
            this->luck
        );
    }
    
    int freePoints()
    {
        return (usedPoints() - this->points);
    }
    
public:
//setters
    void setStrength(int val)
    {
        this->strength = val;
    }
    void setAgility(int val)
    {
        this->agility = val;
    }
    void setIntelligence(int val)
    {
        this->intelligence = val;
    }
    void setLuck(int val)
    {
        this->luck = val;
    }
//getters
    int getStrength()
    {
        return this->strength;
    }
    int getAgility()
    {
        return this->agility;
    }
    int getIntelligence()
    {
        return this->intelligence;
    }
    int getLuck()
    {
        return this->luck;
    }
    
};

class Personage
{
    int name_max_symbols = 16;
public:
    Characteristics * ch;
    char name[15];
    
    Personage()
    {
        this->ch = new Characteristics;
    }
    
    ~Personage()
    {
        delete this->ch;
    }
    
    void create()
    {
        //write personage name
        //get personage name
        this->insert_name();
        
        //write characteristics values
        //get characteristics values
        this->insert_characterictics();
        //add personage to pool
    }
    
    void insert_name()
    {
        Helper helper;
        helper.insert_string(name, this->name_max_symbols); 
    }
    
    void insert_characterictics()
    {
        Helper helper;
        helper.insert_struct(this->ch);
    }
};

class PersonagesPool
{
    int count = 0;
    Personage pool[]; 
};

int main()
{
    const int PERSONAGE_MONSTER = 0;
    const int PERSONAGE_HERO = 1;
    
    const int END_THE_GAME = 0;
    const int PLAY = 1;
    
    char u_choose;
    int play_me = PLAY;
    
    std::cout << "Hello!" << std::endl;
    
    while(play_me != END_THE_GAME) {
        std::cout << std::endl << "Wanna play a game? (Y/n):" << std::endl;
        std::cin >> u_choose;
        
        switch (u_choose)
        {
            case 'y':
            case 'Y':
                std::cout << "You wanna play lez play!" << std::endl << std::endl;
                break;
            case 'n':
            case 'N':
                std::cout << "Good bye! Try not to die :)" << std::endl;
                play_me = END_THE_GAME;
                continue;
            default:
                std::cout << "I will find you...  " << std::endl;
        }
        
        std::cout << "Wanna be a hero or a monster? (\"h\" - hero, \"I want to be a monster\" - monster)?" << std::endl;
        
        int personage_type = PERSONAGE_MONSTER; //everyone is a little bit monster...
        
        char personage_char;
        std::cin >> personage_char;
        
        switch (personage_char)
        {
            case 'h':
            case 'H':
                std::cout << "Good choose! You are already a winner!" << std::endl;
                personage_type = PERSONAGE_HERO;
                break;
            case 'm':
            case 'M':
                std::cout << "OK. But every monster is a little bit a hero... So the one you will be too" << std::endl;
                personage_type = PERSONAGE_HERO;
                break;
            default:
                std::cout << "Are you serious?!?" << std::endl;
        }
        
        if (personage_type == PERSONAGE_HERO)
        {
            std::cout << "So, you are a hero! Create a few personages (at least two)" << std::endl;
        }
        
        Personage personage;
        personage.create();
        
        std::cout << " -> " << personage.name << std::endl;
        
    }
    return 0;
}
