#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
//We have 2 copies of the text file, one with the original data, and the other that can change with user input. For the option to reload to file, the first is copied unto the second.
const int MAX_VIDEOGAMES = 80;

struct videogame{
  enum {MAX_CHARACTERS = 100};
  char name[MAX_CHARACTERS];
  int sales;
  char platform[MAX_CHARACTERS];
  char initialRelease[MAX_CHARACTERS];
  char developer[MAX_CHARACTERS];
  char publisher[MAX_CHARACTERS];
  videogame();
};

videogame::videogame(){
  for(int index = 0; index < MAX_CHARACTERS; ++index){
    name[index] = '\0';
    platform[index] = '\0';
    initialRelease[index] = '\0';
    developer[index] = '\0';
    publisher[index] = '\0';
  }
  sales = 0;
}

//compares 2 character arrays; returns true if they are the same, false if they are different
bool compareCharArray(char cArray1[], char cArray2[]){
  for(int index = 0; index < videogame::MAX_CHARACTERS; ++index){
    if (cArray1[index] != cArray2[index]){
      return false;
    }
  }
  return true;
}

//collects from the file a single field
videogame readVG(ifstream &inFile){
  videogame vg;
  inFile.get(vg.name, videogame::MAX_CHARACTERS, ';');
  inFile.ignore(999, ';');
  inFile >> vg.sales;
  inFile.ignore(999, ';');
  inFile.get(vg.platform, videogame::MAX_CHARACTERS, ';');
  inFile.ignore(999, ';');
  inFile.get(vg.initialRelease, videogame::MAX_CHARACTERS, ';');
  inFile.ignore(999, ';');
  inFile.get(vg.developer, videogame::MAX_CHARACTERS, ';');
  inFile.ignore(999, ';');
  inFile.get(vg.publisher, videogame::MAX_CHARACTERS, '\n');
  inFile.ignore(999, '\n');

  return vg;
}


//this function is called once at the start; it reads from videogames1, the file that changes with the user input, and stores that file into struct array, return vgNum
int initialFileRead(videogame vgList[]){
  int vgNum = 0;
  ifstream inFile("videogames1.txt");

  while(inFile.peek() != EOF && vgNum < MAX_VIDEOGAMES) {
    vgList[vgNum] = readVG(inFile);
    ++vgNum;
    
  }
  return vgNum;
}

//reads the videogames file, stores it in the struct array, and return the number of videogames
int fileRead(videogame vgList[]){
  int vgNum = 0;
  ifstream inFile("videogames.txt");

  while(inFile.peek() != EOF && vgNum < MAX_VIDEOGAMES) {
    vgList[vgNum] = readVG(inFile);
    ++vgNum;
    
  }
  return vgNum;
}

//prints an individual object of struct videogame into the desired location
void printVG(ostream &out, videogame vg){
  out << vg.name << ';';
  out << vg.sales << ';';
  out << vg.platform << ';';
  out << vg.initialRelease << ';';
  out << vg.developer << ';';
  out << vg.publisher << endl;
}

