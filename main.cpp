//Colden Gosselin
//Comp 271
//HW 6
//Recieved tutoring assistance from Abdul and Tom Biju

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int Quadratic_Probing(int hash_tbl[], int index, int max)     //Quadratic Probing
{
    int cat, dog, i;
    cat = index % 70000;      //input determines index
    dog = 1;
    for(i = 1; i < 70000; i++)     //determine if the index is  0
    {
        if(hash_tbl [(cat + (max + i)*(max + i)) % 70000] == 0)
            {
                return index;
            }
    }
    return false;       //overflow
}

int Extraction_Method(int glasses)     //extraction method
{

    string a = "000000000";
    char *aj = new char[100];
    sprintf(aj, "%i", glasses);
    string e = (string) aj;

    int j = 0;
    int i;

    for(i = 0; i < e.size(); i++)
    {
        a[i] = e[j];
        j++;
    }
    string s = "0000";      //extract from the 3th, 5th, 7th, 8th position
    s[0] = a[2];
    s[1] = a[4];
    s[2] = a[6];
    s[3] = a[7];

    return atoi(s.c_str());     //return the extracted position
}

int main()
{
    ifstream file1;      //input file stream named file1
    ofstream file2;      //output file stream named file2
    string light;        //string
    string dark;         //string
    string water;        //string
    int number;          //number for quadratic probing
    int i;

    int * thehashtable;
    thehashtable = new int [70000];     //create a hash table

    for(i = 0; i < 70000; i++)
    {
        thehashtable[i] = 0;        //index of array = 0
    }

    cout << "Hello." << endl;
    cout << "Enter the name of the desired file: ";
    getline(cin, light);
    file1.open(light.c_str());       //c-style string

    while(file1.fail())

    {
        cout << light << " " << "file not found" << endl;
        cout << "Enter in another file: ";
        getline(cin, light);
        file1.open(light.c_str());
    }

    vector <int> ran;        //created a vector to store all numbers
    while(file1)     //read file
    {
        getline(file1, light);
        istringstream out(light);
        while(getline(out, water, ','))
        {
            ran.push_back(atoi(water.c_str()));
        }

    cout << "Enter a number between 1 and 450,000,000: ";
    cin >> number;

    number = number % 70000;

    while(!(number >= 0 && number <= 450000000))
    {
        cout << "Enter a number between 0 and 450,000,000: " << endl;
        cin >> number;
    }

    int the_index;
    for(i = 0; i < ran.size(); i++)
    {
        the_index = Extraction_Method(ran[i]);
        if(thehashtable[the_index] == 0)        //address is found, store the number
        {
            thehashtable[the_index] = ran[i];
            //cout << random[i] << " No Collision " << endl; //if uncommented, prints to console
        }
        else
        {//address isn't found, quadratic probing
            the_index = Quadratic_Probing(thehashtable, the_index, number);
            if(the_index == -1)
            {
                //cout << "Full table" << endl;
            }
            else
            {
                thehashtable[the_index] = ran[i];
                //cout << random[i] << "Collision!" << endl;
            }
        }
    }

    if(file1.is_open())      //if file1 is open
    file2.open("hashed_socials.txt");     //open an output text file
    for(int i = 0; i < 70000; i++)      //write out the hash table to the output file
    {
        file2 << thehashtable[i];
        if(i < 69999)
            {
                file2 << ',';
            }
    }
    file1.clear();
    file2.clear();
	file1.close();
    file2.close();

    //double checking the extraction method
    //cout<< Extraction_Method(123456789) << endl;
    }

    cout << endl;
    cout << "Output file is created" << endl;       //output file is created
    return 0;
}
