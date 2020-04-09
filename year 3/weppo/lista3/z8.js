function fib() {
    var _a = 0;
    var _b = 1;
    var _temp = 0;
    return {
      next: function() {
        _temp = _a;
        _a = _b;
        _b = _temp + _b;
        return {
          value: _b,
          done: false
        };
      }
    };
  }
  
  function* fibGen(current = 0, next = 1) {
    yield current;
    yield* fibGen(next, current + next);
  }
  
  function* take(it, top) {
    let index = 0;
    while (index <= top) {
      yield it.next().value;
      ++index;
    }
  }
  
  var count = 10;
  
  for (let num of take(fib(), count)) {
    console.log(num);
  }
  
  console.log("-----------------");
  
  for (let num of take(fibGen(), count)) {
    console.log(num);
  }
  