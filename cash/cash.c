#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // keep asking till positive number
    int ask_cent;
    do
    {
        ask_cent = get_int("Changes owed? ");
    }
    while (ask_cent < 0);
    return ask_cent;
}

int calculate_quarters(int cents)
{
    // divide cent by quarter
    float not_exact_number_of_quarter = cents / 25;
    int rounded_number_of_quarter = not_exact_number_of_quarter;
    if (rounded_number_of_quarter <= not_exact_number_of_quarter)
    {
        return rounded_number_of_quarter;
    }

    else
    {
        return rounded_number_of_quarter - 1;
    }
}

int calculate_dimes(int cents)
{
    // divide cent by dimes
    float not_exact_number_of_dimes = cents / 10;
    int rounded_number_of_dimes = not_exact_number_of_dimes;
    if (rounded_number_of_dimes <= not_exact_number_of_dimes)
    {
        return rounded_number_of_dimes;
    }

    else
    {
        return rounded_number_of_dimes - 1;
    }
}

int calculate_nickels(int cents)
{
    // divide cent by nickels
    float not_exact_number_of_nickels = cents / 5;
    int rounded_number_of_nickels = not_exact_number_of_nickels;
    if (rounded_number_of_nickels <= not_exact_number_of_nickels)
    {
        return rounded_number_of_nickels;
    }

    else
    {
        return rounded_number_of_nickels - 1;
    }
}

int calculate_pennies(int cents)
{
    // divide cent by pennies
    return cents;
}
