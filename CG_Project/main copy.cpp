// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <iostream>
// #include <vector>

// // Constants
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;
// const float PI = 3.14159265358979323846f;

// // Function prototypes
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void processInput(GLFWwindow* window);
// void drawWheel(float x, float y, float radius, int numSegments, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram);
// void drawCircle(float x, float y, float radius, int numSegments, glm::vec3 color, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram);
// void drawFilledAnnulus(float x, float y, float outerRadius, float innerRadius, int numSegments, glm::vec3 color, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram);
// void drawFrame(float x1, float y1, float x2, float y2, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram);
// void drawSeat(float x, float y, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram);
// void drawSteering(float x, float y, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram);
// void drawPedals(float x, float y, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram);

// // Shader sources
// const char* vertexShaderSource = R"(
//     #version 330 core
//     layout(location = 0) in vec2 aPos;

//     void main()
//     {
//         gl_Position = vec4(aPos, 0.0, 1.0);
//     }
// )";

// const char* fragmentShaderSource = R"(
//     #version 330 core
//     out vec4 FragColor;

//     uniform vec3 color;

//     void main()
//     {
//         FragColor = vec4(color, 1.0);
//     }
// )";

// int main()
// {
//     // Initialize GLFW
//     if (!glfwInit())
//     {
//         std::cerr << "Failed to initialize GLFW" << std::endl;
//         return -1;
//     }

//     // Set GLFW window properties
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     // Create a GLFWwindow object
//     GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Bike", nullptr, nullptr);
//     if (window == nullptr)
//     {
//         std::cerr << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);

//     // Initialize GLAD
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

//     // Set viewport
//     glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

//     // Register framebuffer size callback
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // Build and compile the shader program
//     unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//     glCompileShader(vertexShader);
//     // Check for compile-time errors
//     int success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
//         std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }

//     unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//     glCompileShader(fragmentShader);
//     // Check for compile-time errors
//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success)
//     {
//         glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
//         std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }

//     unsigned int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
//     // Check for linking errors
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success)
//     {
//         glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
//         std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//     }

//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     // Setup buffers
//     unsigned int VAO, VBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     // Render loop
//     while (!glfwWindowShouldClose(window))
//     {
//         // Process input
//         processInput(window);

//         // Clear the screen
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Use the shader program
//         glUseProgram(shaderProgram);

//         // Draw first wheel
//         float wheelRadius = 0.3f;
//         float gap = 0.8f; // Increased gap between wheels
//         drawWheel(-gap / 2.0f, 0.0f, wheelRadius, 36, VAO, VBO, shaderProgram);

//         // Draw second wheel
//         drawWheel(gap / 2.0f, 0.0f, wheelRadius, 36, VAO, VBO, shaderProgram);

//         // Draw the bike frame
//         drawFrame(-gap / 2.0f, 0.0f, gap / 2.0f, 0.0f, VAO, VBO, shaderProgram);

//         // Draw the seat
//         drawSeat(0.0f, 0.3f, VAO, VBO, shaderProgram);

//         // Draw the steering wheel
//         drawSteering(gap / 2.0f, 0.4f, VAO, VBO, shaderProgram);

//         // Draw the pedals
//         drawPedals(0.0f, -0.1f, VAO, VBO, shaderProgram);

//         // Swap buffers and poll IO events
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // Clean up and exit
//     glfwTerminate();
//     return 0;
// }

// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }

// void processInput(GLFWwindow* window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// void drawWheel(float x, float y, float radius, int numSegments, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram)
// {
//     float tireThickness = 0.05f;
    
//     // Draw the tire as a filled annulus with black color
//     drawFilledAnnulus(x, y, radius + tireThickness, radius, numSegments, glm::vec3(0.0f, 0.0f, 0.0f), VAO, VBO, shaderProgram);

//     // Draw the spokes and inner circle with white color
//     drawCircle(x, y, radius, numSegments, glm::vec3(1.0f, 1.0f, 1.0f), VAO, VBO, shaderProgram);

//     std::vector<glm::vec2> vertices(numSegments + 2); // +2 for the center point and to complete the loop

//     // Center point
//     vertices[0] = glm::vec2(x, y);

//     // Outer circle points
//     for (int i = 1; i <= numSegments; ++i)
//     {
//         float angle = 2.0f * PI * float(i - 1) / float(numSegments);
//         vertices[i] = glm::vec2(radius * cosf(angle) + x, radius * sinf(angle) + y);
//     }
//     // Closing the loop
//     vertices[numSegments + 1] = vertices[1];

//     // Bind and set vertex buffer(s) and configure vertex attributes
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Set the color uniform to white for the spokes
//     int vertexColorLocation = glGetUniformLocation(shaderProgram, "color");
//     glUniform3fv(vertexColorLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

//     // Draw the spokes
//     for (int i = 1; i <= numSegments; ++i)
//     {
//         glm::vec2 spokeVertices[] = { vertices[0], vertices[i] };
//         glBufferData(GL_ARRAY_BUFFER, sizeof(spokeVertices), spokeVertices, GL_DYNAMIC_DRAW);
//         glDrawArrays(GL_LINES, 0, 2);
//     }

//     // Unbind the VAO
//     glBindVertexArray(0);
// }

// void drawCircle(float x, float y, float radius, int numSegments, glm::vec3 color, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram)
// {
//     std::vector<glm::vec2> vertices(numSegments);

