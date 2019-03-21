/* ===============================================================
  E.Hardy - Université de Marne-la-Vallée  
  ============================================================= */
#include <g3x.h>
#include <g3x_basix.h>



typedef struct _obj_{
    int id; /*identifiant*/
    G3Xpoint *vertex;
    G3Xvector *normal;
    bool (*pt_in)(struct _obj_ *,G3Xpoint);
    bool (*build)(struct _obj_ *);
    int n,p,size; /*taille , resolution*/
    
    }object;
    
object Sphere, cube, torus, cone;

    
bool BuildSphere_Reg(object *obj){
    
    obj->vertex = (G3Xpoint*)calloc(obj->size,sizeof(G3Xpoint));
    obj->normal=(G3Xvector*)calloc(obj->size,sizeof(G3Xvector));
    G3Xpoint * v = obj->vertex;
    double a = 2*PI/obj->n;
    double b = 2*PI/obj->n;
    int i,j;
    double cosa,sina;
    for (i=0; i<obj->n; i++)
	{
		cosa = cos(i*a);
        sina = sin(i*a);
		for (j=0; j<obj->p; j++)
		{
			/* coordoonéeobj objphériqueobj (Eq. paramétrique) */
			obj->vertex[i*obj->p+j][0]= cosa*sin(j*b);
			obj->vertex[i*obj->p+j][1]= sina*sin(j*b);
			obj->vertex[i*obj->p+j][2]= cos(j*b);			
		}
	}
	/* les normales : même chose que les sommets */
	memcpy(obj->normal,obj->vertex,obj->n*obj->p*sizeof(G3Xcoord));
    return true;
    
    
    }
 
 
bool BuildTorus_Reg(object *obj){
    
    obj->vertex = (G3Xpoint*)calloc(obj->size,sizeof(G3Xpoint));
    obj->normal=(G3Xvector*)calloc(obj->size,sizeof(G3Xvector));
    
    int i,j;
    double objN = (double)obj->n;
    double objP = (double)obj->p;
    
    
    for(i=0;i<obj->p;i++){
        double idouble = (double) i;
        double cosa = cos(2.*idouble*PI/objP);
        double sina = sin(2.*idouble*PI/objP);
        
        for(j=0;j<obj->n;j++){
            double jdouble = (double)j;
            obj->vertex[i*(obj->n)+j][0] = (3.+cos(2.*jdouble*PI/objN))*cosa;
            obj->vertex[i*(obj->n)+j][1] = (3.+cos(2.*jdouble*PI/objN))*sina;
            obj->vertex[i*(obj->n)+j][2] = sin(2.*jdouble*PI/objN);
            
            obj->normal[i*(obj->n)+j][0] = cos(2.*jdouble*PI/objN)*cosa;
            obj->normal[i*(obj->n)+j][1] = cos(2.*jdouble*PI/objN)*sina;
            obj->normal[i*(obj->n)+j][2] = sin(2.*jdouble*PI/objN);
            
            
            }
        
        }
    
    
    return true;
    } 
 
  bool BuildCone_Reg(object *obj){
    
    obj->vertex = (G3Xpoint*)calloc(obj->size,sizeof(G3Xpoint));
    obj->normal=(G3Xvector*)calloc(2+obj->n,sizeof(G3Xvector));
    
    int i,j;
    double objN = (double)obj->n;
    double objP = (double)obj->p;
    
    
    obj->vertex[0][X] = 0.;
	obj->vertex[0][Y] = 0.;
	obj->vertex[0][Z] = 1.;

	obj->vertex[1][X] = 0.;
	obj->vertex[1][Y] = 0.;
	obj->vertex[1][Z] = 0.;
    
    
    
    
    obj->normal[0][X] = 0.;
	obj->normal[0][Y] = 0.;
	obj->normal[0][Z] = 1.;

	obj->normal[1][X] = 0.;
	obj->normal[1][Y] = 0.;
	obj->normal[1][Z] = -1.;
    
    
    
    
    
    for(i=2;i<obj->p;i++){
        double idouble = (double) i;
        for(j=0;j<obj->n;j++){
            double jdouble = (double)j;
            obj->vertex[i*(obj->n)+j][0] = cos(PI*2*jdouble/objN)*((idouble+1.)/objP)
            obj->vertex[i*(obj->n)+j][1] = sin(PI*2*jdouble/objN)*((idouble+1.)/objP)
            obj->vertex[i*(obj->n)+j][2] = -1;
            
            
            }
        
        }
    
    
    return true;
    }   
  
