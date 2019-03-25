#include "../include/cylinder.h"


Object* buildRandomCylinder(int n, int p){
   
   
   Object *obj = (Object *) malloc(sizeof(Object));
    if (obj == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCylinder ");
        exit(1);
    }
    obj->size = n*p;
    obj->n=n;
    obj->p=p;
    obj->vertex = (G3Xpoint*)calloc(obj->size,sizeof(G3Xpoint));
    obj->normal=(G3Xvector*)calloc(obj->size,sizeof(G3Xvector));
    
   
    
   
    int i;
    double d;
    G3Xpoint *vertices = obj->vertex;
    G3Xvector *normals = obj->normal;
    
    for(i=0;i<obj->size/3;i++){
        /*cercle dessus*/
       do{
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
           
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        }while(d>1); 
            
            (*normals)[0] = 0;
            (*normals)[1]=0;
            (*normals)[2]=1;
            
             (*vertices)[2] = 1;
            vertices++;
            normals++;
            
        
        /*cercle dessous*/
        do{
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
           
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        }while(d>1); 
            
            (*normals)[0] = 0;
            (*normals)[1]=0;
            (*normals)[2]=-1;
            
             (*vertices)[2] = -1;
            vertices++;
            normals++;
            
            /*bandeau*/
             do{
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
           
           
           
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];

        }while(d>1); 
            d=sqrt(d);
            (*vertices)[0] = (*vertices)[0]/d;
            (*vertices)[1] = (*vertices)[1]/d;
           
           
            (*normals)[0] = (*vertices)[0]/d;
            (*normals)[1]=(*vertices)[1]/d;
            (*normals)[2]=0;
            
             (*vertices)[2] = g3x_Rand_Delta(0,+1);
            vertices++;
            normals++;
    }
    
    
        
        return obj;
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
