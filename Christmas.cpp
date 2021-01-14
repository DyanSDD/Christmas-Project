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
using namespace std;

static int rowNumber = 0;
static int toyPosition, presentsNumber;

/**###CLASS###**/
class KrisKringle{
protected:
    string name, surname, age, city, color, wishlist[99], presents[99], type, cities[99];
    int toysNumber = 0;
public:
    KrisKringle(int switcher);
    void setCity(string container, int counter);
    string getCity(int container);
};
/**###CLASS###**/
class JessicaGertrude{
private:
    int candyAmount, coalAmount;
public:
    void setCandyAmount(int amount) {this->candyAmount = amount;}
    int returnCandyAmount()         {return this->candyAmount;}
    void setCoalAmount(int counter) {this->coalAmount = counter;}
    int returnCoalAmount();
    float estimateSpendings();
};
/**###CLASS###**/
class Elfs : public KrisKringle{
private:
    static int candyNumber;
    int childBudget, childSpent = 0;
    bool overBudget = false;
    string cities[6] = {"Alatyr","Chadan","Baymak","Novorzhev","Moscow","Sasovo"};
public:
    Elfs (int switcher) : KrisKringle(switcher){}
    string getChildType();
    int returnChildBudget();
    void addToy();
    bool checkInventory(string childToy);
    string returnPresent(int counter);
    int returnCandyNumber();
    string returnCity(int counter);
    string getColor();
    string getType();
};
/**###CLASS###**/
class Trolls{
private:
    string presents[99], sex, type;
    static int coalNumber, boyWrapping, girlWrapping;
public:
    void transferPresents(string present, int position);
    string returnPresent(int i);
    void setSex(string container);
    void setType(string container);
    string getSex();
    string getType();
    void giveCoal();
    void wrapPresents();
    int getCoal();
    int getBoyWrapping();
    int getGirlWrapping();
};

KrisKringle::KrisKringle(int switcher){
    if(switcher != 99){
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
}
string KrisKringle::getCity(int container){
    return this->cities[container];
    }
void KrisKringle::setCity(string container, int counter){
    this->cities[counter] = container;
}

float JessicaGertrude::estimateSpendings()      {return (returnCandyAmount() + returnCoalAmount()/2.0);}
int JessicaGertrude::returnCoalAmount()         {return this->coalAmount;}

string Elfs::returnPresent(int counter){
    return this->presents[counter];
}
string Elfs::returnCity(int counter){
    return this->cities[counter];
}
string Elfs::getColor(){
    return this->color;
}
string Elfs::getType(){
    return this->type;
}
string Elfs::getChildType(){
    return this->type;
}
int Elfs::returnCandyNumber(){
    return this->candyNumber;
}
int Elfs::returnChildBudget(){
    if(this->getChildType() == "good")
        return 100;
    if(this->getChildType() == "bad")
        return 10;
}
bool Elfs::checkInventory(string childToy){
    ifstream inventory;
    string toy;
    bool isAvailable;
    toyPosition = 0;
    inventory.open("Inventory.txt");
    while(inventory.peek() != EOF){
        getline(inventory, toy, ',');
        if(childToy == toy){
            isAvailable = true;
            break;
        }
        else{
            isAvailable = false;
            toyPosition++;
        }
    }
    return isAvailable;
}
void Elfs::addToy(){
    presentsNumber = 0;
    ifstream prices;
    string price;
    int leRealPrice, k = 0;
    prices.open("Prices.txt");
    childBudget = returnChildBudget();
    for(int i = 0; i < toysNumber; i++){
        if(checkInventory(wishlist[i]) == true){
            for(int j = 0; j <= toyPosition; j++){
                getline(prices, price, ',');
                if(j == toyPosition){
                    leRealPrice = std::stoi(price);
                }
            }
            if(leRealPrice > childBudget)   {childSpent = -99;}
            else{
                childSpent += leRealPrice;
                presents[presentsNumber] = wishlist[i];
                presentsNumber++;}
        }
       if(childSpent == -99)        {presents[0] = "A stick with personality"; presentsNumber = 1; break;}
       if(childSpent == 0)          {presents[0] = "Wooden Horse"; presentsNumber = 1;}
    }
    if(childSpent != -99 && childSpent != 0)
        candyNumber = childBudget - childSpent;
    for(int l = 0; l < presentsNumber; l++)
        cout<<presents[l]<<endl;
}

string Trolls::returnPresent(int i){
    return this->presents[i];
}
string Trolls::getSex(){
    return this->sex;
}
string Trolls::getType(){
    return this->type;
}
int Trolls::getBoyWrapping(){
    return this->boyWrapping;
}
int Trolls::getGirlWrapping(){
    return this->girlWrapping;
}
int Trolls::getCoal(){
    return this->coalNumber;
}
void Trolls::transferPresents(string present, int position){
    this->presents[position] = present;
}
void Trolls::giveCoal(){
    this->coalNumber++;
}
void Trolls::wrapPresents(){
    if(getType() == "bad")
        giveCoal();
    for(int i = 0; i < presentsNumber; i ++){
        if(getSex() == "blue")
            boyWrapping++;
        if(getSex() == "pink")
            girlWrapping++;
    }
}
void Trolls::setType(string container){
    this->type = container;
}
void Trolls::setSex(string container){
    this->sex = container;
}

int Elfs::candyNumber = 0;
int Trolls::coalNumber = 0;
int Trolls::boyWrapping = 0;
int Trolls::girlWrapping = 0;

void Loading(){
    sleep(1.5);
    cout<<"Loading";
    for(int i = 0; i < 3; i ++){
    sleep(1);
    cout<<".";
    }
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
void createLetter(){
    ofstream children;
    ofstream wishlist;
    children.open("children.txt", ofstream::out);
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
void createInventoryList(){
    ofstream inventory;
    inventory.open("Inventory.txt");
    inventory<<"car,puppet,doll,puppy";
    inventory.close();
}
void createPrices(){
    ofstream prices;
    prices.open("Prices.txt");
    prices<<"50,75,25,43";
    prices.close();
}
void makeKrisKringleFly(){
    KrisKringle MrSanta(99);
    JessicaGertrude MrsSanta;
    Elfs candyTransfer(99);
    Trolls Trolly;
    string presentsTransfer;
    createLetter();
    createInventoryList();
    createPrices();
    for(int i = 0; i < 5; i ++){
        Elfs Elf(i);
        Trolls Troll;
        Elf.addToy();
        for(int i = 0; i < presentsNumber; i++){
            Troll.transferPresents(Elf.returnPresent(i), i);
        }
        Troll.setSex(Elf.getColor());
        Troll.setType(Elf.getType());
        Troll.wrapPresents();
        cout<<endl;
    }
    MrsSanta.setCandyAmount(candyTransfer.returnCandyNumber());
    MrsSanta.setCoalAmount(Trolly.getCoal());
    for(int i = 0; i < 6; i ++){
        MrSanta.setCity(candyTransfer.returnCity(i), i);
        cout<<MrSanta.getCity(i)<<endl;
    }
    cout<<"Blue Sheet: "<<Trolly.getBoyWrapping()<<endl;
    cout<<"Pink Sheet: "<<Trolly.getGirlWrapping()<<endl;
    cout<<"Candy: "<<MrsSanta.returnCandyAmount()<<endl;
    cout<<"Coal: "<<MrsSanta.returnCoalAmount()<<endl;
    cout<<"Buget: "<<MrsSanta.estimateSpendings()<<endl;
}
int main(){
//    sleep(2);
//    Loading();
    makeKrisKringleFly();
    return 0;
}
