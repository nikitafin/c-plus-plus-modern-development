int Factorial(int num)
{
    if (num < 0)
    {
        return 1;
    }
    int fact = 1;
    while (num > 0)
    {
        fact *= num;
        --num;
    }
    return fact;
}

//int main(){
//  int res = Factorial(5);
//  return  0;
//}