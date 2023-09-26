/*
* Author:
* Program:
* Date:
* Description: 
*/

#pragma warning(disable: 4996)
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

class Money
{
public:
    Money();
    Money(double amount);
    Money(int theDollars, int theCents);
    Money(int theDollars);
    double getAmount() const;
    int getDollars() const;
    int getCents() const;
    //I/O Friend methods, uses overload << and >> in over loaded operator declarations/definitions below.
    friend void input(Money& amount1);
    friend void output(const Money& amount1);
    //Percentage method, +, -, <, >.
    double getPercentage(const Money& amount1);
    Money getAmountSums(const Money& amount1, const Money& amount2);
    Money getAmountDiff(const Money& amount1, const Money& amount2);
    void compareValues(const Money& amount1, const Money& amount2);
    //Overloaded << and >>
    friend ostream& operator <<(ostream& outputStream, const Money& amount);
    friend istream& operator >>(istream& inputStream, Money& amount);
private:
    int dollars; //A negative amount is represented as negative dollars and negative cents.
    int cents;   // Negative $4.50 is represented as -4 and -50.
    int dollarsPart(double amount) const;
    int centsPart(double amount) const;
    int round(double number) const;
    const double PERCENT_VAL = 10;
};

//Overload Operator Declaration.
bool operator ==(const Money& amount1, const Money& amount2);
bool operator <(const Money& amount1, const Money& amount2);
bool operator >(const Money& amount1, const Money& amount2);

int main()
{
    Money yourAmount, myAmount(10,9);
    cout << "Enter an amount of money: ";
    input(yourAmount);
    cout << "Your amount is: ";
    output(yourAmount);
    cout << endl;
    cout << "My amount is: ";
    output(myAmount);
    cout << endl;

    yourAmount.compareValues(yourAmount, myAmount);

    Money percentDiff = yourAmount.getPercentage(yourAmount);
    output(percentDiff);
    cout << endl;

    Money ourAmount = ourAmount.getAmountSums(yourAmount, myAmount);
    output(yourAmount);
    cout << " + ";
    output(myAmount);
    cout << " equals ";
    output(ourAmount);
    cout << endl;

    Money diffAmount = diffAmount.getAmountDiff(yourAmount, myAmount);
    output(yourAmount);
    cout << " - ";
    output(myAmount);
    cout << " equals ";
    output(diffAmount);
    cout << endl;

    return 0;
}

//Constructors.
Money::Money() : dollars(0), cents(0) {}

Money::Money(double amount) : dollars(dollarsPart(amount)), cents(centsPart(amount)) {}

Money::Money(int theDollars) : dollars(theDollars), cents(0) {}

Money::Money(int theDollars, int theCents)
{
    if ((theDollars < 0 && theCents > 0) || (theDollars > 0 && theCents < 0))
    {
        cout << "Inconsistent money data.\n";
        exit(1);
    }
    dollars = theDollars;
    cents = theCents;
}

//Overloaded << and >> operators, uses friend keyword in declaration above.
ostream& operator <<(ostream& outputStream, const Money& amount)
{
    int absDollars = abs(amount.dollars);
    int absCents = abs(amount.cents);
    if (amount.dollars < 0 || amount.cents < 0)
    {
        cout << "$-";
    }
    else
    {
        cout << '$';
    }
    cout << absDollars;

    if (absCents >= 10)
    {
        cout << '.' << absCents;
    }
    else
    {
        cout << '.' << '0' << absCents;
    }
    return outputStream;
}
istream& operator >>(istream& inputStream, Money& amount)
{
    char dollarSign;
    inputStream >> dollarSign;
    if (dollarSign != '$')
    {
        cout << "No dollar sign in Money input.\n";
        exit(1);
    }

    double amountAsDouble;
    inputStream >> amountAsDouble;
    amount.dollars = amount.dollarsPart(amountAsDouble);
    amount.cents = amount.centsPart(amountAsDouble);

    return inputStream;
}

//Overloaded ==, < and > operators, used in class methods.
bool operator ==(const Money& amount1, const Money& amount2)
{
    return ((amount1.getDollars() == amount2.getDollars()) && (amount1.getCents() == amount2.getCents()));
}
bool operator <(const Money& amount1, const Money& amount2)
{
    return (amount1.getDollars() < amount2.getDollars());
}
bool operator >(const Money& amount1, const Money& amount2)
{
    return (amount1.getDollars() > amount2.getDollars());
}
//End overloaded operators.

