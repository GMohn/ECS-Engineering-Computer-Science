#version 300 es

#define MAX_LIGHTS 16

// struct definitions
struct AmbientLight {
    vec3 color;
    float intensity;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
};

struct Material {
    vec3 kA;
    vec3 kD;
    vec3 kS;
    float shininess;
};


// an attribute will receive data from a buffer
in vec3 a_position;
in vec3 a_normal;

// camera position
uniform vec3 u_eye;

// transformation matrices
uniform mat4x4 u_m;
uniform mat4x4 u_v;
uniform mat4x4 u_p;

// lights and materials
uniform AmbientLight u_lights_ambient[MAX_LIGHTS];
uniform DirectionalLight u_lights_directional[MAX_LIGHTS];
uniform PointLight u_lights_point[MAX_LIGHTS];

uniform Material u_material;

// shading output
out vec4 o_color;

// Shades an ambient light and returns this light's contribution
vec3 shadeAmbientLight(Material material, AmbientLight light) {
    
    // TODO: Implement this method
    return vec3(material.kA * light.color * light.intensity);

}

// Shades a directional light and returns its contribution
vec3 shadeDirectionalLight(Material material, DirectionalLight light, vec3 normal, vec3 eye, vec3 vertex_position) {

    // TODO: Implement this method
    eye = normalize(eye);
    vec3 light_dir = normalize(light.direction);
    vec3 vert_dist = normalize(vertex_position - eye);
    vec3 light_reflect = normalize(reflect(light.direction, normal));
    vec3 intensity_dir = material.kD * light.intensity * light.color * (max(dot(light.direction, normal),0.0));
    float spec = pow(max(dot(light_reflect,eye),0.0),material.shininess);
    vec3 intensity_shade = material.kS * light.intensity * light.color * spec;

    return vec3(intensity_dir+intensity_shade);
}

// Shades a point light and returns its contribution
vec3 shadePointLight(Material material, PointLight light, vec3 normal, vec3 eye, vec3 vertex_position) {
    
    // TODO: Implement this method
    vec3 light_dir = normalize(vertex_position - light.position);
    vec3 vert_dist = normalize(vertex_position - eye);
    vec3 light_reflect = normalize(reflect(light_dir, normal));
    float spec = pow(max(dot(light_reflect,-vert_dist),0.0),material.shininess);
    vec3 intensity_dir = material.kD * light.intensity * light.color * (max(dot(-light_dir, normal),0.0));
    float magnitude = (1.0/(pow(length(light_dir),2.0)));
    vec3 intensity_shade = material.kS *(magnitude * light.intensity)* light.color * spec;

    return vec3(intensity_dir+intensity_shade);
}

void main() {

    // TODO: GORAUD SHADING
    // TODO: Implement the vertex stage
    // TODO: Transform positions and normals
    // NOTE: Normals are transformed differently from positions. Check the book and resources.
    // TODO: Use the above methods to shade every light in the light arrays
    // TODO: Accumulate their contribution and use this total light contribution to pass to o_color
    mat4x4  mat = transpose(inverse(u_m));
    vec3 normal = normalize(vec3(mat * vec4(a_normal, 1.0)));
    vec3 position = vec3(u_m * vec4(a_position, 1.0));
    vec3 shaded_color = vec3(0.0, 0.0, 0.0);
     for(int i = 0; i < MAX_LIGHTS; i++){
            shaded_color += shadeAmbientLight(u_material, u_lights_ambient[i])+
            shadePointLight(u_material, u_lights_point[i], normal, u_eye, position)+
            shadeDirectionalLight(u_material, u_lights_directional[i], normal, u_eye, position);
        }
    
    // TODO: Pass the shaded vertex color to the fragment stage
    gl_Position = u_p * u_v * u_m * vec4(a_position, 1);
    
    // TODO: Pass the shaded vertex color to the fragment stage
    o_color = vec4(shaded_color, 1.0);
}