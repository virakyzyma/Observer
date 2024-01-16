#include <iostream>
#include <vector>
using namespace std;


class Observer abstract
{
public:
	virtual void Update() abstract;
};

class Subject abstract
{
	vector<Observer*> observers;
public:
	void Attach(Observer* observer) 
	{
		observers.push_back(observer);
	}
	void Detach(Observer* observer) 
	{
		auto iter = find(observers.begin(), observers.end(), observer);
		if (iter != observers.end())
			observers.erase(iter);
	}
	void Notify() 
	{
		for (Observer* obs : observers)
		{
			obs->Update();
		}
	}
};


class Shop : public Subject 
{
private:
	bool is_available_phone;
public:
	Shop(bool a) 
	{
		is_available_phone = a;
	}
	void SetAvailable(bool a) 
	{
		is_available_phone = a;
	}
	bool GetAvailable() 
	{
		return is_available_phone;
	}
};

class Client : public Observer
{
	Shop* shop;
	string name;

public:
	Client(Shop* shop, string name)
	{
		this->shop = shop;
		this->name = name;
	};
	void Update() override
	{
		cout << name << " Phone available-> " << shop->GetAvailable() << "\n";
	}
	Shop* GetShop() 
	{
		return this->shop;
	}
	void SetShop(Shop* shop)
	{
		this->shop = shop;
	}
};


int main()
{
	Shop* shop = new Shop(false);
	Observer* observer1 = new Client(shop, "Observer 1");
	Observer* observer2 = new Client(shop, "Observer 2");
	Observer* observer3 = new Client(shop, "Observer 3");

	shop->Attach(observer1);
	shop->Attach(observer2);
	shop->Attach(observer3);

	shop->Notify();
	shop->SetAvailable(true);

	shop->Notify();
	shop->Detach(observer2);

	shop->Detach(observer1);
	shop->Notify();

	delete shop;
	delete observer1;
	delete observer2;
	delete observer3;
	return 0;
}