bool BuildCube_Reg(object *obj){
    
    obj->vertex = (G3Xpoint*)calloc(obj->size,sizeof(G3Xpoint));
    obj->normal=(G3Xvector*)calloc(6,sizeof(G3Xvector));
    
    
    obj->normal[0][X] = 0.;
	obj->normal[0][Y] = 0.;
	obj->normal[0][Z] = 1.;

	obj->normal[1][X] = 0.;
	obj->normal[1][Y] = 0.;
	obj->normal[1][Z] = -1.;

	obj->normal[2][X] = 0.;
	obj->normal[2][Y] = 1.;
	obj->normal[2][Z] = 0.;

	obj->normal[3][X] = 0.;
	obj->normal[3][Y] = -1.;
	obj->normal[3][Z] = 0.;

	obj->normal[4][X] = 1.;
	obj->normal[4][Y] = 0.;
	obj->normal[4][Z] = 0.;

	obj->normal[5][X] = -1.;
	obj->normal[5][Y] = 0.;
	obj->normal[5][Z] = 0.;
    
    
    
	int i,j;
    double objN = (double)obj->n;
    double objP = (double)obj->p;
    
    for(i=0;i<obj->n;i++){
        double idouble = (double) i;
        for(j=0;j<obj->p;j++){
            double jdouble = (double)j;
            obj->vertex[i*(obj->p)+j][0] = 2*idouble/objN-1;
            obj->vertex[i*(obj->p)+j][1] = 2*jdouble/objP -1;
            obj->vertex[i*(obj->p)+j][2] = 1.;
            
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*1+j][0] = 2*idouble/objN-1;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*1+j][1] = 2*jdouble/objP -1;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*1+j][2] = -1.;
            
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*2+j][0] = 2*idouble/objN-1;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*2+j][1] = 1.;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*2+j][2] = 2*jdouble/objP -1;
            
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*3+j][0] = 2*idouble/objN-1;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*3+j][1] = -1.;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*3+j][2] = 2*jdouble/objP -1;
            
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*4+j][0] = 1.;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*4+j][1] = 2*idouble/objN-1;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*4+j][2] = 2*jdouble/objP -1;
            
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*5+j][0] = -1.;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*5+j][1] = 2*idouble/objN-1;
            obj->vertex[i*(obj->p)+(obj->p)*(obj->n)*5+j][2] = 2*jdouble/objP -1;
            
            
            }
        
        }
    
    
	
    return true;
    
    
    }
    
 void Draw_Object(object *s, int c){

	G3Xpoint *v;
	G3Xvector *n;

	/*g3x_Material(G3Xw, 0.25, 0.5, 0.5, 0.5, 1);*/
	glPointSize(1);
	glBegin(GL_POINTS);
	v = s->vertex;
	n = s->normal;

	while(v < s->vertex + s->size){
		glNormal3dv(*n); n += c;
		glVertex3dv(*v); v += c;
	}

	

	glEnd();

}  
    
static void Draw_Sphere(object *obj, int cam)
{
	G3Xpoint *v;
    G3Xvector *n;
	
	glPointSize(1);
	glBegin(GL_POINTS);
	v = obj->vertex;
    n =obj->normal;
    while(v<obj->vertex +obj->size){
        glNormal3dv(*n); n += cam;
		glVertex3dv(*v); v += cam;
        }
		
	glEnd();
}

static void Draw_Cube(object *obj, int cam)
{
	G3Xpoint *v;
    G3Xvector *n;
	
	glPointSize(1);
	glBegin(GL_POINTS);
	v = obj->vertex;
    n =obj->normal;
    int face, i, j;
    
    
    
  
    
    
	for(face = 0; face < 6; face++){
		for(i = 0; i < obj->n; i+=cam){
			for(j = 0; j < obj->p; j+=cam){
				glNormal3dv(n[face]);
				glVertex3dv(v[face*(obj->n)*(obj->p) + j+i*(obj->p)]);
			}
            glNormal3dv(n[face]);
            glVertex3dv(v[face*(obj->n)*(obj->p) + i*(obj->p)+(obj->p-1)]);
		}
        int cote;
        for(cote=0;cote<obj->p;cote+=cam){
            glNormal3dv(n[face]);
            glVertex3dv(v[face*(obj->n)*(obj->p) + (obj->p)*(obj->n-1)+cote]);
        }
        glNormal3dv(n[face]);
        glVertex3dv(v[face*(obj->n)*(obj->p) + (obj->p)*(obj->n-1)+(obj->p-1)]);
        
	}
		
	glEnd();
}



