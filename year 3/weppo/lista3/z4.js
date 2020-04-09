function createFs(n){
    var fs = [];
    
    
    for (var i = 0; i < n; i++){
        fs[i] = (function(){
            var j;
            // jak damy tutaj i zamiast i2 to zwróci undefinded
            j = i;
            return function(){
                return j;
            }
        })();
    };

    return fs;
}

var myfs = createFs(10);

console.log(myfs[2]());

//Babel
/*

function createFS2(n){
    var fs = [];

    var _loop = function _loop(i) {
        fs[i] = function () {
            return i;
        };
    };

    for (var i = 0; i < n; i++){
        _loop(i);
    };

    return fs;
}

var myfs2 = createFs(10);

console.log(myfs2[3]());
*/