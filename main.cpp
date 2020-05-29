#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;

#define BOOKFILE "books.dat"
#define STUDENTFILE "students.dat"
#define REVIEWFILE "bookreview.dat"
#define SYSTEMCLEAR "clear" // on windows can use cls


// **************************************************
// Definition of class book
// **************************************************

class book
{
    int bno;
    char bname[50];
    int cost;
    char author[50];
    char publisher[50];
    int copies_in_stock;
    int copies_issued;
  public:
    void  getdata();
    void out();
    char*  getbname();
    int getbno();
    int getcost_book();

   // **************************************************
   // Methods of class book
   // **************************************************

    int returnbno(){
       return bno;
    }
    int return_total(){
      return copies_in_stock;
    }
    int return_issued(){
       return copies_issued;
    }
    void inc_issued(){
       copies_issued=copies_issued+1;
    }

    void dec_issued(){
       copies_issued=copies_issued-1;
    }
};


// **************************************************
// Method to add a book to the Library Database File
// **************************************************

void book::getdata()
{
    cout<<"\nEnter the number of the book = ";
    cin>>bno;
    cout<<"Enter book's name = ";
    cin>>bname;
    cout<<"Enter the book's cost = ";
    cin>>cost;
    cout<<"Enter the book's author = ";
    cin>>author;
    cout<<"Enter the book's publisher = ";
    cin>>publisher;
    cout<<"Enter the number of copies of the book = ";
    cin>>copies_in_stock;
    copies_issued=0;
}

// **************************************************
// Method to display details of a book
// **************************************************

void book::out()
{
    cout<<"\nThe number of the book is =  ";
    cout<<bno<<"\n";
    cout<<"Name of the book = ";
    cout<<bname<<"\n";
    cout<<"Cost of the book = ";
    cout<<cost<<"\n";
    cout<<"Author of the book = ";
    cout<<author<<"\n";
    cout<<"Publisher of the book = ";
    cout<<publisher<<"\n";
    cout<<"Number of copies in stock = ";
    cout<<copies_in_stock<<"\n";
    cout<<"Number of copies issued = ";
    cout<<copies_issued<<"\n";
}

char* book::getbname()
{
    return bname;
}
int book::getcost_book()
{
    return cost;
}
int book::getbno()
{
    return bno;
}

// **************************************************
// Definition of class student
// **************************************************

class student{
  private:
    char sname[50];
    char admin[7];
    int token;
    int stbno;

  public:
    // **************************************************
    // Method to add details of student
    // **************************************************
    void in(){
        cout<<"Enter student's name = ";
        cin>>sname;
        cout<<"Enter student's admin number = ";
        cin>>admin;
        token=0;
        stbno=-1;
    }
    // *************************************************
    // Method to display details of a student
    // *************************************************

    void out(){
        cout<<"\n Name of student = ";
        cout<<sname;
        cout<<"\n class of student = ";
        cout<<"\n Admin number of student = ";
        cout<<admin;
        cout<<"Token status (status=1 means book issued , 0 means no book issued) = ";
        cout<<"token";
    }
    void addtoken(){
        token=1;
    }
    void resettoken(){
        token=0;
    }
    int rettoken(){
        return token;
    }
    char* ret_admin(){
        return admin;
    }
    void gets_bno(int y){
        stbno=y;
    }
    int retstbno(){
        return stbno;
    }

};

// **************************************************
// Method to add students to library
// **************************************************

void add_stu()
{
    system(SYSTEMCLEAR);
    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\nADDING STUDENTS\n\n";
    student s;
    ofstream f(STUDENTFILE,ios::binary|ios::app);
    int n;
    cout<<"\nHow many students wish to register: ? ";
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        s.in();
        f.write((char*)&s,sizeof(s));
    }
    f.close();
}

// *************************************************
// Method to add books
// *************************************************

