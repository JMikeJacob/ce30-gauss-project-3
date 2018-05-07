#include "sigfigs.h"

double absv(double num)
{
  return num*((num>0)-(num<0)); 
}

int exp(int num, int power)
{
  int product = 1;
  for(int i = 0; i < power; i++)
  {
     product = num * product;
  }
  return product;
} 

void printDouble(ostream& out, double num, int setS)
{//varies iostream flags to print out a double with specified accuracy
 //ostream& allows the function to either print the double (with cout)
 //or save it in the file (with ofstream) depending on what 
 //output stream is passed as the parameter
  int set = setS - 1;
  if(num == 0.0)
  {
    //special case: number is exactly 0
    out << fixed << setprecision(set) << num;
    return;
  }
  //counts total number of sigfigs based on base expt
  double log_10 = log10(absv(num));
  int digits = trunc(log_10); //gets integer part only
  if(log_10 >= 0 && digits <= 5)
  {
    if(set < digits) //sigfigs leave integers only
    { //e.g. 123456.789 -> 123460 in 5 sigfigs
      int intNum = round(num); //rounds integer (123457)
      int power = exp(10, digits - set); //gets number of zeroes (e.g. 5 sigfigs for 123457: 10)
      int remove = intNum % (power*10); //for rounder (57)
      int rounder = (remove % exp(10, log10(remove)))/exp(10, log10(remove) - 1);//gets digit next to last sigfig digit (7)
      intNum = intNum/power; //divide number by 10^x (12345)
      intNum = intNum * power; //put necessary zeroes (123450)
      if(rounder >= 5)
      { //adds 10^x to number to simulate rounding up (123460)
        intNum = intNum + (power); 
      }
      out << fixed << setprecision(0);
      out << intNum;
      
      return;
    }
    else
    {
      out << fixed << setprecision(set - digits);
    }
  }
  else if(log_10 < 0 && digits >= -3)
  {
    //if num < 1, base exponent is 10^-(number of zeroes from left-1)
    if(log_10 < trunc(log_10))
    {
     //log10({num < 1}) always returns base exponent value less than
     //predicted if not 1.0x10^-n, so a -1 is added to compensate
      digits -= 1;
    }
    out << fixed << setprecision(set - digits); //ex. 0.00500
  }
  else
  {
    //if integer part has more than 6 digits or decimal part has more
    //than 3 decimal zeroes from the left, the numbers are rendered in 
    //scientific notation for easier reading
    out << scientific << setprecision(set);
  }
  out << num;
  return;
}
