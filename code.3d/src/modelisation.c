/* ===============================================================
  E.Incerti - Université de Marne-la-Vallée - incerti@univ-mlv.fr 
  ============================================================= */

#include <stdio.h>
#include <g3x.h>

#define NBMMAX 100 
#define NBPMAX 100

static G3Xpoint  vertex[NBMMAX*NBPMAX];
static G3Xvector normal[NBMMAX*NBPMAX];
static G3Xcolor  colmap[NBMMAX*NBPMAX];
static int    nbm,nbp;
static double r;

static void SphereCanonique(void)
{
	/* les angles de base */
	double theta = 2.*PI/(NBMMAX-1);
	double phi   =    PI/(NBPMAX-1);
	int i,j;	
	/* les sommets */		
	for (i=0; i<NBPMAX; i++)
	{
		double cosiphi = cos(i*phi);
		double siniphi = sin(i*phi);
		for (j=0; j<NBMMAX; j++)
		{
			int    k =i*NBMMAX+j; 
			double cosjtheta = cos(j*theta);
			double sinjtheta = sin(j*theta);
			/* coordoonées sphériques (Eq. paramétrique) */
			vertex[k][0]= cosjtheta*siniphi;
			vertex[k][1]= sinjtheta*siniphi;
			vertex[k][2]= cosiphi;			
		}
	}
	/* les normales : même chose que les sommets */
	memcpy(normal,vertex,NBMMAX*NBPMAX*sizeof(G3Xcoord));
} 

/* dessin de la sphère en rendu par points */
static void sphere_draw_0(int n, int p)
{
	int nstep=NBMMAX/n;
	int pstep=NBPMAX/p;
	int i,j;
	glDisable(GL_LIGHTING);
	glPointSize(4.);
	glBegin(GL_POINTS);
	for (i=0;i<NBPMAX;i+=pstep)
		for (j=0;j<NBMMAX;j+=nstep)
		{
			int k=i*NBMMAX+j;
			glColor3fv(colmap[k]);
			glVertex3dv(vertex[k]);
		}	
	glEnd();
	glEnable(GL_LIGHTING);
}


static void sphere_draw_1(int n, int p)
{
	int nstep=NBMMAX/n;
	int pstep=NBPMAX/p;
	int i,j;
	glPointSize(4.);
	glBegin(GL_POINTS);
	for (i=0;i<NBPMAX;i+=pstep)
		for (j=0;j<NBMMAX;j+=nstep)
		{
			int k=i*NBMMAX+j;
			g3x_Material(colmap[k],0.25,0.5,0.5,0.5,0.); 		
			glNormal3dv(normal[k]);
			glVertex3dv(vertex[k]);
		}	
	glEnd();
}

/* dessin de la sphere en facettes */
static void sphere_draw_2(int n, int p)
{
	int nstep=NBMMAX/n;
	int pstep=NBPMAX/p;
	int i,j,k;
	glBegin(GL_QUADS);
	for (i=0;i<NBPMAX-pstep;i+=pstep)
	{
		for (j=0;j<NBMMAX-nstep;j+=nstep)
		{
			k=(i      )*NBMMAX+j;
			g3x_Material(colmap[k],0.25,0.5,0.5,0.5,0.); 		
			glVertex3dv(vertex[k]);
			k=(i      )*NBMMAX+j+nstep;
			g3x_Material(colmap[k],0.25,0.5,0.5,0.5,0.); 					
			glVertex3dv(vertex[k]);
			k=(i+pstep)*NBMMAX+j+nstep;
			g3x_Material(colmap[k],0.25,0.5,0.5,0.5,0.); 		
			glVertex3dv(vertex[k]);
			k=(i+pstep)*NBMMAX+j;
			g3x_Material(colmap[k],0.25,0.5,0.5,0.5,0.); 		
			glVertex3dv(vertex[k]);
		}	
		k=(i      )*NBMMAX+j;
		g3x_Material(colmap[k],0.25,0.5,0.5,0.5,0.); 		
		glVertex3dv(vertex[k]);
		k=(i      )*NBMMAX;
		g3x_Material(colmap[k],0.25,0.5,0.5,0.5,0.); 		
		glVertex3dv(vertex[k]);
		k=(i+pstep)*NBMMAX;
		g3x_Material(colmap[k],0.25,0.5,0.5,0.5,0.); 		
		glVertex3dv(vertex[k]);
		k=(i+pstep)*NBMMAX+j;
		g3x_Material(colmap[k],0.25,0.5,0.5,0.5,0.); 		
		glVertex3dv(vertex[k]);

	}
	glEnd();
}



void Init(void)
{
	nbm=50;
	nbp=50;

	/* initialisation d'une carte de couleurs */
 	g3x_FillColorMap(colmap,NBMMAX*NBPMAX);
	/* construction fr la sphère canonique */
	SphereCanonique(); 
}

/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void)
{
	glPushMatrix();	
		sphere_draw_0(nbm,nbp);
		glPushMatrix();	
			glTranslatef(+1.5,0.,0.);
			glScalef(0.75,1.,0.75);
			sphere_draw_1(nbm,nbp);
		glPopMatrix();	
		glPushMatrix();	
			glTranslatef(-1.25,0.,0.);
			sphere_draw_2(nbm,nbp);
		glPopMatrix();	
	glPopMatrix();	
}


int main(int argc, char** argv)
{   
  /* initialisation de la fenêtre graphique et paramétrage Gl */
  g3x_InitWindow(*argv,768,512);

  /* paramètres caméra */
  /* param. géométrique de la caméra. cf. gluLookAt(...) */
  g3x_SetPerspective(40.,100.,1.);
  /* position, orientation de la caméra */
  g3x_SetCameraSpheric(0.25*PI,+0.25*PI,6.,(G3Xpoint){0.,0.,0.});

  /* définition des fonctions */
  g3x_SetInitFunction(Init);     /* la fonction d'initialisation */
  g3x_SetDrawFunction(Draw);     /* la fonction de dessin        */
	g3x_SetAnimFunction(NULL);		 /* pas de fonction d'animation  */
  g3x_SetExitFunction(NULL);     /* pas de fonction de sortie    */

	g3x_CreateScrollv_i("nbm",&nbm,3,NBMMAX,1.,"nombre de méridiens ");
	g3x_CreateScrollv_i("nbp",&nbp,3,NBPMAX,1.,"nombre de parallèles");
	
  /* boucle d'exécution principale */
  return g3x_MainStart();
  /* rien après ça */
}
