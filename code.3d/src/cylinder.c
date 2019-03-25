#include "../include/cylinder.h"

bool BuildCylindre_random(object *obj){
    
    obj->vertex = (G3Xpoint*)calloc(obj->size,sizeof(G3Xpoint));
    obj->normal=(G3Xvector*)calloc(obj->size,sizeof(G3Xvector));
    
    int i,j;
    double objN = (double)obj->n;
    double objP = (double)obj->p;
    
    
   double theta,z;
    
    
    
    
    
    for(i=0;i<obj->p;i++){
        double idouble = (double) i;
        for(j=0;j<obj->n;j++){
            double jdouble = (double)j;
             z= sqrt(g3x_Rand_Delta(0,1));
            theta = g3x_Rand_Delta(0,2*PI);
            obj->vertex[i*(obj->n)+j][0] = z*cos(theta);
            obj->vertex[i*(obj->n)+j][1] = z*sin(theta);
            obj->vertex[i*(obj->n)+j][2] =z;
            
            
            obj->normal[i*(obj->n)+j][0] = cos(theta);
            obj->normal[i*(obj->n)+j][1] = sin(theta);
            obj->normal[i*(obj->n)+j][2] = 1;
            
            }
        
        }
    
    
    return true;
    } 
