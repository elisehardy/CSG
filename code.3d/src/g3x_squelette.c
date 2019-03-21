/* ===============================================================
  E.Incerti - Université de Marne-la-Vallée - incerti@univ-mlv.fr 
  ============================================================= */
/*#include <g3x.h>

objet S;


typedef struct _obj_{
    int id;
    G3Xpoint *Vertex;
    G3Xvecteur *Normal;
    bool (*pt_in)(struct _obj_ *,G3Xpoint);
    bool (*build)(struct _obj_ *);
    int n,p,size;
    
    }
    
bool BuildSphere_Reg(objet *S){
    
    S->vertex = (G3Xpoint*)calloc(S->size,sizeof(G3xpoint));
    S->normal=(G3Xvecteur*)calloc(S->size,sizeof(G3xvecteur));
    G3Xpoint * v = S->vertex;
    double a = 2*PI/S->N;
    double b = 2*PI/S>P;
    int i,j;
    double cosia,sina;
    for (i=0; i<S->N; i++)
	{
		cosa = cos(i*a);
        sina = sin(i*a);
		for (j=0; j<S->P; j++)
		{*/
			/* coordoonées sphériques (Eq. paramétrique) */
			/*vertex[i*S->P+j][0]= cosa*sin(j*b);
			vertex[i*S->P+j][1]= sina*sin(j*b);
			vertex[i*S->P+j][2]= cos(j*b);			
		}
	}*/
	/* les normales : même chose que les sommets */
	/*memcpy(normal,vertex,NBMMAX*NBPMAX*sizeof(G3Xcoord));
    
    
    
    }
    
    
    static void Draw_Objet(objet *S)
{
	G3Xpoint *v;
    G3Xvecteur *n;
	
	glPointSize(1);
	glBegin(GL_POINTS);
	v = S->vertex;
    n =S->normal;
    while(v<S->vertex +S->size){
        gl
        }
		
	glEnd();
}

void Init(void)
{
    S->N = 100;
    S->P=100;
    S->size = S->N*S->P;
    BuildSphere_Reg(&S);
}
*/
/*= FONCTION DE DESSIN PRINCIPALE =*/
/*static void Draw(void)
{
  g3x_Material(G3Xr,0.25,0.5,0.5,0.5,1.);
  Draw_Objet(&S);
}


int main(int argc, char** argv)
{  */ 
  /* initialisation de la fenêtre graphique et paramétrage Gl */
  /*g3x_InitWindow(*argv,768,512);*/
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
 // g3x_SetPerspective(40.,100.,1.);
  /* position, orientation de la caméra */
 // g3x_SetCameraSpheric(0.25*PI,+0.25*PI,6.,(G3Xpoint){0.,0.,0.});

  /* définition des fonctions */
 // g3x_SetInitFunction(Init);     /* la fonction d'initialisation */
 // g3x_SetDrawFunction(Draw);     /* la fonction de dessin        */
 // g3x_SetAnimFunction(NULL);		 /* pas de fonction d'animation  */
 // g3x_SetExitFunction(NULL);     /* pas de fonction de sortie    */

 /* g3x_SetScrollWidth(2);	
  g3x_CreateScrollv_i("p",&p,3,100,1.,"résolution");
  g3x_CreateScrollh_i("n",&n,3,100,1.,"résolution");
	*/
  /* boucle d'exécution principale */
 // return g3x_MainStart();
  /* rien après ça */
//}
