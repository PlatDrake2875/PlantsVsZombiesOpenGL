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
#include "Collisions.h"
#include "Placing.h"


using namespace std;

//  Identificatorii obiectelor de tip OpenGL;
GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId;

//	Variabile catre matricile de transformare;
glm::mat4 myMatrix;

const int NMax = 100000;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;
//	Variabile pentru proiectia ortogonala;
float xMin = 0.0f, xMax = 1000.0f, yMin = 0.0f, yMax = 600.0f;
//	Variabile pentru deplasarea pe axa Ox si pentru rotatie;
float i = 0.0, alpha = 0.0, step = 0.3, beta = 0.002, angle = 0;
Collisions collision_handler;

POINT mousePosition;

GLuint pressedNumber = 0;



void setSquaresCenters() {
	Shared::squares.clear();
	float xBL = 100.f, yBL = 25.f, offset = 25.f;
	for (int i = 0; i < 9; ++i) {
		Shared::squares.push_back({ xBL + 50.f + 100 * (i % 3) + (i % 3) * offset, yBL + 50.f + 100 * (i / 3) + (i / 3) * offset });
	}
}

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

void moveAll() {
	// move all the zombies
	auto it = Shared::zombies.begin();
	while (it != Shared::zombies.end()) {
		(*it)->move();
		//std::cout << (*it)->getPosition().y << '\n';
		if (!(*it)->isActive()) {
			delete* it;
			it = Shared::zombies.erase(it);
		}
		else
			++it;
	}

	auto it1 = Shared::bullets.begin();
	while (it1 != Shared::bullets.end()) {
		(*it1)->move();
		if (!(*it1)->isActive()) {
			delete* it1;
			it1 = Shared::bullets.erase(it1);
		}
		else
			++it1;
	}

	glutPostRedisplay();
}

void drawAll() {
	for (auto zombie : Shared::zombies)
		zombie->draw();

	for (auto bullet : Shared::bullets)
		bullet->draw();
}

bool isMousePressed = false;

//	Functie ce modifica deplasarea dreptunghiurilor in functie de apasarea butoanelor de pe mouse;
void UseMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:			//	CLICK stanga => dreptunghiurile se misca spre stanga;
		if (state == GLUT_DOWN) {
			mousePosition.x = x;
			mousePosition.y = 600 - y;
			isMousePressed = true;
		}
	default:
		break;
	}
}


