
import { hex2rgb, deg2rad, normalize, dot, cross } from './js/utils/utils.js'
import { Box } from './js/app/object3d.js'

class Mat4 {

    /**
     * Creates an identity matrix
     * 
     * @returns {Mat4} An identity matrix
     */
    static identity() {
        return new Mat4(1,0,0,0,
                        0,1,0,0,
                        0,0,1,0,
                        0,0,0,1)
    }

    /**
     * Creates a translation matrix
     * 
     * @param {Number} x Translation in X direction
     * @param {Number} y Translation in Y direction
     * @param {Number} z Translation in Z direction
     * @returns {Mat4} A translation matrix
     */
    static translation(x,y,z) {
        return new Mat4(1,0,0,x,
                        0,1,0,y,
                        0,0,1,z,
                        0,0,0,1)
    }

    /**
     * Creates a rotation matrix for X rotations
     * 
     * @param {Number} deg Angle in degrees
     * @returns {Mat4} A X rotation matrix
     */
    static rotationx(deg) {
        let a = Math.cos(deg2rad(deg))
        let b = -Math.sin(deg2rad(deg))
        let c = -b
        let d = a
        return new Mat4(1,0,0,0,
                        0,a,b,0,
                        0,c,d,0,
                        0,0,0,1)
    }

    /**
     * Creates a rotation matrix for Y rotations
     * 
     * @param {Number} deg Angle in degrees
     * @returns {Mat4} A Y rotation matrix
     */
    static rotationy(deg) {
        let a = Math.cos(deg2rad(deg))
        let b = Math.sin(deg2rad(deg))
        let c = -b
        let d = a
        return new Mat4(a,0,b,0,
                        0,1,0,0,
                        c,0,d,0,
                        0,0,0,1)
    }

    /**
     * Creates a rotation matrix for Z rotations
     * 
     * @param {Number} deg Angle in degrees
     * @returns {Mat4} A Z rotation matrix
     */
    static rotationz(deg) {
        let a = Math.cos(deg2rad(deg))
        let b = -Math.sin(deg2rad(deg))
        let c = -b
        let d = a
        return new Mat4(a,b,0,0,
                        c,d,0,0,
                        0,0,1,0,
                        0,0,0,1)
    }

    /**
     * Creates a scaling matrix
     * 
     * @param {Number} s The factor to scale by
     * @returns {Mat4} A scaling matrix
     */
    static scale(s) {
        return new Mat4(s,0,0,0,
                        0,s,0,0,
                        0,0,s,0,
                        0,0,0,1)
    }

    /**
     * Creates a view matrix using eye position and viewing target position
     * 
     * @param {Array<Number>} eye Position of the camera as list of [x,y,z]
     * @param {Array<Number>} center Position of the viewing target point as list of [x,y,z]
     * @param {Array<Number>} up Direction of the up vector - this is usually the Y axis
     * @returns {Mat4} A view matrix
     */
    static lookat(eye, center, up) {

        // Compute view direction
        let viewdir = [
            eye[0] - center[0],
            eye[1] - center[1],
            eye[2] - center[2]
        ]

        // Normalize view direction to form Z component of orthonormal basis
        let axZ = normalize(viewdir)

        // Get X component of orthonormal basis (cross of Up and Z)
        let axX = normalize(cross(up, axZ))

        // Get Y component of orthonormal basis (cross of Z and X)
        let axY = cross(axZ, axX)

        return new Mat4 (
            axX[0], axX[1], axX[2], -dot(axX, eye),
            axY[0], axY[1], axY[2], -dot(axY, eye),
            axZ[0], axZ[1], axZ[2], -dot(axZ, eye),
            0, 0, 0, 1
        )
    }

    /**
     * Creates a projection matrix using perspective projection
     * 
     * @param {Number} fovy Vertical field of view in degrees
     * @param {Number} aspect Aspect ratio of the canvas (width / height)
     * @param {Number} near Near plane distance
     * @param {Number} far Far plane distance
     * @returns {Mat4} A perspective projection matrix
     */
    static projectionPerspective( fovy, aspect, near, far ) {
        let top = Math.tan(deg2rad(fovy) / 2) * near
        let bottom = -top
        let right = top * aspect
        let left = -top * aspect

        let a = (2*near) / (right - left)
        let b = (right + left) / (right - left)
        let c = (2*near) / (top - bottom)
        let d = (top + bottom) / (top - bottom)
        let e = -(far + near) / (far - near)
        let f = -(2*far*near) / (far - near)

        return new Mat4(
            a, 0, b, 0,
            0, c, d, 0,
            0, 0, e, f,
            0, 0, -1, 0
        )
    }

    /**
     * Creates a projection matrix using orthographic projection
     * 
     * @param {Number} left The left extent of the camera frustum (negative)
     * @param {Number} right The right extent of the camera frustum (positive)
     * @param {Number} aspect Aspect ratio of the canvas (width / height)
     * @param {Number} near Near plane distance
     * @param {Number} far Far plane distance
     * @returns {Mat4} An orthographic projection matrix
     */
    static projectionOrthographic(left, right, aspect, near, far) {

        let top = right / aspect
        let bottom = left / aspect

        let a = 2 / (right - left)
        let b = -(right + left) / (right - left)
        let c = 2 / (top - bottom)
        let d = -(top + bottom) / (top - bottom)
        let e = -2 / (far - near)
        let f = -(far + near) / (far - near)

        return new Mat4(
            a, 0, 0, b,
            0, c, 0, d,
            0, 0, e, f,
            0, 0, 0, 1
        )
    }

