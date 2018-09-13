#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// ---- ROOF -----
//dach powinien byæ dorobiony z szeœcianu (ten sam vs), ale inny fs
// kolor amarantowy: 	(229, 43, 80)
// texture: not included

//0.0f, 1.0f, 0.0f,	 0.898f, 0.1686f, 0.3137f,	 1.0f, 0.0f  //8
unsigned int roof_indices[] = {
	3, 0, 7,
	0, 7, 4,
	3, 0, 8,
	0, 4, 8,
	4, 7, 8,
	7, 3, 8
};

// ----- PIPE -----
float pipe_vertices[] = {
	//coordinates			//color
	0.0f, 0.25f, -0.5f,		0.0f, 0.0f, 0.0f, // 0 - œrodek szeœcianu
	-0.025f, 0.3f, -0.5f,	0.0f, 0.0f, 0.0f, // 1
	0.025f, 0.3f, -0.5f,	0.0f, 0.0f, 0.0f, // 2
	0.043f, 0.25f, -0.5f,	0.0f, 0.0f, 0.0f, // 3
	0.025f, 0.207f, -0.5f,	0.0f, 0.0f, 0.0f, // 4
	-0.025f, 0.207f, -0.5f,	0.0f, 0.0f, 0.0f, // 5
	-0.043f, 0.25f, -0.5f,	0.0f, 0.0f, 0.0f // 6
	,
	//pochylony heaxagon
	0.0f, 0.25f, -1.6f, 0.0f, 0.0f, 0.0f, // 7 - œrodek szeœcianu
	-0.025f, 0.3f, -1.6f, 0.0f, 0.0f, 0.0f, // 8
	0.025f, 0.3f, -1.6f, 0.0f, 0.0f, 0.0f, // 9
	0.043f, 0.25f, -1.6f, 0.0f, 0.0f, 0.0f, // 10
	0.025f, 0.207f, -1.5f, 0.0f, 0.0f, 0.0f, // 11
	-0.025f, 0.207f, -1.5f, 0.0f, 0.0f, 0.0f, // 12
	-0.043f, 0.25f, -1.6f, 0.0f, 0.0f, 0.0f // 13
	,
	//hexagon on the ground
	0.0f, -0.5f, -1.6f, 0.0f, 0.0f, 0.0f, // 14 - œrodek szeœcianu
	-0.025f, -0.5f, -1.6f, 0.0f, 0.0f, 0.0f, // 15
	0.025f, -0.5f, -1.6f, 0.0f, 0.0f, 0.0f, // 16
	0.043f, -0.5f, -1.6f, 0.0f, 0.0f, 0.0f, // 17
	0.025f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f, // 18
	-0.025f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f, // 19
	-0.043f, -0.5f, -1.6f, 0.0f, 0.0f, 0.0f // 20


};

unsigned int pipe_indices[] = {
	//first heaxagon
	0, 1, 2,
	0, 2, 3,
	0, 3, 4,
	0, 4, 5,
	0, 5, 6,
	0, 6, 1
	,
	//second hexagon
	7, 8, 9,
	7, 9, 10,
	7, 10, 11,
	7, 11, 12,
	7, 12, 13,
	7, 13, 8
	,
	// connection 1 - 2
	1, 2, 8,
	2, 9, 8,
	2, 3, 9,
	3, 10, 9,
	3, 4, 10,
	4, 11, 10,
	4, 5, 11,
	5, 12, 11,
	5, 6, 12,
	6, 13, 12,
	6, 1, 13,
	1, 8, 13
	,
	// third hexagon - on the ground
	14, 15, 16,
	14, 16, 17,
	14, 17, 18,
	14, 18, 19,
	14, 19, 20,
	14, 20, 15
	,
	// connection 2 - 3
	15, 16, 8,
	16, 9, 8,
	16, 17, 9,
	17, 10, 9,
	17, 18, 10,
	18, 11, 10,
	18, 19, 11,
	19, 12, 11,
	19, 20, 12,
	20, 13, 12,
	20, 15, 13,
	15, 8, 13

};