void ProcessPlacingKeys(unsigned char key, int x, int y)
{
	switch (key) {		//	Procesarea tastelor 'l' si 'r' modifica unghiul de rotire al patratului;
	case '1':
		pressedNumber = 1;
		break;
	case '2':
		pressedNumber = 2;
		break;
	case '3':
		pressedNumber = 3;
		break;
	case '4':
		pressedNumber = 4;
		break;
	default:
		pressedNumber = 0;
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
void plant(GLfloat Vertices[], int& poz, float x, float y) {
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

// Punem in Vertices punctele care deseneaza un zombie centrat in (0, 0) (mai intai partea exterioara, apoi cea interioara)
void zombie(GLfloat Vertices[], int& poz, float rBig = 40.f, float rSmall = 25.f) {
	const int n = 6;

	// Punctele pentru exterior
	for (int k = 0; k < n; ++k) {
		float angle = 2 * k * Shared::PI / n;
		GLfloat x = rBig * cos(angle), y = rBig * sin(angle);
		Vertices[++poz] = x;
		Vertices[++poz] = y;
		Vertices[++poz] = 0.0f;
		Vertices[++poz] = 1.0f;
	}

	// Punctele pentru interior
	for (int k = 0; k < n; ++k) {
		float angle = 2 * k * Shared::PI / n;
		GLfloat x = rSmall * cos(angle), y = rSmall * sin(angle);
		Vertices[++poz] = x;
		Vertices[++poz] = y;
		Vertices[++poz] = 1.0f; // 1.0f pentru a fi desenat deasupra
		Vertices[++poz] = 1.0f;
	}
}

// Desenam o stea cu 5 colturi
// x, y - coordonatele stanga jos ale chenarului in care se va desena steaua
// actualizam pozitia in vectorul Vertices
void star(GLfloat Vertices[], int& poz, GLfloat x, GLfloat y, GLfloat scale = 2.2f) {
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


void square(GLfloat Vertices[], int& poz, GLfloat x, GLfloat y, GLfloat scale = 1.0f)
{
	// Coltul stanga jos
	Vertices[++poz] = x;
	Vertices[++poz] = y;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	// Coltul dreapta jos
	Vertices[++poz] = x + 100.0f * scale;
	Vertices[++poz] = y;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	// Coltul dreapta sus
	Vertices[++poz] = x + 100.0f * scale;
	Vertices[++poz] = y + 100.0f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	// Coltul stanga sus
	Vertices[++poz] = x;
	Vertices[++poz] = y + 100.0f * scale;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;
}

void rectangle(GLfloat Vertices[], int& poz)
{

	// Coltul stanga jos
	Vertices[++poz] = 20.0f;
	Vertices[++poz] = 25.0f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	//// Coltul dreapta jos
	Vertices[++poz] = 80.0f;
	Vertices[++poz] = 25.0f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	//// Coltul dreapta sus
	Vertices[++poz] = 80.0f;
	Vertices[++poz] = 375.0f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;

	//// Coltul stanga sus
	Vertices[++poz] = 20.0f;
	Vertices[++poz] = 375.0f;
	Vertices[++poz] = 0.0f;
	Vertices[++poz] = 1.0f;
}

//  Se initializeaza
//  un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	// GLfloat Vertices[144 + 16 + 16 * 4 + 16 * 3 + 28 * 4 +40*10 + 40*6] = { 0 };
	GLfloat Vertices[NMax] = { 0 };

	// Culorile axelor
	GLfloat Colors[16] = {
		0.0f, 0.0f, 0.0f, 1.0f,	// Negru
		1.0f, 0.0f, 0.0f, 1.0f,	// Rosu
		0.0f, 1.0f, 0.0f, 1.0f,	// Verde
		0.0f, 0.0f, 1.0f, 1.0f	// Albastru
	};

	int poz = -1;

	float xBL = 100.0f, yBL = 25.0f, offset = 25.0f;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			square(Vertices, poz, xBL + i * (100 + offset), yBL + j * (100 + offset));
		}
	}

	rectangle(Vertices, poz);

	// Kenarele pentru plante
	yBL = 475.f;
	for (int i = 0; i < 4;i++) {
		square(Vertices, poz, xBL + i * (100 + offset), yBL);
	}

	// Patratele pentru vieti
	offset = 25.f;
	for (int i = 0; i < 3; i++) {
		square(Vertices, poz, 625.0f + i * (50 + offset), 500.0f, 0.5f);
	}

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

	// Asezarea obiectelor dinamice in Vertices
	// Planta generica - 7 puncte
	Plant::setOffset((poz + 1) / 4);
	plant(Vertices, poz, -50.f, -50.f); // planta centrata in (0, 0) ca sa o pot pune unde vreau din translatii

	// Zombie - 12 puncte (mai intai partea exterioara, apoi cea interioara
	Zombie::setOffset((poz + 1) / 4);
	zombie(Vertices, poz);

	// Bullet - 10 puncte (o stea)
	Bullet::setOffset((poz + 1) / 4);
	star(Vertices, poz, -30.f, -30.f, 5.f);


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

int getPlantColor(int pressedNumber) {
	switch (pressedNumber) {
	case 1:
		return Colors::MAGENTA;
	case 2:
		return Colors::YELLOW;
	case 3:
		return Colors::CYAN;
	case 4:
		return Colors::ORANGE;
	default:
		return Colors::DEFAULT;
	}
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;

	Shared::resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);

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
	glLineWidth(1.f);
	codCol = WHITE;
	glUniform1i(Shared::codColLocation, codCol);
	switch (pressedNumber) {
	case 1:
		glLineWidth(2.5f);
		glDrawArrays(GL_LINE_LOOP, 40, 4);
		break;
	case 2:
		glLineWidth(2.5f);
		glDrawArrays(GL_LINE_LOOP, 44, 4);
		break;
	case 3:
		glLineWidth(2.5f);
		glDrawArrays(GL_LINE_LOOP, 48, 4);
		break;
	case 4:
		glLineWidth(2.5f);
		glDrawArrays(GL_LINE_LOOP, 52, 4);
		break;

	}

	glLineWidth(1.f);
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
	for (int i = 0; i < 10;i++)
		glDrawArrays(GL_POLYGON, poz + 10 * i, 10);

	// desenam stelele - banii acumulati
	poz = 196;
	for (int i = 0; i < 6;i++)
		glDrawArrays(GL_POLYGON, poz + 10 * i, 10);



	glutKeyboardFunc(ProcessPlacingKeys);

	glutMouseFunc(UseMouse);

	setSquaresCenters();

	int plantColor = getPlantColor(pressedNumber);

	cout << "Plant color: " << plantColor << '\n';

	auto it = Shared::squares.begin();

	while (it != Shared::squares.end()) {
		//std::cout << (*it).x << " " << (*it).y << '\n';
		if (isMousePressed && mousePosition.x >= (*it).x - 50.f && mousePosition.x <= (*it).x + 50.f && mousePosition.y >= (*it).y - 50.f && mousePosition.y <= (*it).y + 50.f) {
			//std::cout << "Pressed " << pressedNumber << '\n';
			//cout << "Mouse position: " << mousePosition.x << " " << mousePosition.y << '\n';
			std::cout << (*it).x << " " << (*it).y << '\n';

			Plant* pl = new Plant(plantColor, (*it).x, (*it).y);
			//pl.draw();
			Placing::addPlant(pl);
			Shared::usedSquares.push_back(*it);
			//pressedNumber = 0;
		}
		++it;
	}

	auto it2 = Shared::plants.begin();

	cout << "Plants size: " << Shared::plants.size() << '\n';

	while (it2 != Shared::plants.end()) {
		Plant p = **it2;
		(*it2)->toString();
		if (p.getColor() > 0)
			p.draw();
		++it2;
	}

	//Bullet b(YELLOW, 0.f, 0.f);
	//b.draw();

	// Test Zombie spawn
	//Zombie z1(YELLOW, 500.f, 75.f);
	//z1.draw();

	collision_handler.ZombieBullet();
	drawAll();

	glutSwapBuffers();	//	Inlocuieste imaginea deseneata in fereastra cu cea randata; 
	glFlush();	//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	// Stabilim dimensiunile ferestrei
	Shared::winWidth = 1000.f;
	Shared::winHeight = 600.f;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);					//	Se folosesc 2 buffere (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutInitWindowSize(Shared::winWidth, Shared::winHeight);									//  Dimensiunea ferestrei;
	glutCreateWindow("Plants Vs Zombies OpenGL");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();

	Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 

	// TESTING PURPOSES
	Zombie* z = new Zombie(YELLOW, 1100.f, 75.f);
	Shared::zombies.push_back(z);
	Bullet* b = new Bullet(YELLOW, 100.f, 75.f);
	Shared::bullets.push_back(b);

	glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
	glutIdleFunc(moveAll);
	glutMouseFunc(UseMouse);			//	Activarea utilizarii mouseului;
	glutCloseFunc(Cleanup);				//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}

