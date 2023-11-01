import { loadExternalFile } from './js/utils/utils.js'

/**
 * A class to load OBJ files from disk
 */
class OBJLoader {

    /**
     * Constructs the loader
     * 
     * @param {String} filename The full path to the model OBJ file on disk
     */
    constructor(filename) {
        this.filename = filename
    }

    /**
     * Loads the file from disk and parses the geometry
     * 
     * @returns {[Array<Number>, Array<Number>]} A tuple / list containing 1) the list of vertices and 2) the list of triangle indices
     */
    load() {
        

        // Load the file's contents
        let contents = loadExternalFile(this.filename)

        // Create lists for vertices and indices
        let vertices = []
        let indices = []
        // TODO: STEP 1
        // Parse the file's contents
        // You can loop through the file line-by-line by splitting the string at line breaks
        // contentx.split('\n')
        contents = contents.split('\n');
        
        // TODO: STEP 2
        // Process (or skip) each line based on its content and call the parsing functions to parse an entry
        // For vertices call OBJLoader.parseVertex
        // For faces call OBJLoader.parseFace
        for(let i =0; i< contents.length; i++){
            if (contents[i][0] == 'v' && contents[i][1] != 'n' && contents[i][1] != 't')
            {
                 vertices.push(this.parseVertex(contents[i]))
            }
            else if(contents[i][0] == 'f'){
                indices.push(this.parseFace(contents[i]));
                
            }
        }
        // TODO: STEP 3
        // Vertex coordinates can be arbitrarily large or small
        // We want to normalize the vertex coordinates to fit within our [-1.0, 1.0]^3 box from the previous assignment
        // As a pre-processing step and to avoid complicated scaling transformations in the main app we perform normalization here
        // Determine the max and min extent of all the vertex coordinates and normalize each entry based on this finding
        let normalizedvertices =[];
     
        let vertmax = Math.max.apply(null, vertices.map(row=> Math.max.apply(Math, row)));
        let vertmin = Math.min.apply(null, vertices.map(row=> Math.min.apply(Math, row)));
        let scalar = 2/(vertmax-vertmin);

        for(let i =0; i < vertices.length; i++){
            for (let j=0; j< vertices[i].length; j++){
                vertices[i][j] = vertices[i][j]*scalar - vertmin*scalar + (-1);
                normalizedvertices.push(parseFloat(vertices[i][j])); 
            }
        }
       
         // TODO: HINT
        // Look up the JavaScript functions String.split, parseFloat, and parseInt 
        // You will need thim in your parsing functions

        // Return the tuple
       return [ normalizedvertices, indices.flat() ]
    }

    /**
     * Parses a single OBJ vertex entry given as a string
     * Call this function from OBJLoader.load()
     * 
     * @param {String} vertex_string String containing the vertex entry 'v {x} {y} {z}'
     * @returns {Array<Number>} A list containing the x, y, z coordinates of the vertex
     */
    parseVertex(vertex_string)
    {
        let vertex = vertex_string.split('\r');
        vertex = vertex[0].split(' ');
        vertex.shift();
        // TODO: Process the entry and parse numbers to float
        for(let i = 0; i<vertex.length;i++){
            parseFloat(vertex[i]);
        }
        return vertex;
        
    }

    /**
     * Parses a single OBJ face entry given as a string
     * Face entries can refer to 3 or 4 elements making them triangle or quad faces
     * WebGL only supports triangle drawing, so we need to triangulate the entry if we find 4 indices
     * This is done using OBJLoader.triangulateFace()
     * 
     * Each index entry can have up to three components separated by '/' 
     * You need to grad the first component. The other ones are for textures and normals which will be treated later
     * Make sure to account for this fact.
     * 
     * Call this function from OBJLoader.load()
     * 
     * @param {String} face_string String containing the face entry 'f {v0}/{vt0}/{vn0} {v1}/{vt1}/{vn1} {v2}/{vt2}/{vn2} ({v3}/{vt3}/{vn3})'
     * @returns {Array<Number>} A list containing three indices defining a triangle
     */
    parseFace(face_string)
    {
        // TODO: Process the entry and parse numbers to ints
        let temp = [];
        let face = face_string.split('\r');
        face = face[0].split(' ');
        face.shift();
        // TODO: Don't forget to handle triangulation if quads are given
        if(face.length == 4){
            face = this.triangulateFace(face);
        }
        
        
        for(let i = 0, len = face.length; i < len; i++){
            temp[i] = face[i].toString().split('/');
        }
        for(let i = 0, len = temp.length; i < len; i++){
            face.push(parseInt(temp[i][0])-1);
            face.shift();
        }
       
        return face;
      
    }

    /**
     * Triangulates a face entry given as a list of 4 indices
     * Use these 4 indices to create indices for two separate triangles that share a side (2 vertices)
     * Return a new index list containing the triangulated indices
     * 
     * @param {Array<Number>} face The quad indices with 4 entries
     * @returns {Array<Number>} The newly created list containing triangulated indices
     */
    triangulateFace(face)
    {
            let triangulate = [];
            for(let i = 0, len = face.length+2; i < len; i++){
                
                if (i == 3){
                    triangulate[i] = face[0];
                }
                else if (i > 3 ){
                    triangulate[i] = face[i-2]
                }
                else {
                    triangulate[i] = face[i]
                }
            }
            
            return triangulate;
        // TODO: Triangulate the face indices
    }
}

export {
    OBJLoader
}