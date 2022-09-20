#version 330 core

float zNear = 5.0f; 
float zFar  = 25.0f; 

float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0; 
    return (2.0 * zNear * zFar) / (zFar + zNear - z * (zFar - zNear));	
}

/*
void main() {             
    //float depth = LinearizeDepth(gl_FragCoord.z) / zFar;
    //gl_FragDepth = depth;
}
*/

/*
void main() {             
    // gl_FragDepth = gl_FragCoord.z;
}
*/

void main() {

}


