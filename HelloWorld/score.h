#pragma once
#include "Play.h"
#include "constants.h"
using namespace Play;

struct Score
{
	Vector2f pos;
	


	Score() : pos({ 10, DISPLAY_HEIGHT - 20 })
	{

	}
};


struct CaurentScore
{
	 Vector2f  pos = Vector2f(20.0f, 50.0f);



	unsigned int score = 0;
	

};

struct Array
{
    int* old_array;
    int size;
	
	Array() : old_array(nullptr), size(0) {
	}

	~Array() {
		if (old_array)
		{
			delete[] old_array;
		}
	}

	void pushback(int integer);
};

extern Array newArray;

void draw_score(const Score& s);
void draw_cur_score(const CaurentScore& s);
void load_file();
void save_file();