//prints the array either to the console or to the file
void printVGs(videogame vgList[], int vgNum, char searchField, char search[], char outputLocation) {
  
  //if platform, the platform asked should show AS WELL AS multi-platform
  int order[vgNum] = {0};

  char comparisonArray[videogame::MAX_CHARACTERS] = {'\0'};
  if (searchField == 'f' && outputLocation == 'c'){
    comparisonArray[0] = 'M';
    comparisonArray[1] = 'u';
    comparisonArray[2] = 'l';
    comparisonArray[3] = 't';
    comparisonArray[4] = 'i';
    comparisonArray[5] = '-';
    comparisonArray[6] = 'p';
    comparisonArray[7] = 'l';
    comparisonArray[8] = 'a';
    comparisonArray[9] = 't';
    comparisonArray[10] = 'f';
    comparisonArray[11] = 'o';
    comparisonArray[12] = 'r';
    comparisonArray[13] = 'm';
  }
    //if search by sales, this will order from high to low or vice versa
  else if (searchField == 's' && outputLocation == 'c'){
    if(search[0] == 'l'){//low--high
      for(int index1 = 0; index1 < vgNum; ++index1){

        for(int index4 = 0; index4 < index1; ++index4){
          if(order[index1] == order[index4] && index1 != 0){
            order[index1] += 1;
          }
        }
        
        for(int index2 = 0; index2 < vgNum; ++index2){
          if(vgList[index2].sales < vgList[order[index1]].sales){
            
            for(int index3 = 0; index3 < vgNum; ++index3){
              if(order[index3] == index2){
                break;
              }
              
              if(index3 == (vgNum - 1)){
                order[index1] = index2;
              }
            }
          
          }
        }
      }
      
      
    }
    else{//high--low
      for(int index1 = 0; index1 < vgNum; ++index1){

        for(int index4 = 0; index4 < index1; ++index4){
          if(order[index1] == order[index4] && index1 != 0){
            order[index1] += 1;
          }
        }
        
        for(int index2 = 0; index2 < vgNum; ++index2){
          if(vgList[index2].sales > vgList[order[index1]].sales){
            
            for(int index3 = 0; index3 < vgNum; ++index3){
              if(order[index3] == index2){
                break;
              }
              
              if(index3 == (vgNum - 1)){
                order[index1] = index2;
              }
            }
          
          }
        }
      }
    }
  }
  if(outputLocation == 'f'){
    ofstream fileout("videogames1.txt");
    for(int index = 0; index < vgNum; ++index){
      printVG(fileout, vgList[index]);
    }
  }
  else{
    for(int index = 0; index < vgNum; ++index){
      //console, all
      if(outputLocation == 'c' && searchField == '\0'){
        cout << "Index " << index << ": ";
        printVG(cout, vgList[index]);
      }
      //console, sales (highest to low, or vice versa)
      else if(outputLocation == 'c' && searchField == 's'){
        cout << "Index " << order[index] << ": ";
        printVG(cout, vgList[order[index]]);
      }
      //console, platform (searched by + multiplatform)
      else if(outputLocation == 'c' && searchField == 'f'){
        if(compareCharArray(search, vgList[index].platform) || compareCharArray(comparisonArray, vgList[index].platform) ){
          cout << "Index " << index << ": ";
          printVG(cout, vgList[index]);
        }
      }
      //console, developer (searched by)
      else if(outputLocation == 'c' && searchField == 'd'){
        if(compareCharArray(search, vgList[index].developer)){
          cout << "Index " << index << ": ";
          printVG(cout, vgList[index]);
        }
      }
      //console, publisher (search by)
      else if(outputLocation == 'c' && searchField == 'p'){
        if(compareCharArray(search, vgList[index].publisher)){
          cout << "Index " << index << ": ";
          printVG(cout, vgList[index]);
        }
      }
    }
  }
  
}

//saves user-input from the array to the videogames1 file.
void saveChanges(videogame vgList[], int vgNum){
  char discard[5] = {'\0'};
  printVGs(vgList, vgNum, '\0', discard, 'f');
}

//reloads the file by copying the base file (videogames) to the user-malleable file (videogames1)
void reloadFile(videogame vgList[], int& vgNum){
  char discard[5] = {'\0'};
  vgNum = fileRead(vgList);
  printVGs(vgList, vgNum, '\0', discard, 'f');
}

//removes a videogame from the struct array
void removeVG(videogame vgList[], int& vgNum){
  int input = 0;
  do{
    cout << "Enter the index of the videogame to remove (-1 to quit): ";
    cin >> input;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(input == -1){
      break;
    }
    else if(!(input < vgNum && input >= 0)){
      cout << "\n\tThat videogame index is not valid.\n" << endl;
    }
    else{
      cout << vgList[input].name << " has been removed." << endl;
      for(int index = input; index < vgNum; ++index){
        vgList[index] = vgList[index + 1];
      }
      --vgNum;
      break;
    }
  }while(true);
  
  return;
}

//adds a videogame to the struct array (user-input)
void addVG(videogame vgList[], int& vgNum){

  videogame a;
  char temp = '\0';
  if(vgNum == MAX_VIDEOGAMES){
    cout << "\tThe videogame database is full, you cannot add another one.\n" << endl;
    return;
  }
  while(true){
    cout << "Enter the name of the videogame to be added: ";
    cin >> temp;
    cin.getline(a.name, videogame::MAX_CHARACTERS - 1, '\n');
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      for(int index = (videogame::MAX_CHARACTERS - 1); index > 0; --index){
        a.name[index] = a.name[index - 1];
      }
      a.name[0] = temp;
      break;
    }
  }
  while(true){
    cout << "Enter " << a.name << "'s total number of sales: ";
    cin >> a.sales;
    if(!cin){
      cin.clear();
      cin.ignore(999999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(a.sales < 0){
      cout << "\n\tThe number of sales cannot be negative.\n" << endl;
    }
    else{
      break;
    }
  }
  while(true){
    cout << "Enter " << a.name << "'s platform (\"Multi-platform\" for more than 1): ";
    cin >> temp;
    cin.getline(a.platform, videogame::MAX_CHARACTERS - 1, '\n');
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      for(int index = (videogame::MAX_CHARACTERS - 1); index > 0; --index){
        a.platform[index] = a.platform[index - 1];
      }
      a.platform[0] = temp;
      break;
    }
  }
  while(true){
    cout << "Enter " << a.name << "'s release date: ";
    cin >> temp;
    cin.getline(a.initialRelease, videogame::MAX_CHARACTERS - 1, '\n');
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      for(int index = (videogame::MAX_CHARACTERS - 1); index > 0; --index){
        a.initialRelease[index] = a.initialRelease[index - 1];
      }
      a.initialRelease[0] = temp;
      break;
    }
  }
  while(true){
    cout << "Enter " << a.name << "'s developer: ";
   cin >> temp;
    cin.getline(a.developer, videogame::MAX_CHARACTERS - 1, '\n');
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      for(int index = (videogame::MAX_CHARACTERS - 1); index > 0; --index){
        a.developer[index] = a.developer[index - 1];
      }
      a.developer[0] = temp;
      break;
    }
  }
  while(true){
    cout << "Enter " << a.name << "'s publisher: ";
    cin >> temp;
    cin.getline(a.publisher, videogame::MAX_CHARACTERS - 1, '\n');
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      for(int index = (videogame::MAX_CHARACTERS - 1); index > 0; --index){
        a.publisher[index] = a.publisher[index - 1];
      }
      a.publisher[0] = temp;
      break;
    }
  }
  vgList[vgNum] = a;
  ++vgNum;
  return;
}

