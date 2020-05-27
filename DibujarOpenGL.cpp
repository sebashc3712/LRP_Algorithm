/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#pragma warning (disable: 4786)

//Para incluir el contenedor que tengo
#include "Container.h"

using namespace std;

float D=250.0;
int cuantos=0;
bool compacta=false;
static GLfloat view_rotx=20.0, view_roty=0.0, view_rotz=0.0;

static int		menu;     // Identificador del menu
typedef enum{ ZOOM,GIRAR,SALIR} opciones_menu;
typedef enum {MOVIENDO,GIRANDO} acciones_raton;
int MODORaton=MOVIENDO;
int RatonPulsado = GL_FALSE;

int Xref=0, Yref=0;
int clientes=0;int cantidad=0;
void CONTAINER:: EscribirMejorSolucionOpenGL(std::list<CONFIGURACAO> lista)
{
	
//	si es la ultima
	for (int kju=0;kju<m_Q;kju++)
		m_Pieces[kju].Set_Num(0);
//	printf("%d",m_max_total_volumen_ocupado);
	FILE *fin3;

	fin3=fopen("temp.txt","w+");
	if(m_num_total_clientes==1)
		fprintf(fin3,"%d\t%d\t%d\t%d\t%d\n",m_Q,m_Q,m_X,m_Y,m_Z);
	else
		fprintf(fin3,"%d\t%d\t%d\t%d\t%d\n",m_Q,m_num_total_clientes,m_X,m_Y,m_Z);
	fprintf(fin3,"%d\t%d\n",m_max_total_volumen_ocupado,m_total_volumen_ocupado);
	std::list< CONFIGURACAO > ::iterator itC;
	
	float divide=20;

	//Ahora las lineas que van de un lado al otro
	//Esto dibuja bloque enteros de piezas
		int cont=0;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
		cont++;
		for (int register i=1;i<=(*itC).Get_dx();i++)
		{
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz();k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
					if (m_num_total_clientes==1)
						fprintf(fin3,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,(*itC).Get_Id(),cont,cont);
					else
						fprintf(fin3,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,(*itC).Get_Id(),cont,(*itC).Get_m_cliente_config());
					
					if ((*itC).Get_Id()>cantidad)
						cantidad=(*itC).Get_Id();
					m_Pieces[(*itC).Get_Id()].Add_Num(1);

				}
			}
		}
	}
	/*
	std::list <CONFIGURACAO> ::reverse_iterator itR;
	for (itR=lista.rbegin();itR!=lista.rend();itR++)
	{
		//Buscar
		flag=0;
		minimo=m_X;
		for (itC=lista.begin();itC!=lista.end();itC++)
		{
			if((*itC).Get_z1()==0)
			{
				if((*itC).Get_x1()>(*itR).Get_x2())
				{
					if(((*itR).Get_y1()<=(*itC).Get_y2()&&(*itR).Get_y2()>=(*itC).Get_y2())||((*itR).Get_y1()<=(*itC).Get_y1()&&(*itR).Get_y2()>=(*itC).Get_y1()))
					{
						if(minimo>(*itC).Get_x2())
						{
							minimo = (*itC).Get_x2();
							flag=1;
						}
					}
					else
					{
						if(((*itR).Get_y1()>=(*itC).Get_y2()&&(*itR).Get_y1()<=(*itC).Get_y2())&&((*itR).Get_y2()>=(*itC).Get_y1()&&(*itR).Get_y2()<=(*itC).Get_y2()))
						{
							if(minimo>(*itC).Get_x2())
							{
								minimo = (*itC).Get_x2();
								flag=1;
							}
						}
					}
				}
			}
		}
		if (flag==1)
		{
			cond_tocable_largo =__min((200-(*itR).Get_z1()),60);
			if((((minimo-(*itR).Get_x2())+(*itR).Get_z1())>=200)&&((minimo-(*itR).Get_x2())<=cond_tocable_largo))
		}				
	}
	*/
	//Piezas que estan fuera
	int kk=m_X;
	for (int i=0;i<m_Q;i++)
	{

		if (m_Pieces[i].Get_Num()!=m_Pieces[i].Get_q())
		{
			cont++;
			int y=0;
			for (int kj=0;kj<(m_Pieces[i].Get_q()-m_Pieces[i].Get_Num());kj++)
			{
				//fprintf(fin3,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",kk,0,y,kk+m_Pieces[i].Get_x(),m_Pieces[i].Get_y(),y+m_Pieces[i].Get_z(),m_Pieces[i].Get_Id(),cont);
				//fprintf(fin3,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",kk*10,0,y*10,(kk+m_Pieces[i].Get_x())*10,m_Pieces[i].Get_y()*10,(y+m_Pieces[i].Get_z())*10,m_Pieces[i].Get_Id(),cont,m_Pieces[i].Get_Cliente());
				fprintf(fin3,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",kk,0,y,(kk+m_Pieces[i].Get_x()),m_Pieces[i].Get_y(),(y+m_Pieces[i].Get_z()),m_Pieces[i].Get_Id(),cont,m_Pieces[i].Get_Cliente());
				y+=m_Pieces[i].Get_z();
			}
			kk+=m_Pieces[i].Get_x()+1;
		}
	}
	fclose(fin3);
}

