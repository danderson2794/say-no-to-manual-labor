#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>

struct Query
{
    std::string qname;
    std::vector<std::string> cmd;
    Query() {qname = ""; }
    Query(std::string n) {qname = n; cmd.reserve(100);}
};

struct View
{
    std::string name;
    std::unordered_map<std::string, std::string> cmd;
    View(){name = " ";}
    View(std::string n) { name = n;}
};

std::vector<View> views;
std::vector<Query> commands;
/*
 * The first argument will be the file I am creating the hash table from. 
 * The second file will be the commands that Matt will use. 
 * Lastly, I will output a TXT file with the new descriptions. 
 * The value of the vector will be the lookup value in the hash table. 
 */

int main(int argc, char *argv[])
{
    std::ifstream newWords(argv[1]);
    std::ifstream commandWords(argv[2]);
    
    commands.reserve(5);
    views.reserve(100);
    
    std::string temp, description;
   
    int c = 0; 
    std::string name;
    // Going to populate the vector first. 
    while(commandWords >> temp)
    {
        if(temp == "NEWFIELD")
        {
            commandWords >> name;
            commands.emplace_back(name);
            c++;
        }
        else
        {   
            // c - 1 becuase I have to update above. 
            if(commands.at(c-1).qname == name)
            {
                commands.at(c-1).cmd.emplace_back(temp);
            } 
        }
    }
   
    // Now I need to pick the first word of the sentence and then grab the sentence. 
    // The first word will be the key, the sentence will be the value for my hash table. 
    std::string line;
    int count = 0;
    while(newWords >> temp)
    {
        if(temp == "NEWFILE")
        {
            newWords >> name;
            views.emplace_back(name);
            count++;
        }
        else
        {
            if(views.at(count-1).name  == name)
            {
                std::getline(newWords, line);
                views.at(count-1).cmd[temp] = line;
            }
        }
    }

    // Now i need to cross-refence them and see if we have any matches. 
    // This is really bad, but I need a quick prototype.. Run time: O(N^4)  ** Sorry Dr. Dean :( **
    for(int i = 0 ; i < static_cast<int>(commands.size()); i++)
    {
        for(int j = 0; j < static_cast<int>(commands.at(i).cmd.size()); j++)
        {
            for(int k = 0; k < static_cast<int>(views.size()); k++)
            {

                std::unordered_map<std::string, std::string>::const_iterator got = views.at(k).cmd.find(commands.at(i).cmd.at(j));
                if( got == views.at(k).cmd.end() ) { } // do nothing
                else
                {
                    std::cout << commands.at(i).qname << " " << commands.at(i).cmd.at(k) << " " << views.at(k).name << " " << got->first << " " << got->second << std::endl; 
                }
            }
        }
    }

    newWords.close();
    commandWords.close(); 
    return 0;
};
