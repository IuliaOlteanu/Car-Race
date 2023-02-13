#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 Colours;
uniform vec3 car_pos;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_color = Colours;

    // TODO(student): Compute gl_Position
    vec4 model_pos = Model * vec4(v_position, 1);
    float scale_factor = 0.0025;
    float y = model_pos.y - pow(length(car_pos - model_pos.xyz), 2) * scale_factor;
    model_pos.y = y;
    gl_Position	= Projection * View * model_pos;

}