// ----- CYLINDER -----
float cylinder[] = {
	// coordinates			// texture
/*	//hexagon on the ground
	0.0f, -0.5f, -1.55f,	0.5f, 0.3f, // 0 - œrodek szeœcianu
	-0.125f, -0.5f, -1.9f,	0.5f, 0.0f, // 1
	0.125f, -0.5f, -1.9f,	0.8f, 0.2f, // 2
	0.443f, -0.5f, -1.55f,	0.8f, 0.4f, // 3
	0.125f, -0.5f, -1.2f,	0.5f, 0.6f, // 4
	-0.125f, -0.5f, -1.2f,	0.2f, 0.4f, // 5
	-0.443f, -0.5f, -1.55f,	0.2f, 0.2f// 6 */
	//hexagon on the ground
	0.0f, -0.5f, -1.55f,	0.5f, 0.3f, // 0 - œrodek szeœcianu
	-0.125f, -0.5f, -1.9f,	0.62f, 0.36f, // 1
	0.125f, -0.5f, -1.9f,	0.5f, 0.44f, // 2
	0.443f, -0.5f, -1.55f, 0.38f, 0.36f, // 3
	0.125f, -0.5f, -1.2f,	0.38f, 0.28f, // 4
	-0.125f, -0.5f, -1.2f, 0.5f, 0.2f, // 5
	-0.443f, -0.5f, -1.55f, 0.62f, 0.28f  // 6
	,
	//hexagon higher
	0.0f, -0.1f, -1.55f,	0.5f, 0.3f,// 7 - œrodek szeœcianu
	-0.125f, -0.1f, -1.9f,	0.8f, 0.4f, // 8
	0.125f, -0.1f, -1.9f,	0.5f, 0.6f, // 9
	0.443f, -0.1f, -1.55f,	0.2f, 0.4f,// 10
	0.125f, -0.1f, -1.2f,	0.2f, 0.2f, // 11
	-0.125f, -0.1f, -1.2f,	0.5f, 0.0f, // 12
	-0.443f, -0.1f, -1.55f, 0.8f, 0.2f, // 13
	-0.443f, -0.1f, -1.55f, 0.8f, 0.2f // 14

};

unsigned int cylinder_indices[] = {
	//first heaxagon
	0, 2, 1,
	0, 3, 2,
	0, 4, 3,
	0, 5, 4,
	0, 6, 5,
	0, 1, 6
	,
	//second hexagon
	7, 8, 9,
	7, 9, 10,
	7, 10, 11,
	7, 11, 12,
	7, 12, 13,
	7, 13, 8
	,
	// connection 1 - 2
	1, 2, 8,
	2, 9, 8,
	2, 3, 9,
	3, 10, 9,
	3, 4, 10,
	4, 11, 10,
	5 , 4, 11, //
	5, 12, 11,
	5, 6, 12,
	6, 13, 12,
	6, 1, 13,
	8, 1, 14
	
};


// Set up vertex data 
GLfloat house_vertices[] = {
	// coordinates			// color					// texture
	0.5f, 0.5f, 0.5f,		0.898f, 0.1686f, 0.3137f,	1.0f, 0.0f, //0
	0.5f, -0.5f, 0.5f,		0.898f, 0.1686f, 0.3137f,	0.0f, 0.0f, //1
	-0.5f, -0.5f, 0.5f,		0.898f, 0.1686f, 0.3137f,	0.0f, 1.0f, //2
	-0.5f, 0.5f, 0.5f,		0.898f, 0.1686f, 0.3137f,	1.0f, 1.0f, //3

	0.5f, 0.5f, -0.5f,		0.898f, 0.1686f, 0.3137f,	1.0f, 1.0f, //4
	0.5f, -0.5f, -0.5f,		0.898f, 0.1686f, 0.3137f,	0.0f, 1.0f, //5
	-0.5f, -0.5f, -0.5f,	0.898f, 0.1686f, 0.3137f,	0.0f, 0.0f, //6
	-0.5f, 0.5f, -0.5f,		0.898f, 0.1686f, 0.3137f,	1.0f, 0.0f,  //7

	0.0f, 1.0f, 0.0f,		0.898f, 0.1686f, 0.3137f,	1.0f, 0.0f  //8
};

GLuint house_indices[] = {
	0, 1, 3,
	1, 2, 3,
	4, 7, 5,
	5, 7, 6,
	0, 4, 5,
	0, 5, 1,
	0, 7, 4,
	0, 3, 7,
	6, 3, 7,
	6, 2, 3,
	1, 6, 5,
	1, 2, 6
};

