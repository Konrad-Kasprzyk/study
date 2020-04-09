function paramFibIter(count) {
    return function fib() {
        var _a = 0;
        var _b = 1;
        var _temp = 0;
        return {
            next: function () {
                _temp = _a;
                _a = _b;
                _b = _temp + _b;
                return {
                    value: _b,
                    done: _b >= count
                };
            }
        };
    };
}


var count = 100;

var paramFibIter = paramFibIter(count);
var _it = paramFibIter();

for (var _result;
    (_result = _it.next()), !_result.done;) {
    console.log(_result.value);
}

// jak działa pętla for w iteratorach?
/*
for (var _result;
    _result = _it.next(); !_result.done) {
    console.log(_result.value);
}
*/

console.log("-----------------");



// czy tutaj jest rekursja ogonowa, czy zapełniam stos 
function* fibGen(current = 0, next = 1) {
    yield current;
    yield* fibGen(next, current + next);
}



var _it_2 = fibGen();

for (
    var _result;
    (_result = _it_2.next()), !_result.done, _result.value <= count;

) {
    console.log(_result.value);
}

/*
console.log("-----------------");

for (var i of paramFibIter()) { // po paramFibIter nie da się tak iterować
  console.log(i);
}
*/

console.log("-----------------");

for (var i of fibGen()) {
    if (i <= count) console.log(i);
    // po fibGen da się tak iterować
    else return;
}

