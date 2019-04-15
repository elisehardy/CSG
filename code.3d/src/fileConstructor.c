#include "../include/fileConstructor.h"

void readAndFillTree(FILE *file, Tree *tree){
    char *line = NULL;
    size_t len = 0;
    char * split;
    while((read = getline(&line, &len, file)) != -1){
        split = strtok(line, ':');
        if(split == NULL){
               fprintf(stderr, "wrong file format");
                exit(1);
        }
        printf("%s", split);
        Tree * node;
        //init node 
        switch(split){
            case "obj":
                split = strtok(split,':');
                if(split != NULL){
                    if(strcmp(split, "cube")==0){
                        Object *cube;
                        node->obj = cube;
                    }
                     else if(strcmp(split, "sphere")==0){
                        Object *sphere;
                        node->obj = sphere;
                    }
                     else if(strcmp(split, "cylinder")==0){
                        Object *cylinder;
                        node->obj = cylinder;
                    }
                     else if(strcmp(split, "torus")==0){
                        Object *torus;
                        node->obj = torus;
                    }
                     else if(strcmp(split, "cone")==0){
                        Object *cone;
                        node->obj = cone;
                    }
                    else{
                        fprintf("bad form ");
                        exit(1);
                    }
                }
                break;
            case "col":
                break;
            case "T":
            int tab[3];
            int i=0;
                while((split = strtok(split, ".")) !=  NULL){
                    tab[i]=atoi(split);
                    i++;
                }
                if(node->obj != NULL){
                        node->md = translate(node->obj, tab[0],tab[1],tab[2]);
                }
                
                break;
            case "Rx":
                
            case "Ry":
            case "Rz":
            case "H":
            case "op":
                split = strtok(split,':');
                if(split != NULL){
                    if(strcmp(split, "sous")==0){
                    }
                    else if(strcmp(split, "inter")==0){
                        
                    }
                    else if(strcmp(split, "union")==0){
                        
                    }
                    else if(strcmp(split, "equal")==0){
                        
                    }
                    else{
                        fprintf("operateur doesn't exist");
                    }
            default :
            fprintf("wrong parameter");
        }
        }
        
    }