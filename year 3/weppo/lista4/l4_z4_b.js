//const cos = require('./l4_z4_a');

//console.log(cos);


module.exports = { work_b };
let a = require('./l4_z4_a');
function work_b(n) { 
    if ( n > 0 ) { 
        console.log( `b: ${n}`);
         a.work_a(n-1);     
        } 
    } 

    console.log("z4_b");