#include <fstream>
#include <iostream>
#include <vector>
#include <limits>

#include <stdio.h>

#define BIBLE_BEGIN 00300
#define BIBLE_END 100109

#define LINE_SIZE 256

void get_verses(std::ifstream& file, std::vector<std::string>& verses)
{
	std::string line;

	while(getline(file, line)) {
		if(line[7] == ':' || line[8] == ':') {
			verses.push_back(line);
			break;
		}
	}

	while(getline(file, line)) {
		if(line[7] != ':' && line[8] != ':') {
			verses.push_back(line);
		} else {
			return;
		}
	}
}

int randint(char* value)
{
	int seed = atoi(value);
	srand(time(NULL) - seed);
	return (rand() % (BIBLE_END + 1 - BIBLE_BEGIN) + BIBLE_BEGIN);
}

void go_to_line(std::ifstream& file, unsigned int num)
{
    file.seekg(std::ios::beg);
    for(int i = 0; i < num - 1; ++i) {
        file.ignore(LINE_SIZE,'\n');
    }
}

int main(int argc, char** argv)
{
	if(argc != 2) {
		printf("Usage: ./program seed\n");
		exit(EXIT_FAILURE);
	}

	int rand_line = randint(argv[1]);
	std::vector<std::string> verses;

	std::ifstream bible("bible.txt");
	go_to_line(bible, rand_line);

	get_verses(bible, verses);

	int offset = ((verses[verses.size() - 1][5] == '\r') ||
				  (verses[verses.size() - 1][6] == '\0')? 1 : 0);

	for(int i = 0; i < verses.size() - offset; i++) {
		printf("%s\n", verses[i].c_str());
	}

	return EXIT_SUCCESS;
}
