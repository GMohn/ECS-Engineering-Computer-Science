#version 300 es

#define MAX_LIGHTS 16

// Fragment shaders don't have a default precision so we need
// to pick one. mediump is a good default. It means "medium precision".
precision mediump float;

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

// lights and materials
uniform AmbientLight u_lights_ambient[MAX_LIGHTS];
uniform DirectionalLight u_lights_directional[MAX_LIGHTS];
uniform PointLight u_lights_point[MAX_LIGHTS];

uniform Material u_material;

// camera position
uniform vec3 u_eye;

// received from vertex stage
// TODO: Create any needed `in` variables here
// TODO: These variables correspond to the `out` variables from the vertex stage

in vec3 normal_out;
in vec3 position_out;
// with webgl 2, we now have to define an out that will be the color of the fragment
out vec4 o_fragColor;

// Shades an ambient light and returns this light's contribution
vec3 shadeAmbientLight(Material material, AmbientLight light) {
    return vec3(material.kA * light.color * light.intensity);
}

// Shades a directional light and returns its contribution
vec3 shadeDirectionalLight(Material material, DirectionalLight light, vec3 normal, vec3 eye, vec3 vertex_position) {
    eye = normalize(eye);
    vec3 light_dir = normalize(light.direction);
    vec3 vert_dist = normalize(vertex_position - eye);
    vec3 light_reflect = reflect(light.direction, normal);
    float spec = pow(max(dot(light_reflect,eye),0.0),material.shininess);

    vec3 intensity_dir = material.kD * light.intensity * light.color * (max(dot(light.direction, normal),0.0));
    vec3 intensity_shade = material.kS * light.intensity * light.color * spec;

    return vec3(intensity_dir+intensity_shade);
}

// Shades a point light and returns its contribution
vec3 shadePointLight(Material material, PointLight light, vec3 normal, vec3 eye, vec3 vertex_position) {
    vec3 light_dir = normalize(vertex_position - light.position);
    vec3 vert_dist = normalize(vertex_position - eye);
    vec3 light_reflect = reflect(light_dir, normal);
    float spec = pow(max(dot(light_reflect,-vert_dist),0.0),material.shininess);
    float magnitude = 1.0/(pow(length(light_dir),2.0));

    vec3 intensity_dir = material.kD * light.intensity * light.color * (max(dot(-light_dir, normal),0.0));
    vec3 intensity_shade = material.kS*(magnitude * light.intensity)* light.color * spec;

    return vec3(intensity_dir+intensity_shade);
}

void main() {

    // TODO: PHONG SHADING
    // TODO: Implement the fragment stage
    // TODO: Use the above methods to shade every light in the light arrays
    // TODO: Accumulate their contribution and use this total light contribution to pass to o_fragColor

     vec3 shaded_color = vec3(0.0, 0.0, 0.0);

     for(int i = 0; i < MAX_LIGHTS; i++){
            shaded_color += shadeAmbientLight(u_material, u_lights_ambient[i])+
            shadeDirectionalLight(u_material, u_lights_directional[i], normal_out, u_eye, position_out)+
            shadePointLight(u_material, u_lights_point[i], normal_out, u_eye, position_out);
        }

    // TODO: Pass the shaded vertex color to the output
    o_fragColor = vec4(shaded_color, 1.0);
}