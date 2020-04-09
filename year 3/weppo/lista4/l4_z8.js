var fs = require('fs');
var util = require('util');
var fsp = fs.promises;

fs.readFile('l4','utf-8', function(err,data1){
    fs.readFile('l4_2','utf-8',function(err,data2){
        console.log(data1 + data2);
    })
})

function fspromise( path, enc ){
    return new Promise ( (res, rej) => {
        fs.readFile( path, enc, (err, data) => {
            if (err)
                rej(err);
            res(data);
        });
    });
}

fspromise('l4','utf-8').then( data => {
    console.log("wykonane pt then: " + data);
})

async function main(){
var data = await fspromise('l4_2','utf-8');

console.log("wykonane po await: " + data);

}

main();

const readFileAsync = util.promisify(fs.readFile);

readFileAsync('l4','utf-8').then( data => {
    console.log("promisify : " + data);
})

fsp.readFile('l4_2','utf-8').then( data => {
    console.log("fs.promises : " + data);
})