GLfloat wings_vertices[] = {
	/*	0.5f, 0.25f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //0
	0.5f, -0.4f, -0.15f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //1
	0.5f, -0.4f, 0.15f,		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //2
	0.8f, 0.25f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //3
	0.8f, -0.4f, -0.15f,	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //4
	0.8f, -0.4f, 0.15,		0.0f, 0.0f, 1.0f, 0.0f, 1.0f //5 */
	// coordinates			// color			// texture
	0.0f, 0.25f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //0
	-0.15f, -0.4f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //1
	0.15f, -0.4f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //2
	0.0f, 0.25f, -0.8f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //3
	-0.15f, -0.4f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //4
	0.15f, -0.4f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f //5
	,
	-0.15f, 0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //6
	0.15f, 0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //7
	-0.15f, 0.9f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //8
	0.15f, 0.9f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f //9
	,
	-0.65f, 0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //10
	-0.65f, 0.4f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //11
	-0.65f, 0.1f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //12
	-0.65f, 0.4f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f //13
	,
	0.65f, 0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //14
	0.65f, 0.4f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //15
	0.65f, 0.1f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //16
	0.65f, 0.4f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f //17
};

GLuint wings_indices[] = {
	0, 1, 2,
	3, 4, 5,
	0, 3, 4,
	0, 1, 4,
	4, 1, 2,
	4, 5, 2,
	0, 3, 5,
	0, 5, 2
	,
	0, 6, 7,
	3, 8, 9,
	0, 3, 8,
	0, 6, 8,
	8, 6, 7,
	8, 9, 7,
	0, 3, 9,
	0, 9, 7
	,
	0, 10, 11,
	3, 12, 13,
	0, 3, 12,
	0, 10, 12,
	12, 10, 11,
	12, 13, 11,
	0, 3, 13,
	0, 13, 11
	,
	0, 14, 15,
	3, 16, 17,
	0, 3, 16,
	0, 14, 16,
	16, 14, 15,
	16, 17, 15,
	0, 3, 17,
	0, 17, 15
};

GLfloat ground_vertices[] = {
	// first square
	-1.0f, -0.5f, -2.4f,	3.0f, 0.0f,
	-1.0f, -0.5f, 1.0f,		0.0f, 0.0f,
	1.0f, -0.5f, 1.0f,		0.0f, 3.0f,
	1.0f, -0.5f, -2.4f,		3.0f, 3.0f,
	//second sqare
	-1.0f, -0.6f, -2.4f,	3.0f, 3.0f,
	-1.0f, -0.6f, 1.0f,		0.0f, 3.0f,
	1.0f, -0.6f, 1.0f,		0.0f, 0.0f,
	1.0f, -0.6f, -2.4f,		3.0f, 0.0f
};

GLuint ground_indices[] = {
	0, 1, 3,
	1, 2, 3,
	4, 7, 5,
	5, 7, 6,
	0, 4, 5,
	0, 5, 1,
	0, 7, 4,
	0, 3, 7,
	6, 3, 7,
	6, 2, 3,
	1, 6, 5,
	1, 2, 6
};

glm::vec3 getCrossProduct(glm::vec3 a, glm::vec3 b) {
	glm::vec3 result(a.x * b.x, a.y *b.y, a.z * b.z);
	return result;
}

glm::vec3 getCrossProduct(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	glm::vec3 result(a.x * b.x * c.x, a.y *b.y *c.y, a.z * b.z *c.z);
	return result;
}

glm::vec3 getCrossProduct(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
	glm::vec3 result(a.x * b.x * c.x *d.x, a.y *b.y *c.y *d.y, a.z * b.z *c.z *d.z);
	return result;
}

glm::vec3 getCrossProduct(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 e, glm::vec3 f) {
	glm::vec3 result(a.x * b.x * c.x *d.x *e.x *f.x, a.y *b.y *c.y *d.y *e.y *f.y, a.z * b.z *c.z *d.z *e.z *f.z);
	return result;
}

GLfloat lenght(glm::vec3 a) {
	GLfloat n = a.x*a.x + a.y*a.y + a.z*a.z;
	n = sqrt(n);
	return n;
}


glm::vec3 getNormalToTrinagle(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	glm::vec3 v1(b.x - a.x, b.y - a.y, b.z - a.z);
	glm::vec3 v2(c.x - a.x, c.y - a.y, c.z - a.z);
	glm::vec3 N = getCrossProduct(v1, v2);
/*	float sin_alpha = length(N) / (length(v1) * length(v2));
	return normalize(N) * asin(sin_alpha); */ //is needed?
	return N;
}



