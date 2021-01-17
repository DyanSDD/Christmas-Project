/** //////////////////////////////////////////
/////   Mr. Santa - Kris Kringle          ////
/////   Mrs. Santa - Gertrude Jessica     ////
////////////////////////////////////////////*/
#include <iostream>
#include <conio.h>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include <limits.h>

using namespace std;

static int rowNumber = 0; /** Row number in data file to pick the right child, used in KrisKringle constructor **/
static int toyPosition, presentsNumber; /** Variables to use in Elfs class, addToy() function to determine child budget and presents **/

/**###CLASS###**/
class KrisKringle{
protected:
    string name, surname, age, city, color, wishlist[99], presents[99], type, deliveryCities[99];
    int toysNumber = 0, visitedCities[6], totalKM = 0; /** visitedCities is the number of the city in the actual deliveryCities[99] where is stored the name **/
    bool createConstructor; /** Does nothing, don't delete! */
public:
    KrisKringle(int switcher);
    KrisKringle(string switcher)                        {createConstructor = false;}
    string returnCity(int counter)                      {return this->deliveryCities[counter];} /** return city name **/
    int returnDeliveryCities(int counter)               {return this->visitedCities[counter];}  /** return the position of the above */
    bool WasVisited(int i, int visited[6], int j);  /** checks if the city was visited in calculateTheWay() function */
    void setCity(string container, int counter)         {this->deliveryCities[counter] = container;} /** set city by name in string */
    void calculateTheWay(); /** calculates the way by kilometers and saves positions by number */
    void showTheWay();  /** prints the calculated route */
};

KrisKringle::KrisKringle(int noConstructor){
    int i = 0, j = 0;
    string garbageBuffer;
    ifstream children, wishlistFile;
    children.open("children.txt");
    if(rowNumber != 0){
        for(j = 0; j < rowNumber; j++){
            getline(children, garbageBuffer);
        }
    }
    if(children.peek() != EOF){
        getline(children, name, ',');
        getline(children, surname, ',');
        getline(children, age, ',');
        getline(children, city, ',');
        getline(children, color, ',');
        getline(children, type, '\n');
        cout<<"\tDear Santa,\n My name is "<<name<<" "<<surname<<" and I am "<<age<<" years old.\n I am from "<<city<<" and I hope I did good for being a good child this year."<<endl;
    }
    children.close();
    wishlistFile.open((surname+name+".txt").c_str());
    cout<<" I sent you my letter in a "<< color << " envelope."<<endl;
    cout<<" This year I hope for those presents: ";
    while(wishlistFile.peek() != EOF)
    {
        getline(wishlistFile, wishlist[i], ',');
        toysNumber++;
        cout<<wishlist[i]<<" ";
        i++;
    }
    cout<<endl;
    rowNumber++;
}
bool KrisKringle::WasVisited(int i, int visited[6], int j){ /** checks if the city was visited in calculateTheWay() function */
    bool check;
    if(i == 0)
        return false;
    else{
        for(int c = 0; c < i; c++)
            if(j == visited[c]) {check = true;  break;}
            else    check = false;
    }
    return check;
}
void KrisKringle::calculateTheWay(){ /** calculates the way by kilometers and saves positions by number */
    int distance[7][6] ={{ 1810, 2431, 3911, 1207, 1475, 1723},
                        { 9999,    809,  2979, 1098, 576,  305},
                        { 809,  9999,    2265, 1905, 1385, 1099},
                        { 2979, 2265, 9999,    3958, 1385, 3284},
                        { 1098, 1905, 3958, 9999,    528,  841},
                        { 576,  1385, 1385, 528,  9999,    315},
                        { 305,  1099, 3284, 841,  315,  9999}};
    int minim;
    for(int i = 0; i < 6; i ++){
        minim = 1000000;
        for(int j = 0; j < 6; j ++){
            if(distance[i][j] <= minim ){
                if(WasVisited(i, visitedCities, j) == false){
                    minim = distance[i][j];
                    visitedCities[i] = j;
                }
            }
        }
        totalKM += minim;
    }
}
void KrisKringle::showTheWay(){ /** prints the calculated route */
    cout << "The journey will take " << totalKM << "KM" << endl;
    cout << "Optimal way is: Rovaniemi";
    for(int i = 0; i < 6; i ++)     cout << "->" << deliveryCities[visitedCities[i]+1];
}

