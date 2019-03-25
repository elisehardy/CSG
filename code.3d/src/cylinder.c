#include "../include/cylinder.h"


bool BuildCylindre_random(object *obj){
    
    obj->vertex = (G3Xpoint*)calloc(obj->size,sizeof(G3Xpoint));
    obj->normal=(G3Xvector*)calloc(obj->size,sizeof(G3Xvector));
    
    int i,j;
    double objN = (double)obj->n;
    double objP = (double)obj->p;
    
    
   
    
    vertices = obj->vertex;
    normals = obj->normal;
    
    for(i=0;i<obj->size;i++){
        do{
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
           
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
           }while(d!=1); 
            
            (*normals)[0] = 0;
            (*normals)[1]=0;
            (*normals)[2]=1;
            
             (*vertices)[2] = 1
            
            
            }
        }
    


Object *buildRegularCylinder(Object *obj) {
    
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    
    double theta, z;
    int i, j;
    
    for (i = 0; i < obj->p; i++) {
        for (j = 0; j < obj->n; j++) {
            z = sqrt(g3x_Rand_Delta(0, 1));
            theta = g3x_Rand_Delta(0, 2 * PI);
            obj->vertex[i * (obj->n) + j][0] = z * cos(theta);
            obj->vertex[i * (obj->n) + j][1] = z * sin(theta);
            obj->vertex[i * (obj->n) + j][2] = z;
            
            obj->normal[i * (obj->n) + j][0] = cos(theta);
            obj->normal[i * (obj->n) + j][1] = sin(theta);
            obj->normal[i * (obj->n) + j][2] = 1;
        }
    }
    
    return obj;
}