//Get Methods.
/*
* Retrieves amount.
* @param none.
* @return (dollars + cents * 0.01).
*/
double Money::getAmount() const
{
    return (dollars + cents * 0.01);
}
/*
* Retrieves dollars.
* @param none
* @return dollars.
*/
int Money::getDollars() const
{
    return dollars;
}
/*
* Rerieves cents.
* @param none.
* @return cents.
*/
int Money::getCents() const
{
    return cents;
}

//Percentage method, +, -, <, >.
/*
* Returns percentage from amount.
* @param Money& amount1.
* @return double percentage.
*/
double Money::getPercentage(const Money& amount1)
{
    cout << PERCENT_VAL << "% of your money is: ";
    double percentage = amount1.getAmount() * (PERCENT_VAL / 100);
    return percentage;
}
/*
* Returns sums of amounts of Money Objects.
* @param Money& amount1, Money& amount2.
* @return Money(finalDollars, finalCents).
*/
Money Money::getAmountSums(const Money& amount1, const Money& amount2)
{
    int allCents1 = amount1.getCents() + amount1.getDollars() * 100;
    int allCents2 = amount2.getCents() + amount2.getDollars() * 100;
    int sumAllCents = allCents1 + allCents2;
    int absAllCents = abs(sumAllCents);
    int finalDollars = absAllCents / 100;
    int finalCents = absAllCents % 100;

    if (sumAllCents < 0)
    {
        finalDollars = -finalDollars;
        finalCents = -finalCents;
    }
    return Money(finalDollars, finalCents);
}
/*
* Returns differences of amounts of Money Objects
* @param Money& amount1, Money& amount2.
* @return Money(finalDollars, finalCents).
*/
Money Money::getAmountDiff(const Money& amount1, const Money& amount2)
{
    int allCents1 = amount1.getCents() + amount1.getDollars() * 100;
    int allCents2 = amount2.getCents() + amount2.getDollars() * 100;
    int diffAllCents = allCents1 - allCents2;
    int absAllCents = abs(diffAllCents);
    int finalDollars = absAllCents / 100;
    int finalCents = absAllCents % 100;

    if (diffAllCents < 0)
    {
        finalDollars = -finalDollars;
        finalCents = -finalCents;
    }
    return Money(finalDollars, finalCents);
}
//Uses overload operators ==, < and >.
/*
* Method to compare amounts between Money Class Objects, uses overloaded operators ==, < and >.
* @params Money& amount1, Money& amount2.
* @return none.
*/
void Money::compareValues(const Money& amount1, const Money& amount2)
{
    if (amount1 == amount2)
    {
        cout << "We have the same amounts.\n";
    }
    else
    {
        cout << "One of us is richer.\n";
        if (amount1 < amount2)
        {
            cout << "I have more money than you.";
            cout << endl;
        }
        else if (amount1 > amount2)
        {
            cout << "You have more money than me.";
            cout << endl;
        }
    }
}

//Output and input friend methods. Uses overload << and >>.
/*
* Method to output dollar amounts of Money Class Object. Uses overload << operator.
* @Param const Money& amount1
* @return cout amount1
*/
void output(const Money& amount1)
{
    cout << amount1;
}
/*
* Method to input amount from user for dollar amount of Money Class Object. Uses overload >> operator.
* @param Money& amount
* @return cin amount
*/
void input(Money& amount)
{
    cin >> amount;
}

//Methods to retrieve dollars and cents.
/*
* Retrieves dollar amount as int.
* @param double amount
* @return <int>(amount)
*/
int Money::dollarsPart(double amount) const 
{
    return static_cast<int>(amount);
}
/*
* Retrieves cent amount as int.
* @param double amount
* @return int intCents
*/
int Money::centsPart(double amount) const
{
    double doubleCents = amount * 100;
    int intCents = (round(fabs(doubleCents))) % 100;
    if (amount < 0)
    {
        intCents = -intCents;
    }
    return intCents;
}
/*
* Returns cent value rounded.
* @param double number
* @return <int>(number)
*/
int Money::round(double number) const
{
    return static_cast<int>(floor(number + 0.5));
}
