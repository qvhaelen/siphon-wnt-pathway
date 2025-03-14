//**************************************************************************************************
// déclaration des bibliothèques utilisées
/* contient les éléments cin et cout entre autre*/
#include <iostream>
/* fstream: stream  class to both read and write  from/to  files */
#include <fstream>
/* utilisation des chaines de caractères*/
#include <string>
/* utilisation des vecteurs*/
#include <vector>
/* utilisation des manipulateurs*/
#include<iomanip>
/*conversion nombre string et tring nombre (stringstream,  etc)*/
#include<sstream>
/*pour avoir les fonctions math de base: sqrt, pow(),  fabs,...*/
#include<cmath>
/* diff, et plein d'autres trucs, genre inner_product,...*/
#include<numeric>
/* ensemble d'algorithmes, STL algorithms, pour la manipulation des  STL containers*/
#include<algorithm>
#include<assert.h>
#include <string>

#include "test_siphon.h"
#include "set_up_stochio_matrix_p.h"
#include "set_up_stochio_matrix_r.h"
using namespace std;

int main()
{
clock_t start, end=0; // pour avoir une estimation du  temps écoulé pour la durée complète du  processus
assert( (start = clock()) != -1); // initialisation du  compteur
cout <<""<< endl; 
cout <<"                            ****************************************************                "<< endl;
cout <<"                            *                                                  *           "<< endl;
cout <<"                            *                  CODE SIPHON                     *        "<< endl;
cout <<"                            *                                                  *     "<< endl;
cout <<"                            ****************************************************           "<< endl;
cout <<"                  "<< endl;
cout <<"========================================================================================================================="<< endl;
cout <<"                                               SUMMARY:             "<< endl;
cout <<"========================================================================================================================="<< endl;
cout << "                   COMPUTATION OF THE SIPHON PRESENT IN THE MAL-CRN " << endl;
cout <<"                 CASE DONE FOR THE WNT PATHWAY VERSION 3, 13 DECEMBER 2022             "<< endl;
cout <<"========================================================================================================================="<< endl;
cout << ""<< endl; 
// allocation of variables, vectors and matrices
int nbre_reactions = 42; // number of elementary irrevesible reactions in the crn
int  number_vertices = 31; // number of species in the system in the mal-crn (dynamical variables in the odes)
bool bool_siphon = true; //  boolean set to true if a given set of species is a siphon
int siphon_size;
int number_siphon = 0;
// assuming that stoichiometric matrix is written as N = r-p:
//matrix with the beta factor or product factor of the stoichiometric matrix 
int** stochio_matrix_p=NULL;
   stochio_matrix_p = new int*[number_vertices+1];
   for (int i=1;i<= number_vertices; ++i){stochio_matrix_p[i] = new int[nbre_reactions+1];}
   
   for (int i=1;i<= number_vertices;++i){
    for (int j=1;j<= nbre_reactions;++j){
     stochio_matrix_p[i][j] =0;
    }
   }
//matrix with the alpha factor or reactant factor of the stoichiometric matrix 
int** stochio_matrix_r=NULL;
   stochio_matrix_r = new int*[number_vertices+1];
   for (int i=1;i<= number_vertices; ++i){stochio_matrix_r[i] = new int[nbre_reactions+1];}
   
   for (int i=1;i<= number_vertices;++i){
    for (int j=1;j<= nbre_reactions;++j){
     stochio_matrix_r[i][j] =0;
    }
   }
// here we complete the vector with i=1,15 species to  be added ina siphon 
int*    permutation_added;
   permutation_added= new int[number_vertices+1];
   for (int i=1; i<=number_vertices;++i){permutation_added[i] = 0;}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// loading the stoichiometric mmatrices
 set_up_stochio_matrix_r(stochio_matrix_r);
 set_up_stochio_matrix_p(stochio_matrix_p);
string  filename = "RESULTS-LISTE-COMPLETE-SIPHONS.txt";
 ofstream output_file(filename.c_str());
if (output_file.is_open()){
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// siphon siwe 1
 for (int ct1=1; ct1<= number_vertices; ++ct1)
 {
	siphon_size = ct1;   
     cout << "looking for siphon of size  "<< ct1  << endl;
	std::string bitmask(ct1, 1); // K leading 1's
    bitmask.resize(number_vertices, 0); // N-K trailing 0's
     //cout << "FUCK you 2"  << endl;
    // print integers and permute bitmask
    do {
        for (int i = 0; i < number_vertices; ++i) // [0..N-1] integers
        { 
            if (bitmask[i]) {/*std::cout << " " << i+1;*/permutation_added[i+1] = 1;}
        }
		// cout << "FUCK you 3"  << endl;
		bool_siphon = true;  
        test_siphon(permutation_added,stochio_matrix_p,stochio_matrix_r,bool_siphon,siphon_size,nbre_reactions, number_vertices );
	    //cout << "FUCK you 3b"  << endl;
		if (bool_siphon)
	    {
	    number_siphon++;
	    cout << "A siphon of size "<< siphon_size <<" has been found"  << endl;
	    cout << "Total number of siphons so  far = "<<  number_siphon << endl;
	     for (int h1=1;h1<=number_vertices; ++h1 )
	     {
	     if (permutation_added[h1] == 1){output_file<< 1 <<",";}
	     if (permutation_added[h1] == 0){output_file<< 0 <<",";} 
	     } 
	    output_file<<""<<endl;
	    }
		for (int i=1; i<=number_vertices;++i){permutation_added[i] = 0;}
		//cout << "FUCK you 4"  << endl;
		// std::cout << std::endl;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
	
	
	
   
	

} 
	

output_file.close();
}else{cout << "file can not be opened"  << endl;}											 		  	 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
end = clock(); // arrêt du  compteur
double cpu_duration = (end-start)/CLOCKS_PER_SEC;
cout << ""<< endl;
cout <<"==================================================================================================================="<< endl;
cout <<" PROGRAM HAS COMPLETED THE TASK, PROGRAM IS BEING CLOSED, COMPLETE CPU TIME FOR COMPLETION IS: "<< cpu_duration<<" SECONDS"<< endl;
cout <<"==================================================================================================================="<< endl;
cout << ""<< endl;
//deallocation of all variables, vectors and matrices
for (int i=1;i<= number_vertices;++i){delete[] stochio_matrix_p[i];}
delete [] stochio_matrix_p;
for (int i=1;i<= number_vertices;++i){delete[] stochio_matrix_r[i];}
delete [] stochio_matrix_r;
 delete [] permutation_added;

return 0;
} // end main function