// Last edit 05.05.2020 by Lavrukhin Timur
//
// This file contains functions to determine the letter and count words in the text passed to it:
//	
//	main()	-	main function of the programm, 
//				allows to choose input or file processing of the text,
//				and outputs the number of words with different length in the text
//
// b = isLetter(ch)	-	function determines is passed ch in A-Z, a-z, "-" ranges of ASCII codes and returns true of false
//		ch	-	char which need to check
//		b	-	true or false
//
//	void countWords(text,arr)	-	function counts the length of all words in the text passed to it 
//									and puts the number of words into array passed to it
//		text	-	text to process
//		arr		-	array[45]	which contain the number of words with length from 1 to 45

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool isLetter(char ch){
	short x;
	x = (short)ch;
	if ((x >= 65 && x <= 90)||(x >= 97 && x <= 122)||(x == 45))
		return true;
	return false;
}

void countWords(string text, short* arr){
	short len = 0;
	for (unsigned int ii = 0; ii < text.length(); ++ii){
		//65 - 90 = "A-Z"  97-122 = "a-z" 45 = "-"
		while(isLetter(text[ii])){
			len++;
			ii++;
		}
		if (len > 0){
			++arr[len];
			len = 0;
		}
	}
}

int main(){
	string text;
	short wordLen[45] = {0}, choice;
	
	cout << "If you want to type the text, please, write 1." << endl \
	<< "Write any other digit to process the text from \"input.txt\" file." << endl << "Your choice: ";
	string tmp;
	getline(cin, tmp);
	cout << endl;
	stringstream(tmp) >> choice;

	if (choice == 1){
		cout << "Write text below: " << endl;
		getline(cin, text);
		cout << "Text:" << endl << text << endl;
		//getline(cin, text);
	}
	else{
		string tmp;
		ifstream inpFile("input.txt");
		while(!inpFile.eof()){
			getline(inpFile, tmp);
			tmp += "\n";
			text.append(tmp);
		}
		inpFile.close();
		cout << "Text:" << endl << text << endl;
	}
	
	countWords(text, wordLen);
	
	cout << "There are " << endl;
	for (short ii = 0; ii < 45; ii++)
		if (wordLen[ii] > 0)
			if (wordLen[ii] == 1)
				cout << wordLen[ii] << " word with " << ii << " letter length" << endl;
			else
				cout << wordLen[ii] << " words with " << ii << " letter length" << endl;
	cout << "in the text." << endl;
	system("pause");
	return 0;
}