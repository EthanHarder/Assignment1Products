#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <chrono>
using namespace std;


class CustomExceptionFileNotFound : public std::exception {
public:
    static string what() 
    {
        return "Exception:File not opened. maybe File cannot be found?";
    }
};




class Product
{
public:
    Product(int pID, string pname, float pprice, string pcatagory) : ID(pID), name(pname), price(pprice), catagory(pcatagory) {}
    void PrintSelf() { cout << "ID: " << ID << " name: " << name << " price: " << price << " catagory: " << catagory << "\n"; }
    void UpdateInfo(string pName, float pPrice, string pCatagory) { name = pName; price = pPrice; catagory = pCatagory; }
    int ID = 00000;
    string name = "Null product";
    float price = 0.00f;
    string catagory = "N/A";
};

static list<Product> products; // the internal list

void PrintList()//basically just for testing
{
    for (auto check = products.begin(); check != products.end(); ++check)
    {
        check->PrintSelf();
    }
}
int Search(int checkID) //Assumption: will not be searching based on catagory/price.
{
    std::cout << "Begin Search\n";
    auto start = std::chrono::steady_clock::now(); // Start timing
    int count = -1;
    for (const auto& target : products)
    {
        ++count;
            if (target.ID == checkID)
            {
                auto end = std::chrono::steady_clock::now(); // End timing
                cout << "Finish Search, found\n";
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "Seaching took " << duration.count() << " microseconds.\n";
                return count;
            }
    }
    auto end = std::chrono::steady_clock::now(); // End timing
    cout << "Finish Search, not found\n";
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Seaching took " << duration.count() << " microseconds.\n";
    return -1;
}

int Search(string checkName) //overloaded for string name, instead of price. Assumption: name duplicates are currently permitted. First found is returned
{
    std::cout << "Begin Search\n";
    auto start = std::chrono::steady_clock::now(); // Start timing
    int count = -1;
    for (const auto& target : products)
    {
        ++count;
        if (target.name == checkName)
        {
            auto end = std::chrono::steady_clock::now(); // End timing
            cout << "Finish Search, found\n";
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Seaching took " << duration.count() << " microseconds.\n";
            return count;
        }
    }
    auto end = std::chrono::steady_clock::now(); // End timing
    cout << "Finish Search, not found\n";
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Seaching took " << duration.count() << " microseconds.\n";
    return -1;
}

void SortID()
{ //using bubble sort. I agknowledge this isn't the best option, but the provided list is only 50 long, so I can assume the application should be sufficient.
    std::cout << "Begin ID sort\n";
    auto start = std::chrono::steady_clock::now(); // Start timing
    for (auto first = products.begin(); first != prev(products.end()); ++first)
    {
        for (auto second = next(first); second != products.end(); ++second)
        {
            if (first->ID > second->ID)
            {
                // Swap the elements
                Product temp = *first;
                *first = *second;
                *second = temp;
            }
        }
    }
    auto end = std::chrono::steady_clock::now(); // End timing
    cout << "Finish ID sort\n";
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Sorting took " << duration.count() << " microseconds.\n";
}

void ReverseSortPrice() //how i get the list in reverse order for testing
{
    std::cout << "Begin ID sort\n";
    auto start = std::chrono::steady_clock::now(); // Start timing
    for (auto first = products.begin(); first != prev(products.end()); ++first)
    {
        for (auto second = next(first); second != products.end(); ++second)
        {
            if (first->price < second->price)
            {
                // Swap the elements
                Product temp = *first;
                *first = *second;
                *second = temp;
            }
        }
    }
    auto end = std::chrono::steady_clock::now(); // End timing
    cout << "Finish ID sort\n";
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Sorting took " << duration.count() << " microseconds.\n";
}

void SortPrice() //assumption: assignmentt requests sort by price, not by all variables. not implementing name/catagory sort.
{ //using bubble sort. I agknowledge this isn't the best option, but the provided list is only 50 long, so I can assume the application should be sufficient.
    cout << "Begin price sort\n";
    auto start = std::chrono::steady_clock::now(); // Start timing
    for (auto first = products.begin(); first != prev(products.end()); ++first)
    {
        for (auto second = next(first); second != products.end(); ++second)
        {
            if (first->price > second->price)
            {
                // Swap the elements
                Product temp = *first;
                *first = *second;
                *second = temp;
            }
        }
    }
    auto end = std::chrono::steady_clock::now(); // End timing
    cout << "Finish price sort\n";

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Sorting took " << duration.count() << " microseconds.\n";
}

void Insert(string iName,float iPrice, string iCatagory) 
{
    int testID = products.back().ID + 1;
    if (Search(testID) != -1) //assumption: duplicate ID are not allowed, other values are. adds cost to an otherwise O(1), unfortunately.
    {
        SortID();
        testID = products.back().ID + 1;
    }
    products.push_back(Product(testID, iName, iPrice, iCatagory));  
    cout << "\n" << products.back().ID << "\n";
}