static void ejes(float o_x, float o_y, float o_z, float x,float y, float z)
{
	glLineWidth(3);
glBegin(GL_LINES);{
  glColor3f(1,1,1);

  //8
  glVertex3f( o_x, o_y, o_z );
  glVertex3f( o_x, o_y, o_z+z );
  glVertex3f( o_x, o_y+y, o_z );
  glVertex3f( o_x, o_y+y, o_z+z );
  glVertex3f( o_x+x, o_y, o_z );
  glVertex3f( o_x+x, o_y, o_z+z );
  glVertex3f( o_x+x, o_y+y, o_z );
  glVertex3f( o_x+x, o_y+y, o_z+z );

  //
  glVertex3f( o_x, o_y+y, o_z );
  glVertex3f( o_x+x, o_y+y, o_z );
  glVertex3f( o_x, o_y+y, o_z+z );
  glVertex3f( o_x+x, o_y+y, o_z+z );
  glVertex3f( o_x, o_y, o_z+z );
  glVertex3f( o_x+x, o_y, o_z+z );
  glVertex3f( o_x, o_y, o_z );
  glVertex3f( o_x+x, o_y, o_z);


   glVertex3f( o_x, o_y+y, o_z );
  glVertex3f( o_x, o_y, o_z );
  glVertex3f( o_x+x, o_y+y, o_z );
  glVertex3f( o_x+x, o_y, o_z );
  glVertex3f( o_x, o_y+y, o_z+z );
  glVertex3f( o_x, o_y, o_z+z );
  glVertex3f( o_x+x, o_y+y, o_z+z );
  glVertex3f( o_x+x, o_y, o_z+z);

 
  //
/*  glVertex3f( o_x, o_y, o_z+z );
  glVertex3f( o_x+x, o_y, o_z+z );
  glVertex3f( o_x, o_y, o_z+z );
  glVertex3f( o_x, o_y+y, o_z+z );
  glVertex3f( o_x+x, o_y+y, o_z );
  glVertex3f( o_x+x, o_y, o_z );
  glVertex3f( o_x+x, o_y+y, o_z );
  glVertex3f( o_x, o_y+y, o_z );
  glVertex3f( o_x, o_y+y, o_z );
  glVertex3f( o_x+x, o_y+y, o_z );
  glVertex3f( o_x+x, o_y+y, o_z+z );
  glVertex3f( o_x, o_y+y, o_z +z);
  glVertex3f( o_x, o_y, o_z+z );
  glVertex3f( o_x, o_y+y, o_z +z);
*/

	}
glEnd();
}

