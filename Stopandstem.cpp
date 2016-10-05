#include "common_header.h"
#include "porter2_stemmer.h"
using namespace std;
unordered_set<string> words;
int ny = 0;
int ap = 0;
void stop_words() {
	std::ifstream stop_words("Stop_Words.txt");
	string a;
	while (stop_words >> a) 
		words.insert(a);
	stop_words.clear();
}
void tolower_case_and_remove_punctuation_and_all_numbers(string &str) {
	char c; int i = 0;
	//str.erase(remove_if(str.begin(), str.end(), &ispunct), str.end()); // Removes all punctuation
	str.erase(remove_if(str.begin(), str.end(), &isdigit), str.end()); // Removes all numbers
	while (str[i])
	{
		c = str[i];
		if (isupper(c)) str[i] = tolower(c);
		i++;
	}
}
void read_txt(std::ifstream &afile, std::ofstream &bfile, string names) {
	string line;
	afile.open(names);
	string changed = names;
	names[6] = 'o';
	names[7] = 'u';
	names[8] = 't';
	bfile.open(names);
	stop_words();
	while (afile >> line) {
		if (line == "<DOCNO>") {
			bfile << endl;
			bfile << line << " : ";
			afile >> line; bfile << line;
		}
		else if (line == "<HEADLINE>") {
			bfile << endl;
			bfile << line << " : ";
			while (afile >> line) {
				if (line == "</HEADLINE>") 
					break;
				tolower_case_and_remove_punctuation_and_all_numbers(line);
				auto search = words.find(line);
				if (search == words.end()) {
					//Porter2Stemmer::trim(line);
					Porter2Stemmer::stem(line);
					line.erase(remove_if(line.begin(), line.end(), &ispunct), line.end()); // Removes all numbers
					bfile << line << " ";
				}
			}
		}
		else if (line == "<TEXT>") {
			bfile << endl << line << " : ";
			while (afile >> line) {
				if (line == "</TEXT>")
					break;
				else if (line != "<P>" && line != "</P>") {
					tolower_case_and_remove_punctuation_and_all_numbers(line);
					auto search = words.find(line);
					if (search == words.end()) {
						line.erase(remove_if(line.begin(), line.end(), &ispunct), line.end()); // Removes all numbers						
						Porter2Stemmer::stem(line);
						Porter2Stemmer::trim(line);
						if(line != "")
						bfile << line << " ";
					}
					else {
					}
				}
			}
		}
	}
	afile.close();
	bfile.close();
	return;
}





void get_text_name(std::vector<string> &NYT, std::vector<string> &APW){
string nyt, apw;
ofstream aaa("lists");
	int years[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	nyt = "ir_corpus\\NYT\\1998\\19980601_NYT";
	apw = "ir_corpus\\APW\\1998\\19980601_APW_ENG";
	for (int i = 1998; i <= 2000; i++) {
		if (i == 1998) {
		}
		if (i == 1999) {
			nyt.at(17) = 9 + 48; nyt.at(22) = 9 + 48;apw.at(17) = 9 + 48; apw.at(22) = 9 + 48;
		}
		else if (i == 2000) {
			nyt.at(14) = 2 + 48; nyt.at(15) = 0 + 48;nyt.at(16) = 0 + 48; nyt.at(17) = 0 + 48;
			nyt.at(19) = 2 + 48; nyt.at(20) = 0 + 48;nyt.at(21) = 0 + 48; nyt.at(22) = 0 + 48;
			apw.at(14) = 2 + 48; apw.at(15) = 0 + 48;apw.at(16) = 0 + 48; apw.at(17) = 0 + 48;
			apw.at(19) = 2 + 48; apw.at(20) = 0 + 48;apw.at(21) = 0 + 48; apw.at(22) = 0 + 48;
		}
		if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0) == 0)
			years[1] = 28;
		else years[1] = 29;

		for (int j = 1; j <= 12; j++) {
			nyt.at(23) = j / 10 + 48; nyt.at(24) = j - (j / 10) * 10 + 48;
			apw.at(23) = j / 10 + 48; apw.at(24) = j - (j / 10) * 10 + 48;
			for (int k = 1; k <= years[j - 1]; k++) {
				nyt.at(25) = k / 10 + 48; nyt.at(26) = k - (k / 10) * 10 + 48;
				apw.at(25) = k / 10 + 48; apw.at(26) = k - (k / 10) * 10 + 48;
				ifstream news(nyt);
				if (news.is_open()) {
					NYT.push_back(nyt);
					aaa << nyt << endl;
					ny++;
				}
				news.close();
				ifstream bos(apw);
				if (bos.is_open()) {
					APW.push_back(apw);
					aaa << apw << endl;
					ap++;
				}
				bos.close();
			}
		}
	}
	aaa.close();
	return;
}
