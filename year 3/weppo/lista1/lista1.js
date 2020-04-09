function z1(){
    var list = [];
    var i, is_good, sum;
    for(i=1; i<100000; i++){
        is_good = true;
        num_str = i.toString();
        sum = 0;
        var j, len, digit;
        for(j=0, len = num_str.length; j<len ; j++){
            digit = parseInt(num_str.charAt(j))
            sum += digit;
            if (i % digit != 0)
                is_good = false;
        }
        if (i % sum != 0)
            is_good = false;

        if (is_good)
            list.push(i);
    }

    for(var i=0; i<list.length; i++){
        console.log(list[i]);
    }
}

function z2(){
    var primes = [];
    var is_prime = true;
    var i,j;
    for(i=2; i<100000; i++){
        is_prime = true
        for(j=Math.floor(Math.sqrt(i)); j>1; j--){
            if(i%j == 0)
                is_prime = false;
        }
        if(is_prime)
            primes.push(i);
    }
    
    for(i=0; i<primes.length; i++){
        console.log(primes[i]);
    }
}

function fib_iter(n){
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    var i, fib1= 0, fib2= 1, fib3;
    for(i=1; i<n; i++){
        fib3 = fib1 + fib2;
        fib1 = fib2;
        fib2 = fib3
    }
    return fib3;
}

function fib_rec(n){
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    return fib_rec(n-2) + fib_rec(n-1);   
}

function time_measure(n){
    var i;
    for(i=10; i<=n; i++){
        console.time('fib_rec');
        fib_rec(i);
        console.timeEnd('fib_rec');
        console.time('fib_iter');
        fib_iter(i);
        console.timeEnd('fib_iter');
        console.log("nr: " + i);
    }
}

z1();
z2();
time_measure(40);