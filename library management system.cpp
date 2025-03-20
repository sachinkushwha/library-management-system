#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <limits>
using namespace std;

//--------------------------------------------------class book------------------------------------------------------------------------------------
class book
{
public:
  string b_id, yop, B_price;
  string b_name, authorname, x, q;

public:
  string b_s;

public:
  void getbdata()
  {
    do
    {

      cout << "Enter Book Name" << endl;
      cin.ignore();
      getline(cin, b_name);
    } while (b_name.empty());
    do
    {
    a:;
      cout << "Enter Author Name" << endl;
      getline(cin, authorname);
      for (char ch : authorname)
      {
        if (!isalpha(ch))
        {
          cout << "enter only charactor" << endl;
          goto a;
        }
      }
    } while (authorname.empty());

    do
    {

      cout << "Enter book id" << endl;
      getline(cin, x);
      if (x.length() <= 7)
      {
        b_id = x;
      }
      else
      {
        cout << "\nBook id must be of 7 digit !" << endl;
      }
    } while (x.length() > 7);
    do
    {
    d:;
      cout << "Enter book price" << endl;
      getline(cin, B_price);
      for (char ch : B_price)
      {
        if (isalpha(ch))
        {
          cout << "enter only digit" << endl;
          goto d;
        }
      }
    } while (B_price.empty());

    cin.ignore();

    do
    {

    c:;
      cout << "Enter year of publication" << endl;
      getline(cin, q);
      for (char ch : q)
      {
        if (isalpha(ch))
        {
          cout << "enter only digit" << endl;
          goto c;
        }
      }
      if (q.length() <= 4)
      {
        yop = q;
      }
      else
      {
        cout << "\nyear of publication must be 4 digit !" << endl;
      }
    } while (q.length() > 4);
    b_s = "Available";
  }
  int t = 0;
  void showbook()
  {
    cout << setw(20) << left << b_name << setw(15) << authorname << setw(9) << right << b_id << setw(14) << b_s << setw(15) << right << yop << setw(12) << right << "Rs." << B_price << endl;
  }

  void storebook();
  void viwebook();
  void search();
  void issue();
  void deleteb();
  void tnofb();
};
book b;
//--------------------------------------------------student class--------------------------------------------------------------------
class student
{
  string name;

public:
  string dp;
  //   int bid;
  string bid;

public:
  int roll;

public:
  void getsdata(string n)
  {
    do
    {
      getline(cin, dp);
      cout << "Enter student name: ";
      cin.ignore();
      getline(cin, name);
    } while (name.empty());
    cout << "\nStudent id:";
    cin >> roll;
    do
    {
      cout << "\nEnter Department: ";
      cin.ignore();
      getline(cin, dp);
    } while (dp.empty());
    bid = n;
  }
  void showsdetail()
  {
    cout << bid << "\t\t" << name << "\t\t\t" << roll << "\t\t\t" << dp << endl;
  }

  void stud_detail()
  {
    cout << "\nName\t\t" << "Rollno" << "\t\t" << endl;
    cout << name << "\t\t" << roll << "\t\t" << endl;
  }
  void viwedata();
  void returnbook();
  void update();
};
student s;
//----------------------------------------------total number of book-------------------------------------
void book::tnofb()
{
  int flag = 0;
  ifstream fin;
  fin.open("book.txt", ios::in | ios::binary);
  fin.read((char *)&b, sizeof(book));
  while (!fin.eof())
  {
    flag++;
    fin.read((char *)&b, sizeof(book));
  }
  cout << "total number of books :" << flag << endl;
}
//-------------------------------------------------delete book--------------------------------------------------------------

