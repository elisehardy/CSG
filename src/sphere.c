/* ===============================================================
  E.Hardy - Université de Marne-la-Vallée  
  ============================================================= */
#include <g3x.h>
#include <g3x_basix.h>


typedef struct _obj_ {
    int id; /*identifiant*/
    G3Xpoint *vertex;
    G3Xvector *normal;
    
    
    bool (*pt_in)(struct _obj_ *, G3Xpoint);
    
    
    bool (*build)(struct _obj_ *);
    
    
    int n, p, size; /*taille , resolution*/
    
} object;


object Sphere, cube;


bool BuildSphere_Reg(object *obj) {
    
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    double a = 2 * PI / obj->n;
    double b = 2 * PI / obj->n;
    int i, j;
    double cosa, sina;
    for (i = 0; i < obj->n; i++) {
        cosa = cos(i * a);
        sina = sin(i * a);
        for (j = 0; j < obj->p; j++) {
            /* coordoonéeobj objphériqueobj (Eq. paramétrique) */
            obj->vertex[i * obj->p + j][0] = cosa * sin(j * b);
            obj->vertex[i * obj->p + j][1] = sina * sin(j * b);
            obj->vertex[i * obj->p + j][2] = cos(j * b);
        }
    }
    /* les normales : même chose que les sommets */
    memcpy(obj->normal, obj->vertex, obj->n * obj->p * sizeof(G3Xcoord));
    return true;
}


/*
bool BuildCube_Reg(object *obj){

    obj->vertex = (G3Xpoint*)calloc(obj->size,sizeof(G3Xpoint));
    obj->normal=(G3Xvector*)calloc(obj->size,sizeof(G3Xvector));
    G3Xpoint * v = obj->vertex;

    s->normal[0][0] = 0.;
	s->normal[0][1] = 0.;
	s->normal[0][2] = 1.;

	s->normal[1][0] = 1.;
	s->normal[1][1] = 0.;
	s->normal[1][2] = 0.;

	s->normal[2][0] = 0.;
	s->normal[2][1] = 0.;
	s->normal[2][2] = -1.;

	s->normal[3][0] = -1.;
	s->normal[3][1] = 0.;
	s->normal[3][2] = 0.;

	s->normal[4][0] = 0.;
	s->normal[4][1] = 1.;
	s->normal[4][2] = 0.;

	s->normal[5][0] = 0.;
	s->normal[5][1] = -1.;
	s->normal[5][2] = 0.;
	*//* les normales : même chose que les sommets *//*
	memcpy(obj->normal,obj->vertex,obj->n*obj->p*sizeof(G3Xcoord));
    return true;


    }*/

void Draw_Object(object *s, int c) {
    
    G3Xpoint *v;
    G3Xvector *n;
    
    g3x_Material(G3Xw, 0.25, 0.5, 0.5, 0.5, 1);
    glPointSize(1);
    glBegin(GL_POINTS);
    v = s->vertex;
    n = s->normal;
    
    while (v < s->vertex + s->size) {
        glNormal3dv(*n);
        n += c;
        glVertex3dv(*v);
        v += c;
    }
    
    glEnd();
}


static void Draw_Sphere(object *obj, int cam) {
    G3Xpoint *v;
    G3Xvector *n;
    
    glPointSize(1);
    glBegin(GL_POINTS);
    v = obj->vertex;
    n = obj->normal;
    while (v < obj->vertex + obj->size) {
        glNormal3dv(*n);
        n += cam;
        glVertex3dv(*v);
        v += cam;
    }
    
    glEnd();
}


/*
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
		for(i = 0; i < obj->n; i++){
			for(j = 0; j < obj->p; j++){
				glNormal3dv(n[face]);
				glVertex3dv(v[face*(obj->n)*(obj->p) + j+i*(obj->p)]);
			}
		}
	}

	glEnd();
}*/


void Init(void) {
    Sphere.n = 4200;
    Sphere.p = 4000;
    Sphere.size = Sphere.n * Sphere.p;
    BuildSphere_Reg(&Sphere);
    /*    cube.n = 400;
    	cube.p = 400;
    	cube.size = 6*cube.n*cube.p;
    	build_cube_reg(&cube); */
}


/*= FONCTION DE DESSIN PRINCIPALE =*/
static void Draw(void) {
    g3x_Material(G3Xr, 0.25, 0.5, 0.5, 0.5, 1.);
    Draw_Sphere(&Sphere, 1);
    G3Xcamera *c = g3x_GetCamera();
    printf("%e ", c->dist);
    if (c->dist < 2.1) {
        Draw_Object(&Sphere, 1);
        printf("haaaaa\n");
    } else if (c->dist < 11.) {
        Draw_Object(&Sphere, 32);
        printf("heeeee\n");
    } else if (c->dist < 19.) {
        Draw_Object(&Sphere, 64);
        printf("hiiiii\n");
    } else if (c->dist < 50.) {
        Draw_Object(&Sphere, 128);
        printf("hooooo\n");
    } else if (c->dist < 100.) {
        Draw_Object(&Sphere, 512);
        printf("huuuuu\n");
    } else {
        Draw_Object(&Sphere, 1024);
        printf("hyyyyy\n");
    }
}


int main(int argc, char **argv) {
    /* initialisation de la fenêtre graphique et paramétrage Gl */
    g3x_InitWindow(*argv, 768, 512);
    /* param. géométrique de la caméra. cf. gluLookAt(...) */
    g3x_SetPerspective(40., 100., 1.);
    /* position, orientation de la caméra */
    g3x_SetCameraSpheric(0.25 * PI, +0.25 * PI, 6., (G3Xpoint) {0., 0., 0.});
    
    /* définition des fonctions */
    g3x_SetInitFunction(Init);     /* la fonction d'initialisation */
    g3x_SetDrawFunction(Draw);     /* la fonction de dessin        */
    g3x_SetAnimFunction(NULL);         /* pas de fonction d'animation  */
    g3x_SetExitFunction(NULL);     /* pas de fonction de sortie    */
    
    
    /* boucle d'exécution principale */
    return g3x_MainStart();
    /* rien après ça */
}