/* Construye una caja con un vertice en o_X de dimensiones
*/
static void cubo(GLfloat o_x, GLfloat o_y, GLfloat o_z, GLfloat x, GLfloat y, GLfloat z,int Id, int Cliente,int nbloque,int cant)
{
//	float color[4]={0,0,0,1};
       //float color[4]={0+((double)1/(double)cantidad)(double)Id,1-((double)1/(double)cantidad)(double)Id,0+((double)1/(double)cantidad)*(double)Id,1};
	float color[4]={0+((double)1/(double)cantidad)*(double)Id,1-((double)1/(double)cantidad)*(double)Id,0+((double)1/(double)cantidad)*(double)Id,1};    
	if (Cliente%9==1)
       {
               color[0]=0.5+((double)1/(double)clientes)*(double)Cliente;
       }
       if (Cliente%9==2)
       {
               color[1]=0.5+((double)1/(double)clientes)*(double)Cliente;
       }
       if (Cliente%9==3)
       {
               color[2]=0.5+((double)1/(double)clientes)*(double)Cliente;
       }
       if (Cliente%9==4)
       {
               color[0]=0.25+((double)1/(double)clientes)*(double)Cliente;
       }
       if (Cliente%9==5)
       {
               color[1]=0.25+((double)1/(double)clientes)*(double)Cliente;
       }
       if (Cliente%9==6)
       {
               color[2]=0.25+((double)1/(double)clientes)*(double)Cliente;
       }
       if (Cliente%9==7)
       {
               color[1]=0.75+((double)1/(double)clientes)*(double)Cliente;
       }
       if (Cliente%9==8)
       {
               color[2]=0.75+((double)1/(double)clientes)*(double)Cliente;
       }
 
//donde cantidad es una variable global que es el mayor id del problema
   glShadeModel( GL_FLAT );

   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color );



   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
glNormal3f( 0.0, 0.0, -1.0 );   /* Vertical hacia atras */

      glVertex3f( o_x+x, o_y+0, o_z+0 );
      glVertex3f( o_x+0, o_y+0, o_z+0 );


      glVertex3f( o_x+x, o_y+y, o_z+0 );
      glVertex3f( o_x+0, o_y+y, o_z+0 );

glNormal3f( 0.0, 1.0, 0.0 );       /* Superior, horizontal */

      glVertex3f( o_x+x, o_y+y,o_z+ z );
      glVertex3f( o_x+0, o_y+y, o_z+z );
glNormal3f( 0.0, 0.0, 1.0 );       /*Vertical delantera*/
      glVertex3f( o_x+x, o_y+0,o_z+ z );
      glVertex3f( o_x+0, o_y+0, o_z+z );

glNormal3f( 0.0, -1.0, 0.0 );       /*Inferior */
      glVertex3f(o_x+ x, o_y+0, o_z+0 );
      glVertex3f(o_x+ 0, o_y+0, o_z+0 );  }
    glEnd();

   /* Costados */
   glBegin( GL_QUADS );{
      glNormal3f( 1.0, 0.0, 0.0 );
      glVertex3f( o_x+x, o_y+0, o_z+0 );
      glVertex3f( o_x+x, o_y+y, o_z+0 );
      glVertex3f( o_x+x, o_y+y, o_z+z );
      glVertex3f( o_x+x, o_y+0, o_z+z ); }
   glEnd();


   glBegin( GL_QUADS );{
      glNormal3f( -1.0, 0.0, 0.0 );
      glVertex3f( o_x+0, o_y+0,o_z+ 0 );
      glVertex3f( o_x+0, o_y+0,o_z+ z );
      glVertex3f( o_x+0, o_y+y,o_z+ z );
      glVertex3f( o_x+0, o_y+y,o_z+ 0 ); }
   glEnd();


}




void DibujaGL( )
{
   static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0 };


	glPushMatrix();		// Apila la transformación geométrica actual

  // Fija el color de fondo a negro
  glClearColor(1,1,1,1);

  // Inicializa el buffer de color
  glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );


  // Fija el color de dibujo

  // Introduce la geometria
 	
 	glTranslatef(-20,0,-D);

// Colocar aqui la luz si esta fija respecto del observador  	
    glLightfv( GL_LIGHT0, GL_POSITION, pos );

 	
 	glRotatef( view_rotx, 1.0, 0.0, 0.0 );
   	glRotatef( view_roty, 0.0, 1.0, 0.0 );
   	glRotatef( view_rotz, 0.0, 0.0, 1.0 );

// Colocar aqui la luz si esta fija en la escena   	
//    glLightfv( GL_LIGHT0, GL_POSITION, pos );