void book::deleteb()
{
  int count = 0;
  string t;
  cin.ignore();
  cout << "Enter Book ID " << endl;
  getline(cin, t);
  ifstream fin;
  ofstream fout;
  fout.open("temp.txt", ios::app | ios::binary);

  fin.open("book.txt", ios::in | ios::binary);
  fin.read((char *)&b, sizeof(book));
  while (!fin.eof())
  {
    if (t.compare(b_id) == 0)
    {
      count++;
    }
    else
    {
      fout.write((char *)&b, sizeof(book));
    }
    fin.read((char *)&b, sizeof(book));
  }
  fin.close();
  fout.close();
  remove("book.txt");
  rename("temp.txt", "book.txt");
  if (count == 0)
  {
    cout << "Book not found!..." << endl;
  }
  else
  {
    cout << "Book Deleted successfully..." << endl;
  }
}
//------------------------------------------------------return book-----------------------------------------------------------------------
void student::returnbook()
{
  int t, count = 0;
  cout << "Enter Student  Roll no. " << endl;
  cin >> t;
  ifstream fin;
  ofstream fout;
  fout.open("temp1.txt", ios::app | ios::binary);

  fin.open("student.txt", ios::in | ios::binary);
  fin.read((char *)&s, sizeof(student));
  while (!fin.eof())
  {
    if (t == roll)
    {
      fstream file;
      file.open("book.txt", ios::in | ios::out | ios::binary);
      file.read((char *)&b, sizeof(book));
      while (!file.eof())
      {
        int pos = file.tellp();
        if (bid.compare(b.b_id) == 0)
        {
          b.b_s = "Available";
          file.seekp(pos - sizeof(b));
          file.write((char *)&b, sizeof(b));
        }
        file.read((char *)&b, sizeof(book));
      }
      file.close();

      count++;
    }
    else
    {
      fout.write((char *)&s, sizeof(student));
    }
    fin.read((char *)&s, sizeof(student));
  }
  fin.close();
  fout.close();
  remove("student.txt");
  rename("temp1.txt", "student.txt");
  if (count == 0)
  {
    cout << "Student not found!..." << endl;
  }
  else
  {
    cout << "Book return successfully..." << endl;
  }
}
//------------------------------------------------issue book----------------------------------------------------------------------
void book::issue()
{
  int count = 0, flag = 0;
  string t;
  cin.ignore();
  cout << "Enter Book ID" << endl;
  getline(cin, t);
  ifstream fin;
  ofstream fout;
  fout.open("student.txt", ios::app | ios::binary | ios::out);
  fin.open("student.txt", ios::in | ios::binary);
  fin.read((char *)&s, sizeof(student));
  while (!fin.eof())
  {
    if (t.compare(s.bid) == 0)
    {
      cout << "Book already issued" << endl;
      flag++;
      break;
    }
    fin.read((char *)&s, sizeof(student));
  }
  fin.close();
  fin.open("book.txt", ios::in | ios::binary);

  if (flag == 0)
  {
    fin.read((char *)&b, sizeof(book));
    while (!fin.eof())
    {
      if (t.compare(b.b_id) == 0)
      {
        s.getsdata(b_id);

        fout.write((char *)&s, sizeof(student));
        count++;
        break;
      }
      else

        fin.read((char *)&b, sizeof(book));
    }
    fout.close();
    fin.close();
    if (count == 0)
    {
      cout << "Book not found..." << endl;
    }
    else
    {
      cout << endl;
      cout << "Book issued successfully" << endl;
      fstream file;
      file.open("book.txt", ios::in | ios::out | ios::binary);
      file.read((char *)&b, sizeof(book));
      while (!file.eof())
      {
        int pos = file.tellp();
        if (t.compare(b_id) == 0)
        {
          b_s = "Not Available";
          file.seekp(pos - sizeof(b));
          file.write((char *)&b, sizeof(b));
        }
        file.read((char *)&b, sizeof(book));
      }
      file.close();
    }
  }
}

//-----------------------------------------------view student data-------------------------------------------------------------------
void student::viwedata()
{
  ifstream fin;
  fin.open("student.txt", ios::in | ios::binary);
  fin.read((char *)&s, sizeof(student));
  while (!fin.eof())
  {
    showsdetail();
    fin.read((char *)&s, sizeof(student));
  }
}
//--------------------------------------------------------------viwe book-------------------------------------------------------------------
void book::viwebook()
{
  ifstream fin;
  fin.open("book.txt", ios::in | ios::binary);
  fin.read((char *)&b, sizeof(book));
  while (!fin.eof())
  {
    showbook();
    fin.read((char *)&b, sizeof(book));
  }
}

