function sum(...args){
    var sum = 0;
    for(var i = 0; i< args.length; i++)
        sum += args[i]
    return sum
}

console.log(sum(1,2,3,4,5))