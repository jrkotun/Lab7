#include "RombergIntegration.h"
#include "RecursiveIntegration.h"
#include "QueueLinked.h"
#include "Double.h"
using CSC2110::Double;

#include <math.h>
#include <iostream>
using namespace std;

//a is the lower limit and b is the upper limit
double RombergIntegration::accurateRomberg(MultiVarFunction* f, double a, double b, int level)
{
   Double* db;  //use this variable to place and retrieve values on the queue
   
   QueueLinked<Double>* q1 = new QueueLinked<Double>();		//I DID
   QueueLinked<Double>* q2 = new QueueLinked<Double>();


   int counter = 0;
   int n = 1;  //current number of intervals
   while ( counter <= level)  //I did 
   {
      //DO THIS
      //obtain the required number of trapezoid evaluations depending on the number of levels requested
      //put all of the level 0 results on the q1


      double integ = RecursiveIntegration::romberg(f, a, b, n);

	  Double* num = new Double(integ);
	  q1->enqueue(num);


      n = 2*n;  //double the number of intervals
      counter++;
   }

   //q1 now has all of the level 0 integration results

   double factor;  //use this to compute the current Romberg Factor (4^k stuff)
   int power = 1;  //k, used to compute the Romberg Factor

   //if level 0 has been requested, the loop will not execute
   //the total number of executions of the loop is ??

   //DO THIS
   int alias = level;
   int iter;
   while(alias>0)
   {
		iter += alias;
		alias--;
   }
   int iterations = iter;	 //can be precomputed I DID
   while (iterations > 0)
   {
      //DO THIS
      //use the algorithm described in the lab to improve the accuracy of your level 0 results

	for(int i = q1->size()-1; i > 0; i--)
	{	
   	  Double* il = q1->dequeue();
	  Double* im = q1->peek();
	  
	  factor = ((pow(4, power) * im->getValue())- il->getValue())/(pow(4, power)-1);
	  
	  delete il;
	  
	  Double* calc = new Double(factor);


	  q2->enqueue(calc);
	  
	}
	
	QueueLinked<Double>* temp = new QueueLinked<Double>();
	
	int size = q2->size();
	for(int i = 1; i <= size; i++)
	{
		if (q2->size() == 1)
		{
			Double* item = q2->dequeue();
			temp->enqueue(item);
			delete item;
			q1 = temp;
			delete q2;
		}
		else
		{
		Double* item = q2->dequeue();
		temp->enqueue(item);
		delete item;
		}
	}

      iterations--;
	  power++;
   }

   //obtain the final answer
   db = q1->dequeue();
   double result = db->getValue();  
   delete db;

   delete q1;
   delete q2;

   return result;
}
