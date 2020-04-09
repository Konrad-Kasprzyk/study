function createParamGenerator(count) {
    return function createGenerator() {
      var _state = 0;
      return {
        next: function() {
          return {
            value: _state,
            done: _state++ >= count
          };
        }
      };
    };
  }
  

  var foo = {
    [Symbol.iterator]: createParamGenerator(10)
  };
  
  var foo1 = {
    [Symbol.iterator]: createParamGenerator(3)
  };
  
  var foo2 = {
    [Symbol.iterator]: createParamGenerator(20)
  };
  
  for (var f of foo) console.log(f);
  console.log("---------------");
  for (var f of foo1) console.log(f);
  console.log("---------------");
  for (var f of foo2) console.log(f);
  