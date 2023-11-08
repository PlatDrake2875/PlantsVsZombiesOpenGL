//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul III - 03_02_Shader.frag |
// ======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core
#define RED 1
#define GREEN 2
#define BLUE 3
#define FIELD_GREEN 4
#define WHITE 5
#define BLACK 6
#define MAGENTA 7
#define YELLOW 8
#define CYAN 9
#define ORANGE 10
#define LIGHT_GRAY 11
#define DARK_GREEN 12

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

//	Variabilele uniforme;
uniform int codCol;

//	Actualizeaza culoarea in functie de codCol;
void main(void)
{
  switch (codCol)
  {
	case RED: 
		out_Color = vec4(1.0, 0.0, 0.0, 1.0);
		break;
	case GREEN: 
		out_Color=vec4 (0.0, 1.0, 0.0, 1.0);
		break;
	case BLUE:
		out_Color=vec4 (0.0, 0.0, 1.0, 1.0);
		break;
	case FIELD_GREEN:
		out_Color = vec4 (0.51, 0.659, 0.349, 1.0);
		break;
	case WHITE:
		out_Color = vec4 (1.0, 1.0, 1.0, 1.0);
		break;
	case BLACK:
		out_Color = vec4 (0.0, 0.0, 0.0, 1.0);
		break;
	case MAGENTA:
		out_Color = vec4 (1.0, 0.0, 1.0, 1.0);
		break;
	case YELLOW:
		out_Color = vec4 (1.0, 1.0, 0.0, 1.0);
		break;
	case CYAN:
		out_Color = vec4 (0.0, 1.0, 1.0, 1.0);
		break;
	case ORANGE:
		out_Color = vec4 (1.0, 0.5, 0.0, 1.0);
		break;
	case LIGHT_GRAY:
		out_Color = vec4 (0.7, 0.7, 0.7, 1.0);
		break;
	case DARK_GREEN:
		out_Color = vec4(0.004, 0.388, 0.063, 1.0);
		break;
	default:
		break;
  };
}
 