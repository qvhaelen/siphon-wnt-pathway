/* contient les éléments cin et cout entre autre*/
#include <iostream>
/* fstream: stream  class to both read and write  from/to  files */
#include <fstream>
/* utilisation des chaines de caractères*/
#include <string>
/* utilisation des manipulateurs*/
#include<iomanip>
/*conversion nombre string et tring nombre (stringstream,  etc)*/
#include<sstream>
#include"test_siphon.h"
using namespace std;
void  test_siphon(int* permutation_added, int** stochio_matrix_p, int** stochio_matrix_r,bool& bool_siphon, int& siphon_size,int& nbre_reactions, int& number_vertices)
{
int ct0 =0; 	
int ct1 =0;	
int ct2 =0;
//cout << "test 1"  << endl   ;	
bool*    input_reactions;
   input_reactions= new bool[nbre_reactions+1];
   for (int i=1; i<=nbre_reactions;++i){input_reactions[i] = false;}
bool*    output_reactions;
   output_reactions= new bool[nbre_reactions+1];
   for (int i=1; i<=nbre_reactions;++i){output_reactions[i] = false;}
//cout << "test 2"  << endl   ;	
   
  while (ct1<siphon_size)
  {
	  ct2++; 
	//  cout << "test 2 b"  << endl   ;
	  if (permutation_added[ct2] == 1)
	   {
		 ct1++; 
	//	 cout << "test 2 c"  << endl   ;
		 for (int j=1;j<=nbre_reactions; ++j )
         {
			if (stochio_matrix_p[ct2][j] ==1){input_reactions[j] = true;}
			if (stochio_matrix_r[ct2][j] ==1){output_reactions[j] = true;}
		 } 	
	//	 cout << "test 2 d"  << endl   ;		 
	   }
  }	  
  //cout << "test 3"  << endl   ;	 
  
  while (bool_siphon && ct0<nbre_reactions)
  {
	ct0++;    
	if (input_reactions[ct0])
	{
		if (output_reactions[ct0] == false){bool_siphon=false;}
	}	
	/*if (input_reactions[ct0] == false)
	{
		if (output_reactions[ct0] == true){bool_siphon=false;}
	}	*/
  }	
   
//cout << "test 4"  << endl   ;	   
//cout << bool_siphon  << endl   ;
   
delete [] input_reactions;
delete [] output_reactions;  

return;}





