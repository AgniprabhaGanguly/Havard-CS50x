#include <stdio.h>
#include <cs50.h>

int get_info(void);

int main(void)
{
    int ans = get_info();
    printf("Years: %d", ans);
}

int get_info(void)
{
    // ask start and end size of population

    int st_sz;
    do
    {
        st_sz = get_int("Enter population start size :");
    }
    while (st_sz < 9);

    int ed_sz;
    do
    {
        ed_sz = get_int("Enter pupulation end size :");
    }
    while (ed_sz < st_sz);

    int born; // llamas born in a year
    int pass_away; // llamas pass away in a year
    int year = 0; // no of years passed
    int i = st_sz; // counter that stores value of population of llamas every passing year
    if (st_sz == ed_sz)
    {
        return year;
    }
    do
    {
        born = i / 3;
        pass_away = i / 4;
        i = i + born - pass_away;
        year = year + 1;
    }
    while (i < ed_sz);
    return year;
}