void book::storebook()
{

  ofstream fout;
  fout.open("book.txt", ios::out | ios::app | ios::binary);
  fout.write((char *)&b, sizeof(book));
  fout.close();
}

//-----------------------------------------------search book-----------------------------------------------------------------
void book::search()
{
  int count, ch;
  string t1, t;
  ifstream fin;
  cout << "1. Search by ID " << endl;
  cout << "2. Search by Title " << endl;
  cout << "Enter your choice" << endl;
  cin >> ch;
  switch (ch)
  {
  case 1:
    count = 0;
    cin.ignore();
    cout << "Enter book id " << endl;
    getline(cin, t);
    fin.open("book.txt", ios::in | ios::binary);
    fin.read((char *)&b, sizeof(book));
    while (!fin.eof())
    {
      if (t.compare(b_id) == 0)
      {
        cout << "Title" << "\t\t" << "Author name" << "\t\t" << "Book id" << "\t\t" << "Status" << "\t\t" << "Price" << endl;
        showbook();
        count++;
        break;
      }
      else

        fin.read((char *)&b, sizeof(book));
    }
    fin.close();
    break;

  case 2:
    count = 0;
    cout << "Enter book title " << endl;
    cin.ignore();
    getline(cin, t1);
    fin.open("book.txt", ios::in | ios::binary);
    fin.read((char *)&b, sizeof(book));
    while (!fin.eof())
    {
      if (t1.compare(b_name) == 0)
      {
        cout << "Title" << "\t\t" << "Author name" << "\t\t" << "Book id" << "\t\t" << "Status" << "\t\t" << "Price" << endl;
        showbook();
        count++;
        break;
      }
      else

        fin.read((char *)&b, sizeof(book));
    }
    fin.close();
    break;
  default:
    cout << "Enter right choice..." << endl;
  }
  if (count == 0)
  {
    cout << "Book not found..." << endl;
  }
  else if (count == 1)
    cout << "Search Successful" << endl;
}
//-------------------------------------------------main manu-----------------------------------------------------------------
class mainmenu
{

