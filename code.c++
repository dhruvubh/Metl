#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cctype>
#include<cstdlib>
#include<ctime>

const int LETTER=5;
const int INCORRECT=0;
const int MAYBE=1;
const int CORRECT=2;

const std::vector<std::string> allowedWords={"Amber","Agate","Topaz","Coral","Pearl","Slate","Ivory","Beryl","Chrys","Shale","Malac","Lapis","Larim"};

void toUpperCase(std::string &input)
{
    std::transform(input.begin(),input.end(),input.begin(),[](unsigned char c){ return std::toupper(c); });
}

std::string getRandomWord()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomIndex=std::rand()%allowedWords.size();
    return allowedWords[randomIndex];
}

bool isValid(std::string word)
{
    return word.length()==LETTER && word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")==std::string::npos;
}

void markCORRECT(std::vector<std::vector<int>> &CORRECTes,int tryIndex,std::string target,std::string guess)
{
    for(int i=0;i<guess.length();i++)
    {
        CORRECTes[tryIndex][i]=INCORRECT;
    }
    for(int j=0;j<guess.length();j++)
    {
        for(int i=0;i<target.length();i++)
        {
            if(guess[j]==target[i])
            {
                if(i==j)
                {
                    CORRECTes[tryIndex][j]=CORRECT;
                    break;
                }
                else
                {
                    CORRECTes[tryIndex][j]=MAYBE;
                }
            }
        }
    }
}

void printWordle(std::vector<std::string> tries,std::vector<std::vector<int>> CORRECTes,int currentTry)
{
    system("clear");
    std::cout<<"METL";
    for(int i=0;i<=currentTry && i<tries.size();i++)
    {
        std::string separator="-";
        std::string padding="|";
        std::string text="|";
        for(int j=0;j<tries[i].length();j++)
        {
            separator+="------";
            padding+="     |";
            char value=std::toupper(tries[i][j]);
            text+="  ";
            if(CORRECTes[i][j]==MAYBE)
            {
                text+="\033[33m";
            }
            else if(CORRECTes[i][j]==CORRECT)
            {
                text+="\033[32m";
            }
            text+=value;
            if(CORRECTes[i][j]==MAYBE || CORRECTes[i][j]==CORRECT)
            {
                text+="\033[0m";
            }
            text+="  |";
        }
        if(i==0)
        {
            std::cout<<separator<<std::endl;
        }
        std::cout<<padding<<std::endl;
        std::cout<<text<<std::endl;
        std::cout<<padding<<std::endl;
        std::cout<<separator<<std::endl;
    }
}

bool isAllCORRECT(std::string target,std::string guess)
{
    for(int i=0;i<guess.length();i++)
    {
        if(guess[i]!=target[i])
            return false;
    }
    return true;
}

int main(int,char**)
{
    int numberOfTries=6;
    std::vector<std::string> tries(numberOfTries);
    std::vector<std::vector<int>> CORRECTes(numberOfTries,std::vector<int>(LETTER));
    std::string targetWord=getRandomWord();
    toUpperCase(targetWord);
    std::string input;
    int currentTry=0;

    while(currentTry<numberOfTries)
    {
        do
        {
            std::cout<<"Please enter your guess (word length must be "+std::to_string(LETTER)+") or type Q to quit: ";
            std::getline(std::cin,input);
            toUpperCase(input);
        } while(input!="Q" && !isValid(input));

        if(input=="Q")
        {
            std::cout<<"Quit game"<<std::endl;
            break;
        }

        tries[currentTry]=input;
        markCORRECT(CORRECTes,currentTry,targetWord,input);
        printWordle(tries,CORRECTes,currentTry);

        if(isAllCORRECT(targetWord,input))
        {
            std::cout<<"Found the word"<<std::endl;
            break;
        }
        else if(currentTry==numberOfTries-1)
        {
            std::cout<<"You didn't find the word"<<std::endl;
        }

        currentTry++;
    }

    return 0;
}
