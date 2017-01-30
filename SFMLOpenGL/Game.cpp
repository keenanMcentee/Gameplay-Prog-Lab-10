#include <Game.h>

static bool flip;
const int numOfVertex = 8;
const int numOfTriangles = 36;
Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[8];
} Vertex;

Vertex vertex[numOfVertex];
GLubyte triangles[numOfTriangles];

/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
vsid,		//Vertex Shader ID
fsid,		//Fragment Shader ID
progID,		//Program ID
vao = 0,	//Vertex Array ID
vbo[1],		// Vertex Buffer ID
positionID, //Position ID
colorID,	// Color ID
to,			// Texture ID 1 to 32
textureID,	//Texture ID
texelID,	// Texel ID
mvpID;
//const string filename = "texture.tga";
//const string filename = "cube.tga";

const string filename = "cube.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA
mat4 mvp, projection, view, model;
unsigned char* img_data;

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	/* Vertices counter-clockwise winding */
	vertex[0].coordinate[0] = -0.5f;
	vertex[0].coordinate[1] = -0.5f;
	vertex[0].coordinate[2] = 0.0f;

	vertex[1].coordinate[0] = 0.5f;
	vertex[1].coordinate[1] = -0.5f;
	vertex[1].coordinate[2] = 0.0f;

	vertex[2].coordinate[0] = 0.5f;
	vertex[2].coordinate[1] = 0.5f;
	vertex[2].coordinate[2] = 0.0f;

	vertex[3].coordinate[0] = -0.5f;
	vertex[3].coordinate[1] = 0.5f;
	vertex[3].coordinate[2] = 0.0f;

	vertex[4].coordinate[0] = -0.5f;
	vertex[4].coordinate[1] = -0.5f;
	vertex[4].coordinate[2] = 1.0f;

	vertex[5].coordinate[0] = 0.5f;
	vertex[5].coordinate[1] = -0.5f;
	vertex[5].coordinate[2] = 1.0f;

	vertex[6].coordinate[0] = 0.5f;
	vertex[6].coordinate[1] = 0.5f;
	vertex[6].coordinate[2] = 1.0f;

	vertex[7].coordinate[0] = -0.5f;
	vertex[7].coordinate[1] = 0.5f;
	vertex[7].coordinate[2] = 1.0f;

	for (size_t i = 0; i < numOfVertex; i++)
	{
		vertex[i].color[0] = 0.0f;
		vertex[i].color[1] = 0.0f;
		vertex[i].color[2] = 0.0f;
		vertex[i].color[3] = 1.0f;
	}
	for (int i = 0; i < 6; i++)
	{
		vertex[i].texel[0] = 0.0f; 
		vertex[i].texel[1] = 0.0f;

		vertex[i].texel[2] = 1.0f;
		vertex[i].texel[3] = 0.0f;

		vertex[i].texel[4] = 1.0f;
		vertex[i].texel[5] = 1.0f;

		vertex[i].texel[6] = 0.0f;
		vertex[i].texel[7] = 1.0f;
	}
	

	

	/*Index of Poly / Triangle to Draw */
	//FRONT FACE
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 0;   triangles[4] = 2;	triangles[5] = 3;

	//BACK FACE
	triangles[6] = 4;   triangles[7] = 6;   triangles[8] = 7;
	triangles[9] = 5;   triangles[10] = 6;  triangles[11] = 4;
	//TOP FACE
	triangles[12] = 3;  triangles[13] = 2; triangles[14] = 6;
	triangles[15] = 3;  triangles[16] = 6; triangles[17] = 7;
	//BOTTOM FACE
	triangles[18] = 0;  triangles[19] = 1; triangles[20] = 5;
	triangles[21] = 0;  triangles[22] = 5; triangles[23] = 4;
	//LEFT FACE
	triangles[24] = 4;  triangles[25] = 0; triangles[26] = 7;
	triangles[27] = 0;  triangles[28] = 3; triangles[29] = 7;
	//RIGHT FACE
	triangles[30] = 5;  triangles[31] = 6; triangles[32] = 1;
	triangles[33] = 1;  triangles[34] = 6; triangles[35] = 2;



	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 9, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * numOfTriangles, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"in vec2 sv_texel;"
		"out vec4 color;"
		"out vec2 texel;"
		"uniform mat4 sv_mvp;"
		"void main() {"
		"	color = sv_color;"
		"	texel = sv_texel;"
		"	gl_Position = sv_mvp * sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"uniform sampler2D f_texture;"
		"in vec4 color;"
		"in vec2 texel;"
		"out vec4 fColor;"
		"void main() {"
		"	fColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
		//"	fColor = texture2D(f_texture, uv);"
		//"   fColor = color + vec4(0.0f, 1.0f, 0.0f, 1.0f);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
	mvpID = glGetUniformLocation(progID, "sv_mvp");
	projection = perspective(
		45.0f,					// Field of View 45 degrees
		5.0f / 5.0f,			// Aspect ratio
		10.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
	);

	// Camera Matrix
	view = lookAt(
		vec3(0.0f, 4.0f, 9.0f),	// Camera (x,y,z), in World Space
		vec3(0.0f, 0.0f, 0.0f),	// Camera looking at origin
		vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);

	// Model matrix
	model = mat4(
		0.1f					// Identity Matrix
	);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	////Change vertex data
	//vertex[0].coordinate[0] += -0.0001f;
	//vertex[0].coordinate[1] += -0.0001f;
	//vertex[0].coordinate[2] += -0.0001f;

	//vertex[1].coordinate[0] += -0.0001f;
	//vertex[1].coordinate[1] += -0.0001f;
	//vertex[1].coordinate[2] += -0.0001f;

	//vertex[2].coordinate[0] += -0.0001f;
	//vertex[2].coordinate[1] += -0.0001f;
	//vertex[2].coordinate[2] += -0.0001f;

	Matrix rotationX(cos(0.0005), 0, sin(0.0005), 0, 1, 0, -sin(0.0005), 0, cos(0.0005));
	Matrix rotationY(1, 0, 0, 0, cos(0.0005), sin(0.0005), 0, -sin(0.0005), cos(0.0005));
	for (size_t i = 0; i < numOfVertex; i++)
	{
		if (vertex[i].coordinate[2] == 1.0f)
		{
			customVector::Vector3 tempVect(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] + 0.5f);
			tempVect.Equals(rotationX* tempVect);
			tempVect.Equals(rotationY * tempVect);
			vertex[i].coordinate[0] = tempVect.x;
			vertex[i].coordinate[1] = tempVect.y;
			vertex[i].coordinate[2] = tempVect.z - 0.5f;
		}
		else
		{
			customVector::Vector3 tempVect(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] - 0.5f);
			tempVect.Equals(rotationX* tempVect);
			tempVect.Equals(rotationY * tempVect);
			vertex[i].coordinate[0] = tempVect.x;
			vertex[i].coordinate[1] = tempVect.y;
			vertex[i].coordinate[2] = tempVect.z + 0.5f;
		}
	}


#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif
	// Update Model View Projection
	mvp = projection * view * model;
}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numOfTriangles, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/
		// Send transformation to shader mvp uniform
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, numOfTriangles, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}

