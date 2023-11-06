//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul III - 03_02_animatie.cpp |
// ============================================
//
//	Program ce deseneaza un dreptunghi ce se deplaseaza stanga-dreapta si are un patrat ce orbiteaza in jurul sau, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	- utilizeaza diverse transformari si compunerea acestora folosind biblioteca glm,
//	- functii pentru utilizarea mouse-ului;
//
//
//	Biblioteci

#include <iostream>			//	Biblioteca necesara pentru afisarea in consola;
#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shared.h"
#include "Plant.h"

using namespace std;

//  Identificatorii obiectelor de tip OpenGL;
GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId;
//	Dimensiunile ferestrei de afisare;
GLfloat
winWidth = 1000, winHeight = 600;
//	Variabile catre matricile de transformare;
glm::mat4 myMatrix;

const int NMax = 100000;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;
//	Variabile pentru proiectia ortogonala;
float xMin = 0.0f, xMax = 1000.0f, yMin = 0.0f, yMax = 600.0f;
//	Variabile pentru deplasarea pe axa Ox si pentru rotatie;
float i = 0.0, alpha = 0.0, step = 0.3, beta = 0.002, angle = 0;


//	Functie pentru afisarea matricei de transformare;
void DisplayMatrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << myMatrix[i][j] << "  ";
		cout << endl;
	};
	cout << "\n";
};

//	Schimba sensul animatiei spre dreapta;
void MoveRight(void)
{
	i = i + alpha;
	if (i > 350.0)			//	Se asigura deplasarea stanga-dreapta pe Ox in limitele ecranului,
		alpha = -step;		//	mai intai efectuandu-se deplasarea spre DREAPTA;
	else if (i < -350.0)
		alpha = step;
	angle = angle - beta;	//	Se actualizeaza unghiul de rotatie constant (mentine orbitarea);
	glutPostRedisplay();	//	Forteza redesenarea scenei;
}

//	Schimba sensul animatiei spre stanga;
void MoveLeft(void)
{
	i = i + alpha;
	if (i < -350.0)			//	Se asigura deplasarea stanga-dreapta pe Ox in limitele ecranului,
		alpha = step;		//	mai intai efectuandu-se deplasarea spre STANGA;
	else if (i > 350.0)
		alpha = -step;
	angle = angle + beta;	//	Se actualizeaza unghiul de rotatie constant (mentine orbitarea);
	glutPostRedisplay();	//	Forteza redesenarea scenei;
}

//	Functie ce modifica deplasarea dreptunghiurilor in functie de apasarea butoanelor de pe mouse;
void UseMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:			//	CLICK stanga => dreptunghiurile se misca spre stanga;
		if (state == GLUT_DOWN)
			alpha = -step;
		glutIdleFunc(MoveLeft);
		break;
	case GLUT_RIGHT_BUTTON:			//	CLICK dreapta => dreptunghiurile se misca spre drepta;
		if (state == GLUT_DOWN)
			alpha = step;
		glutIdleFunc(MoveRight);
		break;
	default:
		break;
	}
}

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("main.vert", "main.frag");
	glUseProgram(ProgramId);
}

// Desenam o planta
// x, y - coordonatele stanga jos ale chenarului in care se va desena planta
void plant(GLfloat Vertices[], int &poz,  float x, float y) {
	Vertices[++poz] = x + 25.f;
	Vertices[++poz] = y + 50.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 50.f;
	Vertices[++poz] = y + 0.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 75.f;
	Vertices[++poz] = y + 33.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 100.f;
	Vertices[++poz] = y + 33.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 100.f;
	Vertices[++poz] = y + 67.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 75.f;
	Vertices[++poz] = y + 67.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 50.f;
	Vertices[++poz] = y + 100.f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;
}

// Desenam o stea cu 5 colturi
// x, y - coordonatele stanga jos ale chenarului in care se va desena steaua
// actualizam pozitia in vectorul Vertices
void star(GLfloat Vertices[], int &poz, GLfloat x, GLfloat y, GLfloat scale = 2.2f) {
	Vertices[++poz] = x + 6.f * scale;
	Vertices[++poz] = y + 3.f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 9.5f * scale;
	Vertices[++poz] = y + 1.f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 8.f * scale;
	Vertices[++poz] = y + 5.5f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 11.75f * scale;
	Vertices[++poz] = y + 8.f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 7.f * scale;
	Vertices[++poz] = y + 7.5f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	// varful stelei
	Vertices[++poz] = x + 6.f * scale;
	Vertices[++poz] = y + 12.f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 5.f * scale;
	Vertices[++poz] = y + 7.5f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 0.25f * scale;
	Vertices[++poz] = y + 8.f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 4.f * scale;
	Vertices[++poz] = y + 5.5f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	Vertices[++poz] = x + 2.5f * scale;
	Vertices[++poz] = y + 1.f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;
}


