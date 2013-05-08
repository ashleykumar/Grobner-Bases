// Ashley Kumar
// 2013

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string> 
#include <stdlib.h>
#include <stdio.h>

#include "polynomial.h"
#include "parser.h"

using namespace std;

int main(int argc, char *argv[]){
    int num_polys = 0;
    int num_vars = 0;  
    int i = 0;
    Polynomial **polys;  
    string buf = ""; 

    cout << "Hello! This program will compute the Grobner Basis ";
    cout << "for a set of polynomials.\n";
   
    // for ease of later parsing, get the total number of polynomials
    while (true){
        cout << "Please enter the number of polynomials ";
        getline(cin, buf); 
        stringstream str(buf); 
   
        if (str >> num_polys){
            break; 
        }
        cout << "Invalid number, try again.\n"; 
    }

    // for ease of later parsing, get the total number of variables in the set
    while (true){
        cout << "Please enter the number of variables ";
        getline(cin, buf); 
        stringstream str(buf); 
   
        if (str >> num_vars){
            break; 
        }
        cout << "Invalid number, try again.\n"; 
    }

    polys = (Polynomial **) malloc(sizeof(Polynomial *) * num_polys);
    for (int j = 0; j < num_polys; j++) {
        polys[j] = (Polynomial *) malloc(sizeof(Polynomial));
        polys[j]->vars = (char *) malloc(sizeof(char) * num_vars); 
    }

    // get the exact variables used in the polynomials 
    while (true){
        cout << "Please enter the variables in the polynomials, ";
        cout << "separated by commas. They should be in decreasing ";
        cout << "order as will be used for the monomial orderings. Ex: x,y,z\n";
        getline(cin, buf);
        if (parse_vars(buf, num_polys, num_vars, polys) == 0){
            break;
        }
    
        // there was a problem parsing the vars
        cout << "Invalid vars, try again.\n";
    }

    cout << "Please enter " << num_polys << " polynomials.\n";

    while (i < num_polys){
        cout << "polynomial " << (i+1) << " ";  
        getline(cin, buf); 
        if (parse_polynomial(buf, polys[i]) == 0){
            i++;
        }
        else{
            cout << "Error parsing polynomial. Please re-enter.\n";   
        }
    }

    // set ordering 
    for (int j = 0; j < num_polys; j++) {
        polys[j]->ordering =2;
        sort_polynomial(polys[j]); 
    }

    printf("computing...\n"); 
    bool red;
    int basis_size = num_polys; 
    int reduced_size; 
    Polynomial **basis, **reduced;  
    Polynomial *quot, *rem, *s;
    /*divide_polys(polys[0], polys[1], &quot, &rem); 
    printf("quot is \n");
    to_string(quot); 
    printf("rem is\n"); 
    to_string(rem);
    free(quot);
    free(rem); */
    /*s = s_poly(polys[0], polys[1]); 
    printf("s poly is\n");
    to_string(s);
    free(s);*/
    //red = can_reduce(s, polys,2);
    //if (red) printf("yes we can reduce!!!\n");
    //else printf("FUCK NO SON\n"); 
    basis = grobner_basis(polys, 2, &basis_size); 
    reduced = reduce_basis(basis, basis_size, &reduced_size);
    printf("lets print the basis\n");  
    for (int j = 0; j < num_polys; j++){
        free_polynomial(polys[j]);
    }
    free(polys);
    for (int j = 0; j < basis_size; j++){
        to_string(basis[j]); 
        free_polynomial(basis[j]);
    }
    free(basis);
    printf("REDUCED BASIS\n"); 
    for (int j = 0; j < reduced_size; j++){
        to_string(reduced[j]);
        free_polynomial(reduced[j]);
    }
    free(reduced); 
    return 0;   
}