    /**
     * Constructs a new 4x4 matrix 
     * Arguments are given in row-major order
     * 
     */
    constructor(m00, m01, m02, m03,
                m10, m11, m12, m13,
                m20, m21, m22, m23,
                m30, m31, m32, m33) {

        // store in column major format
        this.m = [
            [m00, m10, m20, m30],
            [m01, m11, m21, m31],
            [m02, m12, m22, m32],
            [m03, m13, m23, m33]
        ]
    }

    /**
     * Flattens the matrix for use with WebGL/OpenGL calls
     * 
     * @returns {Array<Number>} A linear list of matrix values in column-major order
     */
    flatten() {
        return [...this.m[0], ...this.m[1], ...this.m[2], ...this.m[3]]
    }

    /**
     * Performs column-major matrix multiplication of the current matrix and 'other'
     * 
     * @param {Mat4} other The matrix to multiply with
     * @returns {Mat4} The resulting matrix
     */
    multiply(other) {
        let result = Mat4.identity()

        for (let i = 0; i < 4; i++) {
            for (let j = 0; j < 4; j++) {
                result.m[i][j] = 0

                for (let k = 0; k < 4; k++){
                    result.m[i][j] += this.m[k][j] * other.m[i][k]
                }
            }
        }

        return result
    }
}


/**
 * @Class
 * WebGlApp that will call basic GL functions, manage a list of shapes, and take care of rendering them
 * 
 * This class will use the Shapes that you have implemented to store and render them
 */
class WebGlApp 
{
    /**
     * Initializes the app with a box, and the model, view, and projection matrices
     * 
     * @param {WebGL2RenderingContext} gl The webgl2 rendering context
     * @param {Shader} shader The shader to be used to draw the object
     */
    constructor( gl, shader )
    {
        // Store the shader
        this.shader = shader
        
        // Create a box instance and create a variable to track its rotation
        this.box = new Box( gl, shader, hex2rgb('#FFBF00') )
        this.box_animation_step = 0

        // Create the model matrix
        // Use an identity matrix initially
        this.model = Mat4.identity()

        // Create the view matrix
        // Point the camera at the origin and move it backwards 3 units on the Z Axis
        let eye     =   [2.5, 1.5, -2.5]
        let center  =   [0, 0, 0]
        let up      =   [0, 1, 0]
        this.view = Mat4.lookat(eye, center, up)

        // Create the projection matrix
        // Use a perspective projection initially
        this.fovy = 90
        this.aspect = 16/9
        this.left = -5
        this.right = 5
        this.near = 0.001
        this.far = 1000.0
        this.projection = Mat4.projectionPerspective(this.fovy, this.aspect, this.near, this.far)

        // Combine model, view and projection matrix into a single MVP
        // Pay attention to the correct order of multiplication
        this.mvp = this.projection.multiply(this.view).multiply(this.model)

    }  

    /**
     * Sets the viewport of the canvas to fill the whole available space so we draw to the whole canvas
     * 
     * @param {WebGL2RenderingContext} gl The webgl2 rendering context
     * @param {Number} width 
     * @param {Number} height 
     */
    setViewport( gl, width, height )
    {
        gl.viewport( 0, 0, width, height )
    }

    /**
     * Clears the canvas color
     * 
     * @param {WebGL2RenderingContext} gl The webgl2 rendering context
     */
    clearCanvas( gl )
    {
        gl.clearColor(...hex2rgb('#000000'), 1.0)
        gl.clear(gl.COLOR_BUFFER_BIT)
    }
    
    /**
     * Updates components of this app
     * 
     * @param { AppState } app_state The state of the UI
     */
    update( app_state ) 
    {
        this.box_animation_step = (Math.sin(Date.now() / 2000))
        switch(app_state.getState('Animation')) {
            case 'Translate':
                this.model = Mat4.translation(3 * this.box_animation_step, 0, 3 * this.box_animation_step)
                break
            case 'Rotate':
                this.model = Mat4.rotationy(this.box_animation_step * 360)
                break
            case 'Scale':
                this.model = Mat4.scale(this.box_animation_step)
                break
            case 'Off':
                this.model = Mat4.identity()
        }

        switch(app_state.getState('Projection')) {
            case 'Perspective':
                this.projection = Mat4.projectionPerspective(this.fovy, this.aspect, this.near, this.far)
                break
            case 'Orthographic':
                this.projection = Mat4.projectionOrthographic(this.left, this.right, this.aspect, this.near, this.far)
                break
        }

        // Re-compute the MVP matrix
        this.mvp = this.projection.multiply(this.view).multiply(this.model)
    }

    /**
     * Main render loop which sets up the active viewport (i.e. the area of the canvas we draw to)
     * clears the canvas with a background color and draws a box
     * 
     * @param {WebGL2RenderingContext} gl The webgl2 rendering context
     * @param {Number} canvas_width The canvas width. Needed to set the viewport
     * @param {Number} canvas_height The canvas height. Needed to set the viewport
     */
    render( gl, canvas_width, canvas_height )
    {
        // Set viewport and clear canvas
        this.setViewport( gl, canvas_width, canvas_height )
        this.clearCanvas( gl )

        // Activate the shader
        this.shader.use( )

        // Pass the MVP to the shader 
        // Use the shader's setUniform4x4f function to pass a 4x4 matrix
        this.shader.setUniform4x4f('u_mvp', this.mvp.flatten())

        // Render the box
        // This will use the MVP that was passed to the shader
        this.box.render( gl )
    }

}


// JS Module Export -- No need to modify this
export
{
    WebGlApp
}