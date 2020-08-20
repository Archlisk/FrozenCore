#include <Core/Helpers.h>

#include <Render/RenderEngine.h>

#include <GL/glew.h>
#include <iostream>


Shader* RenderEngine::CompileShaders(const String& vertex_path, const String& fragment_path) {
	std::cout << "Compiling shader '" << vertex_path << "'" << std::endl;
	String vertex_code = ReadFile(vertex_path);
	u32 vertex_id = CompileShader(vertex_code, Shader::Type::VertexShader);
	
	std::cout << "Compiling shader '" << fragment_path << "'" << std::endl;
	String fragment_code = ReadFile(fragment_path);
	u32 fragment_id = CompileShader(fragment_code, Shader::Type::FragmentShader);
	
	std::cout << "Linking shader program" << std::endl;
	u32 program_id = LinkShaders(vertex_id, fragment_id);
	
	Shader* program = new Shader(program_id);
	WriteProgramUniforms(*program);
	return program;
}

u32 RenderEngine::CompileShader(const String& code, Shader::Type type) {
	GLuint shader_id = GL_FALSE;

    if (type == Shader::Type::VertexShader)
        shader_id = glCreateShader(GL_VERTEX_SHADER);
    else if (type == Shader::Type::FragmentShader)
        shader_id = glCreateShader(GL_FRAGMENT_SHADER);
        
    GLint result = GL_FALSE;
    int info_log_len;
    
    const char* code_ptr = code.c_str();
    glShaderSource(shader_id, 1, &code_ptr, nullptr);
    glCompileShader(shader_id);
    
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_len);
    if (info_log_len) {
        std::vector<char> error_msg(info_log_len + 1);
        glGetShaderInfoLog(shader_id, info_log_len, nullptr, error_msg.data());
        throw RuntimeException(String("Failed to compile shader: ") + error_msg.data());
    }
    
    if (shader_id == GL_FALSE)
        throw RuntimeException("Failed to compile shader");
        
    return shader_id;
}

u32 RenderEngine::LinkShaders(u32 vertex_id, u32 fragment_id) {
	GLuint program_id = glCreateProgram();
    
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    {
        GLint result = GL_FALSE;
        int info_log_len;
    
        glLinkProgram(program_id);
        
        glGetProgramiv(program_id, GL_LINK_STATUS, &result);
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_len);
        if (info_log_len) {
            std::vector<char> error_msg(info_log_len + 1);
            glGetProgramInfoLog(program_id, info_log_len, nullptr, error_msg.data());
            throw RuntimeException(String("Failed to link shaders: ") + error_msg.data());
        }
    }
    return program_id;
}

void RenderEngine::WriteProgramUniforms(Shader& program) {
	GLint uniform_count, size;
    GLenum type;
    GLsizei length;
    
    const GLsizei buffer_size = 64;
    GLchar name[buffer_size];
    
    glGetProgramiv(program.gl_id, GL_ACTIVE_UNIFORMS, &uniform_count);
    
    for (GLint i = 0; i < uniform_count; i++) {
        glGetActiveUniform(program.gl_id, (GLuint)i, buffer_size, &length, &size, &type, name);
        program.uniforms[name] = i;
        std::cout << "\tUniform " << i << "(" << type << ") '" << name << "'" << std::endl; 
    }
}

void RenderEngine::UseShaders(Shader* program) {
	if (m_shader != program) {
		glUseProgram(program->gl_id);
		m_shader = program;
	}
}

void RenderEngine::SetUniform(const String& uniform_name, const Vec3& value) {
	glUniform3fv(m_shader->uniforms[uniform_name], 1, &value[0]);
}
