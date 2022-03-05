#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

class Commodity
{
private:
    int id;
    float price;
    string name, group;
public:
    void setID(int);
    int getID();
    string getName();
    float getPrice();
    friend istream &operator >>(istream &, Commodity &);
    friend ostream &operator <<(ostream &, Commodity &);
    friend void writeCommodity(Commodity);
    friend vector<Commodity> readCommodity();
};
void Commodity::setID(int i)
{
    id = i;
}
int Commodity::getID()
{
    return id;
}
string Commodity::getName()
{
    return name;
}
float Commodity::getPrice()
{
    return price;
}
istream &operator >>(istream &is, Commodity &c)
{
    cout << "Item name: ";
    getline(is, c.name);
    cout << "Item group: ";
    getline(is, c.group);
    cout << "Price: ";
    is >> c.price;
    return is;
}
ostream &operator <<(ostream &os, Commodity &c)
{
    os<< left << setw(18) << c.id << setw(20) << c.name << setw(20) << c.group << setw(10) << c.price << endl;
    return os;
}
void writeCommodity(Commodity c)
{
    fstream fout;
    fout.open("Commodity.dat", ios::out | ios::app);
    fout << c.id << endl
         << c.name << endl
         << c.group << endl
         << c.price << endl;
}
vector<Commodity> readCommodity()
{
    vector<Commodity> list;
    fstream fin;
    fin.open("Commodity.dat", ios::in);
    Commodity c;
    while (!fin.eof())
        {
            fin >> c.id >> ws;
            getline(fin,c.name);
            getline(fin,c.group);
            fin >> c.price;
            if(!fin.eof())
                list.push_back(c);
        }
    fin.close();
    return list;
}

class People
{
private:
    string name, address, phone_number;
public:
    People();
    People(string, string, string);
    string getName();
    string getAdd();
    string getPN();
};
People::People() {}
People::People(string n, string a, string p)
{
    name = n;
    address = a;
    phone_number = p;
}
string People::getName()
{
    return name;
}
string People::getAdd()
{
    return address;
}
string People::getPN()
{
    return phone_number;
}

class Customer : public People
{
private:
    int id;
public:
    Customer();
    Customer(int, string, string, string);
    int getID();
    void setID(int);
    friend istream &operator >>(istream &, Customer &);
    friend ostream &operator <<(ostream &, Customer &);
    friend void writeCustomer(Customer);
    friend vector<Customer> readCustomer();
};
Customer::Customer() {}
Customer::Customer(int i, string n, string a, string p) : People(n,a,p)
{
    id = i;
}
void Customer::setID(int i)
{
    id = i;
}
int Customer::getID()
{
    return id;
}

istream &operator >>(istream &is, Customer &cu)
{
    string name, address, phone_number, group;
    cout << "Customer name: ";
    getline(is, name);
    cout << "Address: ";
    getline(is, address);
    cout << "Phone number: ";
    getline(is, phone_number);
    Customer k(0,name,address,phone_number);
    cu = k;
    return is;
}
ostream &operator <<(ostream &os, Customer &cu)
{
    os << left << setw(18) << cu.id << setw(20) << cu.getName() << setw(20) << cu.getAdd()
       << setw(20) << cu.getPN() << endl;
    return os;
}
void writeCustomer(Customer cu)
{
    fstream fout;
    fout.open("Customer.dat", ios::out | ios::app);
    fout << cu.id << endl
         << cu.getName() << endl
         << cu.getAdd() << endl
         << cu.getPN() << endl;
}
vector<Customer> readCustomer()
{
    vector<Customer> list;
    fstream fin;
    fin.open("Customer.dat", ios::in);
    while (!fin.eof())
        {
            string name, address, phone_number, group;
            int id;
            fin >> id >> ws;
            getline(fin,name);
            getline(fin,address);
            getline(fin,phone_number);
            Customer k(id,name,address,phone_number);
            if(!fin.eof())
                list.push_back(k);
        }
    fin.close();
    return list;
}

class List {
private:
    int quantity;
    Commodity commodity;
    Customer customer;
public:
    List();
    List(Customer, Commodity, int);
    int getQuantity();
    Commodity getCommodity();
    Customer getCustomer();
};
List::List() {}
List::List(Customer cu, Commodity c, int q)
{
    customer = cu;
    commodity = c;
    quantity = q;
}
int List::getQuantity()
{
    return quantity;
}
Commodity List::getCommodity()
{
    return commodity;
}
Customer List::getCustomer()
{
    return customer;
}