void Delete(int dID) //assumption: TA said error checking wasn't expected, so I won't be adding a check if the target product ID exists.
{
    list<Product>::iterator itr = products.begin();
    advance(itr, Search(dID));
    products.erase(itr);
}

void Update(int uID, string nName, float nPrice, string nCatagory) //assumption: TA said error checking wasn't expected
{
    list<Product>::iterator itr = products.begin();
    advance(itr, Search(uID));
    itr->UpdateInfo(nName, nPrice, nCatagory);
      
}

void ReadProductFile() //adds read info to product 
{
    cout << "Loading Inventory (file)\n";
    ifstream inventoryFile;
    try
    {
        inventoryFile.open("product_data.txt");
        if (!inventoryFile.is_open()) throw CustomExceptionFileNotFound();
        else cout << "File found!\n";
    }
    catch (CustomExceptionFileNotFound ce)
    {
        cout << "Custom Exception";
        cout << ce.what();
        //try again i suppose.
        inventoryFile.open("product_data.txt");
        if (!inventoryFile.is_open()) {
            cout << "Reading file failed";
            return; //exit if fails.
        }
    }

    string line;
    size_t pos = 0;
    string split = ", ";
    string token[4];
    int count = 0;
    std::cout << "Begin Loading File\n";
    auto start = std::chrono::steady_clock::now(); // Start timing
    while (getline(inventoryFile, line))
    {
        for (int i = 0; i < 4; i++)
        {
            token[i].clear(); //empties all tokens, dont want to move along info from previous item.

            if ((pos = line.find(split)) != std::string::npos) //Assumption; no errors in formatting of data. not putting any error checking here.
            {
                token[i] = line.substr(0, pos);
                line.erase(0, pos + split.length());
            }
            else token[i] = line;
        }
        products.push_back(Product(stoi(token[0]), token[1], stof(token[2]), token[3]));
    }
    inventoryFile.close();
    auto end = std::chrono::steady_clock::now(); // End timing
    cout << "Finished Loading File\n";
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Loading the File took " << duration.count() << " microseconds.\n";
}

void WriteProductFile() //assumption: assignemnt does not request editing the text document.
{}



int main()
{
    
    
    
    cout << "Welcome to store!\n"; 
    ReadProductFile();
    bool terminate = false;

    ReverseSortPrice();

    while (!terminate)
    {
        list<Product>::iterator itr = products.begin();
        int IDInput = 0;
        string nameInput = "";
        float priceInput = 0.0f;
        string catagoryInput = "";

        cout << "Please enter your input\n1:Print the item list\n2:Add a product\n3:Delete a product\n4:Search a product with ID\n5:Search a product with Name\n6:Sort By ID\n7:Sort by Price\n8: Update a product\nOther:Leave\n";
        int input;
        cin >> input;
        switch (input)
        {
            
        case 1:
            PrintList();
            break;
        case 2:
            
            cout << "What is the name of the new product?\n"; //does not include spaces. I do not understand 
            getline(std::cin >> std::ws, nameInput);
            cout << "What is the price of the new product?\n";
            cin >> priceInput;
            cout << "What is the catagory of the new product?\n";
            getline(std::cin >> std::ws, catagoryInput);
            cout << "Understood!";
            Insert(nameInput, priceInput, catagoryInput);
            break;
        case 3:
            cout << "What is the ID of the product you wish to remove?\n";
            cin >> IDInput;
            cout << "Understood!";
            Delete(IDInput);
            break;
        case 4:
            cout << "What is the ID of the product you want to search?\n";
            cin >> IDInput;
            advance(itr, Search(IDInput));
            itr->PrintSelf();
            break;
        case 5:
            cout << "What is the name of the product you want to search?\n";
            getline(std::cin >> std::ws, nameInput);
            advance(itr, Search(nameInput));
            itr->PrintSelf();
            break;
        case 6:
            SortID();
            break;
        case 7:

            SortPrice();
            break;
        case 8:
            cout << "What is the ID of the product?\n";
            cin >> IDInput;
            cout << "What is the name of the new product?\n"; //does not include spaces. I do not understand 
            getline(std::cin >> std::ws, nameInput);
            cout << "What is the price of the new product?\n";
            cin >> priceInput;
            cout << "What is the catagory of the new product?\n";
            getline(std::cin >> std::ws, catagoryInput);
            cout << "Understood!";
            Update(IDInput, nameInput, priceInput, catagoryInput);
                break;

        default:
            terminate = true;
            break;

        }
        

    }
    //cout << "size: " << products.size() << "\n";
    



}