//  ejes(30);
	//Abro el fichero que voy a escribir
//		char string[200];
//	strcpy(string,"Sol\\Sol");
	//Primero buscamos la ultima ocurrencia de 
//	int ch='\\';
//	char *ultimo=strrchr( m_Nombre, ch );
//	strcpy(string,"C:\\afrank\\3dContainer\\Instancias\\BSGrasp\\");
//	strcat(string,ultimo+1);
//	ejes(0,0,0,200,200,200);/*
	FILE *fin2;

	fin2=fopen("temp.txt","r+");
	if (fin2==NULL)
	{
		printf("Problemas al leer el archivo del container, no se encuentra el archivo " );
		exit(4);
	}
	//Leemos el valor
	int valguardado=0,cant=0;
	int x,y,z,x2,y2,z2,Id,X,Y,Z,nblo;
	short int tipo;
	fscanf(fin2,"%d\t%d\t%d\t%d\t%d",&cant,&clientes, &X, &Y, &Z);
	double relacion=(double)(X)/(double)35;
	ejes(0,0,0,(double)(X)/(double)relacion,(double)(Z)/(double)relacion,(double)(Y)/(double)relacion);
	fscanf(fin2,"%d\t%d",&valguardado,&valguardado);
	int cont=0;
	int tempId=-1;
		int cliente;
	Id=-20;
	nblo=-1;
	while(!feof(fin2))
	{
		tempId=nblo;
		//fscanf(fin2,"%d %d %d %d %d %d %d %d ",&x,&y,&z,&x2,&y2,&z2,&Id,&nblo);
		fscanf(fin2,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",&x,&y,&z,&x2,&y2,&z2,&Id,&nblo,&cliente);
		//di
		if (nblo!=tempId) cont++;
		if (cont>cuantos ) break;
		//cubo((double)x/(double)10,(double)z/(double)10,(double)y/(double)10,(double)(x2-x)/(double)10,(double)(z2-z)/(double)10,(double)(y2-y)/(double)10,Id,cant);
		//ejes((double)x/(double)10,(double)z/(double)10,(double)y/(double)10,(double)(x2-x)/(double)10,(double)(z2-z)/(double)10,(double)(y2-y)/(double)10);
		
		
		cubo((double)x/(double)relacion,(double)z/(double)relacion,(double)y/(double)relacion,(double)(x2-x)/(double)relacion,(double)(z2-z)/(double)relacion,(double)(y2-y)/(double)relacion,Id,cliente,nblo,cant);
		ejes((double)x/(double)relacion,(double)z/(double)relacion,(double)y/(double)relacion,(double)(x2-x)/(double)relacion,(double)(z2-z)/(double)relacion,(double)(y2-y)/(double)relacion);
		//		CONFIGURACAO temp(this,Id,x,y,z,x2,y2,z2,tipo,1);
//		temp.Set_dx(1);
//		temp.Set_dy(1);
//		temp.Set_dz(1);
//		printf("%d %d %d %d %d %d %d \n ",x,y,z,x2,y2,z2,Id);
//		m_Best_Configuracao.push_back(temp);
//		m_max_total_volumen_ocupado+=(x2-x)*(y2-y)*(z2-z);
//		if(temp.Get_x1()>=0 && m_X>=temp.Get_x2() &&
//		   temp.Get_y1()>=0 && m_Y>=temp.Get_y2()  &&
//		   temp.Get_z1()>=0 && m_Z>=temp.Get_z2() )
//			continue;
//		return ;


	}
	fclose(fin2);

//  cubo(0,0,0,10,10,10);
 // cubo(0,10,10,10,10,10);
  	glPopMatrix(); // Desapila la transformación geométrica
  	
  glFlush();  // Fuerza el dibujo de las primitivas introducidas
  glutSwapBuffers();



}
/* ------------------------------------------------------------------------- */

void Ventana(GLsizei ancho,GLsizei alto)
{
	float calto; 	// altura de la ventana corregida
  // Establecemos el Viewport usando la nueva anchura y altura de la ventana X
  	glViewport(0,0,ancho,alto);

 // Especificamos la transformación de visualización 	
  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

  	if(ancho>0)
  		calto = 1*(GLfloat)alto/(GLfloat)ancho;
  	else
  		calto = 1;
  		
//  		glOrtho(-50,50,-calto, calto,0,1);
			glFrustum(-1,1,-calto,calto,5,250);

// A partir de este momento las transformaciones son de modelado  		
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();



}