void append()
{
    system(SYSTEMCLEAR);
    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\n#########ADDING BOOK #########\n\n";
    book s;
    ofstream f(BOOKFILE,ios::binary|ios::app);
    int n;
    cout<<"\nHow many records do you want to enter: ? ";
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        s.getdata();
        f.write((char*)&s,sizeof(s));
    }
    f.close();
}

// **************************************************
// Method to modify book details
// **************************************************

void bmodify()
{
    system(SYSTEMCLEAR);
    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\n#########MODIFYING BOOK #########\n\n";
    int num,flag=0;

    cout<<"\nEnter book number that you wish to modify : ";
    cin>>num;

    int x;
    book s;

    fstream f(BOOKFILE,ios::binary|ios::in|ios::out);
    while(f.read((char*)&s,sizeof(s)))
    {
        if(s.getbno()==num){
            x=-1*(int)sizeof(book);
            f.seekp(x,ios::cur);
            cout<<"\nEnter new data\n";
            s.getdata();
            f.write((char*)&s,sizeof(book));
            cout<<"\nRecord Modified\n";
            flag=1;
         break;
        }
    }
    f.close();
    if(flag==0)
        cout<<"\nNo record found!";
}

// **************************************************
// Method to search for a book
// **************************************************

void searchbyname()
{
    system(SYSTEMCLEAR);
    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\n#########SEARCHING FOR BOOK #########\n\n";
    char a[50];
    cout<<"\nEnter book name=";
    cin>>a;
    ifstream fin(BOOKFILE,ios::binary);
        book s;
    while(fin.read((char*)&s,sizeof(s)))
    {
        if(strcmp(s.getbname(),a)==0)
            s.out();
    }
    fin.close();
}

// **************************************************
// Method to delete a book
// **************************************************

void del(int &n)
{
    system(SYSTEMCLEAR);
    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\n#########DELETING BOOK #########\n\n";
    book s;
    ifstream f;
    f.open(BOOKFILE,ios::binary);
    ofstream g;
    g.open("temp.dat",ios::out|ios::binary);
    while(f.read((char*)&s,sizeof(s)))
    {
        if(s.getbno()!=n)
        {
            g.write((char*)&s,sizeof(s));
        } else {
            cout<<"Found record deleting\n";
            s.out();
        }
    }
    f.close();
    g.close();
    remove(BOOKFILE);
    rename("temp.dat",BOOKFILE);
}

// **************************************************
// Method to display books
// **************************************************

void display()
{
    system(SYSTEMCLEAR);
    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\n#########DISPLAYING BOOK #########\n\n";
    cout<<"\n\nLIST OF BOOKS\n\n";
    ifstream fin(BOOKFILE,ios::binary);
    book s;
    while(fin.read((char*)&s,sizeof(s))){
          s.out();
    }
    fin.close();
}

// **************************************************
// Method to sort books
// **************************************************

void sort_cost_book() {
    system(SYSTEMCLEAR);

    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\n#########SORTING BOOKS BY COST#########\n\n";
    int i,j;
    ifstream fin(BOOKFILE,ios::binary);
    book s[50], t;
    int num=0;
    while(fin.read((char*)&s[num],sizeof(book))){
            num=num+1;
    }
    for(i=0; i<num; i++){
        for(j=0;j<num-i-1;j++){
            if(s[j].getcost_book()>s[j+1].getcost_book()){
                t=s[j];
                s[j]=s[j+1];
                s[j+1]=t;
            }
        }
    }
    fin.close();
    for (int i=0; i<num; i++) {
            cout<<"\n**********************************\n";
            s[i].out();
            cout<<"\n**********************************\n";
    }
}

// **************************************************
// Method to issue a book
// **************************************************

