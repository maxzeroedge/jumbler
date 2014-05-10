#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

/* Author: PCZ
 * Word Jumbler
 * Input: A String from the user
 * Output: All possible combinations out of the letters of the String.
 * Difference: Print each word instead of storing in an array.
 * Limit: Due to extensiveness of algorithm, let's keep it limited to 10 letters to begin with
 */
void swapper(string, int);
bool checkWordExists(string, string);
bool checkStringInString(string, string);

int main()
{
	string inp;
	start:
	cout << "Please enter a string that has between 1-10 letters.\n";
	cin >> inp;
	int len = inp.length();
	if(len > 11)
	{
		cout<<"Too many letters"<<endl;
		goto start;
	}
	std::ofstream ofs;
    ofs.open("words.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
	for(int i = 0; i < len; i++)
    {
        swapper(inp, i);
    }
	/*for(int i = 0; i < len; i++)
	{
		for(int j = i; j < len; j++)
		{
			string temp1 = inp;
			temp1.at(j) = inp.at(i);
			temp1.at(i) = inp.at(j);
			cout << counter<<")	" << "n= " << i << " m= " << j << temp1 <<endl;counter++;
			for(int k = len; k > len-j; k--)
			{
				string temp2 = temp1;
				temp2.at(j+k-len) = temp1.at(len-j);
				temp2.at(len-j) = temp1.at(j+k-len);
				cout << counter<<")	" << temp2 <<endl;counter++;
			}
		}
	}*/
	//cout << counter<<")	" <<inp <<endl;
	//system("pause");
	return 0;
}

void swapper(string inp, int pos)
{
	int len=inp.length();
	for(int i = pos; i < len; i++)
	{
		for(int j = i+1; j < len; j++)
		{
			string temp1 = inp;
			temp1.at(j) = inp.at(i);
			temp1.at(i) = inp.at(j);
			if(!checkWordExists("words.txt", temp1))
			{
				cout << temp1 <<endl;
			}
			else
            {
                continue; //cout << "Word exists\n";
            }
			swapper(temp1, pos+1);
		}
	}
}

bool checkWordExists(string fName, string word)
{
	ifstream read(fName.c_str());
	if(!read.is_open())
	{
		cout << "Error opening file to read";
	}
	string file_contents, line;
	while(getline(read, line))
	{
		file_contents += line;
	}
	read.close();
	word = "_"+word+"_";
	//If file_contents has word, return true, else add the word to file and return false
	if(file_contents == ""){goto startWrite;}
	//checkStringInString(file_contents, word)
	if(file_contents.find(word) != std::string::npos)
	{
		return true;
	}
	else
	{
		ofstream write(fName.c_str());
		write << file_contents+"\n"+word+"\n";
		write.close();
		return false;
	}
	startWrite:
    ofstream write(fName.c_str());
	write << word+"\n";
	write.close();
	return false;
}

bool checkStringInString(string s1, string s2) //Check for string s2 in string s1
{
	bool result;
	int n = 0;
	int l = (s1.length() == s2.length()) ? 1 : (s1.length() - s2.length());
	for(int i=0; i < l; i++)
	{
	    for(int j =0; j < s2.length(); j++)
		{
			if(s1.at(i+j) != s2.at(j))
			{
				result = false; cout << i << " "<< j <<endl;
				if(n!=s2.length()){n=0;}
				break;
			}
			else
			{
                n++;
                if(n==s2.length()) {result = true; }
			}
		}
	}
	if(n==s2.length()){cout << n<<" "<<result;} else{cout << n <<" "<< result <<" " << s2 <<endl;}
	return n==s2.length();
}