static void letra (unsigned char k, int x, int y)
{
  switch (k) {
  case '1':
	  cuantos--;
	  break;
  case '2':
	  cuantos++;
	  break;
	case '3':
	  if (compacta==true)
		  compacta=false;
	  else
		  compacta=true;
	  break;
  case 'h':
  case 'H':
  	printf("\n Escape: Salir");
  	printf("\n\n\n");
  	break;
  case 'z':
    view_rotz += 5.0;
    break;
  case '+':
    D -= 5.0;
    break;
  case '-':
    D += 5.0;
    break;
  case 'Z':
    view_rotz -= 5.0;
    break;
  case 27:  /* Escape */
    exit(0);
    break;
  default:
    return;
  }
  glutPostRedisplay();
}



 static void especial(int k, int x, int y)
{
  switch (k) {
  case GLUT_KEY_UP:
    view_rotx += 5.0;
    break;
  case GLUT_KEY_DOWN:
    view_rotx -= 5.0;
    break;
  case GLUT_KEY_LEFT:
    view_roty += 5.0;
    break;
  case GLUT_KEY_RIGHT:
    view_roty -= 5.0;
    break;
  default:
    return;
  }
  glutPostRedisplay();
}

 void seleccionMenu( int opcion )
{
   switch ( opcion )
   {
   case ZOOM:
      MODORaton=MOVIENDO;
      break;
   case GIRAR:
      MODORaton=GIRANDO;
      break;
   case SALIR:
	   return;
//   	  exit(0);
   }
}

// static void RatonMovido( int x, int y );

 void clickRaton( int boton, int estado, int x, int y )
{
	
   	if(boton== GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {

   		if( ~(RatonPulsado)){
      		Xref=x;
      		Yref=y;
      		RatonPulsado=GL_TRUE;
      		}
      	}
	else RatonPulsado=GL_FALSE;
	
}



 static void RatonMovido( int x, int y )
 // Esta función mueve la camara por el escenario
/**/ // Dependiendo del modo mueve o gira la camara
{
if(RatonPulsado)     {
	if(MODORaton==MOVIENDO) {
   		D = 100.0*(Yref-y-150);
		}
	else{
		view_rotx += (Yref -y-150) / 10;
   		view_roty += (Xref -x-150) / 10;
   		}
	glutPostRedisplay();
	}


}

 void CreaMenu()
{

   menu = glutCreateMenu( seleccionMenu );

   glutAddMenuEntry( "Zoom", ZOOM );
   glutAddMenuEntry( "Girar", GIRAR );
   glutAddMenuEntry( "Salir", SALIR );

	MODORaton = MOVIENDO;

   glutAttachMenu( GLUT_RIGHT_BUTTON );
   glutMouseFunc( clickRaton );
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glEnable( GL_LIGHTING );
   glEnable( GL_LIGHT0 );

}



/* ------------------------------------------------------------------------- */




 int CONTAINER::DibujarOpenGL(std::list<CONFIGURACAO> lista)
{
	
	//cout<<endl<<"Entra!!";
// Inicializa glu y Mesa	
   //glutInit(&argc, argv);
	EscribirMejorSolucionOpenGL(lista);
// Crea una ventana X para la salida gráfica
   glutInitWindowPosition( 0, 0 );
   glutInitWindowSize( 2000, 2000 );
   glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
   glutCreateWindow("CAD. Ejemplo GEOMETRIA 1.");


// Inicializa las funciones de dibujo y cambio de tamaño de la ventana X
   glutDisplayFunc( DibujaGL );
   glutReshapeFunc( Ventana );

// FUNCIONES DE INTERACCIÓN
 	CreaMenu();
  	glutKeyboardFunc(letra);
  	glutSpecialFunc(especial);

   	glutPassiveMotionFunc( RatonMovido );

   glutMainLoop();
   return 0;
}