void issue(){
    system(SYSTEMCLEAR);

    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\n#########ISSUING BOOK #########\n\n";
    cout<<"\n";
    student x;
    book s;
    int m;
    char k[50];
    fstream fin;
    fin.open(BOOKFILE, ios::binary|ios::in|ios::out|ios::binary);
    fstream f;
    f.open(STUDENTFILE, ios::out|ios::in | ios::binary);
    cout<<"\nEnter your admin number = ";
    cin>>k;
    int found=0;
    while(f.read((char*)&x, sizeof(x)) && found==0){
        // cout<<"entering loop"<<x.ret_admin();
        if(strcmp(x.ret_admin(),k)==0){
            found=1;
            if(x.rettoken()==0){
                //take book number to be issued
                cout<<"Enter the book number you want to issue = ";
                cin>>m;
                int flag=0;
                while(fin.read((char*)&s, sizeof(s)) && flag==0){
                    if(s.getbno()==m){
                        //to check whether if all copies are issued
                            if(s.return_issued()<s.return_total()){
                                s.inc_issued();
                                int p=-1*(int)sizeof(s);
                                fin.seekp(p,ios::cur);
                                fin.write((char*)&s,sizeof(s));
                                fin.close();
                                //after issue of book, incrementing token
                                x.addtoken();
                                cout<<"\nBook is available. ";
                                cout<<"\nComplete book details are ";
                                s.out();
                                flag=1;
                                x.gets_bno(s.getbno()); //to assign the book number to student member function stbno
                                int pos =-1*(int)sizeof(x);
                                f.seekp(pos,ios::cur);
                                f.write((char*)&x , sizeof(x));
                                f.close();
                                cout<<"\nBook issued successfully";
                            } else {
                                flag=2;
                            }
                    }
                }
                if(flag==0)
                    cout<<"This book does not exist";
                if(flag==2)
                    cout<<"All copies of the book have been issued";
            } else {
                cout<<"You have not returned the last book";
            }
        }
    }
    if(found==0)
        cout<<"Student record does not exist";
    fin.close();
    f.close();
}

// **************************************************
// Method to DEPOSIT A BOOK
// **************************************************

void ret() {
    system(SYSTEMCLEAR);
    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\n#########DEPOSITING BOOK #########\n\n";

    student x;
    book s;
    char a[80];
    cout<<"DEPOSITING BOOK";
    cout<<"\n Enter your admin number = ";
    cin>>a;
    fstream f;
    fstream f1;
    f.open(STUDENTFILE, ios::in| ios::out| ios::binary);
    f1.open(BOOKFILE, ios::in| ios::out| ios::binary);
    int found=0;
    int flag=0;
    while(f.read((char*)&x, sizeof(x)) && found==0){
        if(strcmp((x.ret_admin()),a)==0){
            found=1;
            if(x.rettoken()==1){
                while(f1.read((char*)&s, sizeof(s))&& flag==0){
                    if(s.returnbno()==x.retstbno()){
                        s.out();
                        flag=1;
                        x.resettoken();
                        int pos=-1*(int)sizeof(student);
                        f.seekp(pos,ios::cur);
                        f.write((char*)&x, sizeof(student));
                        s.dec_issued();
                        int p=-1*(int)sizeof(s);
                        f1.seekp(p,ios::cur);
                        f1.write((char*)&s,sizeof(s));
                        f1.close();
                        // s.out();
                        cout<<"\n Book deposited successfully";
                    }
                }
                if(flag==0)
                    cout<<"\n Book does not exist";
            }
            else
                cout<<"\n No book is issued, please check";
        }
    }
    if(found==0)
        cout<<"Student record does not exist";
    f.close();
    f1.close();

}


// **************************************************
// Definition of class review
// **************************************************

class review {
    int bno;
    char comments[200];
    string cmts;
    public:
        void getreview();
        void putreview();
        int getbno();
        int getrating();
};

// **************************************************
// Method to record review of a book
// **************************************************

void review::getreview(){
    cout<<"\nEnter book number for which you want to add a review: ";
    cin>>bno;
    cout<<"\nEnter your opinion about the book in less than 200 characters: ";
    //fflush(stdin);
    // cin.getline(cmts, 200,'\n');
    cin>>cmts;
    // getline(cin,cmts);
    cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
    cout<<"You endtered " << cmts;
    // cout<<"You endtered " << comments;
    //fflush(stdin);
    //fflush(cin);
}

