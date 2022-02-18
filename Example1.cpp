#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct ExampleStruct
{
    enum {MAX_CHAR_ARRAY_SIZE = 100};
    char name[MAX_CHAR_ARRAY_SIZE];
    int numHats;
    double numShoes;
    char description[MAX_CHAR_ARRAY_SIZE];
    ExampleStruct();
    ExampleStruct(const char nameInput[], int hats, int shoes, const char descr[]);
};

ExampleStruct::ExampleStruct() {
    for (int index = 0; index < MAX_CHAR_ARRAY_SIZE; index++) {
        name[index] = '\0';
        description[index] = '\0';
    }
    numHats = 0;
    numShoes = 0;
}
// You will not have a need for a constructor like this. In this code I am not
// showing you the "read from a file" code, since you have done that before.
// I am using this constructor to initialize my array of 3 more easily.
ExampleStruct::ExampleStruct(const char nameInput[], int hats, int shoes, const char descr[]  ) {
    strcpy(name, nameInput);
    numHats = hats;
    numShoes = shoes;
    strcpy(description, descr);
}
/**
Notice how I am taking in an ostream? Both ofstream and cout are ostreams
This means I can use a single printFunction to either print to a file or
the screen.
*/
void printExample(ostream &out, ExampleStruct example){
    out << example.name << ";";
    out << example.numHats << ";";
    out << example.numShoes << ";";
    out << example.description << endl;
}

void printArrayToScreen(ExampleStruct examples[], int numExamples) {
    for (int index = 0; index < numExamples; index++) {
        cout << "Index " << index << ": ";
        printExample(cout, examples[index]);
    }
}

void printArrayToFile(const char fileName[], ExampleStruct examples[], int numExamples) {
    ofstream outFile(fileName);
    for (int index = 0; index < numExamples; index++) {
        printExample(outFile, examples[index]);
    }
}

int main() {
    ExampleStruct myArray[3];
    myArray[0]=ExampleStruct("Example Person1",1,10,"A person with 1 hat and 10 shoes.");
    myArray[1]=ExampleStruct("Example Person2",10,1,"A person with 10 hats and only 1 shoe. A surprising combination.");
    myArray[2]=ExampleStruct("Example Person3",0,1000,"I think this person might be a millipede.");
    printArrayToScreen(myArray, 3);
    printArrayToFile("Example.txt",myArray, 3);

}