/**###CLASS###**/
class JessicaGertrude{
private:
    int candyAmount, coalAmount;
    string Cities[6];
public:
    string returnCity(int counter)                  {return this->Cities[counter];} /** used to print Santa's route*/
    float estimateSpendings()                       {return (returnCandyAmount() + returnCoalAmount()/2.0);} /** Calculates aditional budget by 1$ a candy and 0.5$ a coal*/
    int returnCandyAmount()                         {return this->candyAmount;}
    int returnCoalAmount()                          {return this->coalAmount;}
    void setCities(string container, int counter)   {this->Cities[counter] = container;} /** inherits Santa's route by cities' name */
    void setCandyAmount(int amount)                 {this->candyAmount = amount;}
    void setCoalAmount(int counter)                 {this->coalAmount = counter;}
};

/**###CLASS###**/
class Elfs : public KrisKringle{
private:
    string cities[7] = {"Rovaniemi", "Alatyr", "Chadan", "Baymak", "Novorzhev", "Moscow", "Sasovo"}; /** Initial cities list */
    int childBudget, childSpent = 0;
    bool overBudget = false;
    static int candyNumber; /** to pass to Mrs. Santa */
public:
    Elfs (int switcher) : KrisKringle(switcher){}       /** Initializers for the inherited constructors */
    Elfs (string switcher) : KrisKringle(switcher){}
    string returnPresent(int counter)                  {return this->presents[counter];} /** to pass presents to Trolls */
    string returnCity(int counter)                     {return cities[counter];}    /** Initial pass of the cities, made by name */
    string getColor()                                  {return this->color;} /** To determine child sex in Trolls class */
    string getType()                                   {return this->type;} /** To determine child type(good/bad) in Trolls class */
    int returnCandyNumber()                            {return this->candyNumber;}
    int returnChildBudget()                            {if(this->getType() == "good") return 100;   if(this->getType() == "bad") return 10;}
    bool checkInventory(string childToy);   /** Check every wanted toy in wishlist to see if is available */
    void addToy(); /** Check child type and budget, then gives default present, or adds them one by one */
};
bool Elfs::checkInventory(string childToy){ /** Check every wanted toy in wishlist to see if is available */
    ifstream inventory;
    string toy;
    bool isAvailable;
    toyPosition = 0;
    inventory.open("Inventory.txt");
    while(inventory.peek() != EOF){
        getline(inventory, toy, ',');
        if(childToy == toy) {isAvailable = true;    break;}
        else    {isAvailable = false;   toyPosition++;}
    }
    return isAvailable;
}
void Elfs::addToy(){ /** Check child type and budget, then gives default present, or adds them one by one */
    presentsNumber = 0;
    ifstream prices;
    string price;
    int leRealPrice, k = 0;
    prices.open("Prices.txt");
    childBudget = returnChildBudget();
    cout << " This child got a "<< childBudget << "$ budget because of a "<< type <<" morality."<<endl;
    for(int i = 0; i < toysNumber; i++){
        if(checkInventory(wishlist[i]) == true){
            for(int j = 0; j <= toyPosition; j++){
                getline(prices, price, ',');
                if(j == toyPosition)   leRealPrice = std::stoi(price);
            }
            if(leRealPrice > childBudget)   {childSpent = -99;}
            else{
                childSpent += leRealPrice;
                presents[presentsNumber] = wishlist[i];
                presentsNumber++;}
        }
       if(childSpent == -99)        {presents[0] = "A stick with personality"; presentsNumber = 1; break;}
       if(childSpent == 0)          {presents[0] = "A stick with the same personality"; presentsNumber = 1;}
    }
    if(childSpent != -99 && childSpent != 0)    candyNumber = childBudget - childSpent;
    cout << " This child got those presents:";
    for(int l = 0; l < presentsNumber; l++){
        if(l != 0)  cout<<", " <<presents[l];
        else        cout << presents[l];
    }
    cout << endl;
}

/**###CLASS###**/
class Trolls{
private:
    static int coalNumber, boyWrapping, girlWrapping;
    string presents[99], sex, type;
public:
    string getType()                                        {return this->type;}
    string getSex()                                         {return this->sex;}
    int getGirlWrapping()                                   {return this->girlWrapping;}
    int getBoyWrapping()                                    {return this->boyWrapping;}
    int getCoal()                                           {return this->coalNumber;}
    void transferPresents(string present, int position)     {this->presents[position] = present;} /** To get present from Elfs class */
    void setType(string container)                          {this->type = container;}
    void setSex(string container)                           {this->sex = container;}
    void wrapPresents();    /** To count number of wrappers by type of color */
    void giveCoal()                                         {this->coalNumber++;}
};
void Trolls::wrapPresents(){ /** Counts wrappings */
    if(getType() == "bad")  {giveCoal();    cout << " This bad child got a coal from Trolls" << endl;}
    for(int i = 0; i < presentsNumber; i ++){
        if(getSex() == "blue")  boyWrapping++;
        if(getSex() == "pink")  girlWrapping++;
    }
}

