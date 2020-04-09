var fs = require('fs');

function fspromise( path, enc ){
    return new Promise( (res, rej) => {
        fs.readFile( path, enc, (err, data) =>{
            if ( err )
                rej(err);
            res(data);
        })
    })
}

fspromise('l4', 'utf-8').then( data => {
    console.log(data, "z góry kodu \n");
});

console.log("-----------------------");

(async function(){
    var result = await fs.promises.readFile('l4','utf-8');
    console.log(result);
})();