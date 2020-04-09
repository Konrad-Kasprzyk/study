function forEach(a,f){
    for (var i = 0; i < a.length; i++){
        f(a[i])
    }
}

function map(a,f){
    for (var i = 0; i < a.length; i++){
        a[i] = f(a[i])
    }
}

function filter(a,f){
    for (var i = 0; i < a.length; i++){
        if(f(a[i]))
            a.splice(i,1);
    }
}

var a = [1,2,3,4];

forEach(a, _ => {console.log( _ )})

map(a, _ => _ *  2)
console.log(a)

filter(a, _ => _ < 3)
console.log(a)


