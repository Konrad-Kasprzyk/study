function fib(n){
    if (n == 0){
        return 0;
    }
    if (n == 2 || n == 1){
        return 1;
    }
    return fib(n-1) + fib(n-2)
}

mem_fib = ( function memoize(){

    var cache = {};

    function f(n) {
        var value;

        if (n in cache) {
            value = cache[n]
        }else{
            if (n == 0){
                value = 0;
            }
            else if (n == 2 || n == 1){
                value = 1;
            }
            else{
                value = f(n-1) + f(n-2)
            }
        }

        cache[n] = value;
        return value;
    }
    return f;
} )();



console.log(mem_fib(46))

console.log(fib(46))