/** Templates to use KrisKringle and Elfs clean constructors */
template <typename X>
X ElfConstructor(X choice){
    try                 {throw choice;}
    catch (int x)       {return choice;}
    catch (string x)    {return choice;}
}
template <typename X>
X KrisKringleConstructor(X choice){
    try                 {throw choice;}
    catch (int x)       {return choice;}
    catch (string x)    {return choice;}
}

int Elfs::candyNumber = 0;
int Trolls::coalNumber = 0;
int Trolls::boyWrapping = 0;
int Trolls::girlWrapping = 0;

string returnUserChoice(){  /** For manual input or automated */
    string returnChoice;
    bool wrongInput = false;
    cout << "Do you want the process to be automated, or want to give manual input?"<<endl;
    cout << "demo - for automated filling\nmanual - for manual input\nChoice:";
    do{
        cin >> returnChoice;
        system("cls");
        if(returnChoice == "demo" || returnChoice == "manual")  wrongInput = false;
        else    {wrongInput = true;     cout << "Your input was wrong. Try again.\nChoice:";}
    }while(wrongInput == true);
    return returnChoice;
}
void createManualLetter(int LetterNumber){ /** For manual letter input */
    bool wrongInput = false;
    int wishlistNumber;
    string name, surname, age, city, color, type, wantedPresent;
    ofstream children;
    ofstream wishlist;
    for(int i = 0; i < LetterNumber; i ++){
        system("cls");
        cout<<"blue for boys, and pink for girls.\ngood/bad for child type.\n";
        children.open("Children.txt", ofstream::out);
        cout << "Name:"; cin >> name;
        cout << "Surname:"; cin >> surname;
        cout << "Age:"; cin >> age;
        cout << "City:"; cin >> city;
        do{
            cout << "Color:"; cin >> color;
            if(color == "blue" || color == "pink")  wrongInput = false;
            else    {wrongInput = true;     cout << "Wrong input. Try again." << endl;}
        }
        while(wrongInput == true);
        do{
            cout << "Type:"; cin >> type;
            if(type == "good" || type == "bad") wrongInput = false;
            else        {wrongInput = true;     cout << "Wrong input. Try again." << endl;}
        }while(wrongInput == true);
        children<<name<<","<<surname<<","<<age<<","<<city<<","<<color<<","<<type<<"\n";
        wishlist.open((surname+name+".txt").c_str(), ofstream::out);
        cout << "How many presents does the child want?\nYour answer:";
        cin >> wishlistNumber;
        cout << "Enter the presents one by one." << endl;
        for(int i = 0; i < wishlistNumber; i ++){
            cin >> wantedPresent;
            if(i == 0)                                  wishlist << wantedPresent;
            if(i == (wishlistNumber - 1) && i != 0)     wishlist << "," << wantedPresent << "\n";
            if(i != 0 && i != (wishlistNumber - 1))     wishlist << "," << wantedPresent;
        }
        wishlist.close();
    }
    children.close();
}
void createManualInventoryAndPrices(){ /** Creates inventory and prices files for manual input */
    ofstream inventory;
    ofstream prices;
    int inventoryNumber;
    string toy, price;
    system("cls");
    cout << "How many toys do Elfs have in Santa's inventory?\nAnswer:"; cin >> inventoryNumber;
    for(int i = 0; i < inventoryNumber; i ++){
        system("cls");
        inventory.open("Inventory.txt", ofstream::out);
        cout << "Toy:";  cin >> toy;
        if(i != 0)  inventory << "," << toy;
        else        inventory << toy;
        prices.open("Prices.txt", ofstream::out);
        cout << "Price:"; cin >> price;
        if(i != 0)  prices << "," << price;
        else        prices << price;
    }
    inventory.close();
    prices.close();
    system("cls");
}
int manualInput(){ /** Makes the 2 above work together */
    int letterNumber;
    cout << "How many children letters will have Mr. Kringle?\nYour answer here: ";
    cin >> letterNumber;
    createManualLetter(letterNumber);
    createManualInventoryAndPrices();
    return letterNumber;
}
void Loading(){ /** Nice loading intro */
    sleep(1.5);
    cout<<"Loading";
    for(int i = 0; i < 3; i ++)     {sleep(1);  cout<<".";}
    sleep(1);
    system("cls");
    cout<<
"\n       MERRY CHRISTMAS!              __ _ __ ___"
"\n         &                  _ __'.:;.:;.:;.:`"
"\n   HAPPY NEW YEAR!        _'.:;.:;.:;.:;.:;.:`"
"\n                         '.:. , :`,.,`;'/`__ _` _"
"\n                        '..:;.;'.:,.;.:;\      (_)"
"\n                      -__ --_-_-_-__---_-)"
"\n                     (                    )"
"\n  ____               (_- -__-_-__-____-__-)"
"\n /####\ /\            |  ,~~~'  `~~~.   %@"
"\n |#####\#|             )  ><@>  <@><    %@%"
"\n |#######|            /      /          %@p"
"\n  \######|            ( *   (_c)   * )  % %      .vvvvvvvv."
"\n   |#####|             \ '%@%@%@%@`, %@%@       .vvvvvvvvvv."
"\n   /#####\         _ _ d%@ `----' @%@%@ \ _ _ _.vvvvvvvvvvvvv."
"\n   ~~~~~~~       ':;.;%@@%@%@%@%@%@@%p  /.:;.:;vvvvvvvvvvvvvvv."
"\n    `.:;.'     ':;.;%@@%@%@@%@%@%@%@ :: ____vvmvvvvvvvvvvvvvvvv."
"\n    :.:;.:`   ':;.:d%@%@%@%@%@%@@%@%.:;/####\/\.:;\mvvvvvvvvvvvv"
"\n   :.:;.:;` ';.;;.%@%@@%@%@@%@%@%@p.:;|#####\#|.:;\mvvvvvvvvvvvv."
"\n    :.:;.:;./;.;;.;%@%@%@%@%@%@%@%@ ::.'\######|.:;\mnvvvvvvvvvvvv"
"\n    :.:;.:;.|:.;.;.% %@%@%@%@%@% % :  mvv\#####|.:;.\mnvvvvvvvvvvv"
"\n    :.:;.:;/:;.;.:;.q%@%@@%@%@ %p.:;vv%mv|#####\.:;.\mnvvvvvvvvvv"
"\n    :.:;.:;|:;.:;.;;;%@%@@% %.:;.:;.vmnv. ~~~~~~ .:;.|mvvvvvvvvvv."
"\n    :.:;.:/.:;.:;.:;.: o  .:;.:;.:;.vv.:;/.:;.:;\.:;.|mnvvvvvvvvv."
"\n     `.:;.|:;.:;;;.:;.    .:;;;;;;;;;;;;;|.:;.:;.\.:;\mnvvvvvvvv."
"\n      `::/:;;;.:;;.:; o  .:;.;;.:;;;.:;.:|.:;.:;.:\.:;\mnvvvvvnm"
"\n         ;.:;;.:;;.:     :;;;.:;.:;.:;.:;\.:;.:;.:;.:;|mnvvvnm."
"\n         :::;.:;.:;. o  ..:;.:;.:;;;;.;;;;\.:;.:;.:;.:|mnvvnm."
"\n         :::;.:;;.:     .:;;;;;;;;.:;.:;;;|.:;.:;.:;./mmvnm."
"\n         ;.:;.:;.;. o   .:;.;.:;;.:;.:;.:;.\________/mmmnm."
"\n         :.:;;;.;;;     .:;;.:;.:;;.:;.:;.:;.;.:;;;;`mmnn"
"\n          `#######HHOHHH###########################"
"\n           #######HHOHHH###########################"
"\n          '::;;;.;; o  :;;;.:;.:;;.;;;;;;;;;;;.:;.:`"<<endl;
cout<<"\n\nYou are being hacked by Santa Claus TM"<<endl;
sleep(3);
system("cls");
for(int i = 0; i < 2; i ++){
    cout<<
"LOADING."
"\n           { }"
"\n           {^^,"
"\n           (   `-;"
"\n    _       `;;~~"
"\n   /(______);"
"\n  (         ("
"\n   |:------( )"
"\n _//         \\"
"\n/ /           vv";
sleep(1);
system("cls");
    cout<<
"LOADING.."
"\n        { }"
"\n        {^^,"
"\n        (   `-;"
"\n  _      `;;~~"
"\n /(______);"
"\n(         ("
"\n |:------( )"
"\n ||       ||"
"\n vv       vv";
sleep(1);
system("cls");
cout<<
"LOADING..."
"\n           { }"
"\n           {^^,"
"\n           (   `-;"
"\n    _       `;;~~"
"\n   /(______);"
"\n  (         ("
"\n   |:------( )"
"\n _//         \\"
"\n/ /           vv";
sleep(1);
system("cls");
    cout<<
"LOADING...."
"\n        { }"
"\n        {^^,"
"\n        (   `-;"
"\n  _      `;;~~"
"\n /(______);"
"\n(         ("
"\n |:------( )"
"\n ||       ||"
"\n vv       vv";
sleep(1);
system("cls");
}
}
void createLetter(){ /** Automated letter creation */
    ofstream children;
    ofstream wishlist;
    children.open("Children.txt", ofstream::out);
    children<<"Smith,Liam,14,Bucuresti,blue,bad\n";
    children<<"Brown,Noah,19,Bucuresti,pink,good\n";
    children<<"Williams,Benjamin,7,Bucuresti,blue,good\n";
    children<<"Wilson,Mason,23,Bucuresti,blue,bad\n";
    children<<"Miller,James,2,Bucuresti,pink,bad\n";
    children.close();
    wishlist.open("LiamSmith.txt", ofstream::out);
    wishlist<<"car,puppet";
    wishlist.close();
    wishlist.open("NoahBrown.txt", ofstream::out);
    wishlist<<"car,doll,pen";
    wishlist.close();
    wishlist.open("BenjaminWilliams.txt", ofstream::out);
    wishlist<<"puppy";
    wishlist.close();
    wishlist.open("MasonWilson.txt", ofstream::out);
    wishlist<<"car,puppet,puppy,doll,money,food";
    wishlist.close();
    wishlist.open("JamesMiller.txt", ofstream::out);
    wishlist<<"drawingset";
    wishlist.close();
}
void createInventoryList(){ /** Automated inventory file creation */
    ofstream inventory;
    inventory.open("Inventory.txt");
    inventory<<"car,puppet,doll,puppy";
    inventory.close();
}
void createPrices(){ /** Automated prices file creation */
    ofstream prices;
    prices.open("Prices.txt");
    prices<<"50,75,25,43";
    prices.close();
}
void makeKrisKringleFly(){ /** Main function */
    KrisKringle MrSanta(KrisKringleConstructor<string>("noConstructor"));
    Elfs GeneralUse(ElfConstructor<string>("noConstructor"));
    JessicaGertrude MrsSanta;
    Trolls Trolly;
    int lettersNumber;
    string UserChoice, presentsTransfer;
    UserChoice = returnUserChoice();    /** Function to give manual input **/
    if(UserChoice == "demo"){   /** Automated input choice **/
    createLetter();     /** creates the file for letters for children with name, surname etc.. **/
    createInventoryList();  /** creates inventory file  for Elfs **/
    createPrices();     /** creates file to contain prices for inventory file **/
    lettersNumber = 5;  /** initializer for demo of 5 letters **/
    }
    if(UserChoice == "manual")  {lettersNumber = manualInput();}
    for(int i = 0; i < lettersNumber; i ++){
        Elfs Elf(ElfConstructor<int>(i));
        Trolls Troll;
        Elf.addToy();
        for(int i = 0; i < presentsNumber; i++)     Troll.transferPresents(Elf.returnPresent(i), i);
        Troll.setSex(Elf.getColor());
        Troll.setType(Elf.getType());
        Troll.wrapPresents();
        cout<<endl;
    }
    MrsSanta.setCandyAmount(GeneralUse.returnCandyNumber());
    MrsSanta.setCoalAmount(Trolly.getCoal());
    cout<<"Blue Wrapping used: "<<Trolly.getBoyWrapping()<<endl;
    cout<<"Pink Wrapping used: "<<Trolly.getGirlWrapping()<<endl;
    cout<<"Candy given: "<<MrsSanta.returnCandyAmount()<<endl;
    cout<<"Coal given: "<<MrsSanta.returnCoalAmount()<<endl;
    cout<<"Over buget: "<<MrsSanta.estimateSpendings()<< "$"<<endl;
    cout<<"\nMr. Kris has to visit ";
    for(int i = 1; i < 7; i ++){
        MrSanta.setCity(GeneralUse.returnCity(i), i);
        if(i == 1)  cout<<MrSanta.returnCity(i);
        else        cout<<", "<<MrSanta.returnCity(i);
    }
    cout << endl;
    MrSanta.calculateTheWay();
    MrSanta.showTheWay();
    for(int i = 0; i < 6; i ++)     MrsSanta.setCities(MrSanta.returnCity(MrSanta.returnDeliveryCities(i)+1), i);
    cout << "\nJessica got the delivery way.\nIt is Rovaniemi";
    for(int i = 0; i < 6; i ++)     cout << "->" << MrsSanta.returnCity(i);
    cout << endl << endl;
}

int main(){
    sleep(2);
    Loading(); /** Loading logo & Drawing made for fun **/
    makeKrisKringleFly(); /** Main function that makes everything to work together **/
    return 0;
}