bool bought(vector<List> list, int c_id, int cu_id)
{
    for (int i = 0; i<list.size();i++)
    {
        List l= list[i];
        if (l.getCustomer().getID() == cu_id && l.getCommodity().getID() == c_id)
            return true;
    }
    return false;
}
void printList(vector<List> list)
{
    cout << left << setw(18) << "Customer ID" << setw(20) << "Customer name" << setw(18) << "Item ID"
         << setw(20) << "Item name" << setw(10) << "Qty" << endl;
    
    for (int i=0; i<list.size(); i++)
    {
        List l = list[i];
        cout << left << setw(18) << l.getCustomer().getID() << setw(20) << l.getCustomer().getName() 
             << setw(18) << l.getCommodity().getID() << setw(20) << l.getCommodity().getName() 
             << setw(10) << l.getQuantity() << endl;
         
    }
}
void writeList(vector<List> list)
{
    fstream fout;
    fout.open("List.dat", ios::app); 
    for (int i=0; i<list.size(); i++)
    {
        List l = list[i];
        fout << l.getCustomer().getID() << endl
             << l.getCustomer().getName() << endl
             << l.getCommodity().getID() << endl
             << l.getCommodity().getName() << endl
             << l.getQuantity() << endl;
    }
}

string splitName(string s)
{
    string name = s.substr(s.find_last_of(" ")+1, s.length());
    name += s;
    return name;
}
bool customerName(List l1, List l2)
{
    string name1 = splitName(l1.getCustomer().getName());
    string name2 = splitName(l2.getCustomer().getName());
    return name1 < name2;
}
bool commodityName(List l1, List l2)
{
    return l1.getCommodity().getName() < l2.getCommodity().getName();
}
bool sortIDc(Commodity c1, Commodity c2)
{
    return c1.getID() < c2.getID();
}
bool sortIDcu(Customer cu1, Customer cu2)
{
    return cu1.getID() < cu2.getID();
}
int main()
{
    int choice;
    vector<Commodity> listC = readCommodity();
    vector<Customer> listCu = readCustomer();
    vector<List> list;
    do
    {
        cout << "********************MENU*********************\n";
        cout << "**  1. Commodity.                          **\n";
        cout << "**  2. Customer.                           **\n";
        cout << "**  3. Shopping list.                      **\n";
        cout << "**  0. Exit.                               **\n";
        cout << "*********************************************\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();
        cout << "\n------------------------------------------------------------------\n";
        switch (choice)
        {
        case 0:
            break;
        case 1:
        {
            int n;
            while (true)
            {
                cout << "*******************COMMODITY*****************\n";
                cout << "**  1. Add item.                           **\n";
                cout << "**  2. Delete item.                        **\n";
                cout << "**  3. Print item list.                    **\n";
                cout << "**  0. Back.                               **\n";
                cout << "*********************************************\n";
                cout << "Your choice: ";
                cin >> n;
                cin.ignore();
                cout << "\n------------------------------------------------------------------\n";
                if (n == 0) break;
                switch (n)
                {
                case 1:
                {
                    Commodity c;
            		cin >> c;
            		bool check = false;
            		for (int i=0; i<listC.size(); i++)
            			if (c.getName() == listC[i].getName())
            			{	
            				cout << "Item already exists\n";
            				check = true;
            				break;
            			}
            		cout << "\n------------------------------------------------------------------\n";
            		if (check == true) break;
					int count = 0;
            		for (int i=0; i<listC.size(); i++)
            			if ((listC[i].getID()-1000) != i)
            			{
            				c.setID(1000+i);
            				listC.push_back(c);
            				count++;
            				break;
            			}
					if (count!=0)
					{
        				sort(listC.begin(), listC.end(), sortIDc);
        				remove("Commodity.dat");
            			for (int i=0; i<listC.size(); i++)
    						writeCommodity(listC[i]);
    				}
    				else
    				{
    					c.setID(1000+listC.size());
            			listC.push_back(c);
            			writeCommodity(c);	
					}
            		break;
                }
                case 2:
                {
        			int c_id;
        			bool check = false;
        			cout << "Enter item ID: ";
		    		cin >> c_id;
		    		for (int i=0; i<listC.size(); i++)
		    			if (listC[i].getID() == c_id)
 		   				{
	 		   				cout << "Item:\n";
  			  				cout << left << setw(18) << "ID" << setw(20) << "Name" 
        		            	 << setw(20) << "Group" << setw(10) << "Price" << endl;
                		    cout << listC[i];
                		    cout << "\n------------------------------------------------------------------\n";
               			    check = true;
							listC.erase(listC.begin() + i);
							break;		
						};
					if (check == false)
					{ 
						cout << "This item does not exist\n";
						cout << "\n------------------------------------------------------------------\n";
					}
					else
					{
						remove("Commodity.dat");
            			for (int i=0; i<listC.size(); i++)
    						writeCommodity(listC[i]);
					}
    				break;
                }
                case 3:
                {
                	if (listC.size() > 0)
            		{
                		cout << left << setw(18) << "ID" << setw(20) << "Name" 
                		     << setw(20) << "Group" << setw(10) << "Price" << endl;
                		for (int i=0; i<listC.size(); i++)
                    		cout << listC[i];
                		cout << "\n------------------------------------------------------------------\n";
            		} else
					{
						cout << "\nEmpty list" << endl;
						cout << "\n------------------------------------------------------------------\n";
					} 
            		break;
				}
                default:
                    break;
            	}
            }
            break;
        }
        case 2:
        {
            int n;
            while (true)
            {
                cout << "*******************CUSTOMER******************\n";
                cout << "**  1. Add customer.                       **\n";
                cout << "**  2. Delete customer.                    **\n";
                cout << "**  3. Print customer list.                **\n";
                cout << "**  0. Back.                               **\n";
                cout << "*********************************************\n";
                cout << "Your choice: ";
                cin >> n;
                cin.ignore();
                cout << "\n------------------------------------------------------------------\n";
                if (n == 0) break;
                switch (n)
                {
                case 1:
                {
                    Customer cu;
            		cin >> cu;
            		bool check = false;
            		for (int i=0; i<listCu.size(); i++)
            			if (cu.getName() == listCu[i].getName() && cu.getPN() == listCu[i].getPN() )
            			{	
            				cout << "Customer already exists\n";
            				check = true;
            				break;
            			}
            		cout << "\n------------------------------------------------------------------\n";
            		if (check == true) break;
					int count = 0;
            		for (int i=0; i<listCu.size(); i++)
            			if ((listCu[i].getID()-10000) != i)
            			{
            				cu.setID(10000+i);
            				listCu.push_back(cu);
            				count++;
            				break;
            			}
					if (count!=0)
					{
        				sort(listCu.begin(), listCu.end(), sortIDcu);
        				remove("Customer.dat");
            			for (int i=0; i<listCu.size(); i++)
    						writeCustomer(listCu[i]);
    				}
    				else
    				{
    					cu.setID(10000+listCu.size());
            			listCu.push_back(cu);
            			writeCustomer(cu);	
					}
            		break;
                }
                case 2:
                {
        			int cu_id;
        			bool check = false;
        			cout << "Enter customer ID: ";
		    		cin >> cu_id;
		    		for (int i=0; i<listCu.size(); i++)
		    			if (listCu[i].getID() == cu_id)
 		   				{
	 		   				cout << "Customer:\n";
  			  				cout << left << setw(18) << "ID" << setw(20) << "Name" 
								 << setw(20) << "Address" << setw(20) << "Phone number" << endl;
                		    cout << listCu[i];
                		    cout << endl;
               			    check = true;
							listCu.erase(listCu.begin() + i);
							break;		
						};
					if (check == false) 
					{
						cout << "This customer does not exist\n";
						cout << "\n------------------------------------------------------------------\n";
					}
					else
					{
						remove("Customer.dat");
            			for (int i=0; i<listCu.size(); i++)
    						writeCustomer(listCu[i]);
					}
    				break;
                }
                case 3:
                {
                	if (listCu.size() > 0)
            		{
                		cout << left << setw(18) << "ID" << setw(20) << "Name" 
							 << setw(20) << "Address" << setw(20) << "Phone number" << endl;
                		for (int i=0; i<listCu.size(); i++)
                    		cout << listCu[i];
                		cout << endl;
            		} else cout << "\nEmpty list" << endl;
            		break;
				}
                default:
                    break;
            	}
            }
            break;
        }
        case 3:
        {
            int n;
            while (true)
            {
                cout << "****************SHOPPING LIST****************\n";
                cout << "**  1. Add shopping list.                  **\n";
                cout << "**  2. Print shopping list.                **\n";
                cout << "**  3. Delete shopping list.               **\n";
                cout << "**  4. Sort.                               **\n";
                cout << "**  5. Sale receipt.                       **\n";
                cout << "**  0. Back.                               **\n";
                cout << "*********************************************\n";
                cout << "Your choice: ";
                cin >> n;
                cin.ignore();
                cout << "\n------------------------------------------------------------------------------------\n";
                if (n == 0) break;
                switch (n)
                {
                case 1:
                {
                	remove("List.dat");
                    if (listC.size() > 0)
		            {
		                cout << left << setw(18) << "ID" << setw(20) << "Name" 
		                     << setw(20) << "Group" << setw(10) << "Price" << endl;
		                for (int i=0; i<listC.size(); i++)
		                    cout << listC[i];
		            }
		            int c_id;
		            for (int i=0; i<listCu.size(); i++)
		            {
		            	int count1=0, count2=0;
		                Customer cu = listCu[i];
		                int number;
		                cout << "\nEnter information to buy for " << cu.getName() << ": \n";
		                cout << "Enter the number of items: ";
		                cin >> number;
		                    while (true)
		                    {
		                    	if (count2==number) break;
		                        cout << "Enter ID (0 = exit): ";
		                        cin >> c_id;
		                        if (c_id == 0) 
		                        {
		                            cout << endl;
		                            break;
		                        }
								for (int k=0; k<listC.size(); k++)
		                        	if (c_id == listC[k].getID())
		                        		count1++;
								if (count1 == 0)
								{
									cout << "Don't have this ID.\n";
								}
		                        else {
		                            Commodity c;
		                            if(!bought(list,c_id,cu.getID()))
		                            {
		                                for (int j=0; j<listC.size(); j++)
		                                {
		                                    if (listC[j].getID() == c_id)
		                                    {
		                                        c = listC[j];
		                                        break;
		                                    }
		                                }
		                                cout << "Enter quantity: ";
		                                int n;
		                                cin >> n;
		                                count2++;
		                                List l(cu, c, n);
		                                list.push_back(l);
		                            }
		                            else cout << "Purchased item\n";
		                        }
		                    } 
		            }
		            writeList(list);
		            cout << endl;
		            printList(list);
		            cout << "\n------------------------------------------------------------------------------------\n";
		            break;
                }
                case 2:
                {
        			if (list.empty()) 
						cout << "No shopping list yet.\n";
        			else
        				printList(list);
        			cout << "\n------------------------------------------------------------------------------------\n";
    				break;
                }
                case 3:
                {
                	if (list.empty())
					{
						cout << "No shopping list yet.\n";	
					} 
					else {
						list.clear();
						remove("List.dat");
						cout << "Shopping list removed.\n";
					};
					cout << "\n------------------------------------------------------------------------------------\n";
            		break;
				}
				case 4:
				{
		        	int k;
		            while (true)
		            {
		                cout << "********************SORT*********************\n";
		                cout << "**  1. Customer name.                      **\n";
		                cout << "**  2. Commodity name.                     **\n";
		                cout << "**  0. Back.                               **\n";
		                cout << "*********************************************\n";
		                cout << "Choice: ";
		                cin >> k;
		                cin.ignore();
		                cout << "\n------------------------------------------------------------------------------------\n";
		                if (k == 0) break;
		                switch (k)
		                {
		                case 1:
		                {
		                    sort(list.begin(), list.end(), customerName);
		                    printList(list);
		                    cout << "\n------------------------------------------------------------------------------------\n";
		                    break;
		                }
		                case 2:
		                {
		                    sort(list.begin(), list.end(), commodityName);
		                    printList(list);
		                    cout << "\n------------------------------------------------------------------------------------\n";
		                    break;
		                }
		                default:
		                    break;
		                }
		            }
		            break;					
				}
				case 5:
		        {
		            for (int i=0; i<listCu.size(); i++)
		            {
		                cout << left << setw(18) << "Customer ID" << setw(20) << "Customer Name" << setw(20)
		                     << "Item Name" << setw(10) << "Qty" << setw(10) << "Price" << endl;
		                int total_qty = 0;
		                int total_price = 0;
		                Customer cu = listCu[i];
		                cout << left << setw(18) << cu.getID() << setw(20) << cu.getName() << endl;
		                for (int j=0; j<list.size(); j++)
		                {
		                    List l = list[j];
		                    if (cu.getID() == l.getCustomer().getID())
		                    {
		                        cout << left << setw(38) << " " << setw(20) << l.getCommodity().getName() 
		                             << setw(10) << l.getQuantity() << setw(10) << l.getCommodity().getPrice() << endl;
		                        total_qty += l.getQuantity();
		                        total_price += l.getQuantity() * l.getCommodity().getPrice();
		                    }
		                }
		                cout << left << setw(58) << " " << setw(10) << "Total" << setw(10) << "Total" << endl;
		                cout << left << setw(58) << " " << setw(10) << total_qty << setw(10) << total_price << endl;
		                cout << "-------------------------------------------------------------------------------" << endl;
		            }
		            break;
		        }
                default:
                    break;
            	}
            }
            break;
        }
        default:
            break;
        }
    } while (choice);
    return 0;
}