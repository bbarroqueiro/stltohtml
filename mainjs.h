#pragma once 

char* mainjs = "// Creating a canvas\n"
"var canvas = document.getElementById('glcanvas');\n"
"gl = canvas.getContext('experimental-webgl');\n"
"var ext = gl.getExtension('OES_element_index_uint');\n"
"\n"
"// set the canvas size based on the html client size\n"
"canvas.width = document.body.clientWidth;\n"
"canvas.height = document.body.clientHeight;\n"
"\n"
"// Defining and storing the geometry\n"
"// Create and store data into vertex buffer\n"
"var vertex_buffer = gl.createBuffer();\n"
"gl.bindBuffer(gl.ARRAY_BUFFER, vertex_buffer);\n"
"gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);\n"
"\n"
"// Create and store data into color buffer\n"
"var color_buffer = gl.createBuffer();\n"
"gl.bindBuffer(gl.ARRAY_BUFFER, color_buffer);\n"
"gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);\n"
"\n"
"// Create and store data into normal buffer\n"
"var normal_buffer = gl.createBuffer();\n"
"gl.bindBuffer(gl.ARRAY_BUFFER, normal_buffer);\n"
"gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);\n"
"\n"
"// Create and store data into index buffer\n"
"var index_buffer = gl.createBuffer();\n"
"gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);\n"
"gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint32Array(indices), gl.STATIC_DRAW);\n"
"\n"
"/*=================== SHADERS =================== */\n"
"\n"
"/*var vertCode = 'attribute vec3 position;' +\n"
"   'uniform mat4 Pmatrix;' +\n"
"   'uniform mat4 Vmatrix;' +\n"
"   'uniform mat4 Mmatrix;' +\n"
"   'uniform mat4 uNormalMatrix;' +\n"
"   'attribute vec3 color;' +//the color of the point\n"
"   'attribute vec3 normal;' +//the normal of the point\n"
"   'varying vec3 vColor;' +\n"
"   'varying vec3 vLighting;' +\n"
"   'void main(void) ' +//pre-built function\n"
"   '{' +\n"
"      'gl_Position = Pmatrix*Vmatrix*Mmatrix*vec4(position, 1.);' +\n"
"      'vec3 ambientLight = vec3(0.3, 0.3, 0.3);' +\n"
"      'vec3 directionalLightColor = vec3(1, 1, 1);' +\n"
"      'vec3 directionalVector = normalize(vec3(0.85, 0.8, 0.75));' +\n"
"      'vec4 transformedNormal = uNormalMatrix * vec4(normal, 1.0);' +\n"
"      'float directional = max(dot(transformedNormal.xyz, directionalVector), 0.0);' +\n"
"      'vColor = color;' +\n"
"      'vLighting = ambientLight + (directionalLightColor * directional);'+\n"
"   '}';*/\n"
"var vertCode = 'attribute vec3 position;' +\n"
"   'uniform mat4 Pmatrix;' +\n"
"   'uniform mat4 Vmatrix;' +\n"
"   'uniform mat4 Mmatrix;' +\n"
"   'uniform mat4 Nmatrix;' +\n"
"   'attribute vec3 color;' +//the color of the point\n"
"   'attribute vec3 normal;' +//the normal of the point\n"
"   'varying vec3 vColor;' +\n"
"   'varying vec3 vLighting;' +\n"
"   'void main(void) ' +//pre-built function\n"
"   '{' +\n"
"      'gl_Position = Pmatrix*Vmatrix*Mmatrix*vec4(position, 1.);' +\n"
"      'vec3 ambientLight = vec3(0.3, 0.3, 0.3);' +\n"
"      'vec3 directionalLightColor = vec3(1, 1, 1);' +\n"
"      'vec3 directionalVector = normalize(vec3(0.85, 0.8, 0.75));' +\n"
"      'vec4 transformedNormal = Nmatrix * vec4(normal, 1.0);' +\n"
"	  'float directional = max(dot(transformedNormal.xyz, directionalVector), 0.0);' +\n"
"      'vColor = color;' +\n"
"	  'vLighting = ambientLight + (directionalLightColor * directional);' +\n"
"   '}';\n"
"\n"
"var fragCode = 'precision mediump float;' +\n"
"   'varying vec3 vColor;' +\n"
"   'varying vec3 vLighting;' +\n"
"   'void main(void) {' +\n"
"      'gl_FragColor = vec4(vColor * vLighting,1.);' +\n"
"   '}';\n"
"\n"
"/*var fragCode = 'precision mediump float;' +\n"
"   'varying vec3 vColor;' +\n"
"   'void main(void)' +\n"
"    '{' +\n"
"      'gl_FragColor = vec4(vColor * vLighting,1.);' +\n"
"   '}';*/\n"
"\n"
"var vertShader = gl.createShader(gl.VERTEX_SHADER);\n"
"gl.shaderSource(vertShader, vertCode);\n"
"gl.compileShader(vertShader);\n"
"\n"
"var fragShader = gl.createShader(gl.FRAGMENT_SHADER);\n"
"gl.shaderSource(fragShader, fragCode);\n"
"gl.compileShader(fragShader);\n"
"\n"
"var shaderprogram = gl.createProgram();\n"
"gl.attachShader(shaderprogram, vertShader);\n"
"gl.attachShader(shaderprogram, fragShader);\n"
"gl.linkProgram(shaderprogram);\n"
"\n"
"/*======== Associating attributes to vertex shader =====*/\n"
"var _Pmatrix = gl.getUniformLocation(shaderprogram, \"Pmatrix\");\n"
"var _Vmatrix = gl.getUniformLocation(shaderprogram, \"Vmatrix\");\n"
"var _Mmatrix = gl.getUniformLocation(shaderprogram, \"Mmatrix\");\n"
"var _Nmatrix = gl.getUniformLocation(shaderprogram, \"Nmatrix\");\n"
"\n"
"gl.bindBuffer(gl.ARRAY_BUFFER, vertex_buffer);\n"
"var _position = gl.getAttribLocation(shaderprogram, \"position\");\n"
"gl.vertexAttribPointer(_position, 3, gl.FLOAT, false, 0, 0);\n"
"gl.enableVertexAttribArray(_position);\n"
"\n"
"gl.bindBuffer(gl.ARRAY_BUFFER, color_buffer);\n"
"var _color = gl.getAttribLocation(shaderprogram, \"color\");\n"
"gl.vertexAttribPointer(_color, 3, gl.FLOAT, false, 0, 0);\n"
"gl.enableVertexAttribArray(_color);\n"
"\n"
"gl.bindBuffer(gl.ARRAY_BUFFER, normal_buffer);\n"
"var _normal = gl.getAttribLocation(shaderprogram, \"normal\");\n"
"gl.vertexAttribPointer(_normal, 3, gl.FLOAT, false, 0, 0);\n"
"gl.enableVertexAttribArray(_normal);\n"
"\n"
"gl.useProgram(shaderprogram);\n"
"\n"
"/*==================== MATRIX ====================== */\n"
"\n"
"function get_projection(angle, a, zMin, zMax) {\n"
"    var ang = Math.tan((angle * .5) * Math.PI / 180);//angle*.5\n"
"    return [\n"
"       0.5 / ang, 0, 0, 0,\n"
"       0, 0.5 * a / ang, 0, 0,\n"
"       0, 0, -(zMax + zMin) / (zMax - zMin), -1,\n"
"       0, 0, (-2 * zMax * zMin) / (zMax - zMin), 0\n"
"    ];\n"
"}\n"
"\n"
"var proj_matrix = get_projection(40, canvas.width / canvas.height, 1, 100);\n"
"var mo_matrix = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1];\n"
"var no_matrix = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1];\n"
"var view_matrix = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1];\n"
"\n"
"view_matrix[14] = view_matrix[14] - 6;\n"
"\n"
"/*================= Mouse events ======================*/\n"
"\n"
"var AMORTIZATION = 0.95;\n"
"var drag = false;\n"
"var old_x, old_y;\n"
"var dX = 0, dY = 0;\n"
"\n"
"var mouseDown = function (e) {\n"
"    drag = true;\n"
"    old_x = e.pageX, old_y = e.pageY;\n"
"    e.preventDefault();\n"
"    return false;\n"
"};\n"
"\n"
"var mouseUp = function (e) {\n"
"    drag = false;\n"
"};\n"
"\n"
"var mouseMove = function (e) {\n"
"    if (!drag) return false;\n"
"    dX = (e.pageX - old_x) * 2 * Math.PI / canvas.width,\n"
"    dY = (e.pageY - old_y) * 2 * Math.PI / canvas.height;\n"
"    THETA += dX;\n"
"    PHI += dY;\n"
"    old_x = e.pageX, old_y = e.pageY;\n"
"    e.preventDefault();\n"
"};\n"
"\n"
"canvas.addEventListener(\"mousedown\", mouseDown, false);\n"
"canvas.addEventListener(\"mouseup\", mouseUp, false);\n"
"canvas.addEventListener(\"mouseout\", mouseUp, false);\n"
"canvas.addEventListener(\"mousemove\", mouseMove, false);\n"
"\n"
"function transpose(out, a) {\n"
"    // If we are transposing ourselves we can skip a few steps but have to cache some values\n"
"    if (out === a) {\n"
"        let a01 = a[1], a02 = a[2], a03 = a[3];\n"
"        let a12 = a[6], a13 = a[7];\n"
"        let a23 = a[11];\n"
"\n"
"        out[1] = a[4];\n"
"        out[2] = a[8];\n"
"        out[3] = a[12];\n"
"        out[4] = a01;\n"
"        out[6] = a[9];\n"
"        out[7] = a[13];\n"
"        out[8] = a02;\n"
"        out[9] = a12;\n"
"        out[11] = a[14];\n"
"        out[12] = a03;\n"
"        out[13] = a13;\n"
"        out[14] = a23;\n"
"    } else {\n"
"        out[0] = a[0];\n"
"        out[1] = a[4];\n"
"        out[2] = a[8];\n"
"        out[3] = a[12];\n"
"        out[4] = a[1];\n"
"        out[5] = a[5];\n"
"        out[6] = a[9];\n"
"        out[7] = a[13];\n"
"        out[8] = a[2];\n"
"        out[9] = a[6];\n"
"        out[10] = a[10];\n"
"        out[11] = a[14];\n"
"        out[12] = a[3];\n"
"        out[13] = a[7];\n"
"        out[14] = a[11];\n"
"        out[15] = a[15];\n"
"    }\n"
"\n"
"    return out;\n"
"}\n"
"\n"
"function invert(out, a) {\n"
"    let a00 = a[0], a01 = a[1], a02 = a[2], a03 = a[3];\n"
"    let a10 = a[4], a11 = a[5], a12 = a[6], a13 = a[7];\n"
"    let a20 = a[8], a21 = a[9], a22 = a[10], a23 = a[11];\n"
"    let a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15];\n"
"\n"
"    let b00 = a00 * a11 - a01 * a10;\n"
"    let b01 = a00 * a12 - a02 * a10;\n"
"    let b02 = a00 * a13 - a03 * a10;\n"
"    let b03 = a01 * a12 - a02 * a11;\n"
"    let b04 = a01 * a13 - a03 * a11;\n"
"    let b05 = a02 * a13 - a03 * a12;\n"
"    let b06 = a20 * a31 - a21 * a30;\n"
"    let b07 = a20 * a32 - a22 * a30;\n"
"    let b08 = a20 * a33 - a23 * a30;\n"
"    let b09 = a21 * a32 - a22 * a31;\n"
"    let b10 = a21 * a33 - a23 * a31;\n"
"    let b11 = a22 * a33 - a23 * a32;\n"
"\n"
"    // Calculate the determinant\n"
"    let det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;\n"
"\n"
"    if (!det) {\n"
"        return null;\n"
"    }\n"
"    det = 1.0 / det;\n"
"\n"
"    out[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;\n"
"    out[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;\n"
"    out[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;\n"
"    out[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;\n"
"    out[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;\n"
"    out[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;\n"
"    out[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;\n"
"    out[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;\n"
"    out[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;\n"
"    out[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;\n"
"    out[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;\n"
"    out[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;\n"
"    out[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;\n"
"    out[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;\n"
"    out[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;\n"
"    out[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;\n"
"\n"
"    return out;\n"
"}\n"
"\n"
"/*=========================rotation================*/\n"
"\n"
"function rotateX(m, angle)\n"
"{\n"
"    var c = Math.cos(angle);\n"
"    var s = Math.sin(angle);\n"
"    var mv1 = m[1], mv5 = m[5], mv9 = m[9];\n"
"\n"
"    m[1] = m[1] * c - m[2] * s;\n"
"    m[5] = m[5] * c - m[6] * s;\n"
"    m[9] = m[9] * c - m[10] * s;\n"
"\n"
"    m[2] = m[2] * c + mv1 * s;\n"
"    m[6] = m[6] * c + mv5 * s;\n"
"    m[10] = m[10] * c + mv9 * s;\n"
"}\n"
"\n"
"function rotateY(m, angle)\n"
"{\n"
"    var c = Math.cos(angle);\n"
"    var s = Math.sin(angle);\n"
"    var mv0 = m[0], mv4 = m[4], mv8 = m[8];\n"
"\n"
"    m[0] = c * m[0] + s * m[2];\n"
"    m[4] = c * m[4] + s * m[6];\n"
"    m[8] = c * m[8] + s * m[10];\n"
"\n"
"    m[2] = c * m[2] - s * mv0;\n"
"    m[6] = c * m[6] - s * mv4;\n"
"    m[10] = c * m[10] - s * mv8;\n"
"}\n"
"\n"
"// Drawing\n"
"var THETA = 0,\n"
"PHI = 0;\n"
"var time_old = 0;\n"
"\n"
"var animate = function (time) {\n"
"    var dt = time - time_old;\n"
"\n"
"    if (!drag) {\n"
"        dX *= AMORTIZATION, dY *= AMORTIZATION;\n"
"        THETA += dX, PHI += dY;\n"
"    }\n"
"\n"
"    //set model matrix to I4\n"
"\n"
"    mo_matrix[0] = 1, mo_matrix[1] = 0, mo_matrix[2] = 0,\n"
"    mo_matrix[3] = 0,\n"
"\n"
"    mo_matrix[4] = 0, mo_matrix[5] = 1, mo_matrix[6] = 0,\n"
"    mo_matrix[7] = 0,\n"
"\n"
"    mo_matrix[8] = 0, mo_matrix[9] = 0, mo_matrix[10] = 1,\n"
"    mo_matrix[11] = 0,\n"
"\n"
"    mo_matrix[12] = 0, mo_matrix[13] = 0, mo_matrix[14] = 0,\n"
"    mo_matrix[15] = 1;\n"
"\n"
"    rotateY(mo_matrix, THETA);\n"
"    rotateX(mo_matrix, PHI);\n"
"\n"
"    invert(no_matrix, mo_matrix);\n"
"    transpose(no_matrix, no_matrix);\n"
"\n"
"    time_old = time;\n"
"    gl.enable(gl.DEPTH_TEST);\n"
"\n"
"    // gl.depthFunc(gl.LEQUAL);\n"
"\n"
"    gl.clearColor(0.5, 0.5, 0.5, 0.9);\n"
"    gl.clearDepth(1.0);\n"
"    gl.viewport(0.0, 0.0, canvas.width, canvas.height);\n"
"    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);\n"
"\n"
"    gl.uniformMatrix4fv(_Pmatrix, false, proj_matrix);\n"
"    gl.uniformMatrix4fv(_Vmatrix, false, view_matrix);\n"
"    gl.uniformMatrix4fv(_Mmatrix, false, mo_matrix);\n"
"    gl.uniformMatrix4fv(_Nmatrix, false, no_matrix);\n"
"\n"
"    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);\n"
"    gl.drawElements(gl.TRIANGLES, indices.length, gl.UNSIGNED_INT, 0);\n"
"\n"
"    window.requestAnimationFrame(animate);\n"
"}\n"
"animate(0);\n"
;
