#include "score.h"
#include <string>
using namespace std;

Array newArray;
void Array::pushback(int integer)
{
    // create new array with size+1
    int* new_array = new int[size + 1];

    // go throw old_arry and copy to i
    std::memcpy(new_array, old_array, size * sizeof(int));

    // add new value at end
    new_array[size] =  integer;

    // delete old array if's not empty
    if (old_array)
    {
        delete[] old_array;
    }

    // update pointer and size
    old_array = new_array;
    size++;
}

void draw_score(const Score& s)
{
    const std::string tags[] = { "First  ","Second ","Third  ", "Fourth ", "Fifth  " };
   
 
    DrawDebugText(s.pos, "Highscore", cWhite, false);

    for (int i = 0; i < std::min(newArray.size, 5); i++)
    {
        
        DrawDebugText(s.pos-Vector2f(0,i*15+15), (tags[i] + std::to_string(newArray.old_array[i])).c_str(), cWhite, false);
        
       
    }
}
void save_file()
{

    ofstream file;
    file.open("highscore.txt");
    for (int i = 0; i < newArray.size; i++)
    {
        file << newArray.old_array[i]<<"\n";
    }
    file.close();
}
void load_file()
{
    ifstream file;
    file.open("highscore.txt");
    int tempVar;

    while (file >> tempVar)
    {
        newArray.pushback(tempVar);
    }
}


void draw_cur_score(const CaurentScore& s)
{
    std::string current_score = "Score ";
    current_score += std::to_string(s.score);
    DrawDebugText(s.pos, _strdup(current_score.c_str()), cWhite, false);
}


  