//     for (int i = 0; i < numSegments; ++i)
//     {
//         float angle = 2.0f * PI * float(i) / float(numSegments);
//         vertices[i] = glm::vec2(radius * cosf(angle) + x, radius * sinf(angle) + y);
//     }

//     // Bind and set vertex buffer(s) and configure vertex attributes
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Set the color uniform
//     int vertexColorLocation = glGetUniformLocation(shaderProgram, "color");
//     glUniform3fv(vertexColorLocation, 1, glm::value_ptr(color));

//     // Draw the circle
//     glDrawArrays(GL_LINE_LOOP, 0, numSegments);

//     // Unbind the VAO
//     glBindVertexArray(0);
// }

// void drawFilledAnnulus(float x, float y, float outerRadius, float innerRadius, int numSegments, glm::vec3 color, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram)
// {
//     std::vector<glm::vec2> vertices((numSegments + 1) * 2); // Each segment has two vertices, one for inner and one for outer

//     // Generate vertices for the annulus
//     for (int i = 0; i <= numSegments; ++i)
//     {
//         float angle = 2.0f * PI * float(i) / float(numSegments);
//         vertices[2 * i] = glm::vec2(outerRadius * cosf(angle) + x, outerRadius * sinf(angle) + y); // Outer circle vertex
//         vertices[2 * i + 1] = glm::vec2(innerRadius * cosf(angle) + x, innerRadius * sinf(angle) + y); // Inner circle vertex
//     }

//     // Bind and set vertex buffer(s) and configure vertex attributes
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Set the color uniform
//     int vertexColorLocation = glGetUniformLocation(shaderProgram, "color");
//     glUniform3fv(vertexColorLocation, 1, glm::value_ptr(color));

//     // Draw the annulus as a triangle strip
//     glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());

//     // Unbind the VAO
//     glBindVertexArray(0);
// }

// void drawFrame(float x1, float y1, float x2, float y2, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram)
// {
//     float topY = 0.4f; // Y coordinate for the top point of the frame
//     float seatY = 0.3f; // Y coordinate for the seat
//     float pedalY = -0.1f; // Y coordinate for the pedals

//     glm::vec2 vertices[] = {
//         glm::vec2(x1, y1), // Left wheel hub
//         glm::vec2(x2, y2), // Right wheel hub
//         glm::vec2(0.0f, topY), // Top point of the frame
//         glm::vec2(x1, y1), // Left wheel hub
//         glm::vec2(0.0f, seatY), // Seat
//         glm::vec2(x2, y2), // Right wheel hub
//         glm::vec2(0.0f, pedalY), // Pedals
//         glm::vec2(x1, y1), // Left wheel hub
//     };

//     // Bind and set vertex buffer(s) and configure vertex attributes
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Set the color uniform to navy
//     int vertexColorLocation = glGetUniformLocation(shaderProgram, "color");
//     glUniform3fv(vertexColorLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.5f)));

//     // Draw the frame
//     glDrawArrays(GL_LINE_STRIP, 0, 8);

//     // Unbind the VAO
//     glBindVertexArray(0);
// }

// void drawSeat(float x, float y, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram)
// {
//     glm::vec2 vertices[] = {
//         glm::vec2(x - 0.05f, y + 0.05f), // Left
//         glm::vec2(x + 0.05f, y + 0.05f), // Right
//         glm::vec2(x, y) // Bottom
//     };

//     // Bind and set vertex buffer(s) and configure vertex attributes
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Set the color uniform to black
//     int vertexColorLocation = glGetUniformLocation(shaderProgram, "color");
//     glUniform3fv(vertexColorLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));

//     // Draw the seat
//     glDrawArrays(GL_TRIANGLES, 0, 3);

//     // Unbind the VAO
//     glBindVertexArray(0);
// }

// void drawSteering(float x, float y, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram)
// {
//     glm::vec2 vertices[] = {
//         glm::vec2(x, y), // Bottom
//         glm::vec2(x, y + 0.1f), // Top
//         glm::vec2(x - 0.1f, y + 0.1f), // Left handle
//         glm::vec2(x + 0.1f, y + 0.1f) // Right handle
//     };

//     // Bind and set vertex buffer(s) and configure vertex attributes
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Set the color uniform to black
//     int vertexColorLocation = glGetUniformLocation(shaderProgram, "color");
//     glUniform3fv(vertexColorLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));

//     // Draw the steering wheel
//     glDrawArrays(GL_LINES, 0, 2); // Steering rod
//     glDrawArrays(GL_LINES, 2, 2); // Left handle
//     glDrawArrays(GL_LINES, 2, 4); // Right handle

//     // Unbind the VAO
//     glBindVertexArray(0);
// }

// void drawPedals(float x, float y, unsigned int &VAO, unsigned int &VBO, unsigned int shaderProgram)
// {
//     glm::vec2 vertices[] = {
//         glm::vec2(x - 0.05f, y), // Left pedal
//         glm::vec2(x + 0.05f, y), // Right pedal
//         glm::vec2(x, y - 0.05f), // Bottom pedal
//         glm::vec2(x, y + 0.05f) // Top pedal
//     };

//     // Bind and set vertex buffer(s) and configure vertex attributes
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Set the color uniform to black
//     int vertexColorLocation = glGetUniformLocation(shaderProgram, "color");
//     glUniform3fv(vertexColorLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));

//     // Draw the pedals
//     glDrawArrays(GL_LINES, 0, 2); // Horizontal pedal
//     glDrawArrays(GL_LINES, 2, 2); // Vertical pedal

//     // Unbind the VAO
//     glBindVertexArray(0);
// }
