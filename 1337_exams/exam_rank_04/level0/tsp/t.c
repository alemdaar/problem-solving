#include <stdio.h>
#include <unistd.h>
#include <unistd.h>



int ac = 15;
void f ()
{
    printf ("ac : %d\n", ac);
}
int main ()
{
    ac = 5;
    f ();
    printf ("ac : %d\n", ac);
}