//this function takes the user input and stores it into a character array (I made this a function when I was already nearly done, so it is not used in places that it could have been had I made it earlier)
void charArrayInput(char array[], string prompt){
  char temp = '\0';
  do{
    cout << prompt;
    cin >> temp;
    cin.getline(array, videogame::MAX_CHARACTERS - 1, '\n');
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else{
      for(int index = (videogame::MAX_CHARACTERS - 1); index > 0; --index){
        array[index] = array[index - 1];
      }
      array[0] = temp;
      break;
    }
  }while(true);
}

int main(){
  videogame vgList[MAX_VIDEOGAMES];
  int vgNum = 0;
  //search field is the category they are searching for (developed, publisher ,platform, etc.)
  char searchField = '\0';
  char search[videogame::MAX_CHARACTERS] = {'\0'};
  vgNum = initialFileRead(vgList);
  int option = 0;

  
  while(true){
    search[videogame::MAX_CHARACTERS] = {'\0'};
    searchField = '\0';
    cout << endl << "\t1. Print all Videogames" << endl << "\t2. Print by Sales" << endl << "\t3. Print by Platform" << endl << "\t4. Print by Developer" << endl << "\t5. Print by Publisher" << endl << "\t6. Add Videogame" << endl << "\t7. Remove Videogame" << endl << "\t8. Save Changes" << endl << "\t9. Reload File" << endl << "\t0. Quit" << endl << "\nSelect an option: ";
    cin >> option;
    if(!cin){
      cin.clear();
      cin.ignore(9999, '\n');
      cout << "\n\tInvalid input data.\n" << endl;
    }
    else if(option == 1){
      searchField = '\0';
      printVGs(vgList, vgNum, searchField, search, 'c');
    }
    else if(option == 2){//create two options: high to low or vice versa
      do{
        option = 0;
        cout << "\n\t1. Search Sales by High to Low" << endl << "\t2. Search Sales by Low to High" << endl << "\t3. Quit\n\nSelect an option: ";
        cin >> option;
        if(!cin){
          cin.clear();
          cin.ignore(9999, '\n');
          cout << "\n\tInvalid input data.\n" << endl;
        }
        else if(!(option <= 3 && option >= 1)){
          cout << "\n\tInvalid input.\n" << endl;
        }
        else{
          if(option == 1){
            search[0] = 'h';
          }
          else if(option == 2){
            search[0] = 'l';
          }
          break;
        }
      }while(true);
      if(option != 3){
        searchField = 's';
        printVGs(vgList, vgNum, searchField, search, 'c');
      }
    }
    else if (option == 3){
      charArrayInput(search, "Platform to search: ");
      searchField = 'f';
      printVGs(vgList, vgNum, searchField, search, 'c');
    }
    else if (option == 4){
      charArrayInput(search, "Developer to search: ");
      searchField = 'd';
      printVGs(vgList, vgNum, searchField, search, 'c');
    }
    else if (option == 5){
      charArrayInput(search, "Publisher to search: ");
      searchField = 'p';
      printVGs(vgList, vgNum, searchField, search, 'c');
    }
    else if(option == 6){
      addVG(vgList, vgNum);
    }
    else if(option == 7){
      removeVG(vgList, vgNum);
    }
    else if (option == 8){
      saveChanges(vgList, vgNum);
      cout << "The file has been changed." << endl;
    }
    else if(option == 9){
      reloadFile(vgList, vgNum);
      cout << "The file has been restored." << endl;
    }
      else if(option == 0){
        break;
      }
    else{
      cout << endl << "Invalid response." << endl;
    }
  }
  
  return 0;
}