void test() { // oh well, doesnt work and getting overflow probably
	/*
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,			0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
	*/
	glm::vec3 v0(-0.5f, -0.5f, -0.5f); //0
	glm::vec3 v1(0.5f, -0.5f, -0.5f); //1
	glm::vec3 v2(0.5f, 0.5f, -0.5f); //2
	glm::vec3 v3(-0.5f, 0.5f, -0.5f); //3

	glm::vec3 v4(-0.5f, -0.5f, 0.5f); //4
	glm::vec3 v5(0.5f, -0.5f, 0.5f); //5
	glm::vec3 v6(0.5f, 0.5f, 0.5f); //6
	glm::vec3 v7(-0.5f, 0.5f, 0.5f); //7

	// ---- the walls ----- // have they be counter-clockawise orientated?
	// 0 - 1 - 2
	glm::vec3 n012 = getNormalToTrinagle(v0, v1, v2);
	// 0 - 2 - 3
	glm::vec3 n023 = getNormalToTrinagle(v0, v2, v3);
	// 2 - 6 - 3
	glm::vec3 n263 = getNormalToTrinagle(v2, v6, v3);
	// 3 - 6 - 7
	glm::vec3 n367 = getNormalToTrinagle(v3, v6, v7);
	// 5 - 1 - 0
	glm::vec3 n510 = getNormalToTrinagle(v5, v1, v0);
	// 0 - 4 - 5
	glm::vec3 n045 = getNormalToTrinagle(v0, v4, v5);
	// 1 - 6 - 2
	glm::vec3 n162 = getNormalToTrinagle(v1, v6, v2);
	// 1 - 5 - 6
	glm::vec3 n156 = getNormalToTrinagle(v1, v5, v6);
	// 0 - 3 - 7
	glm::vec3 n037 = getNormalToTrinagle(v0, v3, v7);
	// 0 - 7 - 4
	glm::vec3 n074 = getNormalToTrinagle(v0, v7, v4);
	// 4 - 6 - 5
	glm::vec3 n456 = getNormalToTrinagle(v4, v5, v6);
	// 4 - 7 - 6
	glm::vec3 n476 = getNormalToTrinagle(v4, v7, v6);

	std::cout << "Normals to triangles: " <<
		"(" << n012.x << ", " << n012.y << ", " << n012.z << ") " <<
		"(" << n023.x << ", " << n023.y << ", " << n023.z << ") " <<
		"(" << n263.x << ", " << n263.y << ", " << n263.z << ") " <<
		"(" << n367.x << ", " << n367.y << ", " << n367.z << ") " <<
		"(" << n510.x << ", " << n510.y << ", " << n510.z << ") " <<
		"(" << n045.x << ", " << n045.y << ", " << n045.z << ") " <<
		"(" << n162.x << ", " << n162.y << ", " << n162.z << ") " <<
		"(" << n156.x << ", " << n156.y << ", " << n156.z << ") " <<
		"(" << n037.x << ", " << n037.y << ", " << n037.z << ") " <<
		"(" << n074.x << ", " << n074.y << ", " << n074.z << ") " <<
		"(" << n456.x << ", " << n456.y << ", " << n456.z << ") " <<
		"(" << n476.x << ", " << n476.y << ", " << n476.z << ") " << std::endl;

	glm::vec3 pom;
	std::cout << "Normal to vertices nr: " << std::endl;
	//pom = getCrossProduct(n012, n023, n510, n045, n037, n074);
	//pom = normalize(n012 + n023 + n510 + n045 + n037 + n074);
	pom = (n012 + n023 + n510 + n045 + n037 + n074);
	std::cout << "0 :" << pom.x << " " << pom.y << " " << pom.z << std::endl;
	pom = getCrossProduct(n012, n510, n162, n156);
	std::cout << "1 :" << pom.x << " " << pom.y << " " << pom.z << std::endl;
	pom = getCrossProduct(n012, n023, n263, n162);
	std::cout << "2 :" << pom.x << " " << pom.y << " " << pom.z << std::endl;
	pom = getCrossProduct(n023, n263, n367, n037);
	std::cout << "3 :" << pom.x << " " << pom.y << " " << pom.z << std::endl;
}