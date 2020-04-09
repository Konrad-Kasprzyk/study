/*
exports.a = 1;

require('./l4_z4_b');

exports.b = 2;

exports.c = 3;
*/

module.exports = { work_a }; 
let b = require('./l4_z4_b'); 

function work_a(n) { 
    if ( n > 0 ) { 
        console.log( `a: ${n}`); 
        b.work_b(n-1);     
    }
}

console.log("z4_a");