void review::putreview(){
    cout<<"REVIEW: "<<"\n";
    //cout<<comments;
    cout<<cmts;
}

int review::getbno(){
    return bno;
}

// ************************************************
// Function to add review into the binary file REVIEWFILE
// ***************************************************

void append_review()
{
     system(SYSTEMCLEAR);
     cout<<"**************************************************************";
     cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
     cout<<"\n**************************************************************\n";

     cout<<"\n\n#########ADDING REVIEW #########\n\n";

     review r;
     ofstream f(REVIEWFILE,ios::binary|ios::app);

     r.getreview();
     f.write((char*)&r,sizeof(r));

     f.close();
}

void display_review()
{
    system(SYSTEMCLEAR);
    cout<<"**************************************************************";
    cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
    cout<<"\n**************************************************************\n";

    cout<<"\n\n#########DISPLAYING BOOK REVIEW #########\n\n";

    int num, flag=0;
    cout<<"\nEnter the book number whose review you want to see: ";
    cin>>num;
    review r;
    ifstream fin(REVIEWFILE,ios::binary);

    while(fin.read((char*)&r,sizeof(r))){
            if(r.getbno()==num){
                    cout<<"\n----------------------------------\n";
                    r.putreview();
                    cout<<"\n----------------------------------\n";
                    flag++;
            }

    }
    if(flag==0)
        cout<<"\nNo review found\n";
    fin.close();
}

int main(){

   remove ("temp.dat");
    int choice,t, r;
    int n=0;
    string a;
    while(1)
    {
        system(SYSTEMCLEAR);
        cout<<"**************************************************************";
        cout<<"\n******************BOOK MANAGEMENT SYSTEM**********************\n";
        cout<<"\n**************************************************************\n";
        cout<<"\nMENU:\n\n";
        cout<<"-->LIBRARIAN TO PRESS 1-6 TO MANAGE LIBRARY\n";
        cout<<"-->STUDENTS TO PRESS 7-8 TO ISSUE/RETURN BOOKS\n";
        cout<<"-->IF YOU ARE A NEW ADMISSION, PRESS 9 TO REGISTER YOURSELF\n";
        cout<<"-->TO READ/ADD A REVIEW PRESS 10-11\n";
        cout<<"-->TO EXIT PRESS 12\n";


        cout<<"\nENTER CHOICE :\n1-ADD BOOK TO LIB\n2-MODIFY BOOK DETAILS";
        cout<<"\n3-DISPLAY BOOK DETAILS \n4-SEARCH FOR A BOOK\n5-DELETE A BOOK\n6-SORT BOOKS BY COST";
        cout<<"\n7-ISSUE \n8-RETURN \n9-NEW STUDENTS TO REGISTER THEMSELVES IN LIBRARY ";
        cout<<"\n10-ADD REVIEW \n11-READ REVIEWS  ";
        cout<<"\n12-Exit ";

        cout<<"\nEnter choice : ";
        //int choice;
        // fflush(stdin);
        // cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
        cin>>choice;

        switch (choice ) {

            case 1:
                append();
                n++;
                break;
            case 2:
                bmodify();
                break;
            case 3:
                display();
                break;
            case 4:
                searchbyname();
                break;
            case 5:
                cout<<"\nEnter the book number that you want to delete : ";
                cin>>r;
                del(r);
                break;
            case 6:
                // cout<<"The sorted list is : ";
                sort_cost_book();
                break;
            case 7:
                issue();
                break;
            case 8:
                ret();
                break;
            case 9:
                add_stu();
                break;
            case 10:
                append_review();
                break;
            case 11:
                display_review();
                break;
            case 12:
                exit(0);
            default:
                cout<<"Invalid choice "<<choice;

    }
    //string a;
    cout << "\nPress Any Key to continue"<<endl;

    cin>>a;
    cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
    // cout<<"\n entered string "<<a;
   }

 return 0;
}
