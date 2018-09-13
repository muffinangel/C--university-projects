#define GLEW_STATIC
#include "vertices.h"
#include "shader_s.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLuint WIDTH = 800, HEIGHT = 600;

GLuint LoadMipmapTexture(GLuint texId, const char* fname);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
ostream& operator<<(ostream& os, const glm::mat4& mx);

GLfloat rot_speed = 0.01f;
GLfloat cameraPosY = 0.06f;
bool change_rotation = true;

void change_rot_speed(bool add);

void change_cameraPosY(bool add);

void change_rotation_direction();

enum additional_information {
	TEXT_AND_COL = 0,
	ONLY_TEXT = 1,
	ONLY_COLOR = 2
};

void setAttribThings(additional_information ad);

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 04", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);

		// Build, compile and link shader programs
		ShaderProgram theProgram("house.vs", "house.fs");
		ShaderProgram theWings("wings.vs", "wings.fs");
		ShaderProgram theRoof("house.vs", "roof.fs");
		ShaderProgram thePipe("pipe.vs", "pipe.fs");
		ShaderProgram theCylinder("cylinder.vs", "cylinder.fs");
		ShaderProgram theGround("ground.vs", "ground.fs");


		// 0 - cube
		// 1 - wings
		// 2 - roof
		// 3 - pipe
		// 4 - cylinder
		// 5 - ground
		GLuint VBO[6], EBO[6], VAO[6];
		glGenVertexArrays(6, VAO);
		glGenBuffers(6, VBO);
		glGenBuffers(6, EBO);

		// ---------------- cube part ------------------
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(house_vertices), house_vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(house_indices), house_indices, GL_STATIC_DRAW);
		setAttribThings(additional_information(TEXT_AND_COL));

		// ---------------- wings part -------------------
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(wings_vertices), wings_vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wings_indices), wings_indices, GL_STATIC_DRAW);
		setAttribThings(additional_information(TEXT_AND_COL));

		// ---------------- roof part ---------------------
		glBindVertexArray(VAO[2]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(house_vertices), house_vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(roof_indices), roof_indices, GL_STATIC_DRAW);
		setAttribThings(additional_information(TEXT_AND_COL));

		// ---------------- pipe part ----------------------
		glBindVertexArray(VAO[3]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pipe_vertices), pipe_vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pipe_indices), pipe_indices, GL_STATIC_DRAW);
		setAttribThings(additional_information(ONLY_COLOR));

		// ----------------- cylinder part ------------------
		glBindVertexArray(VAO[4]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cylinder), cylinder, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[4]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cylinder_indices), cylinder_indices, GL_STATIC_DRAW);
		setAttribThings(additional_information(ONLY_TEXT));

		// ------------------ ground part ----------------------
		glBindVertexArray(VAO[5]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ground_vertices), ground_vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[5]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ground_indices), ground_indices, GL_STATIC_DRAW);
		setAttribThings(additional_information(ONLY_TEXT));

		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// prepare textures
		GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "wood1.png");
		GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "rock.png");
		GLuint texture2 = LoadMipmapTexture(GL_TEXTURE2, "grass2.png");

		// vector of translation of a middle point of the wings
		glm::vec3 beg_wings_move(0.0f, 0.25f, -0.5f);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// camera/view transformation
			glm::mat4 camRot;
			glm::mat4 view;
			glm::mat4 projection;
			glm::vec3 cameraPos;
			glm::mat4 trans;

			trans = glm::mat4(1.0);
			static GLfloat rot_angle = 0.0f;
			rot_angle += rot_speed;
			if (rot_angle >= 360.0f)
				rot_angle -= 360.0f;

			camRot = glm::rotate(camRot, glm::radians(rot_angle), glm::vec3(0.0, 1.0, 0.0));
			cameraPos = glm::vec3(camRot * glm::vec4(0.6f, cameraPosY, -4.0f, 1.0f));
			view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);


			// ------------------ cube ------------------------------

			// Bind Textures using texture units
			glBindVertexArray(VAO[0]);
			// Draw our cube
			theProgram.Use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0);
			glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);

			// standard camera transformation
			GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
			GLint projLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

			
			glDrawElements(GL_TRIANGLES, _countof(house_indices), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// -------------------------- roof --------------------------
			glBindVertexArray(VAO[2]);
			// Draw our roof
			theRoof.Use();
			// standard camera transformation
			GLuint roof_transformLoc = glGetUniformLocation(theRoof.get_programID(), "transform");
			glUniformMatrix4fv(roof_transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			GLint roof_viewLoc = glGetUniformLocation(theRoof.get_programID(), "view");
			GLint roof_projLoc = glGetUniformLocation(theRoof.get_programID(), "projection");
			glUniformMatrix4fv(roof_viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(roof_projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glDrawElements(GL_TRIANGLES, _countof(roof_indices), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// ---------------------- pipe ---------------------------
			glBindVertexArray(VAO[3]);
			// Draw our roof
			thePipe.Use();
			// standard camera transformation
			GLuint pipe_transformLoc = glGetUniformLocation(thePipe.get_programID(), "transform");
			glUniformMatrix4fv(pipe_transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			GLint pipe_viewLoc = glGetUniformLocation(thePipe.get_programID(), "view");
			GLint pipe_projLoc = glGetUniformLocation(thePipe.get_programID(), "projection");
			glUniformMatrix4fv(pipe_viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(pipe_projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glDrawElements(GL_TRIANGLES, _countof(pipe_indices), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// ----- wings part ------

			// move the center of the wings to (0, 0, 0) and make reversed shift
			glm::mat4 wings_mov;
			wings_mov = glm::translate(wings_mov, beg_wings_move);
			static GLfloat rot_wings = 0.0f;
			wings_mov = glm::rotate(wings_mov, -glm::radians(rot_wings), glm::vec3(0.0f, 0.0f, 1.0f));
			wings_mov = glm::translate(wings_mov, -beg_wings_move);

			// check if the direction of rotation changed
			if (change_rotation ) {
				rot_wings += 0.01f;
				if (rot_wings >= 360.0f)
					rot_wings -= 360.0f;
			}
			else {
				rot_wings -= 0.01f;
				if (rot_wings <= 0.0f)
					rot_wings += 360.0f;
			}


			glBindVertexArray(VAO[1]);
			// Draw our wings
			theWings.Use();
			// Bind Textures using texture units
			glUniform1i(glGetUniformLocation(theWings.get_programID(), "Texture0"), 0);

			GLuint wings_transformLoc = glGetUniformLocation(theWings.get_programID(), "wings_transform");
			// normal matrix used to rotate other elements is multiplied by matrix of rotation of the wings - calculated above
			glUniformMatrix4fv(wings_transformLoc, 1, GL_FALSE, glm::value_ptr(trans * wings_mov));
			GLint wings_viewLoc = glGetUniformLocation(theWings.get_programID(), "wings_view");
			GLint wings_projLoc = glGetUniformLocation(theWings.get_programID(), "wings_projection");
			glUniformMatrix4fv(wings_viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(wings_projLoc, 1, GL_FALSE, glm::value_ptr(projection));

			glDrawElements(GL_TRIANGLES, _countof(wings_indices), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);


			// cylinder

			// matrxi of cylinder roration - analogous to matrix of wings rotation
			glm::vec3 cylinder_translation(0.0f, -0.5f, -1.55f);
			glm::mat4 cylinder_mov;
			cylinder_mov = glm::translate(cylinder_mov, cylinder_translation);
			static GLfloat rot_cylinder = 0.0f;
			cylinder_mov = glm::rotate(cylinder_mov, glm::radians(rot_cylinder), glm::vec3(0.0f, 1.0f, 0.0f));
			cylinder_mov = glm::translate(cylinder_mov, -cylinder_translation);

			// check if the direction of rotation changed
			if (change_rotation) {
				rot_cylinder += 0.01f;
				if (rot_cylinder >= 360.0f)
					rot_cylinder -= 360.0f;
			}
			else {
				rot_cylinder -= 0.01f;
				if (rot_cylinder <= -360.0f)
					rot_cylinder += 360.0f;
			}

			glBindVertexArray(VAO[4]);
			// Draw our cylinder
			theCylinder.Use();
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glUniform1i(glGetUniformLocation(theCylinder.get_programID(), "Texture1"), 1); // 1 there instead of 0
			GLuint cylinder_transformLoc = glGetUniformLocation(theCylinder.get_programID(), "transform");
			glUniformMatrix4fv(cylinder_transformLoc, 1, GL_FALSE, glm::value_ptr(trans * cylinder_mov));
			GLint cylinder_viewLoc = glGetUniformLocation(theCylinder.get_programID(), "view");
			GLint cylinder_projLoc = glGetUniformLocation(theCylinder.get_programID(), "projection");
			glUniformMatrix4fv(cylinder_viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(cylinder_projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glDrawElements(GL_TRIANGLES, _countof(cylinder), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);


			// ground
			glBindVertexArray(VAO[5]);
			theGround.Use();
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture2);
			glUniform1i(glGetUniformLocation(theGround.get_programID(), "Texture2"), 2);
			GLuint ground_transformLoc = glGetUniformLocation(theGround.get_programID(), "transform");
			glUniformMatrix4fv(roof_transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			GLint ground_viewLoc = glGetUniformLocation(theGround.get_programID(), "view");
			GLint ground_projLoc = glGetUniformLocation(theGround.get_programID(), "projection");
			glUniformMatrix4fv(ground_viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(ground_projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glDrawElements(GL_TRIANGLES, _countof(ground_indices), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}


		glDeleteVertexArrays(2, VAO);
		glDeleteBuffers(2, VBO);
		glDeleteBuffers(2, EBO);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	getchar();
	return 0;
}

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		change_rot_speed(true);
	else if (key == GLFW_KEY_LEFT  && action == GLFW_PRESS)
		change_rot_speed(false);
	else if (key == GLFW_KEY_UP  && action == GLFW_PRESS)
		change_cameraPosY(true);
	else if (key == GLFW_KEY_DOWN  && action == GLFW_PRESS)
		change_cameraPosY(false);
	else if (key == GLFW_KEY_R  && action == GLFW_PRESS)
		change_rotation_direction();
	
}

ostream& operator<<(ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
}


void setAttribThings(additional_information ad) {
	if (ad == TEXT_AND_COL) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}
	else if (ad == ONLY_TEXT) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	else {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(0);
}


void change_rot_speed(bool add) {
	if (add) rot_speed = 2 * rot_speed;
	else rot_speed = 0.5 * rot_speed;
	if (rot_speed >= 2 * 2 * 2 * 2 * 2 * 0.01)
		rot_speed = 2 * 2 * 2 * 2 * 2 * 0.01;
	else if (rot_speed <= 0.5 * 0.5 * 0.5 * 0.5 * 0.01)
		rot_speed = 0.5 * 0.5 * 0.5 * 0.5 * 0.01;
}

void change_cameraPosY(bool add) {
	if (add) cameraPosY += 0.1f;
	else cameraPosY -= 0.1f;
}

void change_rotation_direction() {
	if (change_rotation)  change_rotation = false;
	else  change_rotation = true;
}