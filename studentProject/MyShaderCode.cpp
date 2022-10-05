
const char* vertexShaderCode =
"#version 450\r\n"
""
"in layout(location=0) vec2 position;"
"in layout(location=1) vec3 vertexColor;"
""
""
"out vec3 theColor;"
""
"uniform vec2 posOffset; "
""
""
"void main()"
"{"
"	gl_Position = vec4(position + posOffset, 0.0, 1.0);"
"	theColor =vertexColor;"
"	"
"}"
"";

const char* fragmentShaderCode =
"#version 450\r\n"
""
"out vec4 daColor;"
"in vec3 theColor;"
"uniform vec4 ourColor;"
""
"void main()"
"{"
"	daColor = vec4(theColor, 1.0) + ourColor;"
"}";