  int ch;

public:
  void menu()
  {
    do
    {
      system("cls");
    b:
      cout << "=========================================================================================" << endl;
      cout << "=================================           AGC          ================================" << endl;
      cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
      cout << "=========================================================================================" << endl;
      cout << "----------------------------------------main menu----------------------------------------" << endl;
      cout << endl;
      cout << "                                  1. Add book" << endl;
      cout << "                                  2. Show books Record" << endl;
      cout << "                                  3. Search book" << endl;
      cout << "                                  4. Issue book" << endl;
      cout << "                                  5. Return book" << endl;
      cout << "                                  6. Show issued book data" << endl;
      cout << "                                  7. Delete book" << endl;
      cout << "                                  8. Update student data" << endl;
      cout << "                                  9. total number of books" << endl;
      cout << "                                  10. Exit" << endl;

      cout << "enter your choice..." << endl;
      if (cin >> ch)
      {
        switch (ch)
        {
        case 10:
          exit(10);
          break;
        case 1:
          system("cls");
          cout << "=========================================================================================" << endl;
          cout << "=================================           AGC          ================================" << endl;
          cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
          cout << "=========================================================================================" << endl;
          b.getbdata();
          b.storebook();
          break;

        case 2:
          system("cls");
          cout << "=========================================================================================" << endl;
          cout << "=================================           AGC          ================================" << endl;
          cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
          cout << "=========================================================================================" << endl;
          cout << setw(20) << left << "Title" << setw(10) << left << "Author Name" << setw(15) << right << "Book id" << setw(12) << right << "Status" << setw(16) << right << "Published" << setw(15) << right << "Price" << endl;
          b.viwebook();
          break;

        case 3:
          system("cls");
          cout << "=========================================================================================" << endl;
          cout << "=================================           AGC          ================================" << endl;
          cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
          cout << "=========================================================================================" << endl;
          b.search();
          break;

        case 4:
          system("cls");
          cout << "=========================================================================================" << endl;
          cout << "=================================           AGC          ================================" << endl;
          cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
          cout << "=========================================================================================" << endl;
          b.issue();
          break;
        case 5:
          system("cls");
          cout << "=========================================================================================" << endl;
          cout << "=================================           AGC          ================================" << endl;
          cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
          cout << "=========================================================================================" << endl;
          s.returnbook();
          break;
        case 6:
          system("cls");
          cout << "=========================================================================================" << endl;
          cout << "=================================           AGC          ================================" << endl;
          cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
          cout << "=========================================================================================" << endl;
          cout << "Book id" << "\t\t" << "Student name" << "\t\t" << "Student id" << "\t\t" << "Student department " << endl;
          s.viwedata();
          break;
        case 7:
          system("cls");
          cout << "=========================================================================================" << endl;
          cout << "=================================           AGC          ================================" << endl;
          cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
          cout << "=========================================================================================" << endl;
          b.deleteb();
          break;
        case 8:
          system("cls");
          cout << "=========================================================================================" << endl;
          cout << "=================================           AGC          ================================" << endl;
          cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
          cout << "=========================================================================================" << endl;
          s.update();
          break;
        case 9:
          system("cls");
          cout << "=========================================================================================" << endl;
          cout << "=================================           AGC          ================================" << endl;
          cout << "================================ LIBRARY MANAGMENT SYSTEM ===============================" << endl;
          cout << "=========================================================================================" << endl;
          b.tnofb();
          break;
        default:
          cout << "Invalid Input !\npress any key " << endl;
          getch();
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          system("cls");
          goto b;
        }
      }
      else
      {
        cout << "Invalid Input !\npress any key " << endl;
        getch();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        goto b;
      }
      cout << "To be continue press any key..." << endl;
      getch();
    } while (ch);
  }
};
mainmenu m;
//-----------------------------------------------main function---------------------------------------------------------------------------
int main()
{
  system("cls");

  m.menu();

  return 0;
}
//-------------------------------------------update student info---------------------------------------------------------------------
void student::update()
{
  int r, ch, flag = 0;
  string d, n;
  fstream file;
  file.open("student.txt", ios::in | ios::out | ios::binary);
  cout << "Enter the roll no of the student whose data you want to update." << endl;
  cin >> r;
  file.read((char *)&s, sizeof(s));
  while (!file.eof())
  {
    int pos = file.tellp();
    if (r == roll)
    {

      cout << "Select one which you want to update" << endl;
      cout << "1. Update Student Roll no" << endl;
      cout << "2. Update Student Department " << endl;
      cout << "3. Update Student Name" << endl;
      cout << "Enter your choice..." << endl;
      cin >> ch;
      switch (ch)
      {
      case 1:
        cout << "Enter New Roll no" << endl;
        int nr;
        cin >> nr;
        roll = nr;
        file.seekp(pos - sizeof(s));
        file.write((char *)&s, sizeof(s));
        flag++;

        break;
      case 2:
        cout << "Enter new Department " << endl;
        getline(cin, d);
        getline(cin, d);
        dp = d;
        file.seekp(pos - sizeof(s));
        file.write((char *)&s, sizeof(s));
        flag++;
        break;
      case 3:
        cout << "Enter New Name" << endl;
        getline(cin, n);
        getline(cin, n);
        name = n;
        file.seekp(pos - sizeof(s));
        file.write((char *)&s, sizeof(s));
        flag++;
        break;
      default:
        cout << "Enter right choice..." << endl;
      }
    }
    file.read((char *)&s, sizeof(s));
  }

  file.close();
  if (flag == 0)
  {
    cout << "Record not found! " << endl;
  }
  else
    cout << "Record update successfuly" << endl;
}