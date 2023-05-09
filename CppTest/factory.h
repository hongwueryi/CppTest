#pragma once
//简易工厂模式
class CProduct
{
public:
    CProduct() {}
    virtual void show() = 0;
};

class CProductA :public CProduct
{
public:
    void show() { printf("show product A\n"); }
};

class CProductB :public CProduct
{
public:
    void show() { printf("show product B\n"); }
};

class CFactory
{
public:
    CFactory() {};
    virtual CProduct* CreateProduct() = 0;
};

class CFactoryA :public CFactory
{
public:
    CProduct* CreateProduct() 
    {
        CProduct* p = new CProductA();
        return p;
    }
};

class CFactoryB :public CFactory
{
public:
    CProduct* CreateProduct()
    {
        CProduct* p = new CProductB();
        return p;
    }
};

void testFactory()
{
    CFactory* Fa = new CFactoryA();
    CProduct* pA = Fa->CreateProduct();
    pA->show();
    delete pA;

    CFactory* Fb = new CFactoryB();
    CProduct* pB = Fb->CreateProduct();
    pB->show();
    delete pB;
}