// #include <GLFW/glfw3.h>


// #include <glm/glm.hpp>
// #include <glm/ext/matrix_clip_space.hpp>
// #include <glm/ext/matrix_transform.hpp>

// #include "Matrices.hpp"
// #include "controls.hpp"

// glm::vec3 position = glm::vec3(0,0,5);
// double xpos, ypos;
// float angleH = 3.14f, angleV = 0.0f, initFoV = 45.0f;
// float speed = 3.0f;
// float mouseSpeed = 0.0005f;

// void computeMatricesFromInput(GLFWwindow* window)
// {
// 	static double lastTime = glfwGetTime();

// 	double currentTime = glfwGetTime();
// 	float deltaTime = lastTime - currentTime;

// 	glfwGetCursorPos(window, &xpos, &ypos);

// 	glfwSetCursorPos(window, scr_width/2, scr_height/2);


// 	angleH += mouseSpeed * float(scr_width/2-xpos);
// 	angleV += mouseSpeed * float(scr_height/2-ypos);

// 	glm::vec3 direction(
// 			glm::cos(angleV) * sin(angleH),
// 			glm::sin(angleV),
// 			glm::cos(angleV) * std::cos(angleH)
// 		);
// 	glm::vec3 right(
// 			glm::sin(angleH - 3.14f/2.0f),
// 			0,
// 			glm::cos(angleH - 3.14f/2.0f)
// 		);


// 	glm::vec3 up = glm::cross(right, direction);

// 	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
// 		position -= direction * deltaTime * speed;
// 	}
// 	// Move backward
// 	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
// 		position += direction * deltaTime * speed;
// 	}
// 	// Strafe right
// 	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
// 		position -= right * deltaTime * speed;
// 	}
// 	// Strafe left
// 	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
// 		position += right * deltaTime * speed;
// 	}
// 	float FoV = initFoV;
// 	projection = glm::perspective(
// 			glm::radians(FoV), 4.0f/3.0f, 0.1f, 100.f
// 		);
// 	view  = glm::lookAt(
// 			position,
// 			position + direction,
// 			up
// 		);

// 	lastTime = currentTime;
// }