static void Draw_Torus(object *obj, int cam)
{
	G3Xpoint *v;
    G3Xvector *n;
	
	glPointSize(1);
	glBegin(GL_POINTS);
	v = obj->vertex;
    n =obj->normal;
    int  i, j;
    
    
	
		for(i = 0; i < obj->p; i+=cam){
			for(j = 0; j < obj->n; j+=cam){
				 glNormal3dv(n[i*(obj->n)+j]);
            glVertex3dv(v[i*(obj->n) + j]);
			}
           
		}
	
		
	glEnd();
}



static void Draw_Cone(object *obj, int cam)
{
	G3Xpoint *v;
    G3Xvector *n;
	
	glPointSize(1);
	glBegin(GL_POINTS);
	v = obj->vertex;
    n =obj->normal;
    int  i, j;
    
    glVertex3dv(obj->vertex[0]);
    glVertex3dv(obj->vertex[1]);
    
    glNormal3dv(obj->normal[0]);
    glNormal3dv(obj->normal[1]);
	
		for(i = 0; i < obj->p; i+=cam){
			for(j = 0; j < obj->n; j+=cam){
            glVertex3dv(v[i*(obj->n) + j]);
			}
           
		}
	
		
	glEnd();
}


void Init(void)
{
    Sphere.n = 2000;/*4200*/
    Sphere.p = 2000;/*4000*/
    Sphere.size = Sphere.n*Sphere.p;
    BuildSphere_Reg(&Sphere);
    cube.n = 400;
	cube.p = 400;
	cube.size = 6*cube.n*cube.p;
	BuildCube_Reg(&cube);
    torus.n = 1000;
	torus.p = 400;
	torus.size = torus.n*torus.p;
	BuildTorus_Reg(&torus);
     cone.n = 1000;
	cone.p = 400;
	cone.size = cone.n*cone.p;
	BuildCone_Reg(&cone);
}

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void)
{
  g3x_Material(G3Xr,0.25,0.5,0.5,0.5,1.);
  /*Draw_Sphere(&Sphere,1);*/
  /*Draw_Cube(&cube, 4);*/
  /*Draw_Cube(&cube,1);*/
  
  /*Draw_Torus(&torus,1);*/
   Draw_Cone(&cone,1);
  
  
  /*G3Xcamera *c = g3x_GetCamera();
  if(c->dist < 5.1){
		Draw_Cube(&cube, 1);
        
	} else if(c->dist < 11.){
		Draw_Cube(&cube, 4);
	} else if(c->dist < 19.){
		Draw_Cube(&cube, 8);
	} else if(c->dist < 50.){
		Draw_Cube(&cube, 16);
	} else if(c->dist < 100.){
		Draw_Cube(&cube, 32);
	} else {
		Draw_Cube(&cube, 64);
	}*/
}


int main(int argc, char** argv)
{   
  /* initialisation de la fenêtre graphique et paramétrage Gl */
  g3x_InitWindow(*argv,768,512);
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
  g3x_SetPerspective(40.,100.,1.);
  /* position, orientation de la caméra */
  g3x_SetCameraSpheric(0.25*PI,+0.25*PI,6.,(G3Xpoint){0.,0.,0.});

  /* définition des fonctions */
  g3x_SetInitFunction(Init);     /* la fonction d'initialisation */
  g3x_SetDrawFunction(Draw);     /* la fonction de dessin        */
  g3x_SetAnimFunction(NULL);		 /* pas de fonction d'animation  */
  g3x_SetExitFunction(NULL);     /* pas de fonction de sortie    */

 
  /* boucle d'exécution principale */
  return g3x_MainStart();
  /* rien après ça */
}
