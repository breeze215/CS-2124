/*
 Author : Uvindu Salgado
 Purpose : Inheritance
 */



#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned num) : numberOfPages(num) {}
    virtual void displayNumPages() const = 0;
private:
    unsigned numberOfPages;
};

void PrintedMaterial::displayNumPages() const{
    cout << numberOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned num) : PrintedMaterial(num) {}
    void displayNumPages() const{
        PrintedMaterial::displayNumPages();
    }
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned num) : PrintedMaterial(num) {}
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned num, unsigned index) : Book(num), numOfIndexPages(index) {}
    void displayNumPages() const {
        cout << "Index Pages: " <<  numOfIndexPages << endl;
        cout << "Pages: ";
        PrintedMaterial::displayNumPages();
    }
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned num) : Book(num) {}
    void displayNumPages() const{
        PrintedMaterial::displayNumPages();
    }
private:
};

void displayNumberOfPages(const PrintedMaterial& base){
    base.displayNumPages();
}

// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";

    cout << "\nUsing PrintedMaterial* to \"store\" a TextBook object\n";
    cout << "Now with the virtual mechanism involved\n";
    PrintedMaterial* pmPtr;
    pmPtr = &text; // like putting t into a vector but
    // we are actually putting the address of t
    // into a vector pointers of pointers to
    // PrintedMaterials. We'll "say" we are putting
    // t into the vector
    // (that is, pointers to the Base class)
    pmPtr->displayNumPages();
}