//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{

	//  Coordonatele varfurilor;
	//GLfloat Vertices[144 + 16 + 16 * 4 + 16 * 3 + 28 * 4 +40*10 + 40*6] = { 0 };
	GLfloat Vertices[NMax] = { 0 };

	// Culorile axelor
	GLfloat Colors[16] = { 
		0.0f, 0.0f, 0.0f, 1.0f,	// Negru
		1.0f, 0.0f, 0.0f, 1.0f,	// Rosu
		0.0f, 1.0f, 0.0f, 1.0f,	// Verde
		0.0f, 0.0f, 1.0f, 1.0f	// Albastru
	};

	// Adaugam cele 9 patrate
	float xBL = 100.f, yBL = 25.f, offset = 25.f;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			// Coltul stanga jos
			Vertices[16 * (i * 3 + j)] = xBL + 100 * i + i * offset;
			Vertices[16 * (i * 3 + j) + 1] = yBL + 100 * j + j * offset;
			Vertices[16 * (i * 3 + j) + 2] = 0.0f;
			Vertices[16 * (i * 3 + j) + 3] = 1.0f;
			
			// Coltul dreapta jos
			Vertices[16 * (i * 3 + j) + 4] = xBL + 100 * i + 100 + i * offset;
			Vertices[16 * (i * 3 + j) + 5] = yBL + 100 * j + j * offset;
			Vertices[16 * (i * 3 + j) + 6] = 0.0f;
			Vertices[16 * (i * 3 + j) + 7] = 1.0f;

			// Coltul dreapta sus
			Vertices[16 * (i * 3 + j) + 8] = xBL + 100 * i + 100 + i * offset;
			Vertices[16 * (i * 3 + j) + 9] = yBL + 100 * j + 100 + j * offset;
			Vertices[16 * (i * 3 + j) + 10] = 0.0f;
			Vertices[16 * (i * 3 + j) + 11] = 1.0f;

			// Coltul stanga sus
			Vertices[16 * (i * 3 + j) + 12] = xBL + 100 * i + i * offset;
			Vertices[16 * (i * 3 + j) + 13] = yBL + 100 * j + 100 + j * offset;
			Vertices[16 * (i * 3 + j) + 14] = 0.0f;
			Vertices[16 * (i * 3 + j) + 15] = 1.0f;
		}
	}

	// Dreptungiul 'bazei'
	int poz = 144;
	// Coltul stanga jos
	Vertices[poz] = 20.0f;
	Vertices[poz + 1] = 25.0f;
	Vertices[poz + 2] = 0.0f;
	Vertices[poz + 3] = 1.0f;

	// Coltul dreapta jos
	Vertices[poz + 4] = 80.0f;
	Vertices[poz + 5] = 25.0f;
	Vertices[poz + 6] = 0.0f;
	Vertices[poz + 7] = 1.0f;

	// Coltul dreapta sus
	Vertices[poz + 8] = 80.0f;
	Vertices[poz + 9] = 375.0f;
	Vertices[poz + 10] = 0.0f;
	Vertices[poz + 11] = 1.0f;

	// Coltul stanga sus
	Vertices[poz + 12] = 20.0f;
	Vertices[poz + 13] = 375.0f;
	Vertices[poz + 14] = 0.0f;
	Vertices[poz + 15] = 1.0f;
	
	// Kenarele pentru plante
	poz += 16;
	for (int i = 0;i < 4;i++)
	{
		// stanga jos
		Vertices[poz + 16 * i] = xBL + 100 * i + i * offset;
		Vertices[poz + 16 * i + 1] = 475.f;
		Vertices[poz + 16 * i + 2] = 0.0f;
		Vertices[poz + 16 * i + 3] = 1.0f;

		// dreapta jos
		Vertices[poz + 16 * i + 4] = xBL + 100 * i + 100 + i * offset;
		Vertices[poz + 16 * i + 5] = 475.f;
		Vertices[poz + 16 * i + 6] = 0.0f;
		Vertices[poz + 16 * i + 7] = 1.0f;

		// dreapta sus
		Vertices[poz + 16 * i + 8] = xBL + 100 * i + 100 + i * offset;
		Vertices[poz + 16 * i + 9] = 575.f;
		Vertices[poz + 16 * i + 10] = 0.0f;
		Vertices[poz + 16 * i + 11] = 1.0f;

		// stanga sus
		Vertices[poz + 16 * i + 12] = xBL + 100 * i + i * offset;
		Vertices[poz + 16 * i + 13] = 575.f;
		Vertices[poz + 16 * i + 14] = 0.0f;
		Vertices[poz + 16 * i + 15] = 1.0f;

	}

	// Patratele pentru vieti
	poz += 64;
	offset = 25.f;
	for (int i = 0; i < 3; i++)
	{
		// stanga jos
		Vertices[poz + 16 * i] = 25.f + 50 * i + i * offset + 600;
		Vertices[poz + 16 * i + 1] = 500.f;
		Vertices[poz + 16 * i + 2] = 0.0f;
		Vertices[poz + 16 * i + 3] = 1.0f;

		// dreapta jos
		Vertices[poz + 16 * i + 4] = 75.f + 50 * i + i * offset + 600;
		Vertices[poz + 16 * i + 5] = 500.f;
		Vertices[poz + 16 * i + 6] = 0.0f;
		Vertices[poz + 16 * i + 7] = 1.0f;

		// dreapta sus
		Vertices[poz + 16 * i + 8] = 75.f + 50 * i + i * offset + 600;
		Vertices[poz + 16 * i + 9] = 550.f;
		Vertices[poz + 16 * i + 10] = 0.0f;
		Vertices[poz + 16 * i + 11] = 1.0f;

		// stanga sus
		Vertices[poz + 16 * i + 12] = 25.f + 50 * i + i * offset + 600;
		Vertices[poz + 16 * i + 13] = 550.f;
		Vertices[poz + 16 * i + 14] = 0.0f;
		Vertices[poz + 16 * i + 15] = 1.0f;	
	}

	// plantele
	poz += 48;
	poz -= 1;
	plant(Vertices, poz, 100.f, 475.f);
	plant(Vertices, poz, 225.f, 475.f);
	plant(Vertices, poz, 350.f, 475.f);
	plant(Vertices, poz, 475.f, 475.f);

	// stelele - pretul plantelor
	GLfloat width_stars = 25.0f;	
	GLfloat y_stars = 450.f;
	star(Vertices, poz, 100.f, y_stars);

	star(Vertices, poz, 225.f, 450.f);
	star(Vertices, poz, 225.f + width_stars, y_stars);

	star(Vertices, poz, 350.f, 450.f);
	star(Vertices, poz, 350.f + width_stars, y_stars);
	star(Vertices, poz, 350.f + width_stars * 2, y_stars);

	star(Vertices, poz, 475.f, 450.f);
	star(Vertices, poz, 475.f + width_stars, y_stars);
	star(Vertices, poz, 475.f + width_stars * 2, y_stars);
	star(Vertices, poz, 475.f + width_stars * 3, y_stars);

	// stelele - banii acumulati
	GLfloat x_stars = 625.f;
	y_stars = 470.f;
	for (int i = 0; i < 6;i++)
		star(Vertices, poz, x_stars + width_stars * i, y_stars);

	// Asezarea obiectelor dinamice in Vertices si Indices
	// Planta generica - 7 puncte
	Plant::offset = (poz + 1) / 4;
	plant(Vertices, poz, -50.f, -50.f); // planta centrata in (0, 0) ca sa o pot pune unde vreau din translatii


	//  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
	glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);

	//  Se creeaza un buffer pentru VARFURI;
	glGenBuffers(1, &VboId);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);      //  Punctele sunt "copiate" in bufferul curent;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//  Se creeaza un buffer pentru CULOARE;
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void)
{
	//  Eliberarea atributelor din shadere (pozitie, culoare, texturare etc.);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//  Stergerea bufferelor pentru varfuri, culori;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

	//  Eliberaea obiectelor de tip VAO;
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
	glClearColor(0.23f, 0.23f, 0.23f, 0.0f);		//  Culoarea de fond a ecranului;
	CreateVBO();								//  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateShaders();							//  Initilizarea shaderelor;
	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	Shared::codColLocation = glGetUniformLocation(ProgramId, "codCol");
	Shared::myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;

	// TO DO: schimbati transformarile (de exemplu deplasarea are loc pe axa Oy sau pe o alta dreapta);
	Shared::resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);							//	"Aducem" scena la "patratul standard" [-1,1]x[-1,1];
	//matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0, 0.0));		//	Se translateaza de-a lungul axei Ox;
	//matrDepl = glm::translate(glm::mat4(1.0f), glm::vec3(0, 80.0, 0.0));		//	Se translateaza patratul ROSU fata de patratul ALBASTRU;
	//matrScale1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.1, 0.3, 0.0));			//	Se scaleaza coordonatele initiale si se obtine dreptunghiul ALABSTRU;
	//matrScale2 = glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.25, 0.0));		//	Se scaleaza coordonatele initiale si se obtine patratul ROSU;
	//matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));	//	Roatie folosita la deplasarea patratului ROSU;

	//matrScale3 = glm::scale(glm::mat4(1.0f), glm::vec3(3.0, 3.0, 0.0));	
	// construieste o scalare care dubleaza dimensiunea obiectului



	myMatrix = Shared::resizeMatrix;
	codCol = FIELD_GREEN;
	glUniformMatrix4fv(Shared::myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(Shared::codColLocation, codCol);

	// Desenam cele 9 "campuri" in care vor fi plasate plantele
	for (int i = 0; i < 9; ++i) {
		glDrawArrays(GL_POLYGON, 4 * i, 4);
	}

	// desenam baza
	codCol = RED;
	glUniform1i(Shared::codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 36, 4);

	// desenam kenarele pentru plante
	codCol = WHITE;
	glUniform1i(Shared::codColLocation, codCol);
	glDrawArrays(GL_LINE_LOOP, 40, 4);
	glDrawArrays(GL_LINE_LOOP, 44, 4);
	glDrawArrays(GL_LINE_LOOP, 48, 4);
	glDrawArrays(GL_LINE_LOOP, 52, 4);

	// desenam vietile
	codCol = RED;
	glUniform1i(Shared::codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 56, 4);
	glDrawArrays(GL_POLYGON, 60, 4);
	glDrawArrays(GL_POLYGON, 64, 4);

	// desenam plantele din chenare
	codCol = MAGENTA;
	glUniform1i(Shared::codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 68, 7);

	codCol = YELLOW;
	glUniform1i(Shared::codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 75, 7);

	codCol = CYAN;
	glUniform1i(Shared::codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 82, 7);

	codCol = ORANGE;
	glUniform1i(Shared::codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 89, 7);

	// desenam stelele - pretul plantelor
	codCol = LIGHT_GRAY;
	glUniform1i(Shared::codColLocation, codCol);
	int poz = 96;
	for (int i=0; i<10;i++)
		glDrawArrays(GL_POLYGON, poz + 10 * i, 10);

	// desenam stelele - banii acumulati
	poz = 196;
	for (int i = 0; i < 6;i++)
		glDrawArrays(GL_POLYGON, poz + 10 * i, 10);

	// Test Plant spawn
	Plant p1(YELLOW, 100.f, 100.f);
	Plant p2(CYAN, 225.f, 100.f);
	Plant p3(ORANGE, 350.f, 100.f);
	p1.draw(); 
	p2.draw();
	p3.draw();

	////	Desenarea axelor;

	////	Matricea de redimensionare (pentru elementele "fixe" - axele);
	//myMatrix = resizeMatrix;
	////	Culoarea;
	//codCol = 0;
	////	Transmiterea variabilelor uniforme pentru MATRICE DE TRANSFORMARE si COLORARE spre shadere;
	//glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	//glUniform1i(codColLocation, codCol);
	////  Functia de desenare primeste 3 argumente:
	////  - arg1 = tipul primitivei desenate,
	////  - arg2 = indicele primului punct de desenat din buffer,
	////  - arg3 = numarul de puncte consecutive de desenat;
	//glDrawArrays(GL_LINES, 0, 4);

	////	Desenarea dreptunghiului ALBASTRU;

	////	Matricea de transformare pentru dreptunghiul ALBASTRU; 
	//myMatrix = resizeMatrix * matrTransl * matrScale1;
	//codCol = 1;
	////	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	//glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	//glUniform1i(codColLocation, codCol);
	//glDrawArrays(GL_POLYGON, 4, 4);

	////	Desenarea dreptunghiului ROSU;

	////	Matricea de transformare pentru dreptunghiul ROSU; 
	//myMatrix = resizeMatrix * matrTransl * matrRot * matrDepl * matrScale2;
	//codCol = 2;
	////	Transmiterea variabilelor uniforme pentru MATRICE DE TRANSFORMARE si COLORARE spre shadere;
	//glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	//glUniform1i(codColLocation, codCol);
	//glDrawArrays(GL_POLYGON, 4, 4);

	glutSwapBuffers();	//	Inlocuieste imaginea deseneata in fereastra cu cea randata; 
	glFlush();	//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);					//	Se folosesc 2 buffere (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutInitWindowSize(winWidth, winHeight);									//  Dimensiunea ferestrei;
	glutCreateWindow("Plants Vs Zombies OpenGL");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();

	Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
	glutMouseFunc(UseMouse);			//	Activarea utilizarii mouseului;
	glutCloseFunc(Cleanup);				//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}

