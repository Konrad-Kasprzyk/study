var readline = require('readline');
var fs = require('fs');

var dict = {};

var myInterface = readline.createInterface({
    input: fs.createReadStream('logs2')
  });



myInterface.on('line', function (line) {
    var ip = line.split(" ")[0];
    if (dict.hasOwnProperty(ip))
        dict[ip]++;
    else
        dict[ip] = 1;
});

myInterface.on('close', function(){

var res = {1: ["ip",0], 2: ["ip2",0], 3: ["ip3",0]}

for(var key in dict){
    // jeśli jakieś ip wystąpiło więcej razy niż ten co jest ostatni w trójce najczęściej występujących
    if (dict[key] > res[3][1]){
        var tuple = [key,dict[key]];
        for(var x in res){
            if ( tuple[1] > res[x][1]){
                var temp = res[x];
                res[x] = tuple;
                tuple = temp;
            }
        }
    }
}

console.log(res);

});